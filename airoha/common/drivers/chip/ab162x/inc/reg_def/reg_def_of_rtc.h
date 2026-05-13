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

#ifndef __RTC_REG_DEFINITION_H__
#define __RTC_REG_DEFINITION_H__


#include <stdint.h>


/************************ RTC register definition start line  *******************************
 */

typedef union {
    struct {
        __IO uint32_t EOSC1_CHOP_EN       : 1;
        __IO uint32_t EOSC1_CALI          : 5;
        __IO uint32_t EOSC1_FST_EN        : 2;
        __IO uint32_t EOSC1_LPD_BIAS_RDY  : 1;
        __IO uint32_t EOSC1_LPD_EN        : 1;
        __IO uint32_t EOSC1_LPD_RST       : 1;
        __IO uint32_t EOSC1_STR_ENB       : 1;
        __IO uint32_t EOSC1_VCT_EN        : 1;
        __I uint32_t __RESERVED_00        : 3;
        __IO uint32_t EOSC2_BIAS_CT0      : 1;
        __IO uint32_t EOSC2_BIAS_CT1      : 1;
        __IO uint32_t EOSC2_BIAS_DN       : 2;
        __IO uint32_t EOSC2_CALI          : 5;
        __IO uint32_t EOSC2_FRWQ_CT0      : 1;
        __IO uint32_t EOSC2_FRWQ_CT1      : 1;
        __IO uint32_t EOSC_EN             : 1;
        __I uint32_t __RESERVED_01        : 4;
    } field;
    __IO uint32_t word;
} RTC_OSC32CON0_T;

typedef union {
    struct {
        __IO uint32_t XOSC_QI_PWDB       : 1;
        __IO uint32_t XOSC_AMP_EN        : 1;
        __IO uint32_t XOSC_CALI          : 4;
        __IO uint32_t XOSC_CGM_LP_EN     : 1;
        __IO uint32_t XOSC_CGM_STR_ENB   : 1;
        __IO uint32_t XOSC_LPMODEB       : 1;
        __IO uint32_t XOSC_SW_EN         : 1;
        __IO uint32_t XOSC_AC_ON         : 1;
        __IO uint32_t XOSC_CAP           : 3;
        __IO uint32_t XOSC_DMY           : 4;
        __IO uint32_t XOSC_DMY_EN        : 1;
        __IO uint32_t RFB_BYPASS         : 1;
        __IO uint32_t XOSC_ULP_EN        : 1;
        __I uint32_t __RESERVED_00       : 11;
    } field;
    __IO uint32_t word;
} RTC_OSC32CON1_T;

typedef union {
    struct {
        __I uint32_t  __RESERVED_00       : 16;
        __IO uint32_t F32K_SEL            : 2;
        __I uint32_t  __RESERVED_01       : 6;
        __IO uint32_t SYS32K_SRC_SEL      : 1;
        __I uint32_t  __RESERVED_02       : 7;
    } field;
    __IO uint32_t word;
} RTC_OSC32CON2_T;

typedef union {
    struct {
        __IO uint32_t  DBG_SEL           : 3;
        __I uint32_t  __RESERVED_00      : 4;
        __IO uint32_t  DGB_EN            : 1;
        __I uint32_t  __RESERVED_01      : 8;
        __I uint32_t  OUTPUT             : 16;
    } field;
    __IO uint32_t word;
} RTC_DEBUG_CON_T;

typedef union {
    struct {
        __I uint32_t  __RESERVED_00      : 16;
        __IO uint32_t  F32K_SEL          : 2;
        __I uint32_t  __RESERVED_01      : 6;
        __IO uint32_t  SYS32K_SEL        : 1;
        __I uint32_t  __RESERVED_02      : 7;
    } field;
    __IO uint32_t word;
} RTC_SYS32K_CG_CON_T;

#define RTC_OSC32CON_MAX 3
#define RTC_SPAR_MAX 3
typedef struct {
    union {
        struct {
            __IO uint32_t RTC_OSC32CON0;        /* Address offset: 0x00 */
            __IO uint32_t RTC_OSC32CON1;        /* Address offset: 0x04 */
            __IO uint32_t RTC_OSC32CON2;        /* Address offset: 0x08 */
        };
        __IO uint32_t RTC_OSC32CON[RTC_OSC32CON_MAX];
    };
    __IO uint32_t RTC_DEBUG_CON;                /* Address offset: 0x0C */
    __IO uint32_t RTC_SPAR_REG;                 /* Address offset: 0x10 */
    union {
        struct {
            __IO uint32_t RTC_SPAR0;            /* Address offset: 0x14 */
            __IO uint32_t RTC_SPAR1;            /* Address offset: 0x18 */
            __IO uint32_t RTC_SPAR2;            /* Address offset: 0x1C */
        };
        __IO uint32_t RTC_SPAR[RTC_SPAR_MAX];
    };

    __IO uint32_t RTC_SYS32K_CG_CON;    /* Address offset: 0x20 */
} RTC_32K_REGISTER_T;

/*RTC_OSC32CON0 Register*/
#define     RTC_OSC32CON0_EOSC1_CHOP_EN_OFFSET      (0)
#define     RTC_OSC32CON0_EOSC1_CALI_OFFSET         (1)
#define     RTC_OSC32CON0_EOSC1_FST_EN_OFFSET       (6)
#define     RTC_OSC32CON0_EOSC1_LPD_BIAS_RDY_OFFSET (8)
#define     RTC_OSC32CON0_EOSC1_LPD_EN_OFFSET       (9)
#define     RTC_OSC32CON0_EOSC1_LPD_RST_OFFSET      (10)
#define     RTC_OSC32CON0_EOSC1_STR_ENB_OFFSET      (11)
#define     RTC_OSC32CON0_EOSC1_VCT_EN_OFFSET       (12)
#define     RTC_OSC32CON0_EOSC2_BIAS_CT0_OFFSET     (16)
#define     RTC_OSC32CON0_EOSC2_BIAS_CT1_OFFSET     (17)
#define     RTC_OSC32CON0_EOSC2_BIAS_DN_OFFSET      (18)
#define     RTC_OSC32CON0_EOSC2_CALI_OFFSET         (20)
#define     RTC_OSC32CON0_EOSC2_FREQ_CT0_OFFSET     (25)
#define     RTC_OSC32CON0_EOSC2_FREQ_CT1_OFFSET     (26)
#define     RTC_OSC32CON0_EOSC_EN_OFFSET            (27)
#define     RTC_OSC32CON0_EOSC1_CHOP_EN_MASK       (0x01 << RTC_OSC32CON0_EOSC1_CHOP_EN_OFFSET)
#define     RTC_OSC32CON0_EOSC1_CALI_MASK          (0x1F << RTC_OSC32CON0_EOSC1_CALI_OFFSET)
#define     RTC_OSC32CON0_EOSC1_FST_EN_MASK        (0x03 << RTC_OSC32CON0_EOSC1_FST_EN_OFFSET)
#define     RTC_OSC32CON0_EOSC1_LPD_BIAS_RDY_MASK  (0x01 << RTC_OSC32CON0_EOSC1_LPD_BIAS_RDY_OFFSET)
#define     RTC_OSC32CON0_EOSC1_LPD_EN_MASK        (0x01 << RTC_OSC32CON0_EOSC1_LPD_EN_OFFSET)
#define     RTC_OSC32CON0_EOSC1_LPD_RST_MASK       (0x01 << RTC_OSC32CON0_EOSC1_LPD_RST_OFFSET)
#define     RTC_OSC32CON0_EOSC1_STR_ENB_MASK       (0x01 << RTC_OSC32CON0_EOSC1_STR_ENB_OFFSET)
#define     RTC_OSC32CON0_EOSC1_VCT_EN_MASK        (0x01 << RTC_OSC32CON0_EOSC1_VCT_EN_OFFSET)
#define     RTC_OSC32CON0_EOSC2_BIAS_CT0_MASK      (0x01 << RTC_OSC32CON0_EOSC2_BIAS_CT0_OFFSET)
#define     RTC_OSC32CON0_EOSC2_BIAS_CT1_MASK      (0x01 << RTC_OSC32CON0_EOSC2_BIAS_CT1_OFFSET)
#define     RTC_OSC32CON0_EOSC2_BIAS_DN_MASK       (0x03 << RTC_OSC32CON0_EOSC2_BIAS_DN_OFFSET)
#define     RTC_OSC32CON0_EOSC2_CALI_MASK          (0x1F << RTC_OSC32CON0_EOSC2_CALI_OFFSET)
#define     RTC_OSC32CON0_EOSC2_FREQ_CT0_MASK      (0x01 << RTC_OSC32CON0_EOSC2_FREQ_CT0_OFFSET)
#define     RTC_OSC32CON0_EOSC2_FREQ_CT1_MASK      (0x01 << RTC_OSC32CON0_EOSC2_FREQ_CT1_OFFSET)
#define     RTC_OSC32CON0_EOSC_EN_MASK             (0x01 << RTC_OSC32CON0_EOSC_EN_OFFSET)

/*RTC_OSC32CON1 Register*/
#define     RTC_OSC32CON1_XOSC_QI_PWDB_OFFSET       (0)
#define     RTC_OSC32CON1_XOSC_AMP_EN_OFFSET        (1)
#define     RTC_OSC32CON1_XOSC_CALI_OFFSET          (2)
#define     RTC_OSC32CON1_XOSC_CGM_LP_EN_OFFSET     (6)
#define     RTC_OSC32CON1_XOSC_CGM_STR_ENB_OFFSET   (7)
#define     RTC_OSC32CON1_XOSC_LPMODEB_OFFSET       (8)
#define     RTC_OSC32CON1_XOSC_SW_EN_OFFSET         (9)
#define     RTC_OSC32CON1_XOSC_AC_ON_OFFSET         (10)
#define     RTC_OSC32CON1_XOSC_CAP_OFFSET           (11)
#define     RTC_OSC32CON1_XOSC_DMY_OFFSET           (14)
#define     RTC_OSC32CON1_XOSC_DMY_EN_OFFSET        (18)
#define     RTC_OSC32CON1_RFB_BYPASS_OFFSET         (19)
#define     RTC_OSC32CON1_XOSC_ULP_EN_OFFSET        (20)
#define     RTC_OSC32CON1_XOSC_QI_PWDB_MASK         (0x01 << RTC_OSC32CON1_XOSC_QI_PWDB_OFFSET)
#define     RTC_OSC32CON1_XOSC_AMP_EN_MASK          (0x01 << RTC_OSC32CON1_XOSC_AMP_EN_OFFSET)
#define     RTC_OSC32CON1_XOSC_CALI_MASK            (0x0F << RTC_OSC32CON1_XOSC_CALI_OFFSET)
#define     RTC_OSC32CON1_XOSC_CGM_LP_EN_MASK       (0x01 << RTC_OSC32CON1_XOSC_CGM_LP_EN_OFFSET)
#define     RTC_OSC32CON1_XOSC_CGM_STR_ENB_MASK     (0x01 << RTC_OSC32CON1_XOSC_CGM_STR_ENB_OFFSET)
#define     RTC_OSC32CON1_XOSC_LPMODEB_MASK         (0x01 << RTC_OSC32CON1_XOSC_LPMODEB_OFFSET)
#define     RTC_OSC32CON1_XOSC_SW_EN_MASK           (0x01 << RTC_OSC32CON1_XOSC_SW_EN_OFFSET)
#define     RTC_OSC32CON1_XOSC_AC_ON_MASK           (0x01 << RTC_OSC32CON1_XOSC_AC_ON_OFFSET)
#define     RTC_OSC32CON1_XOSC_CAP_MASK             (0x07 << RTC_OSC32CON1_XOSC_CAP_OFFSET)
#define     RTC_OSC32CON1_XOSC_DMY_MASK             (0x0F << RTC_OSC32CON1_XOSC_DMY_OFFSET)
#define     RTC_OSC32CON1_XOSC_DMY_EN_MASK          (0x01 << RTC_OSC32CON1_XOSC_DMY_EN_OFFSET)
#define     RTC_OSC32CON1_RFB_BYPASS_MASK           (0x01 << RTC_OSC32CON1_RFB_BYPASS_OFFSET)
#define     RTC_OSC32CON1_XOSC_ULP_EN_MASK          (0x01 << RTC_OSC32CON1_XOSC_ULP_EN_OFFSET)
/*RTC_OSC32CON2 Register*/
#define     RTC_OSC32CON2_F32K_SEL_EOSC                     (0x1)
#define     RTC_OSC32CON2_F32K_SEL_DCXO_AO_EOSC             (0x0)
#define     RTC_OSC32CON2_F32K_SEL_DCXO_AO_XOSC             (0x2)
#define     RTC_OSC32CON2_F32K_SEL_XOSC                     (0x3)
#define     RTC_OSC32CON2_F32K_SEL_OFFSET                   (16)
#define     RTC_OSC32CON2_SYS32K_SRC_SEL_OFFSET             (24)
#define     RTC_OSC32CON2_F32K_SEL_EOSC_MASK                (RTC_OSC32CON2_F32K_SEL_EOSC << RTC_OSC32CON2_F32K_SEL_OFFSET)
#define     RTC_OSC32CON2_F32K_SEL_XOSC_MASK                (RTC_OSC32CON2_F32K_SEL_XOSC << RTC_OSC32CON2_F32K_SEL_OFFSET)
#define     RTC_OSC32CON2_F32K_SEL_DCXO_AO_EOSC_MASK        (RTC_OSC32CON2_F32K_SEL_DCXO_AO_EOSC << RTC_OSC32CON2_F32K_SEL_OFFSET)
#define     RTC_OSC32CON2_F32K_SEL_DCXO_AO_XOSC_MASK        (RTC_OSC32CON2_F32K_SEL_DCXO_AO_XOSC << RTC_OSC32CON2_F32K_SEL_OFFSET)
#define     RTC_OSC32CON2_F32K_SEL_MASK                     (0x03 << RTC_OSC32CON2_F32K_SEL_OFFSET)
#define     RTC_OSC32CON2_SYS32K_SRC_SEL_MASK               (0x01 << RTC_OSC32CON2_SYS32K_SRC_SEL_OFFSET)
/*RTC_SYS32K_CG_CON Register*/
#define     RTC_SYS32K_CG_CON_LED_32K_CG_OFFSET             (0)
#define     RTC_SYS32K_CG_CON_QDEC_32K_CG_OFFSET            (1)
#define     RTC_SYS32K_CG_CON_RAMBOZ_32K_CG_OFFSET          (2)
#define     RTC_SYS32K_CG_CON_RTC_TIMER_32K_CG_OFFSET       (3)
#define     RTC_SYS32K_CG_CON_RTCSYS_BT_COUNTER_CG_OFFSET   (4)
#define     RTC_SYS32K_CG_CON_LED_32K_CG_MASK               (0x01 << RTC_SYS32K_CG_CON_LED_32K_CG_OFFSET)
#define     RTC_SYS32K_CG_CON_QDEC_32K_CG_MASK              (0x01 << RTC_SYS32K_CG_CON_QDEC_32K_CG_OFFSET)
#define     RTC_SYS32K_CG_CON_RAMBOZ_32K_CG_MASK            (0x01 << RTC_SYS32K_CG_CON_RAMBOZ_32K_CG_OFFSET)
#define     RTC_SYS32K_CG_CON_RTC_TIMER_32K_CG_MASK         (0x01 << RTC_SYS32K_CG_CON_RTC_TIMER_32K_CG_OFFSET)
#define     RTC_SYS32K_CG_CON_RTCSYS_BT_COUNTER_CG_MASK     (0x01 << RTC_SYS32K_CG_CON_RTCSYS_BT_COUNTER_CG_OFFSET)

/*RTC_SPARE_REG*/
#define     RTC_SPAR_REG_BROM_SKIP_OFFSET       (0)
#define     RTC_SPAR_REG_PWR_FLG_OFFSET         (7)
#define     RTC_SPAR_REG_RESRV_OFFSET           (8)
#define     RTC_SPAR_REG_BROM_SKIP_MASK         (1<<RTC_SPAR_REG_BROM_SKIP_OFFSET)
#define     RTC_SPAR_REG_PWR_FLG_MASK           (1<<RTC_SPAR_REG_PWR_FLG_OFFSET)

/*RTC_DEBUG_CON0*/
#define     RTC_DEBUG_CON_DBG_SEL_OFFSET       (0)
#define     RTC_DEBUG_CON_DBG_EN_OFFSET        (8)
#define     RTC_DEBUG_CON_DBG_OUTPUT_OFFSET    (16)
#define     RTC_DEBUG_CON_DBG_SEL_MASK         (0x0F << RTC_DEBUG_CON_DBG_SEL_OFFSET)
#define     RTC_DEBUG_CON_DBG_EN_MASK          (0x01 << RTC_DEBUG_CON_DBG_EN_OFFSET)
#define     RTC_DEBUG_CON_DBG_OUTPUT_MASK      (0xFFFF << RTC_DEBUG_CON_DBG_OUTPUT_OFFSET)

/************************ RTC register definition end line  *******************************
 */


#endif /* __RTC_REG_DEFINITION_H__ */