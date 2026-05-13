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

#ifndef __HAL_CLOCK_PLATFORM_H__
#define __HAL_CLOCK_PLATFORM_H__

#include "air_chip.h"

#ifdef HAL_CLOCK_MODULE_ENABLED

/*####################################################################################
 * !!! Auto Generated Code Start !!!
 *************************************************************************************/
/*************************************************************************************
 *  RG Module Base Address
 *************************************************************************************/
#if 1 //def AIR_CPU_IN_SECURITY_MODE maybe it's not defined
#define RM_DCXO_CFG_BASE                    0x400C0000 /* 2024-1023, Force All Fields non Align Byte Boundary of RG */
#define RM_TOP_MISC_CFG_BASE                0x42010000 /* 2024-1129, All Fields Align Byte Boundary of RG */
#define RM_CKSYS_BASE                       0x42030000 /* 2024-1209, All Fields Align Byte Boundary of RG */
#define RM_CKSYS_XO_CLK_BASE                0x42040000 /* 2024-0925, All Fields Align Byte Boundary of RG */
#define RM_MIXEDSYS_D_BASE                  0x42050000 /* 2024-1202, All Fields Align Byte Boundary of RG */
#define RM_DCXO_PWR_CTRL_BASE               0x42060000 /* 2024-1001, All Fields Align Byte Boundary of RG */
#define RM_RTC_DIG_MISC_BASE                0x42107000 /* 2024-1021, All Fields Align Byte Boundary of RG */
#define RM_CKSYS_BUS_CLK_BASE               0x422D0000 /* 2024-0925, All Fields Align Byte Boundary of RG */
#else
#define RM_DCXO_CFG_BASE                    0x500C0000
#define RM_TOP_MISC_CFG_BASE                0x52010000
#define RM_CKSYS_BASE                       0x52030000
#define RM_CKSYS_XO_CLK_BASE                0x52040000
#define RM_MIXEDSYS_D_BASE                  0x52050000
#define RM_DCXO_PWR_CTRL_BASE               0x52060000
#define RM_RTC_DIG_MISC_BASE                0x52107000
#define RM_CKSYS_BUS_CLK_BASE               0x522D0000
#endif

/*************************************************************************************
 * DCXO_CFG, 0x400C0000, 2024-1023, Force All RG_Field non Byte Boundary of RG
 * Define struct for non Byte Boundary RG_Field
 *************************************************************************************/
/* DCXO_CFG, 0x400C0000, DCXO_SW_EN, Offset 0x0000 */
typedef union {
    __IO uint32_t value;
    struct {
        __IO uint32_t DCXO_1MDIV_EN                            : 1; /* [ 0: 0], RW, Default 0x1 */
        __IO uint32_t DCXO_LPM_PREBUF_EN                       : 1; /* [ 1: 1], RW, Default 0x1 */
        __IO uint32_t DCXO_CORE_EN                             : 1; /* [ 2: 2], RW, Default 0x1 */
        __IO uint32_t DCXO_PREBUF_EN                           : 1; /* [ 3: 3], RW, Default 0x1 */
        __IO uint32_t DCXO_PREBUFEXT_EN                        : 1; /* [ 4: 4], RW, Default 0x1 */
        __IO uint32_t DCXO_BTRF_BUF_EN                         : 1; /* [ 5: 5], RW, Default 0x1 */
        __IO uint32_t DCXO_DBB_BUF_EN                          : 1; /* [ 6: 6], RW, Default 0x1 */
        __IO uint32_t DCXO_EXT_BUF_EN                          : 1; /* [ 7: 7], RW, Default 0x1 */
        __IO uint32_t DCXO_LPM_LDO_EN                          : 1; /* [ 8: 8], RW, Default 0x1 */
        __IO uint32_t DCXO_EXT_BUF_LDO_EN                      : 1; /* [ 9: 9], RW, Default 0x1 */
        __IO uint32_t DCXO_FPM_LDO_EN                          : 1; /* [10:10], RW, Default 0x1 */
        __IO uint32_t DCXO_FPM_LDO_SW_EN                       : 1; /* [11:11], RW, Default 0x1 */
        __IO uint32_t DCXO_P3_BUF_EN                           : 1; /* [12:12], RW, Default 0x1 */
        __IO uint32_t DCXO_P2_BUF_EN                           : 1; /* [13:13], RW, Default 0x1 */
        __IO uint32_t DCXO_LDO_VREF_EN                         : 1; /* [14:14], RW, Default 0x1 */
        __IO uint32_t UNUSED_31_15                             :17; /* [31:15] */
    } field;
} T_DCXO_SW_EN;

/* DCXO_CFG, 0x400C0000, DCXO_CTUNE_FPM, Offset 0x0004 */
typedef union {
    __IO uint32_t value;
    struct {
        __IO uint32_t DCXO_CDAC                                : 9; /* [ 8: 0], RW, Default 0x086 */
        __IO uint32_t UNUSED_31_9                              :23; /* [31: 9] */
    } field;
} T_DCXO_CTUNE_FPM;

/* DCXO_CFG, 0x400C0000, DCXO_CTUNE_LPM, Offset 0x0008 */
typedef union {
    __IO uint32_t value;
    struct {
        __IO uint32_t DCXO_CDAC_LPM                            : 9; /* [ 8: 0], RW, Default 0x000 */
        __IO uint32_t UNUSED_31_9                              :23; /* [31: 9] */
    } field;
} T_DCXO_CTUNE_LPM;

/* DCXO_CFG, 0x400C0000, DCXO_REV, Offset 0x000C */
typedef union {
    __IO uint32_t value;
    struct {
        __IO uint32_t RG_DCXO_REV                              : 9; /* [ 8: 0], RW, Default 0x000 */
        __IO uint32_t UNUSED_31_9                              :23; /* [31: 9] */
    } field;
} T_DCXO_REV;

/* DCXO_CFG, 0x400C0000, DCXO_CTUNE_STEP, Offset 0x0010 */
typedef union {
    __IO uint32_t value;
    struct {
        __IO uint32_t DCXO_CTUNE_LPM_FPM_STEP                  : 2; /* [ 1: 0], RW, Default 0x0 */
        __IO uint32_t UNUSED_3_2                               : 2; /* [ 3: 2] */
        __IO uint32_t FPM32_LPM32_STEP_SEL                     : 1; /* [ 4: 4], RW, Default 0x0 */
        __IO uint32_t UNUSED_7_5                               : 3; /* [ 7: 5] */
        __IO uint32_t RG_CDAC_CONSERVATIVE_STEP_SIZE           : 2; /* [ 9: 8], RW, Default 0x0 */
        __IO uint32_t UNUSED_31_10                             :22; /* [31:10] */
    } field;
} T_DCXO_CTUNE_STEP;

/* DCXO_CFG, 0x400C0000, DCXO_CORE_ISEL, Offset 0x0014 */
typedef union {
    __IO uint32_t value;
    struct {
        __IO uint32_t DCXO_CORE_ISEL                           : 4; /* [ 3: 0], RW, Default 0xA */
        __IO uint32_t UNUSED_31_4                              :28; /* [31: 4] */
    } field;
} T_DCXO_CORE_ISEL;

/* DCXO_CFG, 0x400C0000, DCXO_CORE_ISEL_LPM, Offset 0x0018 */
typedef union {
    __IO uint32_t value;
    struct {
        __IO uint32_t UNUSED_7_0                               : 8; /* [ 7: 0] */
        __IO uint32_t DCXO_CORE_ISEL_LPM                       : 4; /* [11: 8], RW, Default 0x8 */
        __IO uint32_t UNUSED_31_12                             :20; /* [31:12] */
    } field;
} T_DCXO_CORE_ISEL_LPM;

/* DCXO_CFG, 0x400C0000, BGCORE_CTRL0, Offset 0x001C */
typedef union {
    __IO uint32_t value;
    struct {
        __IO uint32_t UNUSED_0_0                               : 1; /* [ 0: 0] */
        __IO uint32_t BG_FC_OFF_BT                             : 1; /* [ 1: 1], RW, Default 0x1 */
        __IO uint32_t IPP1P75UA_DCXO_EN                        : 1; /* [ 2: 2], RW, Default 0x1 */
        __IO uint32_t BG_EN                                    : 1; /* [ 3: 3], RW, Default 0x1 */
        __IO uint32_t UNUSED_12_4                              : 9; /* [12: 4] */
        __IO uint32_t IPP10P5UA_VREF_DCXO_EN                   : 1; /* [13:13], RW, Default 0x1 */
        __IO uint32_t UNUSED_31_14                             :18; /* [31:14] */
    } field;
} T_BGCORE_CTRL0;

/* DCXO_CFG, 0x400C0000, BGCORE_CTRL1, Offset 0x0020 */
typedef union {
    __IO uint32_t value;
    struct {
        __IO uint32_t VREF_SEL_TRANSITION                      : 5; /* [ 4: 0], RW, Default 0x0F */
        __IO uint32_t UNUSED_7_5                               : 3; /* [ 7: 5] */
        __IO uint32_t VREF_SEL                                 : 5; /* [12: 8], RW, Default 0x0F */
        __IO uint32_t UNUSED_31_13                             :19; /* [31:13] */
    } field;
} T_BGCORE_CTRL1;

/* DCXO_CFG, 0x400C0000, RFLDO_CTRL0, Offset 0x0090 */
typedef union {
    __IO uint32_t value;
    struct {
        __IO uint32_t RFLDO_EN                                 : 1; /* [ 0: 0], RW, Default 0x1 */
        __IO uint32_t RFLDOFC_OFF                              : 1; /* [ 1: 1], RW, Default 0x1 */
        __IO uint32_t RFLDO_STARTUP_EN                         : 1; /* [ 2: 2], RW, Default 0x1 */
        __IO uint32_t RFLDO_SOFTSTART_EN                       : 1; /* [ 3: 3], RW, Default 0x0 */
        __IO uint32_t IPP1P75UA_RFLDO_EN                       : 1; /* [ 4: 4], RW, Default 0x1 */
        __IO uint32_t RFLDO_BYPASS_EN                          : 1; /* [ 5: 5], RW, Default 0x1 */
        __IO uint32_t DCXO_LDO_BYPASS_EN                       : 1; /* [ 6: 6], RW, Default 0x1 */
        __IO uint32_t UNUSED_31_7                              :25; /* [31: 7] */
    } field;
} T_RFLDO_CTRL0;

/* DCXO_CFG, 0x400C0000, DCXO_CK_RDY, Offset 0x0024 */
typedef union {
    __IO uint32_t value;
    struct {
        __IO uint32_t RG_DCXO_CK_RDY_COMP_VREF                 : 4; /* [ 3: 0], RW, Default 0x3 */
        __IO uint32_t UNUSED_31_4                              :28; /* [31: 4] */
    } field;
} T_DCXO_CK_RDY;

/* DCXO_CFG, 0x400C0000, DCXO_LDO_VOUT0, Offset 0x0028 */
typedef union {
    __IO uint32_t value;
    struct {
        __IO uint32_t RG_DCXO_EXT_BUF_LDO_VOUT                 : 3; /* [ 2: 0], RW, Default 0x0 */
        __IO uint32_t UNUSED_3_3                               : 1; /* [ 3: 3] */
        __IO uint32_t DCXO_FPM_LDO_VOUT_LPM                    : 3; /* [ 6: 4], RW, Default 0x5 */
        __IO uint32_t UNUSED_7_7                               : 1; /* [ 7: 7] */
        __IO uint32_t DCXO_FPM_LDO_VOUT                        : 3; /* [10: 8], RW, Default 0x7 */
        __IO uint32_t UNUSED_31_11                             :21; /* [31:11] */
    } field;
} T_DCXO_LDO_VOUT0;

/* DCXO_CFG, 0x400C0000, DCXO_LDO_VOUT1, Offset 0x002C */
typedef union {
    __IO uint32_t value;
    struct {
        __IO uint32_t DCXO_LPM_LDO_VOUT                        : 3; /* [ 2: 0], RW, Default 0x3 */
        __IO uint32_t UNUSED_3_3                               : 1; /* [ 3: 3] */
        __IO uint32_t DCXO_LPM_LDO_VOUT_F2L                    : 3; /* [ 6: 4], RW, Default 0x4 */
        __IO uint32_t UNUSED_7_7                               : 1; /* [ 7: 7] */
        __IO uint32_t DCXO_LPM_LDO_VOUT_L2F                    : 3; /* [10: 8], RW, Default 0x2 */
        __IO uint32_t UNUSED_31_11                             :21; /* [31:11] */
    } field;
} T_DCXO_LDO_VOUT1;

/* DCXO_CFG, 0x400C0000, DCXO_SOR, Offset 0x0038 */
typedef union {
    __IO uint32_t value;
    struct {
        __IO uint32_t SOR_DCXOSYS                              : 1; /* [ 0: 0], RW, Default 0x1 */
        __IO uint32_t UNUSED_31_1                              :31; /* [31: 1] */
    } field;
} T_DCXO_SOR;

/* DCXO_CFG, 0x400C0000, DCXO_RG0, Offset 0x003C */
typedef union {
    __IO uint32_t value;
    struct {
        __IO uint32_t RG_DCXO_1MDIV_TEST_EN                    : 1; /* [ 0: 0], RW, Default 0x0 */
        __IO uint32_t UNUSED_1_1                               : 1; /* [ 1: 1] */
        __IO uint32_t RG_DCXO_BTRF_DIFF_EN                     : 1; /* [ 2: 2], RW, Default 0x1 */
        __IO uint32_t RG_DCXO_DBB_DIFF_EN                      : 1; /* [ 3: 3], RW, Default 0x1 */
        __IO uint32_t RG_DCXO_EXT_BUF_LDR2                     : 1; /* [ 4: 4], RW, Default 0x0 */
        __IO uint32_t RG_DCXO_EXT_BUF_HDR                      : 1; /* [ 5: 5], RW, Default 0x1 */
        __IO uint32_t RG_DCXO_EXT_BUF_LDR                      : 1; /* [ 6: 6], RW, Default 0x0 */
        __IO uint32_t UNUSED_8_7                               : 2; /* [ 8: 7] */
        __IO uint32_t DCXO_IBOOST_MAN_EN                       : 1; /* [ 9: 9], RW, Default 0x0 */
        __IO uint32_t RG_DCXO_FPM_LDO_BIAS_SEL                 : 1; /* [10:10], RW, Default 0x0 */
        __IO uint32_t UNUSED_31_11                             :21; /* [31:11] */
    } field;
} T_DCXO_RG0;

/* DCXO_CFG, 0x400C0000, DCXO_RG1, Offset 0x0040 */
typedef union {
    __IO uint32_t value;
    struct {
        __IO uint32_t RG_DCXO_DBB_I                            : 2; /* [ 1: 0], RW, Default 0x2 */
        __IO uint32_t UNUSED_7_2                               : 6; /* [ 7: 2] */
        __IO uint32_t RG_DCXO_BTRF_32M_I                       : 2; /* [ 9: 8], RW, Default 0x2 */
        __IO uint32_t UNUSED_10_10                             : 1; /* [10:10] */
        __IO uint32_t RG_DCXO_PREBUF_RES_SEL                   : 1; /* [11:11], RW, Default 0x0 */
        __IO uint32_t DCXO_PREBUF_LPM_I                        : 2; /* [13:12], RW, Default 0x0 */
        __IO uint32_t DCXO_PREBUF_I                            : 2; /* [15:14], RW, Default 0x2 */
        __IO uint32_t UNUSED_31_16                             :16; /* [31:16] */
    } field;
} T_DCXO_RG1;

/* DCXO_CFG, 0x400C0000, DCXO_RG2, Offset 0x0094 */
typedef union {
    __IO uint32_t value;
    struct {
        __IO uint32_t RG_DCXO_REFDBL_VSUPR_SEL                 : 1; /* [ 0: 0], RW, Default 0x0 */
        __IO uint32_t RG_DCXO_DBB_64M_EN                       : 1; /* [ 1: 1], RW, Default 0x0 */
        __IO uint32_t RG_DCXO_P3_32M_I                         : 2; /* [ 3: 2], RW, Default 0x2 */
        __IO uint32_t RG_DCXO_P2_32M_I                         : 2; /* [ 5: 4], RW, Default 0x2 */
        __IO uint32_t RG_DCXO_64M_DBB_I                        : 2; /* [ 7: 6], RW, Default 0x2 */
        __IO uint32_t UNUSED_31_8                              :24; /* [31: 8] */
    } field;
} T_DCXO_RG2;

/* DCXO_CFG, 0x400C0000, DCXO_RG3, Offset 0x0098 */
typedef union {
    __IO uint32_t value;
    struct {
        __IO uint32_t RG_RX_BYPASS_EN                          : 1; /* [ 0: 0], RW, Default 0x0 */
        __IO uint32_t UNUSED_7_1                               : 7; /* [ 7: 1] */
        __IO uint32_t RG_RFLDO_VSEL                            : 3; /* [10: 8], RW, Default 0x2 */
        __IO uint32_t UNUSED_31_11                             :21; /* [31:11] */
    } field;
} T_DCXO_RG3;

/* DCXO_CFG, 0x400C0000, DCXO_RG4, Offset 0x009C */
typedef union {
    __IO uint32_t value;
    struct {
        __IO uint32_t RG_DCXO2RF_RSV                           : 8; /* [ 7: 0], RW, Default 0x00 */
        __IO uint32_t UNUSED_31_8                              :24; /* [31: 8] */
    } field;
} T_DCXO_RG4;

/* DCXO_CFG, 0x400C0000, DCXO_RG5, Offset 0x0100 */
typedef union {
    __IO uint32_t value;
    struct {
        __IO uint32_t RG_DCXO_DBL_RSV                          :15; /* [14: 0], RW, Default 0x0001 */
        __IO uint32_t UNUSED_31_15                             :17; /* [31:15] */
    } field;
} T_DCXO_RG5;

/* DCXO_CFG, 0x400C0000, DCXO_MONV_SEL, Offset 0x0044 */
typedef union {
    __IO uint32_t value;
    struct {
        __IO uint32_t RG_DCXO_MONV_SEL                         :12; /* [11: 0], RW, Default 0x000 */
        __IO uint32_t UNUSED_31_12                             :20; /* [31:12] */
    } field;
} T_DCXO_MONV_SEL;

/* DCXO_CFG, 0x400C0000, DCXO_SEG0, Offset 0x0048 */
typedef union {
    __IO uint32_t value;
    struct {
        __IO uint32_t SEG2                                     : 5; /* [ 4: 0], RW, Default 0x00 */
        __IO uint32_t UNUSED_7_5                               : 3; /* [ 7: 5] */
        __IO uint32_t SEG1                                     : 5; /* [12: 8], RW, Default 0x00 */
        __IO uint32_t UNUSED_31_13                             :19; /* [31:13] */
    } field;
} T_DCXO_SEG0;

/* DCXO_CFG, 0x400C0000, DCXO_SEG1, Offset 0x004C */
typedef union {
    __IO uint32_t value;
    struct {
        __IO uint32_t SEG4                                     : 5; /* [ 4: 0], RW, Default 0x00 */
        __IO uint32_t UNUSED_7_5                               : 3; /* [ 7: 5] */
        __IO uint32_t SEG3                                     : 5; /* [12: 8], RW, Default 0x00 */
        __IO uint32_t UNUSED_31_13                             :19; /* [31:13] */
    } field;
} T_DCXO_SEG1;

/* DCXO_CFG, 0x400C0000, DCXO_SEG2, Offset 0x0050 */
typedef union {
    __IO uint32_t value;
    struct {
        __IO uint32_t SEG6                                     : 5; /* [ 4: 0], RW, Default 0x01 */
        __IO uint32_t UNUSED_7_5                               : 3; /* [ 7: 5] */
        __IO uint32_t SEG5                                     : 5; /* [12: 8], RW, Default 0x00 */
        __IO uint32_t UNUSED_31_13                             :19; /* [31:13] */
    } field;
} T_DCXO_SEG2;

/* DCXO_CFG, 0x400C0000, DCXO_SEG3, Offset 0x0054 */
typedef union {
    __IO uint32_t value;
    struct {
        __IO uint32_t SEG8                                     : 5; /* [ 4: 0], RW, Default 0x03 */
        __IO uint32_t UNUSED_7_5                               : 3; /* [ 7: 5] */
        __IO uint32_t SEG7                                     : 5; /* [12: 8], RW, Default 0x02 */
        __IO uint32_t UNUSED_31_13                             :19; /* [31:13] */
    } field;
} T_DCXO_SEG3;

/* DCXO_CFG, 0x400C0000, DCXO_SEG4, Offset 0x0058 */
typedef union {
    __IO uint32_t value;
    struct {
        __IO uint32_t SEG10                                    : 5; /* [ 4: 0], RW, Default 0x05 */
        __IO uint32_t UNUSED_7_5                               : 3; /* [ 7: 5] */
        __IO uint32_t SEG9                                     : 5; /* [12: 8], RW, Default 0x04 */
        __IO uint32_t UNUSED_31_13                             :19; /* [31:13] */
    } field;
} T_DCXO_SEG4;

/* DCXO_CFG, 0x400C0000, DCXO_SEG5, Offset 0x005C */
typedef union {
    __IO uint32_t value;
    struct {
        __IO uint32_t SEG12                                    : 5; /* [ 4: 0], RW, Default 0x07 */
        __IO uint32_t UNUSED_7_5                               : 3; /* [ 7: 5] */
        __IO uint32_t SEG11                                    : 5; /* [12: 8], RW, Default 0x06 */
        __IO uint32_t UNUSED_31_13                             :19; /* [31:13] */
    } field;
} T_DCXO_SEG5;

/* DCXO_CFG, 0x400C0000, DCXO_SEG6, Offset 0x0060 */
typedef union {
    __IO uint32_t value;
    struct {
        __IO uint32_t SEG14                                    : 5; /* [ 4: 0], RW, Default 0x09 */
        __IO uint32_t UNUSED_7_5                               : 3; /* [ 7: 5] */
        __IO uint32_t SEG13                                    : 5; /* [12: 8], RW, Default 0x08 */
        __IO uint32_t UNUSED_31_13                             :19; /* [31:13] */
    } field;
} T_DCXO_SEG6;

/* DCXO_CFG, 0x400C0000, DCXO_CFG1, Offset 0x0064 */
typedef union {
    __IO uint32_t value;
    struct {
        __IO uint32_t DCXO_STRICT_OUT                          : 1; /* [ 0: 0], RW, Default 0x0 */
        __IO uint32_t UNUSED_7_1                               : 7; /* [ 7: 1] */
        __IO uint32_t PWR_AWARE_DIS                            : 1; /* [ 8: 8], RW, Default 0x0 */
        __IO uint32_t UNUSED_31_9                              :23; /* [31: 9] */
    } field;
} T_DCXO_CFG1;

/* DCXO_CFG, 0x400C0000, DCXO_MAN_EN, Offset 0x0068 */
typedef union {
    __IO uint32_t value;
    struct {
        __IO uint32_t DCXO_PO_IN_MAN                           : 1; /* [ 0: 0], RW, Default 0x1 */
        __IO uint32_t UNUSED_7_1                               : 7; /* [ 7: 1] */
        __IO uint32_t DCXO_PO_MAN                              : 1; /* [ 8: 8], RW, Default 0x1 */
        __IO uint32_t UNUSED_31_9                              :23; /* [31: 9] */
    } field;
} T_DCXO_MAN_EN;

/* DCXO_CFG, 0x400C0000, DCXO_MAN0, Offset 0x006C */
typedef union {
    __IO uint32_t value;
    struct {
        __IO uint32_t DCXO_CORE_MAN_EN                         : 1; /* [ 0: 0], RW, Default 0x0 */
        __IO uint32_t DCXO_PREBUF_MAN_EN                       : 1; /* [ 1: 1], RW, Default 0x0 */
        __IO uint32_t DCXO_PREBUFEXT_MAN_EN                    : 1; /* [ 2: 2], RW, Default 0x0 */
        __IO uint32_t DCXO_BTRF_BUF_MAN_EN                     : 1; /* [ 3: 3], RW, Default 0x0 */
        __IO uint32_t DCXO_DBB_BUF_MAN_EN                      : 1; /* [ 4: 4], RW, Default 0x0 */
        __IO uint32_t DCXO_EXT_BUF_MAN_EN                      : 1; /* [ 5: 5], RW, Default 0x0 */
        __IO uint32_t DCXO_LPM_LDO_MAN_EN                      : 1; /* [ 6: 6], RW, Default 0x0 */
        __IO uint32_t DCXO_EXT_BUF_LDO_MAN_EN                  : 1; /* [ 7: 7], RW, Default 0x0 */
        __IO uint32_t UNUSED_8_8                               : 1; /* [ 8: 8] */
        __IO uint32_t DCXO_FPM_LDO_MAN_EN                      : 1; /* [ 9: 9], RW, Default 0x0 */
        __IO uint32_t DCXO_FPM_LDO_SW_EN_MAN                   : 1; /* [10:10], RW, Default 0x0 */
        __IO uint32_t RG_DCXO_FPM_LDO_OFF_PULLDOWN_MAN_EN      : 1; /* [11:11], RW, Default 0x0 */
        __IO uint32_t DCXO_P3_BUF_MAN_EN                       : 1; /* [12:12], RW, Default 0x0 */
        __IO uint32_t DCXO_P2_BUF_MAN_EN                       : 1; /* [13:13], RW, Default 0x0 */
        __IO uint32_t UNUSED_14_14                             : 1; /* [14:14] */
        __IO uint32_t DCXO_LDO_VREF_EN_MAN                     : 1; /* [15:15], RW, Default 0x0 */
        __IO uint32_t UNUSED_31_16                             :16; /* [31:16] */
    } field;
} T_DCXO_MAN0;

/* DCXO_CFG, 0x400C0000, DCXO_MAN1, Offset 0x0070 */
typedef union {
    __IO uint32_t value;
    struct {
        __IO uint32_t DCXO_DELAY_MAN                           : 1; /* [ 0: 0], RW, Default 0x0 */
        __IO uint32_t EN_EXT1_MAN                              : 1; /* [ 1: 1], RW, Default 0x0 */
        __IO uint32_t BT_32M_EN_MAN                            : 1; /* [ 2: 2], RW, Default 0x0 */
        __IO uint32_t EN_BB_MAN                                : 1; /* [ 3: 3], RW, Default 0x0 */
        __IO uint32_t RG_DCXO1M_EN_MAN                         : 1; /* [ 4: 4], RW, Default 0x0 */
        __IO uint32_t EN_32MHZ_FPM_MAN                         : 1; /* [ 5: 5], RW, Default 0x0 */
        __IO uint32_t ABB_32M_EN_MAN                           : 1; /* [ 6: 6], RW, Default 0x0 */
        __IO uint32_t DBL_64M_EN_MAN                           : 1; /* [ 7: 7], RW, Default 0x0 */
        __IO uint32_t USB_32M_EN_MAN                           : 1; /* [ 8: 8], RW, Default 0x0 */
        __IO uint32_t EN_BG_MAN                                : 1; /* [ 9: 9], RW, Default 0x0 */
        __IO uint32_t EN_RFLDO_MAN                             : 1; /* [10:10], RW, Default 0x0 */
        __IO uint32_t UNUSED_31_11                             :21; /* [31:11] */
    } field;
} T_DCXO_MAN1;

/* DCXO_CFG, 0x400C0000, DCXO_MAN2, Offset 0x0074 */
typedef union {
    __IO uint32_t value;
    struct {
        __IO uint32_t DCXO_PREBUF_I_MAN                        : 2; /* [ 1: 0], RW, Default 0x2 */
        __IO uint32_t UNUSED_3_2                               : 2; /* [ 3: 2] */
        __IO uint32_t DCXO_LPM_LDO_VOUT_MAN                    : 3; /* [ 6: 4], RW, Default 0x0 */
        __IO uint32_t UNUSED_7_7                               : 1; /* [ 7: 7] */
        __IO uint32_t DCXO_CORE_ISEL_MAN                       : 4; /* [11: 8], RW, Default 0xF */
        __IO uint32_t DCXO_FPM_LDO_VOUT_MAN                    : 3; /* [14:12], RW, Default 0x0 */
        __IO uint32_t UNUSED_31_15                             :17; /* [31:15] */
    } field;
} T_DCXO_MAN2;

/* DCXO_CFG, 0x400C0000, DCXO_MAN4, Offset 0x007C */
typedef union {
    __IO uint32_t value;
    struct {
        __IO uint32_t DCXO_CDAC_MAN                            : 9; /* [ 8: 0], RW, Default 0x086 */
        __IO uint32_t DCXO_1MDIV_EN_MAN                        : 1; /* [ 9: 9], RW, Default 0x0 */
        __IO uint32_t DCXO_PD_EN_MAN                           : 1; /* [10:10], RW, Default 0x0 */
        __IO uint32_t DCXO_COMP_EN_MAN                         : 1; /* [11:11], RW, Default 0x0 */
        __IO uint32_t DCXO_CK_RDY_COMP_VREF_MAN                : 4; /* [15:12], RW, Default 0x0 */
        __IO uint32_t UNUSED_31_16                             :16; /* [31:16] */
    } field;
} T_DCXO_MAN4;

/* DCXO_CFG, 0x400C0000, DCXO_MAN5, Offset 0x0080 */
typedef union {
    __IO uint32_t value;
    struct {
        __IO uint32_t BG_FC_OFF_BT_MAN                         : 1; /* [ 0: 0], RW, Default 0x0 */
        __IO uint32_t IPP1P75UA_DCXO_EN_MAN                    : 1; /* [ 1: 1], RW, Default 0x0 */
        __IO uint32_t BG_EN_MAN                                : 1; /* [ 2: 2], RW, Default 0x0 */
        __IO uint32_t UNUSED_7_3                               : 5; /* [ 7: 3] */
        __IO uint32_t VREF_SEL_MAN                             : 5; /* [12: 8], RW, Default 0x0F */
        __IO uint32_t IPP10P5UA_VREF_DCXO_EN_MAN               : 1; /* [13:13], RW, Default 0x0 */
        __IO uint32_t UNUSED_31_14                             :18; /* [31:14] */
    } field;
} T_DCXO_MAN5;

/* DCXO_CFG, 0x400C0000, DCXO_MAN6, Offset 0x0104 */
typedef union {
    __IO uint32_t value;
    struct {
        __IO uint32_t RFLDO_EN_MAN                             : 1; /* [ 0: 0], RW, Default 0x0 */
        __IO uint32_t RFLDOFC_OFF_MAN                          : 1; /* [ 1: 1], RW, Default 0x0 */
        __IO uint32_t RFLDO_STARTUP_EN_MAN                     : 1; /* [ 2: 2], RW, Default 0x0 */
        __IO uint32_t RFLDO_SOFTSTART_EN_MAN                   : 1; /* [ 3: 3], RW, Default 0x0 */
        __IO uint32_t IPP1P75UA_RFLDO_EN_MAN                   : 1; /* [ 4: 4], RW, Default 0x0 */
        __IO uint32_t RFLDO_SOFT_START_EN_MAN                  : 1; /* [ 5: 5], RW, Default 0x0 */
        __IO uint32_t RFLDO_BYPASS_EN_MAN                      : 1; /* [ 6: 6], RW, Default 0x0 */
        __IO uint32_t DCXO_LDO_BYPASS_EN_MAN                   : 1; /* [ 7: 7], RW, Default 0x0 */
        __IO uint32_t DCXO_LDO_VREF_SEL_MAN                    : 4; /* [11: 8], RW, Default 0x0 */
        __IO uint32_t RFLDO_SOFTSTART_SEL_MAN                  : 2; /* [13:12], RW, Default 0x0 */
        __IO uint32_t UNUSED_31_14                             :18; /* [31:14] */
    } field;
} T_DCXO_MAN6;

/* DCXO_CFG, 0x400C0000, DCXO_AUX_SEL, Offset 0x0084 */
typedef union {
    __IO uint32_t value;
    struct {
        __IO uint32_t DCXO_DEBUG_SEL                           : 6; /* [ 5: 0], RW, Default 0x00 */
        __IO uint32_t DCXO_DEBUG_EN                            : 1; /* [ 6: 6], RW, Default 0x0 */
        __IO uint32_t UNUSED_7_7                               : 1; /* [ 7: 7] */
        __IO uint32_t DCXO_AUX_SEL                             : 5; /* [12: 8], RW, Default 0x00 */
        __IO uint32_t UNUSED_31_13                             :19; /* [31:13] */
    } field;
} T_DCXO_AUX_SEL;

/* DCXO_CFG, 0x400C0000, DCXO_AUX_OUT0, Offset 0x0088 */
typedef union {
    __IO uint32_t value;
    struct {
        __I  uint32_t DCXO_AUX_OUT0                            :16; /* [15: 0], RO, Default 0x0000 */
        __IO uint32_t UNUSED_31_16                             :16; /* [31:16] */
    } field;
} T_DCXO_AUX_OUT0;

/* DCXO_CFG, 0x400C0000, DCXO_AUX_OUT1, Offset 0x008C */
typedef union {
    __IO uint32_t value;
    struct {
        __I  uint32_t DCXO_AUX_OUT1                            : 4; /* [ 3: 0], RO, Default 0x0 */
        __IO uint32_t UNUSED_31_4                              :28; /* [31: 4] */
    } field;
} T_DCXO_AUX_OUT1;

/* DCXO_CFG, 0x400C0000, DCXO_MAN_SEL0, Offset 0x0108 */
typedef union {
    __IO uint32_t value;
    struct {
        __IO uint32_t DCXO_CORE_MAN_EN_SEL                     : 1; /* [ 0: 0], RW, Default 0x1 */
        __IO uint32_t DCXO_PREBUF_MAN_EN_SEL                   : 1; /* [ 1: 1], RW, Default 0x1 */
        __IO uint32_t DCXO_PREBUFEXT_MAN_EN_SEL                : 1; /* [ 2: 2], RW, Default 0x1 */
        __IO uint32_t DCXO_BTRF_BUF_MAN_EN_SEL                 : 1; /* [ 3: 3], RW, Default 0x1 */
        __IO uint32_t DCXO_DBB_BUF_MAN_EN_SEL                  : 1; /* [ 4: 4], RW, Default 0x1 */
        __IO uint32_t DCXO_EXT_BUF_MAN_EN_SEL                  : 1; /* [ 5: 5], RW, Default 0x1 */
        __IO uint32_t DCXO_LPM_LDO_MAN_EN_SEL                  : 1; /* [ 6: 6], RW, Default 0x1 */
        __IO uint32_t DCXO_EXT_BUF_LDO_MAN_EN_SEL              : 1; /* [ 7: 7], RW, Default 0x1 */
        __IO uint32_t UNUSED_8_8                               : 1; /* [ 8: 8] */
        __IO uint32_t DCXO_FPM_LDO_MAN_EN_SEL                  : 1; /* [ 9: 9], RW, Default 0x1 */
        __IO uint32_t DCXO_FPM_LDO_SW_EN_MAN_SEL               : 1; /* [10:10], RW, Default 0x1 */
        __IO uint32_t DCXO_FPM_LDO_OFF_PULLDOWN_MAN_SEL        : 1; /* [11:11], RW, Default 0x1 */
        __IO uint32_t DCXO_P3_BUF_MAN_EN_SEL                   : 1; /* [12:12], RW, Default 0x1 */
        __IO uint32_t DCXO_P2_BUF_MAN_EN_SEL                   : 1; /* [13:13], RW, Default 0x1 */
        __IO uint32_t DCXO_IBOOST_EN_MAN_SEL                   : 1; /* [14:14], RW, Default 0x1 */
        __IO uint32_t DCXO_LDO_VREF_EN_MAN_SEL                 : 1; /* [15:15], RW, Default 0x1 */
        __IO uint32_t UNUSED_31_16                             :16; /* [31:16] */
    } field;
} T_DCXO_MAN_SEL0;

/* DCXO_CFG, 0x400C0000, DCXO_MAN_SEL1, Offset 0x010C */
typedef union {
    __IO uint32_t value;
    struct {
        __IO uint32_t DCXO_DELAY_MAN_SEL                       : 1; /* [ 0: 0], RW, Default 0x1 */
        __IO uint32_t EN_EXT1_MAN_SEL                          : 1; /* [ 1: 1], RW, Default 0x1 */
        __IO uint32_t BT_32M_EN_MAN_SEL                        : 1; /* [ 2: 2], RW, Default 0x1 */
        __IO uint32_t EN_BB_MAN_SEL                            : 1; /* [ 3: 3], RW, Default 0x1 */
        __IO uint32_t RG_DCXO1M_EN_MAN_SEL                     : 1; /* [ 4: 4], RW, Default 0x1 */
        __IO uint32_t EN_32MHZ_FPM_MAN_SEL                     : 1; /* [ 5: 5], RW, Default 0x1 */
        __IO uint32_t ABB_32M_EN_MAN_SEL                       : 1; /* [ 6: 6], RW, Default 0x1 */
        __IO uint32_t DBL_64M_EN_MAN_SEL                       : 1; /* [ 7: 7], RW, Default 0x1 */
        __IO uint32_t USB_32M_EN_MAN_SEL                       : 1; /* [ 8: 8], RW, Default 0x1 */
        __IO uint32_t EN_BG_MAN_SEL                            : 1; /* [ 9: 9], RW, Default 0x1 */
        __IO uint32_t EN_RFLDO_MAN_SEL                         : 1; /* [10:10], RW, Default 0x1 */
        __IO uint32_t UNUSED_31_11                             :21; /* [31:11] */
    } field;
} T_DCXO_MAN_SEL1;

/* DCXO_CFG, 0x400C0000, DCXO_MAN_SEL2, Offset 0x0110 */
typedef union {
    __IO uint32_t value;
    struct {
        __IO uint32_t DCXO_PREBUF_I_MAN_SEL                    : 1; /* [ 0: 0], RW, Default 0x1 */
        __IO uint32_t UNUSED_3_1                               : 3; /* [ 3: 1] */
        __IO uint32_t DCXO_LPM_LDO_VOUT_MAN_SEL                : 1; /* [ 4: 4], RW, Default 0x1 */
        __IO uint32_t UNUSED_7_5                               : 3; /* [ 7: 5] */
        __IO uint32_t DCXO_CORE_ISEL_MAN_SEL                   : 1; /* [ 8: 8], RW, Default 0x1 */
        __IO uint32_t UNUSED_11_9                              : 3; /* [11: 9] */
        __IO uint32_t DCXO_FPM_LDO_VOUT_MAN_SEL                : 1; /* [12:12], RW, Default 0x1 */
        __IO uint32_t UNUSED_31_13                             :19; /* [31:13] */
    } field;
} T_DCXO_MAN_SEL2;

/* DCXO_CFG, 0x400C0000, DCXO_MAN_SEL4, Offset 0x0114 */
typedef union {
    __IO uint32_t value;
    struct {
        __IO uint32_t DCXO_CDAC_MAN_SEL                        : 1; /* [ 0: 0], RW, Default 0x1 */
        __IO uint32_t UNUSED_8_1                               : 8; /* [ 8: 1] */
        __IO uint32_t DCXO_1MDIV_EN_MAN_SEL                    : 1; /* [ 9: 9], RW, Default 0x1 */
        __IO uint32_t DCXO_PD_EN_MAN_SEL                       : 1; /* [10:10], RW, Default 0x1 */
        __IO uint32_t DCXO_COMP_EN_MAN_SEL                     : 1; /* [11:11], RW, Default 0x1 */
        __IO uint32_t DCXO_CK_RDY_COMP_VREF_MAN_SEL            : 1; /* [12:12], RW, Default 0x1 */
        __IO uint32_t UNUSED_31_13                             :19; /* [31:13] */
    } field;
} T_DCXO_MAN_SEL4;

/* DCXO_CFG, 0x400C0000, DCXO_MAN_SEL5, Offset 0x0118 */
typedef union {
    __IO uint32_t value;
    struct {
        __IO uint32_t BG_FC_OFF_BT_MAN_SEL                     : 1; /* [ 0: 0], RW, Default 0x1 */
        __IO uint32_t IPP1P75UA_DCXO_EN_MAN_SEL                : 1; /* [ 1: 1], RW, Default 0x1 */
        __IO uint32_t BG_EN_MAN_SEL                            : 1; /* [ 2: 2], RW, Default 0x1 */
        __IO uint32_t UNUSED_7_3                               : 5; /* [ 7: 3] */
        __IO uint32_t VREF_SEL_MAN_SEL                         : 1; /* [ 8: 8], RW, Default 0x1 */
        __IO uint32_t UNUSED_12_9                              : 4; /* [12: 9] */
        __IO uint32_t IPP10P5UA_VREF_DCXO_EN_MAN_SEL           : 1; /* [13:13], RW, Default 0x1 */
        __IO uint32_t UNUSED_31_14                             :18; /* [31:14] */
    } field;
} T_DCXO_MAN_SEL5;

/* DCXO_CFG, 0x400C0000, DCXO_MAN_SEL6, Offset 0x011C */
typedef union {
    __IO uint32_t value;
    struct {
        __IO uint32_t RFLDO_EN_MAN_SEL                         : 1; /* [ 0: 0], RW, Default 0x1 */
        __IO uint32_t RFLDOFC_OFF_MAN_SEL                      : 1; /* [ 1: 1], RW, Default 0x1 */
        __IO uint32_t RFLDO_STARTUP_EN_MAN_SEL                 : 1; /* [ 2: 2], RW, Default 0x1 */
        __IO uint32_t RFLDO_SOFTSTART_EN_MAN_SEL               : 1; /* [ 3: 3], RW, Default 0x1 */
        __IO uint32_t IPP1P75UA_RFLDO_EN_MAN_SEL               : 1; /* [ 4: 4], RW, Default 0x1 */
        __IO uint32_t RFLDO_SOFT_START_EN_MAN_SEL              : 1; /* [ 5: 5], RW, Default 0x1 */
        __IO uint32_t RFLDO_BYPASS_EN_MAN_SEL                  : 1; /* [ 6: 6], RW, Default 0x1 */
        __IO uint32_t DCXO_LDO_BYPASS_EN_MAN_SEL               : 1; /* [ 7: 7], RW, Default 0x1 */
        __IO uint32_t DCXO_LDO_VREF_SEL_MAN_SEL                : 1; /* [ 8: 8], RW, Default 0x1 */
        __IO uint32_t UNUSED_11_9                              : 3; /* [11: 9] */
        __IO uint32_t RFLDO_SOFTSTART_SEL_MAN_SEL              : 1; /* [12:12], RW, Default 0x1 */
        __IO uint32_t UNUSED_31_13                             :19; /* [31:13] */
    } field;
} T_DCXO_MAN_SEL6;

/* DCXO_CFG, 0x400C0000, DBL_CFG0, Offset 0x0120 */
typedef union {
    __IO uint32_t value;
    struct {
        __IO uint32_t DCC_EN_M                                 : 1; /* [ 0: 0], RW, Default 0x0 */
        __IO uint32_t DCC_HW_TRIG_EN                           : 1; /* [ 1: 1], RW, Default 0x1 */
        __IO uint32_t REFDBL_DUTY_11_5_SEQ_SEL                 : 1; /* [ 2: 2], RW, Default 0x0 */
        __IO uint32_t DCXO_REFDCC_DUTY_0P5                     : 1; /* [ 3: 3], RW, Default 0x0 */
        __IO uint32_t DCXO_REFDBL_32M_CG_EN                    : 1; /* [ 4: 4], RW, Default 0x0 */
        __IO uint32_t UNUSED_31_5                              :27; /* [31: 5] */
    } field;
} T_DBL_CFG0;

/* DCXO_CFG, 0x400C0000, DBL_CFG1, Offset 0x0124 */
typedef union {
    __IO uint32_t value;
    struct {
        __IO uint32_t REFDBL_DCC_START_WAIT_SEL                : 4; /* [ 3: 0], RW, Default 0x0 */
        __IO uint32_t UNUSED_7_4                               : 4; /* [ 7: 4] */
        __IO uint32_t REFDBL_DCC_SETTLE_WAIT_SEL               : 4; /* [11: 8], RW, Default 0x0 */
        __IO uint32_t UNUSED_31_12                             :20; /* [31:12] */
    } field;
} T_DBL_CFG1;

/* DCXO_CFG, 0x400C0000, DBL_CFG2, Offset 0x0128 */
typedef union {
    __IO uint32_t value;
    struct {
        __IO uint32_t REFDBL_DCC_FINISH_WAIT_SEL               : 4; /* [ 3: 0], RW, Default 0x0 */
        __IO uint32_t REFDBL_DCC_PD_SKIP_SEL                   : 2; /* [ 5: 4], RW, Default 0x1 */
        __IO uint32_t REFDBL_PD_MODE_SEL                       : 2; /* [ 7: 6], RW, Default 0x0 */
        __IO uint32_t REFDBL_DCC_PD_WAIT_SEL                   : 4; /* [11: 8], RW, Default 0x2 */
        __IO uint32_t UNUSED_31_12                             :20; /* [31:12] */
    } field;
} T_DBL_CFG2;

/* DCXO_CFG, 0x400C0000, DBL_MAN0, Offset 0x012C */
typedef union {
    __IO uint32_t value;
    struct {
        __IO uint32_t DBL_EN_MAN                               : 1; /* [ 0: 0], RW, Default 0x0 */
        __IO uint32_t DCXO_REFDCC_DUTY_0P5_MAN                 : 1; /* [ 1: 1], RW, Default 0x0 */
        __IO uint32_t DCXO_REFDBL_POLARITY_MAN                 : 1; /* [ 2: 2], RW, Default 0x0 */
        __IO uint32_t DCXO_REFDBL_DCC_FINISH_MAN               : 1; /* [ 3: 3], RW, Default 0x0 */
        __IO uint32_t DCXO_REFDBL_EN_MAN                       : 1; /* [ 4: 4], RW, Default 0x0 */
        __IO uint32_t DCXO_CLK_DIG_EN_MAN                      : 1; /* [ 5: 5], RW, Default 0x0 */
        __IO uint32_t SEL_ADC_32M_64M_CK_MAN                   : 1; /* [ 6: 6], RW, Default 0x0 */
        __IO uint32_t SEL_DBL_32M_64M_CK_MAN                   : 1; /* [ 7: 7], RW, Default 0x0 */
        __IO uint32_t DCXO_DBB_64M_EN_MAN                      : 1; /* [ 8: 8], RW, Default 0x0 */
        __IO uint32_t DCXO_REFDBL_DELAY_MAN                    : 7; /* [15: 9], RW, Default 0x00 */
        __IO uint32_t UNUSED_31_16                             :16; /* [31:16] */
    } field;
} T_DBL_MAN0;

/* DCXO_CFG, 0x400C0000, DBL_MAN1, Offset 0x0130 */
typedef union {
    __IO uint32_t value;
    struct {
        __IO uint32_t DCXO_REFDBL_DUTY_MAN                     :12; /* [11: 0], RW, Default 0x000 */
        __IO uint32_t UNUSED_31_12                             :20; /* [31:12] */
    } field;
} T_DBL_MAN1;

/* DCXO_CFG, 0x400C0000, DBL_MAN_SEL0, Offset 0x0134 */
typedef union {
    __IO uint32_t value;
    struct {
        __IO uint32_t DBL_EN_MAN_SEL                           : 1; /* [ 0: 0], RW, Default 0x1 */
        __IO uint32_t DCXO_REFDCC_DUTY_0P5_MAN_SEL             : 1; /* [ 1: 1], RW, Default 0x1 */
        __IO uint32_t DCXO_REFDBL_POLARITY_MAN_SEL             : 1; /* [ 2: 2], RW, Default 0x1 */
        __IO uint32_t DCXO_REFDBL_DCC_FINISH_MAN_SEL           : 1; /* [ 3: 3], RW, Default 0x1 */
        __IO uint32_t DCXO_REFDBL_EN_MAN_SEL                   : 1; /* [ 4: 4], RW, Default 0x1 */
        __IO uint32_t DCXO_CLK_DIG_EN_MAN_SEL                  : 1; /* [ 5: 5], RW, Default 0x1 */
        __IO uint32_t SEL_ADC_32M_64M_CK_MAN_SEL               : 1; /* [ 6: 6], RW, Default 0x1 */
        __IO uint32_t SEL_DBL_32M_64M_CK_MAN_SEL               : 1; /* [ 7: 7], RW, Default 0x1 */
        __IO uint32_t DCXO_DBB_64M_EN_MAN_SEL                  : 1; /* [ 8: 8], RW, Default 0x1 */
        __IO uint32_t DCXO_REFDBL_DELAY_MAN_SEL                : 1; /* [ 9: 9], RW, Default 0x1 */
        __IO uint32_t DCXO_REFDBL_DUTY_MAN_SEL                 : 1; /* [10:10], RW, Default 0x1 */
        __IO uint32_t UNUSED_31_11                             :21; /* [31:11] */
    } field;
} T_DBL_MAN_SEL0;

/* DCXO_CFG, 0x400C0000, DCXO_DIG_RSV0, Offset 0x0138 */
typedef union {
    __IO uint32_t value;
    struct {
        __IO uint32_t DCXO_RSV0                                :16; /* [15: 0], RW, Default 0xFF00 */
        __IO uint32_t UNUSED_31_16                             :16; /* [31:16] */
    } field;
} T_DCXO_DIG_RSV0;

/* DCXO_CFG, 0x400C0000, DCXO_DIG_RSV1, Offset 0x013C */
typedef union {
    __IO uint32_t value;
    struct {
        __IO uint32_t DCXO_RSV1                                :16; /* [15: 0], RW, Default 0xFF00 */
        __IO uint32_t UNUSED_31_16                             :16; /* [31:16] */
    } field;
} T_DCXO_DIG_RSV1;

/* DCXO_CFG, 0x400C0000, DCXO_DBL_OUT0, Offset 0x0140 */
typedef union {
    __IO uint32_t value;
    struct {
        __I  uint32_t DA_DCXO_REFDBL_DUTY                      :12; /* [11: 0], RO, Default 0x000 */
        __I  uint32_t DA_DCXO_REFDBL_DCC_FINISH                : 1; /* [12:12], RO, Default 0x1 */
        __I  uint32_t DD_REFDBL_DCC_FINISH                     : 1; /* [13:13], RO, Default 0x1 */
        __IO uint32_t UNUSED_31_14                             :18; /* [31:14] */
    } field;
} T_DCXO_DBL_OUT0;

/* DCXO_CFG, 0x400C0000, DCXO_DBL_OUT1, Offset 0x0144 */
typedef union {
    __IO uint32_t value;
    struct {
        __I  uint32_t DA_DCXO_REFDBL_DELAY                     : 7; /* [ 6: 0], RO, Default 0x00 */
        __IO uint32_t UNUSED_7_7                               : 1; /* [ 7: 7] */
        __I  uint32_t DA_DCXO_REFDCC_DUTY_0P5                  : 1; /* [ 8: 8], RO, Default 0x0 */
        __IO uint32_t UNUSED_11_9                              : 3; /* [11: 9] */
        __I  uint32_t DA_DCXO_REFDBL_POLARITY                  : 1; /* [12:12], RO, Default 0x1 */
        __IO uint32_t UNUSED_31_13                             :19; /* [31:13] */
    } field;
} T_DCXO_DBL_OUT1;

/* DCXO_CFG, 0x400C0000, 2024-1023, non Byte Boundary, pointer to RG_Field struct */
#define PT_DCXO_SW_EN                              ((T_DCXO_SW_EN *)              (RM_DCXO_CFG_BASE        +0x0000))
#define PT_DCXO_CTUNE_FPM                          ((T_DCXO_CTUNE_FPM *)          (RM_DCXO_CFG_BASE        +0x0004))
#define PT_DCXO_CTUNE_LPM                          ((T_DCXO_CTUNE_LPM *)          (RM_DCXO_CFG_BASE        +0x0008))
#define PT_DCXO_REV                                ((T_DCXO_REV *)                (RM_DCXO_CFG_BASE        +0x000C))
#define PT_DCXO_CTUNE_STEP                         ((T_DCXO_CTUNE_STEP *)         (RM_DCXO_CFG_BASE        +0x0010))
#define PT_DCXO_CORE_ISEL                          ((T_DCXO_CORE_ISEL *)          (RM_DCXO_CFG_BASE        +0x0014))
#define PT_DCXO_CORE_ISEL_LPM                      ((T_DCXO_CORE_ISEL_LPM *)      (RM_DCXO_CFG_BASE        +0x0018))
#define PT_BGCORE_CTRL0                            ((T_BGCORE_CTRL0 *)            (RM_DCXO_CFG_BASE        +0x001C))
#define PT_BGCORE_CTRL1                            ((T_BGCORE_CTRL1 *)            (RM_DCXO_CFG_BASE        +0x0020))
#define PT_RFLDO_CTRL0                             ((T_RFLDO_CTRL0 *)             (RM_DCXO_CFG_BASE        +0x0090))
#define PT_DCXO_CK_RDY                             ((T_DCXO_CK_RDY *)             (RM_DCXO_CFG_BASE        +0x0024))
#define PT_DCXO_LDO_VOUT0                          ((T_DCXO_LDO_VOUT0 *)          (RM_DCXO_CFG_BASE        +0x0028))
#define PT_DCXO_LDO_VOUT1                          ((T_DCXO_LDO_VOUT1 *)          (RM_DCXO_CFG_BASE        +0x002C))
#define PT_DCXO_SOR                                ((T_DCXO_SOR *)                (RM_DCXO_CFG_BASE        +0x0038))
#define PT_DCXO_RG0                                ((T_DCXO_RG0 *)                (RM_DCXO_CFG_BASE        +0x003C))
#define PT_DCXO_RG1                                ((T_DCXO_RG1 *)                (RM_DCXO_CFG_BASE        +0x0040))
#define PT_DCXO_RG2                                ((T_DCXO_RG2 *)                (RM_DCXO_CFG_BASE        +0x0094))
#define PT_DCXO_RG3                                ((T_DCXO_RG3 *)                (RM_DCXO_CFG_BASE        +0x0098))
#define PT_DCXO_RG4                                ((T_DCXO_RG4 *)                (RM_DCXO_CFG_BASE        +0x009C))
#define PT_DCXO_RG5                                ((T_DCXO_RG5 *)                (RM_DCXO_CFG_BASE        +0x0100))
#define PT_DCXO_MONV_SEL                           ((T_DCXO_MONV_SEL *)           (RM_DCXO_CFG_BASE        +0x0044))
#define PT_DCXO_SEG0                               ((T_DCXO_SEG0 *)               (RM_DCXO_CFG_BASE        +0x0048))
#define PT_DCXO_SEG1                               ((T_DCXO_SEG1 *)               (RM_DCXO_CFG_BASE        +0x004C))
#define PT_DCXO_SEG2                               ((T_DCXO_SEG2 *)               (RM_DCXO_CFG_BASE        +0x0050))
#define PT_DCXO_SEG3                               ((T_DCXO_SEG3 *)               (RM_DCXO_CFG_BASE        +0x0054))
#define PT_DCXO_SEG4                               ((T_DCXO_SEG4 *)               (RM_DCXO_CFG_BASE        +0x0058))
#define PT_DCXO_SEG5                               ((T_DCXO_SEG5 *)               (RM_DCXO_CFG_BASE        +0x005C))
#define PT_DCXO_SEG6                               ((T_DCXO_SEG6 *)               (RM_DCXO_CFG_BASE        +0x0060))
#define PT_DCXO_CFG1                               ((T_DCXO_CFG1 *)               (RM_DCXO_CFG_BASE        +0x0064))
#define PT_DCXO_MAN_EN                             ((T_DCXO_MAN_EN *)             (RM_DCXO_CFG_BASE        +0x0068))
#define PT_DCXO_MAN0                               ((T_DCXO_MAN0 *)               (RM_DCXO_CFG_BASE        +0x006C))
#define PT_DCXO_MAN1                               ((T_DCXO_MAN1 *)               (RM_DCXO_CFG_BASE        +0x0070))
#define PT_DCXO_MAN2                               ((T_DCXO_MAN2 *)               (RM_DCXO_CFG_BASE        +0x0074))
#define PT_DCXO_MAN4                               ((T_DCXO_MAN4 *)               (RM_DCXO_CFG_BASE        +0x007C))
#define PT_DCXO_MAN5                               ((T_DCXO_MAN5 *)               (RM_DCXO_CFG_BASE        +0x0080))
#define PT_DCXO_MAN6                               ((T_DCXO_MAN6 *)               (RM_DCXO_CFG_BASE        +0x0104))
#define PT_DCXO_AUX_SEL                            ((T_DCXO_AUX_SEL *)            (RM_DCXO_CFG_BASE        +0x0084))
#define PT_DCXO_AUX_OUT0                           ((T_DCXO_AUX_OUT0 *)           (RM_DCXO_CFG_BASE        +0x0088))
#define PT_DCXO_AUX_OUT1                           ((T_DCXO_AUX_OUT1 *)           (RM_DCXO_CFG_BASE        +0x008C))
#define PT_DCXO_MAN_SEL0                           ((T_DCXO_MAN_SEL0 *)           (RM_DCXO_CFG_BASE        +0x0108))
#define PT_DCXO_MAN_SEL1                           ((T_DCXO_MAN_SEL1 *)           (RM_DCXO_CFG_BASE        +0x010C))
#define PT_DCXO_MAN_SEL2                           ((T_DCXO_MAN_SEL2 *)           (RM_DCXO_CFG_BASE        +0x0110))
#define PT_DCXO_MAN_SEL4                           ((T_DCXO_MAN_SEL4 *)           (RM_DCXO_CFG_BASE        +0x0114))
#define PT_DCXO_MAN_SEL5                           ((T_DCXO_MAN_SEL5 *)           (RM_DCXO_CFG_BASE        +0x0118))
#define PT_DCXO_MAN_SEL6                           ((T_DCXO_MAN_SEL6 *)           (RM_DCXO_CFG_BASE        +0x011C))
#define PT_DBL_CFG0                                ((T_DBL_CFG0 *)                (RM_DCXO_CFG_BASE        +0x0120))
#define PT_DBL_CFG1                                ((T_DBL_CFG1 *)                (RM_DCXO_CFG_BASE        +0x0124))
#define PT_DBL_CFG2                                ((T_DBL_CFG2 *)                (RM_DCXO_CFG_BASE        +0x0128))
#define PT_DBL_MAN0                                ((T_DBL_MAN0 *)                (RM_DCXO_CFG_BASE        +0x012C))
#define PT_DBL_MAN1                                ((T_DBL_MAN1 *)                (RM_DCXO_CFG_BASE        +0x0130))
#define PT_DBL_MAN_SEL0                            ((T_DBL_MAN_SEL0 *)            (RM_DCXO_CFG_BASE        +0x0134))
#define PT_DCXO_DIG_RSV0                           ((T_DCXO_DIG_RSV0 *)           (RM_DCXO_CFG_BASE        +0x0138))
#define PT_DCXO_DIG_RSV1                           ((T_DCXO_DIG_RSV1 *)           (RM_DCXO_CFG_BASE        +0x013C))
#define PT_DCXO_DBL_OUT0                           ((T_DCXO_DBL_OUT0 *)           (RM_DCXO_CFG_BASE        +0x0140))
#define PT_DCXO_DBL_OUT1                           ((T_DCXO_DBL_OUT1 *)           (RM_DCXO_CFG_BASE        +0x0144))

/* DCXO_CFG, 0x400C0000, 2024-1023, non Byte Boundary, pointer to RG_Field struct field */
#define PTF_DCXO_SW_EN                             ((T_DCXO_SW_EN *)              (RM_DCXO_CFG_BASE        +0x0000))->field
#define PTF_DCXO_CTUNE_FPM                         ((T_DCXO_CTUNE_FPM *)          (RM_DCXO_CFG_BASE        +0x0004))->field
#define PTF_DCXO_CTUNE_LPM                         ((T_DCXO_CTUNE_LPM *)          (RM_DCXO_CFG_BASE        +0x0008))->field
#define PTF_DCXO_REV                               ((T_DCXO_REV *)                (RM_DCXO_CFG_BASE        +0x000C))->field
#define PTF_DCXO_CTUNE_STEP                        ((T_DCXO_CTUNE_STEP *)         (RM_DCXO_CFG_BASE        +0x0010))->field
#define PTF_DCXO_CORE_ISEL                         ((T_DCXO_CORE_ISEL *)          (RM_DCXO_CFG_BASE        +0x0014))->field
#define PTF_DCXO_CORE_ISEL_LPM                     ((T_DCXO_CORE_ISEL_LPM *)      (RM_DCXO_CFG_BASE        +0x0018))->field
#define PTF_BGCORE_CTRL0                           ((T_BGCORE_CTRL0 *)            (RM_DCXO_CFG_BASE        +0x001C))->field
#define PTF_BGCORE_CTRL1                           ((T_BGCORE_CTRL1 *)            (RM_DCXO_CFG_BASE        +0x0020))->field
#define PTF_RFLDO_CTRL0                            ((T_RFLDO_CTRL0 *)             (RM_DCXO_CFG_BASE        +0x0090))->field
#define PTF_DCXO_CK_RDY                            ((T_DCXO_CK_RDY *)             (RM_DCXO_CFG_BASE        +0x0024))->field
#define PTF_DCXO_LDO_VOUT0                         ((T_DCXO_LDO_VOUT0 *)          (RM_DCXO_CFG_BASE        +0x0028))->field
#define PTF_DCXO_LDO_VOUT1                         ((T_DCXO_LDO_VOUT1 *)          (RM_DCXO_CFG_BASE        +0x002C))->field
#define PTF_DCXO_SOR                               ((T_DCXO_SOR *)                (RM_DCXO_CFG_BASE        +0x0038))->field
#define PTF_DCXO_RG0                               ((T_DCXO_RG0 *)                (RM_DCXO_CFG_BASE        +0x003C))->field
#define PTF_DCXO_RG1                               ((T_DCXO_RG1 *)                (RM_DCXO_CFG_BASE        +0x0040))->field
#define PTF_DCXO_RG2                               ((T_DCXO_RG2 *)                (RM_DCXO_CFG_BASE        +0x0094))->field
#define PTF_DCXO_RG3                               ((T_DCXO_RG3 *)                (RM_DCXO_CFG_BASE        +0x0098))->field
#define PTF_DCXO_RG4                               ((T_DCXO_RG4 *)                (RM_DCXO_CFG_BASE        +0x009C))->field
#define PTF_DCXO_RG5                               ((T_DCXO_RG5 *)                (RM_DCXO_CFG_BASE        +0x0100))->field
#define PTF_DCXO_MONV_SEL                          ((T_DCXO_MONV_SEL *)           (RM_DCXO_CFG_BASE        +0x0044))->field
#define PTF_DCXO_SEG0                              ((T_DCXO_SEG0 *)               (RM_DCXO_CFG_BASE        +0x0048))->field
#define PTF_DCXO_SEG1                              ((T_DCXO_SEG1 *)               (RM_DCXO_CFG_BASE        +0x004C))->field
#define PTF_DCXO_SEG2                              ((T_DCXO_SEG2 *)               (RM_DCXO_CFG_BASE        +0x0050))->field
#define PTF_DCXO_SEG3                              ((T_DCXO_SEG3 *)               (RM_DCXO_CFG_BASE        +0x0054))->field
#define PTF_DCXO_SEG4                              ((T_DCXO_SEG4 *)               (RM_DCXO_CFG_BASE        +0x0058))->field
#define PTF_DCXO_SEG5                              ((T_DCXO_SEG5 *)               (RM_DCXO_CFG_BASE        +0x005C))->field
#define PTF_DCXO_SEG6                              ((T_DCXO_SEG6 *)               (RM_DCXO_CFG_BASE        +0x0060))->field
#define PTF_DCXO_CFG1                              ((T_DCXO_CFG1 *)               (RM_DCXO_CFG_BASE        +0x0064))->field
#define PTF_DCXO_MAN_EN                            ((T_DCXO_MAN_EN *)             (RM_DCXO_CFG_BASE        +0x0068))->field
#define PTF_DCXO_MAN0                              ((T_DCXO_MAN0 *)               (RM_DCXO_CFG_BASE        +0x006C))->field
#define PTF_DCXO_MAN1                              ((T_DCXO_MAN1 *)               (RM_DCXO_CFG_BASE        +0x0070))->field
#define PTF_DCXO_MAN2                              ((T_DCXO_MAN2 *)               (RM_DCXO_CFG_BASE        +0x0074))->field
#define PTF_DCXO_MAN4                              ((T_DCXO_MAN4 *)               (RM_DCXO_CFG_BASE        +0x007C))->field
#define PTF_DCXO_MAN5                              ((T_DCXO_MAN5 *)               (RM_DCXO_CFG_BASE        +0x0080))->field
#define PTF_DCXO_MAN6                              ((T_DCXO_MAN6 *)               (RM_DCXO_CFG_BASE        +0x0104))->field
#define PTF_DCXO_AUX_SEL                           ((T_DCXO_AUX_SEL *)            (RM_DCXO_CFG_BASE        +0x0084))->field
#define PTF_DCXO_AUX_OUT0                          ((T_DCXO_AUX_OUT0 *)           (RM_DCXO_CFG_BASE        +0x0088))->field
#define PTF_DCXO_AUX_OUT1                          ((T_DCXO_AUX_OUT1 *)           (RM_DCXO_CFG_BASE        +0x008C))->field
#define PTF_DCXO_MAN_SEL0                          ((T_DCXO_MAN_SEL0 *)           (RM_DCXO_CFG_BASE        +0x0108))->field
#define PTF_DCXO_MAN_SEL1                          ((T_DCXO_MAN_SEL1 *)           (RM_DCXO_CFG_BASE        +0x010C))->field
#define PTF_DCXO_MAN_SEL2                          ((T_DCXO_MAN_SEL2 *)           (RM_DCXO_CFG_BASE        +0x0110))->field
#define PTF_DCXO_MAN_SEL4                          ((T_DCXO_MAN_SEL4 *)           (RM_DCXO_CFG_BASE        +0x0114))->field
#define PTF_DCXO_MAN_SEL5                          ((T_DCXO_MAN_SEL5 *)           (RM_DCXO_CFG_BASE        +0x0118))->field
#define PTF_DCXO_MAN_SEL6                          ((T_DCXO_MAN_SEL6 *)           (RM_DCXO_CFG_BASE        +0x011C))->field
#define PTF_DBL_CFG0                               ((T_DBL_CFG0 *)                (RM_DCXO_CFG_BASE        +0x0120))->field
#define PTF_DBL_CFG1                               ((T_DBL_CFG1 *)                (RM_DCXO_CFG_BASE        +0x0124))->field
#define PTF_DBL_CFG2                               ((T_DBL_CFG2 *)                (RM_DCXO_CFG_BASE        +0x0128))->field
#define PTF_DBL_MAN0                               ((T_DBL_MAN0 *)                (RM_DCXO_CFG_BASE        +0x012C))->field
#define PTF_DBL_MAN1                               ((T_DBL_MAN1 *)                (RM_DCXO_CFG_BASE        +0x0130))->field
#define PTF_DBL_MAN_SEL0                           ((T_DBL_MAN_SEL0 *)            (RM_DCXO_CFG_BASE        +0x0134))->field
#define PTF_DCXO_DIG_RSV0                          ((T_DCXO_DIG_RSV0 *)           (RM_DCXO_CFG_BASE        +0x0138))->field
#define PTF_DCXO_DIG_RSV1                          ((T_DCXO_DIG_RSV1 *)           (RM_DCXO_CFG_BASE        +0x013C))->field
#define PTF_DCXO_DBL_OUT0                          ((T_DCXO_DBL_OUT0 *)           (RM_DCXO_CFG_BASE        +0x0140))->field
#define PTF_DCXO_DBL_OUT1                          ((T_DCXO_DBL_OUT1 *)           (RM_DCXO_CFG_BASE        +0x0144))->field

/*************************************************************************************
 * TOP_MISC_CFG, 0x42010000, 2024-1129, Byte Boundary, only Define RG_Field Address
 *************************************************************************************/
#define RF_HDE_DELSEL_HV__RF_HDE_DELSEL_HV                                        ((volatile uint32_t *)(RM_TOP_MISC_CFG_BASE    +0x0000)) /* [18: 0], 19-bit, RW, Default 0x0010B */
#define RF_HDE_DELSEL_LV__RF_HDE_DELSEL_LV                                        ((volatile uint32_t *)(RM_TOP_MISC_CFG_BASE    +0x0004)) /* [18: 0], 19-bit, RW, Default 0x00304 */
#define RF_UHDE_DELSEL_HV__RF_UHDE_DELSEL_HV                                      ((volatile uint32_t *)(RM_TOP_MISC_CFG_BASE    +0x0008)) /* [18: 0], 19-bit, RW, Default 0x3010B */
#define RF_UHDE_DELSEL_LV__RF_UHDE_DELSEL_LV                                      ((volatile uint32_t *)(RM_TOP_MISC_CFG_BASE    +0x000C)) /* [18: 0], 19-bit, RW, Default 0x50304 */
#define SRAM_HDE_DELSEL_HV__SRAM_HDE_DELSEL_HV                                    ((volatile uint32_t *)(RM_TOP_MISC_CFG_BASE    +0x0010)) /* [18: 0], 19-bit, RW, Default 0x00102 */
#define SRAM_HDE_DELSEL_LV__SRAM_HDE_DELSEL_LV                                    ((volatile uint32_t *)(RM_TOP_MISC_CFG_BASE    +0x0014)) /* [18: 0], 19-bit, RW, Default 0x00304 */
#define SRAM_UHDE_DELSEL_HV__SRAM_UHDE_DELSEL_HV                                  ((volatile uint32_t *)(RM_TOP_MISC_CFG_BASE    +0x0018)) /* [18: 0], 19-bit, RW, Default 0x30102 */
#define SRAM_UHDE_DELSEL_LV__SRAM_UHDE_DELSEL_LV                                  ((volatile uint32_t *)(RM_TOP_MISC_CFG_BASE    +0x001C)) /* [18: 0], 19-bit, RW, Default 0x70704 */
#define SRAM_DELSEL_SEL__SRAM_DELSEL_SEL                                          ((volatile uint8_t  *)(RM_TOP_MISC_CFG_BASE    +0x0020)) /* [ 0: 0],  1-bit, RW, Default 0x0 */
#define DCXO_DBL_MISC0__DCXO_DBL_MISC0                                            ((volatile uint32_t *)(RM_TOP_MISC_CFG_BASE    +0x0024)) /* [31: 0], 32-bit, RW, Default 0xF0000001 */
#define HW_MISC0__HW_MISC0                                                        ((volatile uint16_t *)(RM_TOP_MISC_CFG_BASE    +0x0030)) /* [15: 0], 16-bit, RW, Default 0x0000 */
#define HW_MISC1__HW_MISC1                                                        ((volatile uint16_t *)(RM_TOP_MISC_CFG_BASE    +0x0034)) /* [15: 0], 16-bit, RW, Default 0x0000 */
#define HW_MISC2__HW_MISC2                                                        ((volatile uint16_t *)(RM_TOP_MISC_CFG_BASE    +0x0038)) /* [15: 0], 16-bit, RW, Default 0x0000 */
#define HW_MISC3__HW_MISC3                                                        ((volatile uint16_t *)(RM_TOP_MISC_CFG_BASE    +0x003C)) /* [15: 0], 16-bit, RW, Default 0x0000 */
#define SW_MISC0__SW_MISC0                                                        ((volatile uint16_t *)(RM_TOP_MISC_CFG_BASE    +0x0040)) /* [15: 0], 16-bit, RW, Default 0x0000 */
#define BROM_MISC0__BROM_MISC0                                                    ((volatile uint16_t *)(RM_TOP_MISC_CFG_BASE    +0x0044)) /* [15: 0], 16-bit, RW, Default 0x0000 */
#define SYSTEM_INFOD__SYSTEM_INFO                                                 ((volatile uint32_t *)(RM_TOP_MISC_CFG_BASE    +0x0100)) /* [31: 0], 32-bit, RO, Default 0x01000000 */
#define TOP_DEBUG_MON__TOP_DEBUG_MON                                              ((volatile uint16_t *)(RM_TOP_MISC_CFG_BASE    +0x0104)) /* [15: 0], 16-bit, RO, Default 0x0000 */
#define TOP_DEBUG_CTRL__TOP_DEBUG_CTRL                                            ((volatile uint16_t *)(RM_TOP_MISC_CFG_BASE    +0x0108)) /* [15: 0], 16-bit, RW, Default 0x0000 */
#define TOP_TRAP_REG_CTRL__TOP_TRAP_REG_CTRL                                      ((volatile uint8_t  *)(RM_TOP_MISC_CFG_BASE    +0x010C)) /* [ 7: 0],  8-bit, RW, Default 0x00 */
#define TOP_TRAP_REG_CTRL__TOP_NM_TRAP_DUMMY_MASK                                 ((volatile uint8_t  *)(RM_TOP_MISC_CFG_BASE    +0x010D)) /* [ 8: 8],  1-bit, RW, Default 0x0 */
#define SFC_SLT_SEL__SFC_SLT_SEL                                                  ((volatile uint8_t  *)(RM_TOP_MISC_CFG_BASE    +0x0110)) /* [ 0: 0],  1-bit, RW, Default 0x0 */
#define EXIT_SLT_MODE__EXIT_SLT_MODE                                              ((volatile uint8_t  *)(RM_TOP_MISC_CFG_BASE    +0x0114)) /* [ 0: 0],  1-bit, RW, Default 0x0 */
#define USB_CTRL__USB_I2C_MODE                                                    ((volatile uint8_t  *)(RM_TOP_MISC_CFG_BASE    +0x0118)) /* [ 0: 0],  1-bit, RW, Default 0x0 */
#define TM_CTRL__TM_CTRL                                                          ((volatile uint16_t *)(RM_TOP_MISC_CFG_BASE    +0x0120)) /* [15: 0], 16-bit, RW, Default 0x0006 */
#define TM_CTRL_CK_MON__TM_CTRL_CLOCK_MON                                         ((volatile uint16_t *)(RM_TOP_MISC_CFG_BASE    +0x0124)) /* [15: 0], 16-bit, RW, Default 0x0000 */
#define TMBIST_CTRL__CR_TMBIST_JTAG_CTRL                                          ((volatile uint8_t  *)(RM_TOP_MISC_CFG_BASE    +0x0128)) /* [ 3: 0],  4-bit, RW, Default 0x0 */
#define TMBIST_CTRL__CR_TMBIST_JTAG_MODE                                          ((volatile uint8_t  *)(RM_TOP_MISC_CFG_BASE    +0x0129)) /* [ 8: 8],  1-bit, RW, Default 0x0 */
#define TM_RBIST_CTRL__RBIST_ENABLE                                               ((volatile uint8_t  *)(RM_TOP_MISC_CFG_BASE    +0x012C)) /* [ 0: 0],  1-bit, RW, Default 0x0 */
#define TM_RBIST_CTRL__RBIST_SRAM_CK_INVERSE                                      ((volatile uint8_t  *)(RM_TOP_MISC_CFG_BASE    +0x012D)) /* [ 8: 8],  1-bit, RW, Default 0x0 */
#define SFIO_CFG_WP__SFIO_CFG_WP                                                  ((volatile uint32_t *)(RM_TOP_MISC_CFG_BASE    +0x0200)) /* [31: 0], 32-bit, RW, Default 0x00003012 */
#define SFIO_CFG_CS__SFIO_CFG_CS                                                  ((volatile uint32_t *)(RM_TOP_MISC_CFG_BASE    +0x0204)) /* [31: 0], 32-bit, RW, Default 0x00003032 */
#define SFIO_CFG_CK__SFIO_CFG_CK                                                  ((volatile uint32_t *)(RM_TOP_MISC_CFG_BASE    +0x0208)) /* [31: 0], 32-bit, RW, Default 0x00001012 */
#define SFIO_CFG_IN__SFIO_CFG_IN                                                  ((volatile uint32_t *)(RM_TOP_MISC_CFG_BASE    +0x020C)) /* [31: 0], 32-bit, RW, Default 0x00003012 */
#define SFIO_CFG_OUT__SFIO_CFG_OUT                                                ((volatile uint32_t *)(RM_TOP_MISC_CFG_BASE    +0x0210)) /* [31: 0], 32-bit, RW, Default 0x00003012 */
#define SFIO_CFG_HOLD__SFIO_CFG_HOLD                                              ((volatile uint32_t *)(RM_TOP_MISC_CFG_BASE    +0x0214)) /* [31: 0], 32-bit, RW, Default 0x00003012 */
#define VBUS_DET__VBUS_DETECT_STAUS                                               ((volatile uint8_t  *)(RM_TOP_MISC_CFG_BASE    +0x0300)) /* [ 0: 0],  1-bit, RO, Default 0x0 */
#define DUMMY_RSV__DUMMY_RSV                                                      ((volatile uint32_t *)(RM_TOP_MISC_CFG_BASE    +0x0304)) /* [31: 0], 32-bit, RW, Default 0x00000000 */
#define ABB_CLK_GEN_CFG_0__ABBCK200K_BGR_DIV_EN                                   ((volatile uint8_t  *)(RM_TOP_MISC_CFG_BASE    +0x0400)) /* [ 0: 0],  1-bit, RW, Default 0x0 */
#define ABB_CLK_GEN_CFG_0__ABBCK200K_BGR_DIV_CHG                                  ((volatile uint8_t  *)(RM_TOP_MISC_CFG_BASE    +0x0401)) /* [ 8: 8],  1-bit, RW, Default 0x0 */
#define ABB_CLK_GEN_CFG_0__ABBCK200K_BGR_DIV_SEL                                  ((volatile uint16_t *)(RM_TOP_MISC_CFG_BASE    +0x0402)) /* [26:16], 11-bit, RW, Default 0x104 */
#define ABB_CLK_GEN_CFG_1__ABBCK200K_AIO_DIV_EN                                   ((volatile uint8_t  *)(RM_TOP_MISC_CFG_BASE    +0x0404)) /* [ 0: 0],  1-bit, RW, Default 0x0 */
#define ABB_CLK_GEN_CFG_1__ABBCK200K_AIO_DIV_CHG                                  ((volatile uint8_t  *)(RM_TOP_MISC_CFG_BASE    +0x0405)) /* [ 8: 8],  1-bit, RW, Default 0x0 */
#define ABB_CLK_GEN_CFG_1__ABBCK200K_AIO_DIV_SEL                                  ((volatile uint16_t *)(RM_TOP_MISC_CFG_BASE    +0x0406)) /* [26:16], 11-bit, RW, Default 0x104 */
#define ABB_CLK_GEN_CFG_2__AUD01ADC_CLK_DIV_EN                                    ((volatile uint8_t  *)(RM_TOP_MISC_CFG_BASE    +0x0408)) /* [ 0: 0],  1-bit, RW, Default 0x0 */
#define ABB_CLK_GEN_CFG_2__AUD01ADC_CLK_DIV_CHG                                   ((volatile uint8_t  *)(RM_TOP_MISC_CFG_BASE    +0x0409)) /* [ 8: 8],  1-bit, RW, Default 0x0 */
#define ABB_CLK_GEN_CFG_2__AUD01ADC_CLK_DIV_SEL                                   ((volatile uint16_t *)(RM_TOP_MISC_CFG_BASE    +0x040A)) /* [26:16], 11-bit, RW, Default 0x104 */
#define ABB_CLK_GEN_CFG_3__ABBCK200K_BGR_DIV_RDY                                  ((volatile uint8_t  *)(RM_TOP_MISC_CFG_BASE    +0x040C)) /* [ 0: 0],  1-bit, RO, Default 0x0 */
#define ABB_CLK_GEN_CFG_3__ABBCK200K_BGR_DIV_SWRST                                ((volatile uint8_t  *)(RM_TOP_MISC_CFG_BASE    +0x040D)) /* [ 8: 8],  1-bit, RW, Default 0x0 */
#define ABB_CLK_GEN_CFG_3__ABBCK200K_AIO_DIV_RDY                                  ((volatile uint8_t  *)(RM_TOP_MISC_CFG_BASE    +0x040E)) /* [16:16],  1-bit, RO, Default 0x0 */
#define ABB_CLK_GEN_CFG_3__ABBCK200K_AIO_DIV_SWRST                                ((volatile uint8_t  *)(RM_TOP_MISC_CFG_BASE    +0x040F)) /* [24:24],  1-bit, RW, Default 0x0 */
#define ABB_CLK_GEN_CFG_4__AUD01ADC_CLK_DIV_RDY                                   ((volatile uint8_t  *)(RM_TOP_MISC_CFG_BASE    +0x0410)) /* [ 0: 0],  1-bit, RO, Default 0x0 */
#define ABB_CLK_GEN_CFG_4__AUD01ADC_CLK_DIV_SWRST                                 ((volatile uint8_t  *)(RM_TOP_MISC_CFG_BASE    +0x0411)) /* [ 8: 8],  1-bit, RW, Default 0x0 */
#define ABB_CLK_GEN_CFG_4__AUD01ADC_TEST_SEL                                      ((volatile uint8_t  *)(RM_TOP_MISC_CFG_BASE    +0x0412)) /* [16:16],  1-bit, RW, Default 0x0 */
#define ABB_CLK_GEN_CFG_4__DBG_CLK_OUT_EN                                         ((volatile uint8_t  *)(RM_TOP_MISC_CFG_BASE    +0x0413)) /* [24:24],  1-bit, RW, Default 0x0 */
#define SPI_BYPASS__SPI_BYPASS_OE                                                 ((volatile uint8_t  *)(RM_TOP_MISC_CFG_BASE    +0x0503)) /* [27:24],  4-bit, RW, Default 0xD */
#define SPI_BYPASS__SPI_BYPASS_CS_EN                                              ((volatile uint8_t  *)(RM_TOP_MISC_CFG_BASE    +0x0502)) /* [19:16],  4-bit, RW, Default 0x0 */
#define SPI_BYPASS__SPI_BYPASS_MST_SEL                                            ((volatile uint8_t  *)(RM_TOP_MISC_CFG_BASE    +0x0501)) /* [ 9: 8],  2-bit, RW, Default 0x0 */
#define SPI_BYPASS__SPI_BYPASS_EN                                                 ((volatile uint8_t  *)(RM_TOP_MISC_CFG_BASE    +0x0500)) /* [ 0: 0],  1-bit, RW, Default 0x0 */
#define SW_IRQ_0__SW_IRQ_0_TRIG                                                   ((volatile uint8_t  *)(RM_TOP_MISC_CFG_BASE    +0x0600)) /* [ 0: 0],  1-bit, WO, Default 0x0 */
#define SW_IRQ_0__SW_IRQ_0_STA                                                    ((volatile uint8_t  *)(RM_TOP_MISC_CFG_BASE    +0x0601)) /* [ 8: 8],  1-bit, W1C, Default 0x0 */
#define USB_WAKE_STS_0__USB_WAKE_STATUS                                           ((volatile uint32_t *)(RM_TOP_MISC_CFG_BASE    +0x0700)) /* [31: 0], 32-bit, RO, Default 0x00000000 */
#define TOP_BUS_DBGMON__BUS_DEBUG_EN                                              ((volatile uint8_t  *)(RM_TOP_MISC_CFG_BASE    +0x0800)) /* [ 0: 0],  1-bit, RW, Default 0x0 */
#define TOP_BUS_DBGMON__TOP_DBGMON_SEL                                            ((volatile uint8_t  *)(RM_TOP_MISC_CFG_BASE    +0x0801)) /* [15: 8],  8-bit, RW, Default 0xFF */

/*************************************************************************************
 * CKSYS, 0x42030000, 2024-1209, Byte Boundary, only Define RG_Field Address
 *************************************************************************************/
#define SYS_FREE_DCM_CON__RG_SYS_FREE_FSEL0                                       ((volatile uint8_t  *)(RM_CKSYS_BASE           +0x0000)) /* [ 5: 0],  6-bit, RW, Default 0x20 */
#define SYS_FREE_DCM_CON__RG_SYS_FSEL_UPDATE                                      ((volatile uint8_t  *)(RM_CKSYS_BASE           +0x0003)) /* [24:24],  1-bit, RW, Default 0x0 */
#define BT_FREE_DCM_CON__RG_BT_FREE_FSEL0                                         ((volatile uint8_t  *)(RM_CKSYS_BASE           +0x0004)) /* [ 5: 0],  6-bit, RW, Default 0x20 */
#define BT_FREE_DCM_CON__RG_BT_FSEL_UPDATE                                        ((volatile uint8_t  *)(RM_CKSYS_BASE           +0x0007)) /* [24:24],  1-bit, RW, Default 0x0 */
#define BT_DCM_CON_0__RG_BT_PLLCK_SEL                                             ((volatile uint8_t  *)(RM_CKSYS_BASE           +0x000B)) /* [24:24],  1-bit, RW, Default 0x0 */
#define BT_DCM_CON_0__RG_BT_DCM_DBC_EN                                            ((volatile uint8_t  *)(RM_CKSYS_BASE           +0x000A)) /* [16:16],  1-bit, RW, Default 0x0 */
#define BT_DCM_CON_0__RG_BT_DCM_DBC_NUM                                           ((volatile uint8_t  *)(RM_CKSYS_BASE           +0x0009)) /* [12: 8],  5-bit, RW, Default 0x00 */
#define BT_DCM_CON_0__RG_BT_SFSEL                                                 ((volatile uint8_t  *)(RM_CKSYS_BASE           +0x0008)) /* [ 5: 0],  6-bit, RW, Default 0x02 */
#define BT_DCM_CON_1__RG_BT_FORCE_CLKSLOW                                         ((volatile uint8_t  *)(RM_CKSYS_BASE           +0x000F)) /* [24:24],  1-bit, RW, Default 0x0 */
#define BT_DCM_CON_1__RG_BT_FORCE_CLKOFF                                          ((volatile uint8_t  *)(RM_CKSYS_BASE           +0x000E)) /* [16:16],  1-bit, RW, Default 0x0 */
#define BT_DCM_CON_1__RG_BT_CLKSLOW_EN                                            ((volatile uint8_t  *)(RM_CKSYS_BASE           +0x000D)) /* [ 8: 8],  1-bit, RW, Default 0x0 */
#define BT_DCM_CON_1__RG_BT_CLKOFF_EN                                             ((volatile uint8_t  *)(RM_CKSYS_BASE           +0x000C)) /* [ 0: 0],  1-bit, RW, Default 0x0 */
#define SFC_DCM_CON_0__RG_SFC_DCM_APB_SEL                                         ((volatile uint8_t  *)(RM_CKSYS_BASE           +0x0013)) /* [28:24],  5-bit, RW, Default 0x00 */
#define SFC_DCM_CON_0__RG_SFC_DCM_DBC_EN                                          ((volatile uint8_t  *)(RM_CKSYS_BASE           +0x0012)) /* [16:16],  1-bit, RW, Default 0x0 */
#define SFC_DCM_CON_0__RG_SFC_DCM_DBC_NUM                                         ((volatile uint8_t  *)(RM_CKSYS_BASE           +0x0011)) /* [15: 8],  8-bit, RW, Default 0x00 */
#define SFC_DCM_CON_1__RG_SFC_DCM_APB_TOG                                         ((volatile uint8_t  *)(RM_CKSYS_BASE           +0x0017)) /* [24:24],  1-bit, RW, Default 0x0 */
#define SFC_DCM_CON_1__RG_SFC_FORCE_CLKOFF                                        ((volatile uint8_t  *)(RM_CKSYS_BASE           +0x0016)) /* [16:16],  1-bit, RW, Default 0x0 */
#define SFC_DCM_CON_1__RG_SFC_CLKOFF_EN                                           ((volatile uint8_t  *)(RM_CKSYS_BASE           +0x0014)) /* [ 0: 0],  1-bit, RW, Default 0x0 */
#define ESC_DCM_CON_0__RG_ESC_DCM_APB_SEL                                         ((volatile uint8_t  *)(RM_CKSYS_BASE           +0x001B)) /* [28:24],  5-bit, RW, Default 0x00 */
#define ESC_DCM_CON_0__RG_ESC_DCM_DBC_EN                                          ((volatile uint8_t  *)(RM_CKSYS_BASE           +0x001A)) /* [16:16],  1-bit, RW, Default 0x0 */
#define ESC_DCM_CON_0__RG_ESC_DCM_DBC_NUM                                         ((volatile uint8_t  *)(RM_CKSYS_BASE           +0x0019)) /* [15: 8],  8-bit, RW, Default 0x00 */
#define ESC_DCM_CON_1__RG_ESC_DCM_APB_TOG                                         ((volatile uint8_t  *)(RM_CKSYS_BASE           +0x001F)) /* [24:24],  1-bit, RW, Default 0x0 */
#define ESC_DCM_CON_1__RG_ESC_FORCE_CLKOFF                                        ((volatile uint8_t  *)(RM_CKSYS_BASE           +0x001E)) /* [16:16],  1-bit, RW, Default 0x0 */
#define ESC_DCM_CON_1__RG_ESC_CLKOFF_EN                                           ((volatile uint8_t  *)(RM_CKSYS_BASE           +0x001C)) /* [ 0: 0],  1-bit, RW, Default 0x0 */
#define CKSYS_CLK_CFG_0__CLK_SYS_SEL                                              ((volatile uint8_t  *)(RM_CKSYS_BASE           +0x0020)) /* [ 2: 0],  3-bit, RW, Default 0x0 */
#define CKSYS_CLK_CFG_0__CLK_SFC_SEL                                              ((volatile uint8_t  *)(RM_CKSYS_BASE           +0x0021)) /* [10: 8],  3-bit, RW, Default 0x0 */
#define CKSYS_CLK_CFG_0__CLK_ESC_SEL                                              ((volatile uint8_t  *)(RM_CKSYS_BASE           +0x0022)) /* [18:16],  3-bit, RW, Default 0x0 */
#define CKSYS_CLK_CFG_0__CLK_IBEX_SEL                                             ((volatile uint8_t  *)(RM_CKSYS_BASE           +0x0023)) /* [26:24],  3-bit, RW, Default 0x0 */
#define CKSYS_CLK_CFG_1__CLK_SPIMST0_SEL                                          ((volatile uint8_t  *)(RM_CKSYS_BASE           +0x0024)) /* [ 2: 0],  3-bit, RW, Default 0x0 */
#define CKSYS_CLK_CFG_1__CLK_SPIMST1_SEL                                          ((volatile uint8_t  *)(RM_CKSYS_BASE           +0x0025)) /* [10: 8],  3-bit, RW, Default 0x0 */
#define CKSYS_CLK_CFG_1__CLK_SPIMST2_SEL                                          ((volatile uint8_t  *)(RM_CKSYS_BASE           +0x0026)) /* [18:16],  3-bit, RW, Default 0x0 */
#define CKSYS_CLK_CFG_1__CLK_SPISLV_SEL                                           ((volatile uint8_t  *)(RM_CKSYS_BASE           +0x0027)) /* [26:24],  3-bit, RW, Default 0x0 */
#define CKSYS_CLK_CFG_2__CLK_USB_SEL                                              ((volatile uint8_t  *)(RM_CKSYS_BASE           +0x0028)) /* [ 2: 0],  3-bit, RW, Default 0x0 */
#define CKSYS_CLK_CFG_2__CLK_I3C_SEL                                              ((volatile uint8_t  *)(RM_CKSYS_BASE           +0x0029)) /* [10: 8],  3-bit, RW, Default 0x0 */
#define CKSYS_CLK_CFG_2__CLK_BT_HOP_SEL                                           ((volatile uint8_t  *)(RM_CKSYS_BASE           +0x002A)) /* [18:16],  3-bit, RW, Default 0x0 */
#define CKSYS_CLK_CFG_2__CLK_AUD_INTBUS_SEL                                       ((volatile uint8_t  *)(RM_CKSYS_BASE           +0x002B)) /* [26:24],  3-bit, RW, Default 0x0 */
#define CKSYS_CLK_CFG_3__CLK_IRTX_SEL                                             ((volatile uint8_t  *)(RM_CKSYS_BASE           +0x002C)) /* [ 2: 0],  3-bit, RW, Default 0x0 */
#define CKSYS_CLK_CFG_3__CLK_SLOW_BUS_SEL                                         ((volatile uint8_t  *)(RM_CKSYS_BASE           +0x002D)) /* [10: 8],  3-bit, RW, Default 0x0 */
#define CKSYS_CLK_CFG_3__CLK_AUD_ENGINE_SEL                                       ((volatile uint8_t  *)(RM_CKSYS_BASE           +0x002E)) /* [18:16],  3-bit, RW, Default 0x0 */
#define CKSYS_CLK_CFG_3__CLK_BT_MAC_SEL                                           ((volatile uint8_t  *)(RM_CKSYS_BASE           +0x002F)) /* [26:24],  3-bit, RW, Default 0x0 */
#define CKSYS_CLK_CFG_4__CLK_RGU_32K_SEL                                          ((volatile uint8_t  *)(RM_CKSYS_BASE           +0x0030)) /* [ 0: 0],  1-bit, RW, Default 0x0 */
#define CKSYS_CLK_CFG_4__CLK_DCXO_PWR_CTRL_SEL                                    ((volatile uint8_t  *)(RM_CKSYS_BASE           +0x0031)) /* [ 8: 8],  1-bit, RW, Default 0x0 */
#define CKSYS_CLK_CFG_4__CLK_DCXO_DIG_MACRO_SEL                                   ((volatile uint8_t  *)(RM_CKSYS_BASE           +0x0032)) /* [16:16],  1-bit, RW, Default 0x0 */
#define CKSYS_CLK_CFG_4__CLK_OSC_26M_SEL                                          ((volatile uint8_t  *)(RM_CKSYS_BASE           +0x0033)) /* [26:24],  3-bit, RW, Default 0x0 */
#define CKSYS_CLK_UPDATE_0__CHG_SYS                                               ((volatile uint8_t  *)(RM_CKSYS_BASE           +0x0034)) /* [ 0: 0],  1-bit, RW, Default 0x0 */
#define CKSYS_CLK_UPDATE_0__CHG_SFC                                               ((volatile uint8_t  *)(RM_CKSYS_BASE           +0x0035)) /* [ 8: 8],  1-bit, RW, Default 0x0 */
#define CKSYS_CLK_UPDATE_0__CHG_ESC                                               ((volatile uint8_t  *)(RM_CKSYS_BASE           +0x0036)) /* [16:16],  1-bit, RW, Default 0x0 */
#define CKSYS_CLK_UPDATE_0__CHG_IBEX                                              ((volatile uint8_t  *)(RM_CKSYS_BASE           +0x0037)) /* [24:24],  1-bit, RW, Default 0x0 */
#define CKSYS_CLK_UPDATE_1__CHG_SPIMST2                                           ((volatile uint8_t  *)(RM_CKSYS_BASE           +0x003A)) /* [16:16],  1-bit, RW, Default 0x0 */
#define CKSYS_CLK_UPDATE_1__CHG_SPISLV                                            ((volatile uint8_t  *)(RM_CKSYS_BASE           +0x003B)) /* [24:24],  1-bit, RW, Default 0x0 */
#define CKSYS_CLK_UPDATE_2__CHG_USB                                               ((volatile uint8_t  *)(RM_CKSYS_BASE           +0x003C)) /* [ 0: 0],  1-bit, RW, Default 0x0 */
#define CKSYS_CLK_UPDATE_2__CHG_I3C                                               ((volatile uint8_t  *)(RM_CKSYS_BASE           +0x003D)) /* [ 8: 8],  1-bit, RW, Default 0x0 */
#define CKSYS_CLK_UPDATE_2__CHG_BT_HOP                                            ((volatile uint8_t  *)(RM_CKSYS_BASE           +0x003E)) /* [16:16],  1-bit, RW, Default 0x0 */
#define CKSYS_CLK_UPDATE_2__CHG_AUD_INTBUS                                        ((volatile uint8_t  *)(RM_CKSYS_BASE           +0x003F)) /* [24:24],  1-bit, RW, Default 0x0 */
#define CKSYS_CLK_UPDATE_3__CHG_IRTX                                              ((volatile uint8_t  *)(RM_CKSYS_BASE           +0x0040)) /* [ 0: 0],  1-bit, RW, Default 0x0 */
#define CKSYS_CLK_FORCE_ON_0__CLK_SYS_FORCE_ON                                    ((volatile uint8_t  *)(RM_CKSYS_BASE           +0x0044)) /* [ 0: 0],  1-bit, RW, Default 0x0 */
#define CKSYS_CLK_FORCE_ON_0__CLK_SFC_FORCE_ON                                    ((volatile uint8_t  *)(RM_CKSYS_BASE           +0x0045)) /* [ 8: 8],  1-bit, RW, Default 0x0 */
#define CKSYS_CLK_FORCE_ON_0__CLK_ESC_FORCE_ON                                    ((volatile uint8_t  *)(RM_CKSYS_BASE           +0x0046)) /* [16:16],  1-bit, RW, Default 0x0 */
#define CKSYS_CLK_FORCE_ON_0__CLK_IBEX_FORCE_ON                                   ((volatile uint8_t  *)(RM_CKSYS_BASE           +0x0047)) /* [24:24],  1-bit, RW, Default 0x0 */
#define CKSYS_CLK_FORCE_ON_1__CLK_SPIMST2_FORCE_ON                                ((volatile uint8_t  *)(RM_CKSYS_BASE           +0x004A)) /* [16:16],  1-bit, RW, Default 0x0 */
#define CKSYS_CLK_FORCE_ON_1__CLK_SPISLV_FORCE_ON                                 ((volatile uint8_t  *)(RM_CKSYS_BASE           +0x004B)) /* [24:24],  1-bit, RW, Default 0x0 */
#define CKSYS_CLK_FORCE_ON_2__CLK_USB_FORCE_ON                                    ((volatile uint8_t  *)(RM_CKSYS_BASE           +0x004C)) /* [ 0: 0],  1-bit, RW, Default 0x0 */
#define CKSYS_CLK_FORCE_ON_2__CLK_I3C_FORCE_ON                                    ((volatile uint8_t  *)(RM_CKSYS_BASE           +0x004D)) /* [ 8: 8],  1-bit, RW, Default 0x0 */
#define CKSYS_CLK_FORCE_ON_2__CLK_BT_HOP_FORCE_ON                                 ((volatile uint8_t  *)(RM_CKSYS_BASE           +0x004E)) /* [16:16],  1-bit, RW, Default 0x0 */
#define CKSYS_CLK_FORCE_ON_2__CLK_AUD_INTBUS_FORCE_ON                             ((volatile uint8_t  *)(RM_CKSYS_BASE           +0x004F)) /* [24:24],  1-bit, RW, Default 0x0 */
#define CKSYS_CLK_FORCE_ON_3__CLK_IRTX_FORCE_ON                                   ((volatile uint8_t  *)(RM_CKSYS_BASE           +0x0050)) /* [ 0: 0],  1-bit, RW, Default 0x0 */
#define CKSYS_CLK_DIV_0__CHOP_DIV_SEL                                             ((volatile uint16_t *)(RM_CKSYS_BASE           +0x0056)) /* [26:16], 11-bit, RW, Default 0x07F */
#define CKSYS_CLK_DIV_0__CHOP_DIV_CHG                                             ((volatile uint8_t  *)(RM_CKSYS_BASE           +0x0055)) /* [ 8: 8],  1-bit, RW, Default 0x0 */
#define CKSYS_CLK_DIV_0__CHOP_DIV_EN                                              ((volatile uint8_t  *)(RM_CKSYS_BASE           +0x0054)) /* [ 0: 0],  1-bit, RW, Default 0x0 */
#define GPIO_CLKO_CTRL_A__CLKO_MODE0                                              ((volatile uint8_t  *)(RM_CKSYS_BASE           +0x0058)) /* [ 3: 0],  4-bit, RW, Default 0x0 */
#define GPIO_CLKO_CTRL_A__CLKO_MODE1                                              ((volatile uint8_t  *)(RM_CKSYS_BASE           +0x0059)) /* [11: 8],  4-bit, RW, Default 0x0 */
#define GPIO_CLKO_CTRL_A__CLKO_MODE2                                              ((volatile uint8_t  *)(RM_CKSYS_BASE           +0x005A)) /* [19:16],  4-bit, RW, Default 0x0 */
#define CKSYS_MISC_0__CKSYS_REG_SPARE                                             ((volatile uint16_t *)(RM_CKSYS_BASE           +0x005C)) /* [15: 0], 16-bit, RW, Default 0x0000 */
#define CKSYS_MISC_0__ESC_EXTRA_DIV_SEL                                           ((volatile uint8_t  *)(RM_CKSYS_BASE           +0x005E)) /* [17:16],  2-bit, RW, Default 0x0 */
#define CKSYS_MISC_0__ESC_EXTRA_DIV_CK_EN                                         ((volatile uint8_t  *)(RM_CKSYS_BASE           +0x005F)) /* [24:24],  1-bit, RW, Default 0x1 */
#define CKSYS_TST_SEL_0__TST_SEL_0                                                ((volatile uint32_t *)(RM_CKSYS_BASE           +0x0220)) /* [31: 0], 32-bit, RW, Default 0x00000000 */
#define CKSYS_TST_SEL_1__TST_SEL_1                                                ((volatile uint32_t *)(RM_CKSYS_BASE           +0x0224)) /* [31: 0], 32-bit, RW, Default 0x00000000 */
#define CKSYS_TST_SEL_2__TST_SEL_2                                                ((volatile uint32_t *)(RM_CKSYS_BASE           +0x0228)) /* [31: 0], 32-bit, RW, Default 0x00000000 */
#define CKSYS_CLK_UPDATE_STATUS_0__CHG_SYS_OK                                     ((volatile uint8_t  *)(RM_CKSYS_BASE           +0x0260)) /* [ 0: 0],  1-bit, RO, Default 0x0 */
#define CKSYS_CLK_UPDATE_STATUS_0__CHG_SFC_OK                                     ((volatile uint8_t  *)(RM_CKSYS_BASE           +0x0261)) /* [ 8: 8],  1-bit, RO, Default 0x0 */
#define CKSYS_CLK_UPDATE_STATUS_0__CHG_ESC_OK                                     ((volatile uint8_t  *)(RM_CKSYS_BASE           +0x0262)) /* [16:16],  1-bit, RO, Default 0x0 */
#define CKSYS_CLK_UPDATE_STATUS_0__CHG_IBEX_OK                                    ((volatile uint8_t  *)(RM_CKSYS_BASE           +0x0263)) /* [24:24],  1-bit, RO, Default 0x0 */
#define CKSYS_CLK_UPDATE_STATUS_1__CHG_SPIMST2_OK                                 ((volatile uint8_t  *)(RM_CKSYS_BASE           +0x0266)) /* [16:16],  1-bit, RO, Default 0x0 */
#define CKSYS_CLK_UPDATE_STATUS_1__CHG_SPISLV_OK                                  ((volatile uint8_t  *)(RM_CKSYS_BASE           +0x0267)) /* [24:24],  1-bit, RO, Default 0x0 */
#define CKSYS_CLK_UPDATE_STATUS_2__CHG_USB_OK                                     ((volatile uint8_t  *)(RM_CKSYS_BASE           +0x0268)) /* [ 0: 0],  1-bit, RO, Default 0x0 */
#define CKSYS_CLK_UPDATE_STATUS_2__CHG_I3C_OK                                     ((volatile uint8_t  *)(RM_CKSYS_BASE           +0x0269)) /* [ 8: 8],  1-bit, RO, Default 0x0 */
#define CKSYS_CLK_UPDATE_STATUS_2__CHG_BT_HOP_OK                                  ((volatile uint8_t  *)(RM_CKSYS_BASE           +0x026A)) /* [16:16],  1-bit, RO, Default 0x0 */
#define CKSYS_CLK_UPDATE_STATUS_2__CHG_AUD_INTBUS_OK                              ((volatile uint8_t  *)(RM_CKSYS_BASE           +0x026B)) /* [24:24],  1-bit, RO, Default 0x0 */
#define CKSYS_CLK_UPDATE_STATUS_3__CHG_IRTX_OK                                    ((volatile uint8_t  *)(RM_CKSYS_BASE           +0x026C)) /* [ 0: 0],  1-bit, RO, Default 0x0 */
#define CKSYS_REF_CLK_SEL__RG_TM_REF_CLK_SEL                                      ((volatile uint8_t  *)(RM_CKSYS_BASE           +0x02A0)) /* [ 0: 0],  1-bit, RW, Default 0x1 */
#define CKSYS_REF_CLK_SEL__RG_TM_RF_DIG_CLK_SEL                                   ((volatile uint8_t  *)(RM_CKSYS_BASE           +0x02A1)) /* [ 8: 8],  1-bit, RW, Default 0x0 */
#define CKSYS_REF_CLK_SEL__RG_TM_SARADC_CLK_SEL                                   ((volatile uint8_t  *)(RM_CKSYS_BASE           +0x02A2)) /* [16:16],  1-bit, RW, Default 0x0 */
#define PLL_ABIST_FQMTR_CON0__FQMTR_WINSET                                        ((volatile uint32_t *)(RM_CKSYS_BASE           +0x0400)) /* [20: 0], 21-bit, RW, Default 0x000000 */
#define PLL_ABIST_FQMTR_CON1__PLL_ABIST_FQMTR_CON1                                ((volatile uint16_t *)(RM_CKSYS_BASE           +0x0404)) /* [15: 0], 16-bit, RO, Default 0x0000 */
#define PLL_ABIST_FQMTR_CON1__FQMTR_EN                                            ((volatile uint8_t  *)(RM_CKSYS_BASE           +0x0406)) /* [16:16],  1-bit, RW, Default 0x0 */
#define PLL_ABIST_FQMTR_CON1__FQMTR_RST                                           ((volatile uint8_t  *)(RM_CKSYS_BASE           +0x0407)) /* [24:24],  1-bit, RW, Default 0x0 */
#define PLL_ABIST_FQMTR_CON2__FQMTR_CLKDIV_EN                                     ((volatile uint8_t  *)(RM_CKSYS_BASE           +0x0409)) /* [ 8: 8],  1-bit, RW, Default 0x0 */
#define PLL_ABIST_FQMTR_CON2__FQMTR_CLKDIV                                        ((volatile uint8_t  *)(RM_CKSYS_BASE           +0x0408)) /* [ 1: 0],  2-bit, RW, Default 0x0 */
#define PLL_ABIST_FQMTR_DATA__FQMTR_DATA                                          ((volatile uint32_t *)(RM_CKSYS_BASE           +0x040C)) /* [23: 0], 24-bit, RO, Default 0x000000 */

/*************************************************************************************
 * CKSYS_XO_CLK, 0x42040000, 2024-0925, Byte Boundary, only Define RG_Field Address
 *************************************************************************************/
#define XO_PDN_PD_COND0__XO_PDN_PD_COND0                                          ((volatile uint32_t *)(RM_CKSYS_XO_CLK_BASE    +0x0000)) /* [31: 0], 32-bit, RW, Default 0x0000FFFF */
#define XO_PDN_AO_COND0__XO_PDN_AO_COND0                                          ((volatile uint32_t *)(RM_CKSYS_XO_CLK_BASE    +0x0004)) /* [31: 0], 32-bit, RW, Default 0x0000FFFF */
#define XO_PDN_AO_COND1__XO_PDN_AO_COND1                                          ((volatile uint32_t *)(RM_CKSYS_XO_CLK_BASE    +0x0008)) /* [31: 0], 32-bit, RW, Default 0x0000FFFF */
#define XO_PDN_TOP_COND0__XO_PDN_TOP_COND0                                        ((volatile uint32_t *)(RM_CKSYS_XO_CLK_BASE    +0x000C)) /* [31: 0], 32-bit, RW, Default 0x0000FFFF */
#define XO_PDN_TOP_COND1__XO_PDN_TOP_COND1                                        ((volatile uint32_t *)(RM_CKSYS_XO_CLK_BASE    +0x0010)) /* [31: 0], 32-bit, RW, Default 0x0000FFFF */
#define XO_DCM_CON_0__RG_XO_PLLCK_SEL                                             ((volatile uint8_t  *)(RM_CKSYS_XO_CLK_BASE    +0x0017)) /* [24:24],  1-bit, RW, Default 0x0 */
#define XO_DCM_CON_0__RG_XO_DCM_DBC_EN                                            ((volatile uint8_t  *)(RM_CKSYS_XO_CLK_BASE    +0x0016)) /* [16:16],  1-bit, RW, Default 0x0 */
#define XO_DCM_CON_0__RG_XO_DCM_DBC_NUM                                           ((volatile uint8_t  *)(RM_CKSYS_XO_CLK_BASE    +0x0015)) /* [12: 8],  5-bit, RW, Default 0x00 */
#define XO_DCM_CON_0__RG_XO_SFSEL                                                 ((volatile uint8_t  *)(RM_CKSYS_XO_CLK_BASE    +0x0014)) /* [ 5: 0],  6-bit, RW, Default 0x02 */
#define XO_DCM_CON_1__RG_XO_FORCE_CLKSLOW                                         ((volatile uint8_t  *)(RM_CKSYS_XO_CLK_BASE    +0x001B)) /* [24:24],  1-bit, RW, Default 0x0 */
#define XO_DCM_CON_1__RG_XO_FORCE_CLKOFF                                          ((volatile uint8_t  *)(RM_CKSYS_XO_CLK_BASE    +0x001A)) /* [16:16],  1-bit, RW, Default 0x0 */
#define XO_DCM_CON_1__RG_XO_CLKSLOW_EN                                            ((volatile uint8_t  *)(RM_CKSYS_XO_CLK_BASE    +0x0019)) /* [ 8: 8],  1-bit, RW, Default 0x0 */
#define XO_DCM_CON_1__RG_XO_CLKOFF_EN                                             ((volatile uint8_t  *)(RM_CKSYS_XO_CLK_BASE    +0x0018)) /* [ 0: 0],  1-bit, RW, Default 0x0 */
#define SPM_CLK_SW_CON__RG_CM_FORCE_FAST_BAR                                      ((volatile uint8_t  *)(RM_CKSYS_XO_CLK_BASE    +0x001C)) /* [ 0: 0],  1-bit, RW, Default 0x1 */
#define XO_PDN_PD_WAKUP0__XO_PDN_PD_WAKUP0                                        ((volatile uint32_t *)(RM_CKSYS_XO_CLK_BASE    +0x0020)) /* [31: 0], 32-bit, RW, Default 0xFFFFFFFF */
#define XO_PDN_AO_WAKUP0__XO_PDN_AO_WAKUP0                                        ((volatile uint32_t *)(RM_CKSYS_XO_CLK_BASE    +0x0024)) /* [31: 0], 32-bit, RW, Default 0xFFFFFFFF */
#define XO_PDN_AO_WAKUP1__XO_PDN_AO_WAKUP1                                        ((volatile uint32_t *)(RM_CKSYS_XO_CLK_BASE    +0x0028)) /* [31: 0], 32-bit, RW, Default 0xFFFFFFFF */
#define XO_PDN_TOP_WAKUP0__XO_PDN_TOP_WAKUP0                                      ((volatile uint32_t *)(RM_CKSYS_XO_CLK_BASE    +0x002C)) /* [31: 0], 32-bit, RW, Default 0xFFFFFFFF */
#define XO_PDN_TOP_WAKUP1__XO_PDN_TOP_WAKUP1                                      ((volatile uint32_t *)(RM_CKSYS_XO_CLK_BASE    +0x0030)) /* [31: 0], 32-bit, RW, Default 0xFFFFFFFF */
#define XO_PDN_PD_SETD0__XO_PDN_PD_SETD0                                          ((volatile uint32_t *)(RM_CKSYS_XO_CLK_BASE    +0x0B10)) /* [31: 0], 32-bit, WO, Default 0x00000000 */
#define XO_PDN_PD_CLRD0__XO_PDN_PD_CLRD0                                          ((volatile uint32_t *)(RM_CKSYS_XO_CLK_BASE    +0x0B20)) /* [31: 0], 32-bit, WO, Default 0x00000000 */
#define XO_PDN_AO_SETD0__XO_PDN_AO_SETD0                                          ((volatile uint32_t *)(RM_CKSYS_XO_CLK_BASE    +0x0B40)) /* [31: 0], 32-bit, WO, Default 0x00000000 */
#define XO_PDN_AO_CLRD0__XO_PDN_AO_CLRD0                                          ((volatile uint32_t *)(RM_CKSYS_XO_CLK_BASE    +0x0B50)) /* [31: 0], 32-bit, WO, Default 0x00000000 */
#define XO_PDN_AO_SETD1__XO_PDN_AO_SETD1                                          ((volatile uint32_t *)(RM_CKSYS_XO_CLK_BASE    +0x0B44)) /* [31: 0], 32-bit, WO, Default 0x00000000 */
#define XO_PDN_AO_CLRD1__XO_PDN_AO_CLRD1                                          ((volatile uint32_t *)(RM_CKSYS_XO_CLK_BASE    +0x0B54)) /* [31: 0], 32-bit, WO, Default 0x00000000 */
#define XO_PDN_TOP_SETD0__XO_PDN_TOP_SETD0                                        ((volatile uint32_t *)(RM_CKSYS_XO_CLK_BASE    +0x0B70)) /* [31: 0], 32-bit, WO, Default 0x00000000 */
#define XO_PDN_TOP_CLRD0__XO_PDN_TOP_CLRD0                                        ((volatile uint32_t *)(RM_CKSYS_XO_CLK_BASE    +0x0B80)) /* [31: 0], 32-bit, WO, Default 0x00000000 */
#define XO_PDN_TOP_SETD1__XO_PDN_TOP_SETD1                                        ((volatile uint32_t *)(RM_CKSYS_XO_CLK_BASE    +0x0BA0)) /* [31: 0], 32-bit, WO, Default 0x00000000 */
#define XO_PDN_TOP_CLRD1__XO_PDN_TOP_CLRD1                                        ((volatile uint32_t *)(RM_CKSYS_XO_CLK_BASE    +0x0BB0)) /* [31: 0], 32-bit, WO, Default 0x00000000 */

/*************************************************************************************
 * MIXEDSYS_D, 0x42050000, 2024-1202, Byte Boundary, only Define RG_Field Address
 *************************************************************************************/
#define SSC1_CON0__LPOSC_FHCTL_EN                                                 ((volatile uint8_t  *)(RM_MIXEDSYS_D_BASE      +0x0000)) /* [ 0: 0],  1-bit, RW, Default 0x0 */
#define SSC1_CON0__LPOSC_SFSTR_EN                                                 ((volatile uint8_t  *)(RM_MIXEDSYS_D_BASE      +0x0001)) /* [ 8: 8],  1-bit, RW, Default 0x0 */
#define SSC1_CON0__LPOSC_FRSSC_EN                                                 ((volatile uint8_t  *)(RM_MIXEDSYS_D_BASE      +0x0002)) /* [16:16],  1-bit, RW, Default 0x0 */
#define SSC1_CON0__LPOSC_FHCTL_RST                                                ((volatile uint8_t  *)(RM_MIXEDSYS_D_BASE      +0x0003)) /* [24:24],  1-bit, RW, Default 0x0 */
#define SSC1_CON1__LPOSC_SFSTR_DTS                                                ((volatile uint8_t  *)(RM_MIXEDSYS_D_BASE      +0x0004)) /* [ 2: 0],  3-bit, RW, Default 0x0 */
#define SSC1_CON1__LPOSC_SFSTR_DYS                                                ((volatile uint8_t  *)(RM_MIXEDSYS_D_BASE      +0x0005)) /* [10: 8],  3-bit, RW, Default 0x0 */
#define SSC1_CON1__LPOSC_FRSSC_DTS                                                ((volatile uint8_t  *)(RM_MIXEDSYS_D_BASE      +0x0006)) /* [18:16],  3-bit, RW, Default 0x0 */
#define SSC1_CON1__LPOSC_FRSSC_DYS                                                ((volatile uint8_t  *)(RM_MIXEDSYS_D_BASE      +0x0007)) /* [26:24],  3-bit, RW, Default 0x0 */
#define SSC1_CON2__LPOSC_FHCTL_STATE                                              ((volatile uint8_t  *)(RM_MIXEDSYS_D_BASE      +0x0008)) /* [ 3: 0],  4-bit, RO, Default 0x0 */
#define SSC1_CON2__FRSSC_LPOSC_PRD                                                ((volatile uint8_t  *)(RM_MIXEDSYS_D_BASE      +0x0009)) /* [ 8: 8],  1-bit, RO, Default 0x0 */
#define SSC1_CON2__SFSTR_LPOSC_PRD                                                ((volatile uint8_t  *)(RM_MIXEDSYS_D_BASE      +0x000A)) /* [16:16],  1-bit, RO, Default 0x0 */
#define SSC1_CON3__LPOSC_FRSSC_UPLMT                                              ((volatile uint16_t *)(RM_MIXEDSYS_D_BASE      +0x000C)) /* [10: 0], 11-bit, RW, Default 0x000 */
#define SSC1_CON3__LPOSC_FRSSC_DNLMT                                              ((volatile uint16_t *)(RM_MIXEDSYS_D_BASE      +0x000E)) /* [26:16], 11-bit, RW, Default 0x000 */
#define SSC1_CON4__LPOSC_FREQ_STR                                                 ((volatile uint8_t  *)(RM_MIXEDSYS_D_BASE      +0x0010)) /* [ 0: 0],  1-bit, RW, Default 0x0 */
#define SSC1_CON4__LPOSC_FHSET                                                    ((volatile uint16_t *)(RM_MIXEDSYS_D_BASE      +0x0012)) /* [26:16], 11-bit, RW, Default 0x280 */
#define SSC1_CON5__LPOSC_SFSTR_DTS_CFG                                            ((volatile uint8_t  *)(RM_MIXEDSYS_D_BASE      +0x0014)) /* [ 7: 0],  8-bit, RW, Default 0x01 */
#define SSC1_CON5__LPOSC_SFSTR_DYS_CFG                                            ((volatile uint8_t  *)(RM_MIXEDSYS_D_BASE      +0x0015)) /* [15: 8],  8-bit, RW, Default 0x01 */
#define SSC1_CON5__LPOSC_FRSSC_DTS_CFG                                            ((volatile uint8_t  *)(RM_MIXEDSYS_D_BASE      +0x0016)) /* [23:16],  8-bit, RW, Default 0x01 */
#define SSC1_CON5__LPOSC_FRSSC_DYS_CFG                                            ((volatile uint8_t  *)(RM_MIXEDSYS_D_BASE      +0x0017)) /* [31:24],  8-bit, RW, Default 0x01 */
#define CLKSQ_CON0__BP_PLL_DLY                                                    ((volatile uint8_t  *)(RM_MIXEDSYS_D_BASE      +0x0018)) /* [ 0: 0],  1-bit, RW, Default 0x1 */
#define CLKSQ_CON0__LPOSC_EN_SEL                                                  ((volatile uint8_t  *)(RM_MIXEDSYS_D_BASE      +0x0019)) /* [ 8: 8],  1-bit, RW, Default 0x1 */
#define CLKSQ_CON0__LPOSC_CK_CG                                                   ((volatile uint8_t  *)(RM_MIXEDSYS_D_BASE      +0x001A)) /* [16:16],  1-bit, RW, Default 0x1 */
#define CLKSQ_CON0__LPOSC_FORCE_ON                                                ((volatile uint8_t  *)(RM_MIXEDSYS_D_BASE      +0x001B)) /* [24:24],  1-bit, RW, Default 0x0 */
#define CLKSQ_CON1__DA_LPOSC_EN                                                   ((volatile uint8_t  *)(RM_MIXEDSYS_D_BASE      +0x001C)) /* [ 0: 0],  1-bit, RW, Default 0x0 */
#define CLKSQ_CON1__RG_LPOSC_LS_RDY                                               ((volatile uint8_t  *)(RM_MIXEDSYS_D_BASE      +0x001D)) /* [ 8: 8],  1-bit, RW, Default 0x0 */
#define CLKSQ_CON1__RG_LPOSC_HS_RDY                                               ((volatile uint8_t  *)(RM_MIXEDSYS_D_BASE      +0x001E)) /* [16:16],  1-bit, RW, Default 0x0 */
#define CLKSQ_CON1__RG_LPOSC_DIV3_RDY                                             ((volatile uint8_t  *)(RM_MIXEDSYS_D_BASE      +0x001F)) /* [24:24],  1-bit, RW, Default 0x0 */
#define LPOSC1_CON0__DA_LPOSC_EN_OCC                                              ((volatile uint8_t  *)(RM_MIXEDSYS_D_BASE      +0x0200)) /* [ 0: 0],  1-bit, RW, Default 0x0 */
#define LPOSC1_CON0__RG_LPOSC_CBANK_HF_EN_OCC                                     ((volatile uint8_t  *)(RM_MIXEDSYS_D_BASE      +0x0201)) /* [ 8: 8],  1-bit, RW, Default 0x0 */
#define LPOSC1_CON0__RG_LPOSC_DIV3_CK_EN_OCC                                      ((volatile uint8_t  *)(RM_MIXEDSYS_D_BASE      +0x0202)) /* [16:16],  1-bit, RW, Default 0x0 */
#define LPOSC1_CON0__RG_LPOSC_DIV48_CK_EN_OCC                                     ((volatile uint8_t  *)(RM_MIXEDSYS_D_BASE      +0x0203)) /* [24:24],  1-bit, RW, Default 0x0 */
#define LPOSC1_CON1__DA_LPOSC_RBANK_FT_OCC                                        ((volatile uint8_t  *)(RM_MIXEDSYS_D_BASE      +0x0204)) /* [ 4: 0],  5-bit, RW, Default 0x0F */
#define LPOSC1_CON1__DA_LPOSC_RBANK_CALI_OCC                                      ((volatile uint8_t  *)(RM_MIXEDSYS_D_BASE      +0x0205)) /* [13: 8],  6-bit, RW, Default 0x2A */
#define LPOSC1_CON1__RG_LPOSC_BIAS_SEL_OCC                                        ((volatile uint8_t  *)(RM_MIXEDSYS_D_BASE      +0x0206)) /* [22:16],  7-bit, RW, Default 0x21 */
#define LPOSC1_CON2__RG_LPOSC_CBANK_SEL_OCC                                       ((volatile uint8_t  *)(RM_MIXEDSYS_D_BASE      +0x0208)) /* [ 3: 0],  4-bit, RW, Default 0xD */
#define LPOSC1_CON2__RG_LPOSC_AMP_CP_EN_OCC                                       ((volatile uint8_t  *)(RM_MIXEDSYS_D_BASE      +0x0209)) /* [ 8: 8],  1-bit, RW, Default 0x1 */
#define LPOSC1_CON2__RG_LPOSC_HFOSC_HF_EN_OCC                                     ((volatile uint8_t  *)(RM_MIXEDSYS_D_BASE      +0x020A)) /* [16:16],  1-bit, RW, Default 0x1 */
#define LPOSC1_CON3__RG_LPOSC_RSV                                                 ((volatile uint8_t  *)(RM_MIXEDSYS_D_BASE      +0x020C)) /* [ 7: 0],  8-bit, RW, Default 0x00 */
#define LPOSC1_CON3__RG_LPOSC_VINT_ATST_EN                                        ((volatile uint8_t  *)(RM_MIXEDSYS_D_BASE      +0x020D)) /* [ 8: 8],  1-bit, RW, Default 0x0 */
#define LPOSC1_CON3__RG_LPOSC_CK_ATST_EN                                          ((volatile uint8_t  *)(RM_MIXEDSYS_D_BASE      +0x020E)) /* [16:16],  1-bit, RW, Default 0x0 */
#define LPOSC1_CON3__RG_LPOSC_CK_ATST_MUX_SEL                                     ((volatile uint8_t  *)(RM_MIXEDSYS_D_BASE      +0x020F)) /* [25:24],  2-bit, RW, Default 0x0 */
#define LPOSC1_CON4__RG_HFOSC_HS_EN_OCC                                           ((volatile uint8_t  *)(RM_MIXEDSYS_D_BASE      +0x0210)) /* [ 0: 0],  1-bit, RW, Default 0x0 */
#define LPOSC1_CON4__RG_HFOSC_HS_SEL_OCC                                          ((volatile uint8_t  *)(RM_MIXEDSYS_D_BASE      +0x0211)) /* [ 9: 8],  2-bit, RW, Default 0x0 */
#define LPOSC1_CON4__RG_HFOSC_LS_EN_OCC                                           ((volatile uint8_t  *)(RM_MIXEDSYS_D_BASE      +0x0212)) /* [16:16],  1-bit, RW, Default 0x0 */
#define LPOSC1_CON4__RG_HFOSC_LS_SEL_OCC                                          ((volatile uint8_t  *)(RM_MIXEDSYS_D_BASE      +0x0213)) /* [25:24],  2-bit, RW, Default 0x1 */
#define LPOSC1_CON5__RG_SWMODE_SEL_EN                                             ((volatile uint8_t  *)(RM_MIXEDSYS_D_BASE      +0x0214)) /* [ 0: 0],  1-bit, RW, Default 0x0 */
#define LPOSC1_CON5__RG_HFOSC_EN_SW                                               ((volatile uint8_t  *)(RM_MIXEDSYS_D_BASE      +0x0215)) /* [ 8: 8],  1-bit, RW, Default 0x0 */
#define LPOSC1_CON5__RG_HFOSC_LS_EN_SW                                            ((volatile uint8_t  *)(RM_MIXEDSYS_D_BASE      +0x0216)) /* [16:16],  1-bit, RW, Default 0x0 */
#define LPOSC1_CON5__RG_HFOSC_HS_EN_SW                                            ((volatile uint8_t  *)(RM_MIXEDSYS_D_BASE      +0x0217)) /* [24:24],  1-bit, RW, Default 0x0 */
#define SYS_ABIST_MON_CON0__ABIST_MON_CHG                                         ((volatile uint8_t  *)(RM_MIXEDSYS_D_BASE      +0x0502)) /* [16:16],  1-bit, RW, Default 0x0 */
#define SYS_ABIST_MON_CON0__ABIST_MON_CFG                                         ((volatile uint8_t  *)(RM_MIXEDSYS_D_BASE      +0x0500)) /* [ 0: 0],  1-bit, RW, Default 0x0 */
#define SYS_ABIST_MON_CON1__ABIST_HMON_SEL                                        ((volatile uint8_t  *)(RM_MIXEDSYS_D_BASE      +0x0506)) /* [23:16],  8-bit, RW, Default 0x00 */
#define SYS_ABIST_MON_CON1__ABIST_LMON_SEL                                        ((volatile uint8_t  *)(RM_MIXEDSYS_D_BASE      +0x0504)) /* [ 7: 0],  8-bit, RW, Default 0x00 */
#define SYS_ABIST_MON_CON2__ABIST_HMON_OUT                                        ((volatile uint8_t  *)(RM_MIXEDSYS_D_BASE      +0x050A)) /* [19:16],  4-bit, RW, Default 0x0 */
#define SYS_ABIST_MON_CON2__ABIST_LMON_OUT                                        ((volatile uint8_t  *)(RM_MIXEDSYS_D_BASE      +0x0508)) /* [ 3: 0],  4-bit, RW, Default 0x0 */
#define ABIST_MON_DATA0__ABIST_HMON_DATA                                          ((volatile uint8_t  *)(RM_MIXEDSYS_D_BASE      +0x050E)) /* [19:16],  4-bit, RO, Default 0x0 */
#define ABIST_MON_DATA0__ABIST_LMON_DATA                                          ((volatile uint8_t  *)(RM_MIXEDSYS_D_BASE      +0x050C)) /* [ 3: 0],  4-bit, RO, Default 0x0 */
#define RSV_CON0__SCAN_RSV0                                                       ((volatile uint8_t  *)(RM_MIXEDSYS_D_BASE      +0x0510)) /* [ 7: 0],  8-bit, RW, Default 0x00 */

/*************************************************************************************
 * DCXO_PWR_CTRL, 0x42060000, 2024-1001, Byte Boundary, only Define RG_Field Address
 *************************************************************************************/
#define DCXO_PCON0__FRC_DCXO_PWR_ON                                               ((volatile uint8_t  *)(RM_DCXO_PWR_CTRL_BASE   +0x0003)) /* [24:24],  1-bit, RW, Default 0x0 */
#define DCXO_PCON0__FRC_BB32MCK_OFF                                               ((volatile uint8_t  *)(RM_DCXO_PWR_CTRL_BASE   +0x0002)) /* [16:16],  1-bit, RW, Default 0x0 */
#define DCXO_PCON0__DIS_DCXO_ISO_EN                                               ((volatile uint8_t  *)(RM_DCXO_PWR_CTRL_BASE   +0x0001)) /* [ 8: 8],  1-bit, RW, Default 0x0 */
#define DCXO_PCON0__GSM_DCXO_CTL_EN                                               ((volatile uint8_t  *)(RM_DCXO_PWR_CTRL_BASE   +0x0000)) /* [ 0: 0],  1-bit, RW, Default 0x0 */
#define DCXO_PCON1__EXT_DCXO_CTL_EN                                               ((volatile uint8_t  *)(RM_DCXO_PWR_CTRL_BASE   +0x0007)) /* [24:24],  1-bit, RW, Default 0x0 */
#define DCXO_PCON1__FRC_COCLK_EN                                                  ((volatile uint8_t  *)(RM_DCXO_PWR_CTRL_BASE   +0x0006)) /* [16:16],  1-bit, RW, Default 0x0 */
#define DCXO_PCON1__FRC_BB32MCK_EN                                                ((volatile uint8_t  *)(RM_DCXO_PWR_CTRL_BASE   +0x0005)) /* [ 8: 8],  1-bit, RW, Default 0x0 */
#define DCXO_PCON1__FRC_DCXO_F32M_RDY                                             ((volatile uint8_t  *)(RM_DCXO_PWR_CTRL_BASE   +0x0004)) /* [ 0: 0],  1-bit, RW, Default 0x0 */
#define DCXO_PCON2__FRC_GSM_SGLSTGE                                               ((volatile uint8_t  *)(RM_DCXO_PWR_CTRL_BASE   +0x000A)) /* [16:16],  1-bit, RW, Default 0x0 */
#define DCXO_PCON2__HW_COCLK_EN                                                   ((volatile uint8_t  *)(RM_DCXO_PWR_CTRL_BASE   +0x0009)) /* [ 8: 8],  1-bit, RW, Default 0x1 */
#define DCXO_PCON2__FRC_EXT_SGLSTGE                                               ((volatile uint8_t  *)(RM_DCXO_PWR_CTRL_BASE   +0x0008)) /* [ 0: 0],  1-bit, RW, Default 0x0 */
#define DCXO_PCON3__DCXO_EN_TD                                                    ((volatile uint8_t  *)(RM_DCXO_PWR_CTRL_BASE   +0x000F)) /* [31:24],  8-bit, RW, Default 0x01 */
#define DCXO_PCON3__DCXO_BUF_EN_TD                                                ((volatile uint8_t  *)(RM_DCXO_PWR_CTRL_BASE   +0x000E)) /* [23:16],  8-bit, RW, Default 0x7B */
#define DCXO_PCON3__DCXO_ISO_EN_TD                                                ((volatile uint8_t  *)(RM_DCXO_PWR_CTRL_BASE   +0x000D)) /* [15: 8],  8-bit, RW, Default 0x06 */
#define DCXO_PCON3__BG_EN_TD                                                      ((volatile uint8_t  *)(RM_DCXO_PWR_CTRL_BASE   +0x000C)) /* [ 0: 0],  1-bit, RW, Default 0x0 */
#define DCXO_PCON4__DCXO_32M_RDY_EN                                               ((volatile uint8_t  *)(RM_DCXO_PWR_CTRL_BASE   +0x0013)) /* [24:24],  1-bit, RW, Default 0x1 */
#define DCXO_PCON4__DCXO_SLEEP_TD                                                 ((volatile uint8_t  *)(RM_DCXO_PWR_CTRL_BASE   +0x0012)) /* [23:16],  8-bit, RW, Default 0x0A */
#define DCXO_PCON4__DCXO_PWR_EN_TD                                                ((volatile uint16_t *)(RM_DCXO_PWR_CTRL_BASE   +0x0010)) /* [ 8: 0],  9-bit, RW, Default 0x001 */
#define DCXO_PCON5__DCXO32K_EN                                                    ((volatile uint8_t  *)(RM_DCXO_PWR_CTRL_BASE   +0x0016)) /* [16:16],  1-bit, RW, Default 0x0 */
#define DCXO_PCON5__BT_32M_EN                                                     ((volatile uint8_t  *)(RM_DCXO_PWR_CTRL_BASE   +0x0015)) /* [ 8: 8],  1-bit, RW, Default 0x1 */
#define DCXO_PCON5__EN_32M_FPM                                                    ((volatile uint8_t  *)(RM_DCXO_PWR_CTRL_BASE   +0x0014)) /* [ 0: 0],  1-bit, RW, Default 0x1 */
#define DCXO_PCON6__DCXO_CAPID_EFUSE                                              ((volatile uint16_t *)(RM_DCXO_PWR_CTRL_BASE   +0x001A)) /* [24:16],  9-bit, RW, Default 0x1AF */
#define DCXO_PCON6__DCXO_CAPID_EFUSE_SEL                                          ((volatile uint8_t  *)(RM_DCXO_PWR_CTRL_BASE   +0x0018)) /* [ 0: 0],  1-bit, RW, Default 0x0 */
#define DCXO_PCON7__HI_CDAC_IBOOST_EN                                             ((volatile uint8_t  *)(RM_DCXO_PWR_CTRL_BASE   +0x001F)) /* [24:24],  1-bit, RW, Default 0x0 */
#define DCXO_PCON7__RG_DCXO_FPM_LDO_OFF_PULLDOWN                                  ((volatile uint8_t  *)(RM_DCXO_PWR_CTRL_BASE   +0x001E)) /* [16:16],  1-bit, RW, Default 0x1 */
#define DCXO_PCON7__DCXO_CK_RDY_COMP_VREF_DBB                                     ((volatile uint8_t  *)(RM_DCXO_PWR_CTRL_BASE   +0x001D)) /* [11: 8],  4-bit, RW, Default 0x8 */
#define DCXO_PCON7__DCXO_CK_RDY_COMP_VREF_SEL                                     ((volatile uint8_t  *)(RM_DCXO_PWR_CTRL_BASE   +0x001C)) /* [ 0: 0],  1-bit, RW, Default 0x0 */
#define DCXO_PCON8__USB_32M_EN                                                    ((volatile uint8_t  *)(RM_DCXO_PWR_CTRL_BASE   +0x002E)) /* [16:16],  1-bit, RW, Default 0x0 */
#define DCXO_PCON8__ABB_32M_EN                                                    ((volatile uint8_t  *)(RM_DCXO_PWR_CTRL_BASE   +0x002D)) /* [ 8: 8],  1-bit, RW, Default 0x0 */
#define DCXO_PCON8__DBL_64M_EN                                                    ((volatile uint8_t  *)(RM_DCXO_PWR_CTRL_BASE   +0x002C)) /* [ 0: 0],  1-bit, RW, Default 0x0 */
#define DCXO_PCON9__DCXO_CON_RSV                                                  ((volatile uint16_t *)(RM_DCXO_PWR_CTRL_BASE   +0x0030)) /* [11: 0], 12-bit, RW, Default 0x000 */
#define DCXO_PCON10__DCXO_DIG_WRAP_PWR_RSTB                                       ((volatile uint8_t  *)(RM_DCXO_PWR_CTRL_BASE   +0x0036)) /* [16:16],  1-bit, RW, Default 0x1 */
#define DCXO_PCON10__DCXO_DIG_WRAP_ISO_EN                                         ((volatile uint8_t  *)(RM_DCXO_PWR_CTRL_BASE   +0x0035)) /* [ 8: 8],  1-bit, RW, Default 0x0 */
#define DCXO_PCON10__DCXO_DIG_WRAP_PWR_ON                                         ((volatile uint8_t  *)(RM_DCXO_PWR_CTRL_BASE   +0x0034)) /* [ 0: 0],  1-bit, RW, Default 0x1 */
#define DCXO_PCON11__DCXO_BYPASS_HW_CON_RSV                                       ((volatile uint16_t *)(RM_DCXO_PWR_CTRL_BASE   +0x0038)) /* [11: 0], 12-bit, RW, Default 0x000 */
#define DCXO_RSV__REDUCE_COCLK_VARIATION_EN                                       ((volatile uint8_t  *)(RM_DCXO_PWR_CTRL_BASE   +0x0022)) /* [16:16],  1-bit, RW, Default 0x0 */
#define DCXO_RSV__DCXO_RSV                                                        ((volatile uint16_t *)(RM_DCXO_PWR_CTRL_BASE   +0x0020)) /* [15: 0], 16-bit, RW, Default 0xF000 */
#define DCXO_32KDIV__DCXO_1MDIV_COUNT                                             ((volatile uint8_t  *)(RM_DCXO_PWR_CTRL_BASE   +0x0027)) /* [28:24],  5-bit, RW, Default 0x0F */
#define DCXO_32KDIV__DCXO_32KDIV_SW_RSTB                                          ((volatile uint8_t  *)(RM_DCXO_PWR_CTRL_BASE   +0x0026)) /* [16:16],  1-bit, RW, Default 0x1 */
#define DCXO_32KDIV__DCXO_32KDIV_NFRAC                                            ((volatile uint16_t *)(RM_DCXO_PWR_CTRL_BASE   +0x0024)) /* [13: 0], 14-bit, RW, Default 0x2120 */
#define DCXO_COUNT__DIV32_1MCOUNT                                                 ((volatile uint16_t *)(RM_DCXO_PWR_CTRL_BASE   +0x002A)) /* [25:16], 10-bit, RW, Default 0x01E */
#define DCXO_CFG_RST__DCXO_CFG_SW_RSTB                                            ((volatile uint8_t  *)(RM_DCXO_PWR_CTRL_BASE   +0x003C)) /* [ 0: 0],  1-bit, RW, Default 0x0 */
#define DCXO_DBL_64M_RDY__DCXO_DBL_64M_RDY                                        ((volatile uint8_t  *)(RM_DCXO_PWR_CTRL_BASE   +0x0040)) /* [ 0: 0],  1-bit, RO, Default 0x0 */
#define DCXO_DEBUG0__DCXO_DEBUG_SEL                                               ((volatile uint8_t  *)(RM_DCXO_PWR_CTRL_BASE   +0x0102)) /* [20:16],  5-bit, RW, Default 0x00 */
#define DCXO_DEBUG0__DCXO_DEBUG_EN                                                ((volatile uint8_t  *)(RM_DCXO_PWR_CTRL_BASE   +0x0100)) /* [ 0: 0],  1-bit, RW, Default 0x0 */
#define DCXO_DEBUG1__DCXO_DEBUG_O                                                 ((volatile uint8_t  *)(RM_DCXO_PWR_CTRL_BASE   +0x0104)) /* [ 7: 0],  8-bit, RO, Default 0x00 */

/*************************************************************************************
 * RTC_DIG_MISC, 0x42107000, 2024-1021, Byte Boundary, only Define RG_Field Address
 *************************************************************************************/
#define RTC_LPOSC_CON0__LPOSC_CK_EN                                               ((volatile uint8_t  *)(RM_RTC_DIG_MISC_BASE    +0x0000)) /* [ 0: 0],  1-bit, RW, Default 0x0 */
#define RTC_LPOSC_CON0__LPOSC_DIV3_CK_EN                                          ((volatile uint8_t  *)(RM_RTC_DIG_MISC_BASE    +0x0001)) /* [ 8: 8],  1-bit, RW, Default 0x0 */
#define RTC_LPOSC_CON0__LPOSC_DIV48_CK_EN                                         ((volatile uint8_t  *)(RM_RTC_DIG_MISC_BASE    +0x0002)) /* [16:16],  1-bit, RW, Default 0x0 */
#define RTC_LPOSC_CON0__LPOSC_HFOSC_HF_EN                                         ((volatile uint8_t  *)(RM_RTC_DIG_MISC_BASE    +0x0003)) /* [24:24],  1-bit, RW, Default 0x1 */
#define RTC_LPOSC_CON1__LPOSC_HFOSC_CP_EN                                         ((volatile uint8_t  *)(RM_RTC_DIG_MISC_BASE    +0x0004)) /* [ 0: 0],  1-bit, RW, Default 0x1 */
#define RTC_LPOSC_CON1__LPOSC_HFOSC_LS_EN                                         ((volatile uint8_t  *)(RM_RTC_DIG_MISC_BASE    +0x0005)) /* [ 8: 8],  1-bit, RW, Default 0x0 */
#define RTC_LPOSC_CON1__LPOSC_HFOSC_HS_EN                                         ((volatile uint8_t  *)(RM_RTC_DIG_MISC_BASE    +0x0006)) /* [16:16],  1-bit, RW, Default 0x0 */
#define RTC_LPOSC_CON1__LPOSC_EXTEND_SLEEP_MODE                                   ((volatile uint8_t  *)(RM_RTC_DIG_MISC_BASE    +0x0007)) /* [24:24],  1-bit, RW, Default 0x0 */
#define RTC_LPOSC_CON2__LPOSC_RBANK_FT                                            ((volatile uint8_t  *)(RM_RTC_DIG_MISC_BASE    +0x0008)) /* [ 4: 0],  5-bit, RW, Default 0x0F */
#define RTC_LPOSC_CON2__LPOSC_RBANK_CALI                                          ((volatile uint8_t  *)(RM_RTC_DIG_MISC_BASE    +0x0009)) /* [13: 8],  6-bit, RW, Default 0x2E */
#define RTC_LPOSC_CON2__LPOSC_BIAS_SEL                                            ((volatile uint8_t  *)(RM_RTC_DIG_MISC_BASE    +0x000A)) /* [22:16],  7-bit, RW, Default 0x21 */
#define RTC_LPOSC_CON2__LPOSC_CBANK_SEL                                           ((volatile uint8_t  *)(RM_RTC_DIG_MISC_BASE    +0x000B)) /* [27:24],  4-bit, RW, Default 0xE */
#define RTC_LPOSC_CON3__LPOSC_HFOSC_LS_SEL                                        ((volatile uint8_t  *)(RM_RTC_DIG_MISC_BASE    +0x0010)) /* [ 1: 0],  2-bit, RW, Default 0x0 */
#define RTC_LPOSC_CON3__LPOSC_HFOSC_HS_SEL                                        ((volatile uint8_t  *)(RM_RTC_DIG_MISC_BASE    +0x0011)) /* [ 9: 8],  2-bit, RW, Default 0x0 */
#define RTC_LPOSC_CON3__LPOSC_SETTLE_TIME                                         ((volatile uint16_t *)(RM_RTC_DIG_MISC_BASE    +0x0012)) /* [24:16],  9-bit, RW, Default 0x080 */
#define RTC_LPOSC_CON4__CLK_SLOW_BUS_SEL                                          ((volatile uint8_t  *)(RM_RTC_DIG_MISC_BASE    +0x0014)) /* [ 0: 0],  1-bit, RW, Default 0x0 */
#define RTC_LPOSC_CON4__CLK_OSC_26M_SEL                                           ((volatile uint8_t  *)(RM_RTC_DIG_MISC_BASE    +0x0015)) /* [ 8: 8],  1-bit, RW, Default 0x0 */
#define RTC_LPOSC_CON4__CLK_SYS_SEL                                               ((volatile uint8_t  *)(RM_RTC_DIG_MISC_BASE    +0x0016)) /* [18:16],  3-bit, RW, Default 0x0 */
#define RTC_DCXO_CON0__RFLDO_RDY_CNT                                              ((volatile uint8_t  *)(RM_RTC_DIG_MISC_BASE    +0x0018)) /* [ 2: 0],  3-bit, RW, Default 0x2 */
#define RTC_DCXO_CON0__DCXO_RDY_CNT                                               ((volatile uint8_t  *)(RM_RTC_DIG_MISC_BASE    +0x0019)) /* [11: 8],  4-bit, RW, Default 0xF */
#define RTC_DCXO_CON0__BG_RDY_CNT                                                 ((volatile uint8_t  *)(RM_RTC_DIG_MISC_BASE    +0x001A)) /* [16:16],  1-bit, RW, Default 0x0 */
#define RTC_DCXO_CON0__DCXO_BB_RDY_CNT                                            ((volatile uint8_t  *)(RM_RTC_DIG_MISC_BASE    +0x001B)) /* [25:24],  2-bit, RW, Default 0x1 */
#define RTC_DCXO_CON1__RFLDO_FC_OFF                                               ((volatile uint8_t  *)(RM_RTC_DIG_MISC_BASE    +0x001C)) /* [ 0: 0],  1-bit, RW, Default 0x0 */
#define RTC_DCXO_CON1__DCXO_FPM_LDO_VOUT                                          ((volatile uint8_t  *)(RM_RTC_DIG_MISC_BASE    +0x001D)) /* [10: 8],  3-bit, RW, Default 0x3 */
#define RTC_DCXO_CON1__DCXO_CORE_ISEL_INIT                                        ((volatile uint8_t  *)(RM_RTC_DIG_MISC_BASE    +0x001E)) /* [19:16],  4-bit, RW, Default 0xD */
#define RTC_DCXO_CON1__DCXO_CORE_ISEL_RDY                                         ((volatile uint8_t  *)(RM_RTC_DIG_MISC_BASE    +0x001F)) /* [27:24],  4-bit, RW, Default 0xC */
#define RTC_DCXO_CON2__DCXO_CDAC_INIT                                             ((volatile uint16_t *)(RM_RTC_DIG_MISC_BASE    +0x0020)) /* [ 8: 0],  9-bit, RW, Default 0x032 */
#define RTC_DCXO_CON2__DCXO_CDAC_RDY                                              ((volatile uint16_t *)(RM_RTC_DIG_MISC_BASE    +0x0022)) /* [24:16],  9-bit, RW, Default 0x086 */
#define RTC_DCXO_CON3__VREF_SEL                                                   ((volatile uint8_t  *)(RM_RTC_DIG_MISC_BASE    +0x0024)) /* [ 4: 0],  5-bit, RW, Default 0x0F */
#define RTC_DCXO_CON3__DCXO_LDO_VREF_SEL                                          ((volatile uint8_t  *)(RM_RTC_DIG_MISC_BASE    +0x0025)) /* [11: 8],  4-bit, RW, Default 0x8 */
#define RTC_DCXO_CON3__SOFTSTART_SEL                                              ((volatile uint8_t  *)(RM_RTC_DIG_MISC_BASE    +0x0026)) /* [17:16],  2-bit, RW, Default 0x0 */
#define RTC_DCXO_CON3__RFLDO_SOFTSTART_EN                                         ((volatile uint8_t  *)(RM_RTC_DIG_MISC_BASE    +0x0027)) /* [24:24],  1-bit, RW, Default 0x0 */
#define RTC_DCXO_CON4__DCXO_CK_RDY_COMP_VREF                                      ((volatile uint8_t  *)(RM_RTC_DIG_MISC_BASE    +0x0028)) /* [ 3: 0],  4-bit, RW, Default 0x4 */
#define RTC_DCXO_CON4__DBL_64M_EN                                                 ((volatile uint8_t  *)(RM_RTC_DIG_MISC_BASE    +0x0029)) /* [ 8: 8],  1-bit, RW, Default 0x0 */
#define RTC_DCXO_CON4__DCXO_32M_RDY_EN                                            ((volatile uint8_t  *)(RM_RTC_DIG_MISC_BASE    +0x002A)) /* [16:16],  1-bit, RW, Default 0x0 */
#define RTC_DCXO_CON4__DCXO_RFLDO_BYPASS_EN                                       ((volatile uint8_t  *)(RM_RTC_DIG_MISC_BASE    +0x002B)) /* [25:24],  2-bit, RW, Default 0x1 */
#define SPM_BARE_ADDR__BACKUP_RESTORE_INSTRUCTION_ADDR                            ((volatile uint32_t *)(RM_RTC_DIG_MISC_BASE    +0x0030)) /* [31: 0], 32-bit, RW, Default 0x00000000 */
#define SPM_BARE_DUMMY__DUMMY_BACKUP_RESTORE                                      ((volatile uint32_t *)(RM_RTC_DIG_MISC_BASE    +0x0034)) /* [31: 0], 32-bit, RW, Default 0x00000000 */
#define RTC_DEBUG__DEBUG_EN                                                       ((volatile uint8_t  *)(RM_RTC_DIG_MISC_BASE    +0x0038)) /* [ 0: 0],  1-bit, RW, Default 0x0 */
#define RTC_DEBUG__DEBUG_SEL                                                      ((volatile uint8_t  *)(RM_RTC_DIG_MISC_BASE    +0x0039)) /* [10: 8],  3-bit, RW, Default 0x0 */
#define RTC_DIG_RSV0__RTC_DIG_RSV0                                                ((volatile uint16_t *)(RM_RTC_DIG_MISC_BASE    +0x0040)) /* [15: 0], 16-bit, RW, Default 0xFF00 */
#define RTC_DIG_RSV1__RTC_DIG_RSV1                                                ((volatile uint16_t *)(RM_RTC_DIG_MISC_BASE    +0x0044)) /* [15: 0], 16-bit, RW, Default 0xFF00 */

/*************************************************************************************
 * CKSYS_BUS_CLK, 0x422D0000, 2024-0925, Byte Boundary, only Define RG_Field Address
 *************************************************************************************/
#define BUS_DCM_CON_0__RG_BUS_PLLCK_SEL                                           ((volatile uint8_t  *)(RM_CKSYS_BUS_CLK_BASE   +0x0003)) /* [24:24],  1-bit, RW, Default 0x0 */
#define BUS_DCM_CON_0__RG_BUS_DCM_DBC_EN                                          ((volatile uint8_t  *)(RM_CKSYS_BUS_CLK_BASE   +0x0002)) /* [16:16],  1-bit, RW, Default 0x0 */
#define BUS_DCM_CON_0__RG_BUS_DCM_DBC_NUM                                         ((volatile uint8_t  *)(RM_CKSYS_BUS_CLK_BASE   +0x0001)) /* [12: 8],  5-bit, RW, Default 0x00 */
#define BUS_DCM_CON_0__RG_BUS_SFSEL                                               ((volatile uint8_t  *)(RM_CKSYS_BUS_CLK_BASE   +0x0000)) /* [ 5: 0],  6-bit, RW, Default 0x00 */
#define BUS_DCM_CON_1__RG_BUS_FORCE_CLKSLOW                                       ((volatile uint8_t  *)(RM_CKSYS_BUS_CLK_BASE   +0x0007)) /* [24:24],  1-bit, RW, Default 0x0 */
#define BUS_DCM_CON_1__RG_BUS_FORCE_CLKOFF                                        ((volatile uint8_t  *)(RM_CKSYS_BUS_CLK_BASE   +0x0006)) /* [16:16],  1-bit, RW, Default 0x0 */
#define BUS_DCM_CON_1__RG_BUS_CLKSLOW_EN                                          ((volatile uint8_t  *)(RM_CKSYS_BUS_CLK_BASE   +0x0005)) /* [ 8: 8],  1-bit, RW, Default 0x0 */
#define BUS_DCM_CON_1__RG_BUS_CLKOFF_EN                                           ((volatile uint8_t  *)(RM_CKSYS_BUS_CLK_BASE   +0x0004)) /* [ 0: 0],  1-bit, RW, Default 0x0 */
#define CMSYS_DCM_CON_0__RG_CM_PLLCK_SEL                                          ((volatile uint8_t  *)(RM_CKSYS_BUS_CLK_BASE   +0x000B)) /* [24:24],  1-bit, RW, Default 0x1 */
#define CMSYS_DCM_CON_0__RG_CM_DCM_DBC_EN                                         ((volatile uint8_t  *)(RM_CKSYS_BUS_CLK_BASE   +0x000A)) /* [16:16],  1-bit, RW, Default 0x0 */
#define CMSYS_DCM_CON_0__RG_CM_DCM_DBC_NUM                                        ((volatile uint8_t  *)(RM_CKSYS_BUS_CLK_BASE   +0x0009)) /* [12: 8],  5-bit, RW, Default 0x00 */
#define CMSYS_DCM_CON_0__RG_CM_SFSEL                                              ((volatile uint8_t  *)(RM_CKSYS_BUS_CLK_BASE   +0x0008)) /* [ 5: 0],  6-bit, RW, Default 0x00 */
#define CMSYS_DCM_CON_1__RG_CM_FORCE_CLKSLOW                                      ((volatile uint8_t  *)(RM_CKSYS_BUS_CLK_BASE   +0x000F)) /* [24:24],  1-bit, RW, Default 0x0 */
#define CMSYS_DCM_CON_1__RG_CM_FORCE_CLKOFF                                       ((volatile uint8_t  *)(RM_CKSYS_BUS_CLK_BASE   +0x000E)) /* [16:16],  1-bit, RW, Default 0x0 */
#define CMSYS_DCM_CON_1__RG_CM_CLKSLOW_EN                                         ((volatile uint8_t  *)(RM_CKSYS_BUS_CLK_BASE   +0x000D)) /* [ 8: 8],  1-bit, RW, Default 0x0 */
#define MEMSYS_DCM_CON_0__RG_MEMSYS_PLLCK_SEL                                     ((volatile uint8_t  *)(RM_CKSYS_BUS_CLK_BASE   +0x0013)) /* [24:24],  1-bit, RW, Default 0x1 */
#define MEMSYS_DCM_CON_0__RG_MEMSYS_DCM_DBC_EN                                    ((volatile uint8_t  *)(RM_CKSYS_BUS_CLK_BASE   +0x0012)) /* [16:16],  1-bit, RW, Default 0x0 */
#define MEMSYS_DCM_CON_0__RG_MEMSYS_DCM_DBC_NUM                                   ((volatile uint8_t  *)(RM_CKSYS_BUS_CLK_BASE   +0x0011)) /* [12: 8],  5-bit, RW, Default 0x00 */
#define MEMSYS_DCM_CON_0__RG_MEMSYS_SFSEL                                         ((volatile uint8_t  *)(RM_CKSYS_BUS_CLK_BASE   +0x0010)) /* [ 5: 0],  6-bit, RW, Default 0x00 */
#define MEMSYS_DCM_CON_1__RG_MEMSYS_FORCE_CLKSLOW                                 ((volatile uint8_t  *)(RM_CKSYS_BUS_CLK_BASE   +0x0017)) /* [24:24],  1-bit, RW, Default 0x0 */
#define MEMSYS_DCM_CON_1__RG_MEMSYS_FORCE_CLKOFF                                  ((volatile uint8_t  *)(RM_CKSYS_BUS_CLK_BASE   +0x0016)) /* [16:16],  1-bit, RW, Default 0x0 */
#define MEMSYS_DCM_CON_1__RG_MEMSYS_CLKOFF_EN                                     ((volatile uint8_t  *)(RM_CKSYS_BUS_CLK_BASE   +0x0014)) /* [ 0: 0],  1-bit, RW, Default 0x0 */
#define CLOCK_SEL0__RG_UART0_BCLK_SEL                                             ((volatile uint8_t  *)(RM_CKSYS_BUS_CLK_BASE   +0x0018)) /* [ 1: 0],  2-bit, RW, Default 0x0 */
#define CLOCK_SEL0__RG_UART1_BCLK_SEL                                             ((volatile uint8_t  *)(RM_CKSYS_BUS_CLK_BASE   +0x0019)) /* [ 9: 8],  2-bit, RW, Default 0x0 */
#define CLOCK_SEL0__RG_UART2_BCLK_SEL                                             ((volatile uint8_t  *)(RM_CKSYS_BUS_CLK_BASE   +0x001A)) /* [17:16],  2-bit, RW, Default 0x0 */
#define CLOCK_SEL0__RG_IRRX_BCLK_SEL                                              ((volatile uint8_t  *)(RM_CKSYS_BUS_CLK_BASE   +0x001B)) /* [24:24],  1-bit, RW, Default 0x0 */
#define CLOCK_SEL1__RG_GPT_BCLK_SEL                                               ((volatile uint8_t  *)(RM_CKSYS_BUS_CLK_BASE   +0x001C)) /* [ 0: 0],  1-bit, RW, Default 0x0 */
#define CLOCK_SEL1__RG_OSGPT_BCLK_SEL                                             ((volatile uint8_t  *)(RM_CKSYS_BUS_CLK_BASE   +0x001D)) /* [ 8: 8],  1-bit, RW, Default 0x0 */
#define CLOCK_SEL1__RG_SEC_GPT_BCLK_SEL                                           ((volatile uint8_t  *)(RM_CKSYS_BUS_CLK_BASE   +0x001E)) /* [16:16],  1-bit, RW, Default 0x0 */
#define PDN_PD_COND0__PDN_PD_COND0                                                ((volatile uint32_t *)(RM_CKSYS_BUS_CLK_BASE   +0x0020)) /* [31: 0], 32-bit, RW, Default 0x0000FFFF */
#define PDN_AO_COND0__PDN_AO_COND0                                                ((volatile uint32_t *)(RM_CKSYS_BUS_CLK_BASE   +0x0024)) /* [31: 0], 32-bit, RW, Default 0x0000FFFF */
#define PDN_TOP_COND0__PDN_TOP_COND0                                              ((volatile uint32_t *)(RM_CKSYS_BUS_CLK_BASE   +0x0028)) /* [31: 0], 32-bit, RW, Default 0x0000FFFF */
#define PDN_PD_WAKUP0__PDN_PD_WAKUP0                                              ((volatile uint32_t *)(RM_CKSYS_BUS_CLK_BASE   +0x002C)) /* [31: 0], 32-bit, RW, Default 0xFFFFFFFF */
#define PDN_AO_WAKUP0__PDN_AO_WAKUP0                                              ((volatile uint32_t *)(RM_CKSYS_BUS_CLK_BASE   +0x0030)) /* [31: 0], 32-bit, RW, Default 0xFFFFFFFF */
#define PDN_TOP_WAKUP0__PDN_TOP_WAKUP0                                            ((volatile uint32_t *)(RM_CKSYS_BUS_CLK_BASE   +0x0034)) /* [31: 0], 32-bit, RW, Default 0xFFFFFFFF */
#define PDN_PD_SETD0__PDN_PD_SETD0                                                ((volatile uint32_t *)(RM_CKSYS_BUS_CLK_BASE   +0x0310)) /* [31: 0], 32-bit, WO, Default 0x00000000 */
#define PDN_PD_CLRD0__PDN_PD_CLRD0                                                ((volatile uint32_t *)(RM_CKSYS_BUS_CLK_BASE   +0x0320)) /* [31: 0], 32-bit, WO, Default 0x00000000 */
#define PDN_AO_SETD0__PDN_AO_SETD0                                                ((volatile uint32_t *)(RM_CKSYS_BUS_CLK_BASE   +0x0340)) /* [31: 0], 32-bit, WO, Default 0x00000000 */
#define PDN_AO_CLRD0__PDN_AO_CLRD0                                                ((volatile uint32_t *)(RM_CKSYS_BUS_CLK_BASE   +0x0350)) /* [31: 0], 32-bit, WO, Default 0x00000000 */
#define PDN_TOP_SETD0__PDN_TOP_SETD0                                              ((volatile uint32_t *)(RM_CKSYS_BUS_CLK_BASE   +0x0370)) /* [31: 0], 32-bit, WO, Default 0x00000000 */
#define PDN_TOP_CLRD0__PDN_TOP_CLRD0                                              ((volatile uint32_t *)(RM_CKSYS_BUS_CLK_BASE   +0x0380)) /* [31: 0], 32-bit, WO, Default 0x00000000 */

/*####################################################################################
 * !!! Auto Generated Code End !!!
 *************************************************************************************/

#endif /* HAL_CLOCK_MODULE_ENABLED */
#endif /* __HAL_CLOCK_PLATFORM_H__ */
