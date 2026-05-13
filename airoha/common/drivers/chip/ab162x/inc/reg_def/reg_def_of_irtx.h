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

#ifndef __IRTX_REG_DEFINITION_H__
#define __IRTX_REG_DEFINITION_H__

typedef union {
    struct {
        __IO uint32_t level1_cnt     :16;    /* bits:0-15, count for logic level1 of unit00 [15:0] */
        __I  uint32_t __reserved_00      :16;
    } field;
    __IO uint32_t reg_level1_cnt;
} REG_LEVEL1_CNT_T;

typedef union {
    struct {
        __IO uint32_t level2_cnt     :16;    /* bits:0-15, count for logic level1 of unit00 [15:0] */
        __I  uint32_t __reserved_00      :16;
    } field;
    __IO uint32_t reg_level2_cnt;
} REG_LEVEL2_CNT_T;

typedef struct{
    REG_LEVEL1_CNT_T level1_cnt_t;
    REG_LEVEL2_CNT_T level2_cnt_t;
}REG_LEVEL_CNT_T;

/* reg_VALUE0_ir_tx_0 */
typedef union {
    struct {
        __IO uint32_t reg_value_unit00           :2;    /* bits:0-1, logic value of unit00[1:0] [1]: level1 [0]: level2 */
        __IO uint32_t reg_value_unit01           :2;    /* bits:2-3, logic value of unit01[1:0] [1]: level1 [0]: level2 */
        __IO uint32_t reg_value_unit02           :2;    /* bits:4-5, logic value of unit02[1:0] [1]: level1 [0]: level2 */
        __IO uint32_t reg_value_unit03           :2;    /* bits:6-7, logic value of unit03[1:0] [1]: level1 [0]: level2 */
        __IO uint32_t reg_value_unit04           :2;    /* bits:8-9, logic value of unit04[1:0] [1]: level1 [0]: level2 */
        __IO uint32_t reg_value_unit05           :2;    /* bits:10-11, logic value of unit05[1:0] [1]: level1 [0]: level2 */
        __IO uint32_t reg_value_unit06           :2;    /* bits:12-13, logic value of unit06[1:0] [1]: level1 [0]: level2 */
        __IO uint32_t reg_value_unit07           :2;    /* bits:14-15, logic value of unit07[1:0] [1]: level1 [0]: level2 */
        __I  uint32_t __reserved_00                   :16;
    } field;
    __IO uint32_t word;
} REG_LEVEL_VALUE0_T;

#define REG_VALUE0_IR_TX_0_REG_VALUE_UNIT00_VALUE0_OFFSET                    (0U)
#define REG_VALUE0_IR_TX_0_REG_VALUE_UNIT00_VALUE0_MASK                      (0x3U << REG_VALUE0_IR_TX_0_REG_VALUE_UNIT00_VALUE0_OFFSET)
#define REG_VALUE0_IR_TX_0_REG_VALUE_UNIT01_VALUE0_OFFSET                    (2U)
#define REG_VALUE0_IR_TX_0_REG_VALUE_UNIT01_VALUE0_MASK                      (0x3U << REG_VALUE0_IR_TX_0_REG_VALUE_UNIT01_VALUE0_OFFSET)
#define REG_VALUE0_IR_TX_0_REG_VALUE_UNIT02_VALUE0_OFFSET                    (4U)
#define REG_VALUE0_IR_TX_0_REG_VALUE_UNIT02_VALUE0_MASK                      (0x3U << REG_VALUE0_IR_TX_0_REG_VALUE_UNIT02_VALUE0_OFFSET)
#define REG_VALUE0_IR_TX_0_REG_VALUE_UNIT03_VALUE0_OFFSET                    (6U)
#define REG_VALUE0_IR_TX_0_REG_VALUE_UNIT03_VALUE0_MASK                      (0x3U << REG_VALUE0_IR_TX_0_REG_VALUE_UNIT03_VALUE0_OFFSET)
#define REG_VALUE0_IR_TX_0_REG_VALUE_UNIT04_VALUE0_OFFSET                    (8U)
#define REG_VALUE0_IR_TX_0_REG_VALUE_UNIT04_VALUE0_MASK                      (0x3U << REG_VALUE0_IR_TX_0_REG_VALUE_UNIT04_VALUE0_OFFSET)
#define REG_VALUE0_IR_TX_0_REG_VALUE_UNIT05_VALUE0_OFFSET                    (10U)
#define REG_VALUE0_IR_TX_0_REG_VALUE_UNIT05_VALUE0_MASK                      (0x3U << REG_VALUE0_IR_TX_0_REG_VALUE_UNIT05_VALUE0_OFFSET)
#define REG_VALUE0_IR_TX_0_REG_VALUE_UNIT06_VALUE0_OFFSET                    (12U)
#define REG_VALUE0_IR_TX_0_REG_VALUE_UNIT06_VALUE0_MASK                      (0x3U << REG_VALUE0_IR_TX_0_REG_VALUE_UNIT06_VALUE0_OFFSET)
#define REG_VALUE0_IR_TX_0_REG_VALUE_UNIT07_VALUE0_OFFSET                    (14U)
#define REG_VALUE0_IR_TX_0_REG_VALUE_UNIT07_VALUE0_MASK                      (0x3U << REG_VALUE0_IR_TX_0_REG_VALUE_UNIT07_VALUE0_OFFSET)


/* reg_VALUE1_ir_tx_0 */
typedef union {
    struct {
        __IO uint32_t reg_value_unit08           :2;    /* bits:0-1, logic value of unit08[1:0] [1]: level1 [0]: level2 */
        __IO uint32_t reg_value_unit09           :2;    /* bits:2-3, logic value of unit09[1:0] [1]: level1 [0]: level2 */
        __IO uint32_t reg_value_unit10           :2;    /* bits:4-5, logic value of unit10[1:0] [1]: level1 [0]: level2 */
        __IO uint32_t reg_value_unit11           :2;    /* bits:6-7, logic value of unit11[1:0] [1]: level1 [0]: level2 */
        __IO uint32_t reg_value_unit12           :2;    /* bits:8-9, logic value of unit12[1:0] [1]: level1 [0]: level2 */
        __IO uint32_t reg_value_unit13           :2;    /* bits:10-11, logic value of unit13[1:0] [1]: level1 [0]: level2 */
        __I  uint32_t __reserved_00                   :20;
    } field;
    __IO uint32_t word;
} REG_LEVEL_VALUE1_T;

#define REG_VALUE1_IR_TX_0_REG_VALUE_UNIT08_VALUE1_OFFSET                    (0U)
#define REG_VALUE1_IR_TX_0_REG_VALUE_UNIT08_VALUE1_MASK                      (0x3U << REG_VALUE1_IR_TX_0_REG_VALUE_UNIT08_VALUE1_OFFSET)
#define REG_VALUE1_IR_TX_0_REG_VALUE_UNIT09_VALUE1_OFFSET                    (2U)
#define REG_VALUE1_IR_TX_0_REG_VALUE_UNIT09_VALUE1_MASK                      (0x3U << REG_VALUE1_IR_TX_0_REG_VALUE_UNIT09_VALUE1_OFFSET)
#define REG_VALUE1_IR_TX_0_REG_VALUE_UNIT10_VALUE1_OFFSET                    (4U)
#define REG_VALUE1_IR_TX_0_REG_VALUE_UNIT10_VALUE1_MASK                      (0x3U << REG_VALUE1_IR_TX_0_REG_VALUE_UNIT10_VALUE1_OFFSET)
#define REG_VALUE1_IR_TX_0_REG_VALUE_UNIT11_VALUE1_OFFSET                    (6U)
#define REG_VALUE1_IR_TX_0_REG_VALUE_UNIT11_VALUE1_MASK                      (0x3U << REG_VALUE1_IR_TX_0_REG_VALUE_UNIT11_VALUE1_OFFSET)
#define REG_VALUE1_IR_TX_0_REG_VALUE_UNIT12_VALUE1_OFFSET                    (8U)
#define REG_VALUE1_IR_TX_0_REG_VALUE_UNIT12_VALUE1_MASK                      (0x3U << REG_VALUE1_IR_TX_0_REG_VALUE_UNIT12_VALUE1_OFFSET)
#define REG_VALUE1_IR_TX_0_REG_VALUE_UNIT13_VALUE1_OFFSET                    (10U)
#define REG_VALUE1_IR_TX_0_REG_VALUE_UNIT13_VALUE1_MASK                      (0x3U << REG_VALUE1_IR_TX_0_REG_VALUE_UNIT13_VALUE1_OFFSET)


/* reg_0078_ir_tx_0 */
typedef union {
    struct {
        __IO uint32_t reg_ir_tx_total_cycle_cnt_1:16;    /* bits:0-15, count for total cycle time[31:16] */
        __I  uint32_t __reserved_00                   :16;
    } field;
    __IO uint32_t word;
} REG_TOTAL_CNT1_T;

/* reg_007C_ir_tx_0 */
typedef union {
    struct {
        __IO uint32_t reg_ir_tx_total_cycle_cnt_0:16;    /* bits:0-15, count for total cycle time[15:00] */
        __I  uint32_t __reserved_00                   :16;
    } field;
    __IO uint32_t word;
} REG_TOTAL_CNT0_T;

/* reg_0080_ir_tx_0 */
typedef union {
    struct {
        __IO uint32_t reg_ir_tx_wait_value_0080       :1;    /* bits:0-0, logic value of ir_tx_out at the wait state */
        __I  uint32_t __reserved_00                   :7;
        __IO uint32_t reg_ir_tx_ckdiv_num_0080        :8;    /* bits:8-15, the divided number of IR TX input clock, the divided clock is for internal counter use.  The input clock source of IR TX is XTAL MHz.  8_h00 : divided by 1.  8_h01 : divided by 2.    8_hff : divided by 256. */
        __I  uint32_t __reserved_01                   :16;
    } field;
    __IO uint32_t word;
} REG_0080_IR_TX_0_T;

#define REG_0080_IR_TX_0_REG_IR_TX_WAIT_VALUE_0080_OFFSET                (0U)
#define REG_0080_IR_TX_0_REG_IR_TX_WAIT_VALUE_0080_MASK                  (0x1U << REG_0080_IR_TX_0_REG_IR_TX_WAIT_VALUE_0080_OFFSET)
#define REG_0080_IR_TX_0_REG_IR_TX_CKDIV_NUM_0080_OFFSET                 (8U)
#define REG_0080_IR_TX_0_REG_IR_TX_CKDIV_NUM_0080_MASK                   (0xFFU << REG_0080_IR_TX_0_REG_IR_TX_CKDIV_NUM_0080_OFFSET)


/* reg_0084_ir_tx_0 */
typedef union {
    struct {
        __IO uint32_t reg_ir_tx_carrier_hcnt_0084     :8;    /* bits:0-7, the high count register to determine the frequency and duty cycle of carrier frequency */
        __IO uint32_t reg_ir_tx_carrier_lcnt_0084     :8;    /* bits:8-15, the low count register to determine the frequency and duty cycle of carrier frequency */
        __I  uint32_t __reserved_00                   :16;
    } field;
    __IO uint32_t word;
} REG_0084_IR_TX_0_T;

#define REG_0084_IR_TX_0_REG_IR_TX_CARRIER_HCNT_0084_OFFSET              (0U)
#define REG_0084_IR_TX_0_REG_IR_TX_CARRIER_HCNT_0084_MASK                (0xFFU << REG_0084_IR_TX_0_REG_IR_TX_CARRIER_HCNT_0084_OFFSET)
#define REG_0084_IR_TX_0_REG_IR_TX_CARRIER_LCNT_0084_OFFSET              (8U)
#define REG_0084_IR_TX_0_REG_IR_TX_CARRIER_LCNT_0084_MASK                (0xFFU << REG_0084_IR_TX_0_REG_IR_TX_CARRIER_LCNT_0084_OFFSET)


/* reg_0088_ir_tx_0 */
typedef union {
    struct {
        __IO uint32_t reg_ir_tx_en_0088               :1;    /* bits:0-0, enable ir tx 0: disable 1: enable */
        __IO uint32_t reg_ir_tx_rstz_0088             :1;    /* bits:1-1, reset ir tx 0: reset 1: not reset */
        __IO uint32_t reg_ir_tx_int_en_0088           :1;    /* bits:2-2, enable ir_tx interrupt 0: disable 1: enable */
        __IO uint32_t reg_ir_tx_out_inv_baseband_0088 :1;    /* bits:3-3, invert the polarity of baseband output signal 0: not invert 1: invert */
        __IO uint32_t reg_ir_tx_carrier_en_0088       :1;    /* bits:4-4, determine ir tx out 0: baseband 1: with carrier */
        __I  uint32_t __reserved_00                   :3;
        __IO uint32_t reg_ir_tx_test_sel_0088         :2;    /* bits:8-9, test bus selection */
        __IO uint32_t reg_ir_tx_out_inv_0088          :1;    /* bits:10-10, invert the polarity of output signal 0: not invert 1: invert */
        __I  uint32_t __reserved_01                   :21;
    } field;
    __IO uint32_t word;
} REG_0088_IR_TX_0_T;

#define REG_0088_IR_TX_0_REG_IR_TX_EN_0088_OFFSET                        (0U)
#define REG_0088_IR_TX_0_REG_IR_TX_EN_0088_MASK                          (0x1U << REG_0088_IR_TX_0_REG_IR_TX_EN_0088_OFFSET)
#define REG_0088_IR_TX_0_REG_IR_TX_RSTZ_0088_OFFSET                      (1U)
#define REG_0088_IR_TX_0_REG_IR_TX_RSTZ_0088_MASK                        (0x1U << REG_0088_IR_TX_0_REG_IR_TX_RSTZ_0088_OFFSET)
#define REG_0088_IR_TX_0_REG_IR_TX_INT_EN_0088_OFFSET                    (2U)
#define REG_0088_IR_TX_0_REG_IR_TX_INT_EN_0088_MASK                      (0x1U << REG_0088_IR_TX_0_REG_IR_TX_INT_EN_0088_OFFSET)
#define REG_0088_IR_TX_0_REG_IR_TX_OUT_INV_BASEBAND_0088_OFFSET          (3U)
#define REG_0088_IR_TX_0_REG_IR_TX_OUT_INV_BASEBAND_0088_MASK            (0x1U << REG_0088_IR_TX_0_REG_IR_TX_OUT_INV_BASEBAND_0088_OFFSET)
#define REG_0088_IR_TX_0_REG_IR_TX_CARRIER_EN_0088_OFFSET                (4U)
#define REG_0088_IR_TX_0_REG_IR_TX_CARRIER_EN_0088_MASK                  (0x1U << REG_0088_IR_TX_0_REG_IR_TX_CARRIER_EN_0088_OFFSET)
#define REG_0088_IR_TX_0_REG_IR_TX_TEST_SEL_0088_OFFSET                  (8U)
#define REG_0088_IR_TX_0_REG_IR_TX_TEST_SEL_0088_MASK                    (0x3U << REG_0088_IR_TX_0_REG_IR_TX_TEST_SEL_0088_OFFSET)
#define REG_0088_IR_TX_0_REG_IR_TX_OUT_INV_0088_OFFSET                   (10U)
#define REG_0088_IR_TX_0_REG_IR_TX_OUT_INV_0088_MASK                     (0x1U << REG_0088_IR_TX_0_REG_IR_TX_OUT_INV_0088_OFFSET)


/* reg_008C_ir_tx_0 */
typedef union {
    struct {
        __IO uint32_t reg_ir_tx_trigger_008C          :1;    /* bits:0-0, trigger engine to start transfer */
        __I  uint32_t __reserved_00                   :31;
    } field;
    __IO uint32_t word;
} REG_008C_IR_TX_0_T;

#define REG_008C_IR_TX_0_REG_IR_TX_TRIGGER_008C_OFFSET                   (0U)
#define REG_008C_IR_TX_0_REG_IR_TX_TRIGGER_008C_MASK                     (0x1U << REG_008C_IR_TX_0_REG_IR_TX_TRIGGER_008C_OFFSET)


/* reg_0090_ir_tx_0 */
typedef union {
    struct {
        __I  uint32_t reg_ir_tx_done_flag_0090        :1;    /* bits:0-0, busy status, hardware sets this bit to 1'b1 when transfer is completed 1: transfer done or interrupt pending 0: transfer busy or interrupt not pending */
        __I  uint32_t __reserved_00                   :31;
    } field;
    __IO uint32_t word;
} REG_0090_IR_TX_0_T;

#define REG_0090_IR_TX_0_REG_IR_TX_DONE_FLAG_0090_OFFSET                 (0U)
#define REG_0090_IR_TX_0_REG_IR_TX_DONE_FLAG_0090_MASK                   (0x1U << REG_0090_IR_TX_0_REG_IR_TX_DONE_FLAG_0090_OFFSET)


/* reg_0094_ir_tx_0 */
typedef union {
    struct {
        __IO uint32_t reg_ir_tx_clr_done_flag_0094    :1;    /* bits:0-0, SW needs to set this bit to clear done flag or interrupt */
        __I  uint32_t __reserved_00                   :31;
    } field;
    __IO uint32_t word;
} REG_0094_IR_TX_0_T;

#define REG_0094_IR_TX_0_REG_IR_TX_CLR_DONE_FLAG_0094_OFFSET             (0U)
#define REG_0094_IR_TX_0_REG_IR_TX_CLR_DONE_FLAG_0094_MASK               (0x1U << REG_0094_IR_TX_0_REG_IR_TX_CLR_DONE_FLAG_0094_OFFSET)


/* reg_0098_ir_tx_0 */
typedef union {
    struct {
        __IO uint32_t reg_reserved00_0098             :16;    /* bits:0-15, reserved */
        __I  uint32_t __reserved_00                   :16;
    } field;
    __IO uint32_t word;
} REG_0098_IR_TX_0_T;

#define REG_0098_IR_TX_0_REG_RESERVED00_0098_OFFSET                      (0U)
#define REG_0098_IR_TX_0_REG_RESERVED00_0098_MASK                        (0xFFFFU << REG_0098_IR_TX_0_REG_RESERVED00_0098_OFFSET)


/* reg_009C_ir_tx_0 */
typedef union {
    struct {
        __IO uint32_t reg_reserved01_009C             :16;    /* bits:0-15, reserved */
        __I  uint32_t __reserved_00                   :16;
    } field;
    __IO uint32_t word;
} REG_009C_IR_TX_0_T;

#define REG_009C_IR_TX_0_REG_RESERVED01_009C_OFFSET                      (0U)
#define REG_009C_IR_TX_0_REG_RESERVED01_009C_MASK                        (0xFFFFU << REG_009C_IR_TX_0_REG_RESERVED01_009C_OFFSET)


/* reg_00A0_ir_tx_0 */
typedef union {
    struct {
        __IO uint32_t reg_reserved02_00A0             :16;    /* bits:0-15, reserved */
        __I  uint32_t __reserved_00                   :16;
    } field;
    __IO uint32_t word;
} REG_00A0_IR_TX_0_T;

#define REG_00A0_IR_TX_0_REG_RESERVED02_00A0_OFFSET                      (0U)
#define REG_00A0_IR_TX_0_REG_RESERVED02_00A0_MASK                        (0xFFFFU << REG_00A0_IR_TX_0_REG_RESERVED02_00A0_OFFSET)


/* reg_00A4_ir_tx_0 */
typedef union {
    struct {
        __IO uint32_t reg_reserved03_00A4             :16;    /* bits:0-15, reserved */
        __I  uint32_t __reserved_00                   :16;
    } field;
    __IO uint32_t word;
} REG_00A4_IR_TX_0_T;

#define REG_00A4_IR_TX_0_REG_RESERVED03_00A4_OFFSET                      (0U)
#define REG_00A4_IR_TX_0_REG_RESERVED03_00A4_MASK                        (0xFFFFU << REG_00A4_IR_TX_0_REG_RESERVED03_00A4_OFFSET)


/* reg_00A8_ir_tx_0 */
typedef union {
    struct {
        __I  uint32_t reg_ir_tx_bist_fail_00A8        :16;    /* bits:0-15, ir tx bist fail list */
        __I  uint32_t __reserved_00                   :16;
    } field;
    __IO uint32_t word;
} REG_00A8_IR_TX_0_T;

#define REG_00A8_IR_TX_0_REG_IR_TX_BIST_FAIL_00A8_OFFSET                 (0U)
#define REG_00A8_IR_TX_0_REG_IR_TX_BIST_FAIL_00A8_MASK                   (0xFFFFU << REG_00A8_IR_TX_0_REG_IR_TX_BIST_FAIL_00A8_OFFSET)


/* reg_00AC_ir_tx_0 */
typedef union {
    struct {
        __I  uint32_t reg_ir_tx_dbg_bus_0_00AC        :16;    /* bits:0-15, ir tx debug bus 0 */
        __I  uint32_t __reserved_00                   :16;
    } field;
    __IO uint32_t word;
} REG_00AC_IR_TX_0_T;

#define REG_00AC_IR_TX_0_REG_IR_TX_DBG_BUS_0_00AC_OFFSET                 (0U)
#define REG_00AC_IR_TX_0_REG_IR_TX_DBG_BUS_0_00AC_MASK                   (0xFFFFU << REG_00AC_IR_TX_0_REG_IR_TX_DBG_BUS_0_00AC_OFFSET)


/* reg_00B0_ir_tx_0 */
typedef union {
    struct {
        __I  uint32_t reg_ir_tx_dbg_bus_1_00B0        :16;    /* bits:0-15, ir tx debug bus 1 */
        __I  uint32_t __reserved_00                   :16;
    } field;
    __IO uint32_t word;
} REG_00B0_IR_TX_0_T;

#define REG_00B0_IR_TX_0_REG_IR_TX_DBG_BUS_1_00B0_OFFSET                 (0U)
#define REG_00B0_IR_TX_0_REG_IR_TX_DBG_BUS_1_00B0_MASK                   (0xFFFFU << REG_00B0_IR_TX_0_REG_IR_TX_DBG_BUS_1_00B0_OFFSET)


/* reg_00B4_ir_tx_0 */
typedef union {
    struct {
        __I  uint32_t reg_ir_tx_dbg_bus_2_00B4        :16;    /* bits:0-15, ir tx debug bus 2 */
        __I  uint32_t __reserved_00                   :16;
    } field;
    __IO uint32_t word;
} REG_00B4_IR_TX_0_T;

#define REG_00B4_IR_TX_0_REG_IR_TX_DBG_BUS_2_00B4_OFFSET                 (0U)
#define REG_00B4_IR_TX_0_REG_IR_TX_DBG_BUS_2_00B4_MASK                   (0xFFFFU << REG_00B4_IR_TX_0_REG_IR_TX_DBG_BUS_2_00B4_OFFSET)


/* reg_00B8_ir_tx_0 */
typedef union {
    struct {
        __I  uint32_t reg_ir_tx_dbg_bus_3_00B8        :16;    /* bits:0-15, ir tx debug bus 3 */
        __I  uint32_t __reserved_00                   :16;
    } field;
    __IO uint32_t word;
} REG_00B8_IR_TX_0_T;

#define REG_00B8_IR_TX_0_REG_IR_TX_DBG_BUS_3_00B8_OFFSET                 (0U)
#define REG_00B8_IR_TX_0_REG_IR_TX_DBG_BUS_3_00B8_MASK                   (0xFFFFU << REG_00B8_IR_TX_0_REG_IR_TX_DBG_BUS_3_00B8_OFFSET)


/* reg_0100_ir_tx_0 */
typedef union {
    struct {
        __IO uint32_t reg_ir_tx_xmp_1_en_0100         :1;    /* bits:0-0, enable the XMP-1 infrared protocol */
        __I  uint32_t __reserved_00                   :7;
        __IO uint32_t reg_ir_tx_xmp_1_start_unit_0100 :4;    /* bits:8-11, determine which unit setting represents the start (high to low) of the XMP-1 protocol */
        __IO uint32_t reg_ir_tx_xmp_1_data_unit_0100  :4;    /* bits:12-15, determine which unit setting represents the data (delay) of the XMP-1 protocol */
        __I  uint32_t __reserved_01                   :16;
    } field;
    __IO uint32_t word;
} REG_0100_IR_TX_0_T;

#define REG_0100_IR_TX_0_REG_IR_TX_XMP_1_EN_0100_OFFSET                  (0U)
#define REG_0100_IR_TX_0_REG_IR_TX_XMP_1_EN_0100_MASK                    (0x1U << REG_0100_IR_TX_0_REG_IR_TX_XMP_1_EN_0100_OFFSET)
#define REG_0100_IR_TX_0_REG_IR_TX_XMP_1_START_UNIT_0100_OFFSET          (8U)
#define REG_0100_IR_TX_0_REG_IR_TX_XMP_1_START_UNIT_0100_MASK            (0xFU << REG_0100_IR_TX_0_REG_IR_TX_XMP_1_START_UNIT_0100_OFFSET)
#define REG_0100_IR_TX_0_REG_IR_TX_XMP_1_DATA_UNIT_0100_OFFSET           (12U)
#define REG_0100_IR_TX_0_REG_IR_TX_XMP_1_DATA_UNIT_0100_MASK             (0xFU << REG_0100_IR_TX_0_REG_IR_TX_XMP_1_DATA_UNIT_0100_OFFSET)


/* reg_0104_ir_tx_0 */
typedef union {
    struct {
        __IO uint32_t reg_ir_tx_xmp_1_packet_size_0104:16;    /* bits:0-15, how much data will be transferred in this packet */
        __I  uint32_t __reserved_00                   :16;
    } field;
    __IO uint32_t word;
} REG_0104_IR_TX_0_T;

#define REG_0104_IR_TX_0_REG_IR_TX_XMP_1_PACKET_SIZE_0104_OFFSET         (0U)
#define REG_0104_IR_TX_0_REG_IR_TX_XMP_1_PACKET_SIZE_0104_MASK           (0xFFFFU << REG_0104_IR_TX_0_REG_IR_TX_XMP_1_PACKET_SIZE_0104_OFFSET)


/* reg_1004_ir_tx_mem_0 */
typedef union {
    struct {
        __I  uint32_t __reserved_00                   :8;
        __IO uint32_t reg_addr_auto_inc               :1;    /* bits:8-8, set: address will auto-increase when Read/Write 'reg_sram_data' (16 bits based address) */
        __I  uint32_t __reserved_01                   :3;
        __IO uint32_t reg_key                         :4;    /* bits:12-15, set as 0x5 to enable ir_tx_mem interface */
        __I  uint32_t __reserved_02                   :16;
    } field;
    __IO uint32_t word;
} REG_1004_IR_TX_MEM_0_T;

#define REG_1004_IR_TX_MEM_0_REG_ADDR_AUTO_INC_OFFSET                    (8U)
#define REG_1004_IR_TX_MEM_0_REG_ADDR_AUTO_INC_MASK                      (0x1U << REG_1004_IR_TX_MEM_0_REG_ADDR_AUTO_INC_OFFSET)
#define REG_1004_IR_TX_MEM_0_REG_KEY_OFFSET                              (12U)
#define REG_1004_IR_TX_MEM_0_REG_KEY_MASK                                (0xFU << REG_1004_IR_TX_MEM_0_REG_KEY_OFFSET)


/* reg_1108_ir_tx_mem_0 */
typedef union {
    struct {
        __IO uint32_t reg_addr                        :16;    /* bits:0-15, ir_tx sram address (16 bits based address) Note: auto-increase when 'reg_addr_auto_inc' is set and write 'reg_sram_wd' or read 'reg_sram_rd' PS: Do not read h0005 and h0007 by MS TV tool, or it may be incresed. */
        __I  uint32_t __reserved_00                   :16;
    } field;
    __IO uint32_t word;
} REG_1108_IR_TX_MEM_0_T;

#define REG_1108_IR_TX_MEM_0_REG_ADDR_OFFSET                             (0U)
#define REG_1108_IR_TX_MEM_0_REG_ADDR_MASK                               (0xFFFFU << REG_1108_IR_TX_MEM_0_REG_ADDR_OFFSET)


/* reg_1118_ir_tx_mem_0 */
typedef union {
    struct {
        __IO uint32_t reg_sram_wd                     :16;    /* bits:0-15, Write: write data to ir_tx sram */
        __I  uint32_t __reserved_00                   :16;
    } field;
    __IO uint32_t word;
} REG_1118_IR_TX_MEM_0_T;

#define REG_1118_IR_TX_MEM_0_REG_SRAM_WD_OFFSET                          (0U)
#define REG_1118_IR_TX_MEM_0_REG_SRAM_WD_MASK                            (0xFFFFU << REG_1118_IR_TX_MEM_0_REG_SRAM_WD_OFFSET)


/* reg_1120_ir_tx_mem_0 */
typedef union {
    struct {
        __I  uint32_t reg_sram_rd                     :16;    /* bits:0-15, Read: read data from ir_tx sram */
        __I  uint32_t __reserved_00                   :16;
    } field;
    __IO uint32_t word;
} REG_1120_IR_TX_MEM_0_T;

#define REG_1120_IR_TX_MEM_0_REG_SRAM_RD_OFFSET                          (0U)
#define REG_1120_IR_TX_MEM_0_REG_SRAM_RD_MASK                            (0xFFFFU << REG_1120_IR_TX_MEM_0_REG_SRAM_RD_OFFSET)


typedef struct {
    REG_LEVEL_CNT_T                                  reg_level_cnt[14];
    REG_LEVEL_VALUE0_T                               reg_level_value_0;
    REG_LEVEL_VALUE1_T                               reg_level_value_1;
    REG_TOTAL_CNT1_T                                 reg_total_cnt_1; /* offset: 0x00000078, reg_0078_ir_tx_0 */
    REG_TOTAL_CNT0_T                                 reg_total_cnt_0; /* offset: 0x00000078, reg_0078_ir_tx_0 */
    REG_0080_IR_TX_0_T                               reg_0080_ir_tx_0; /* offset: 0x00000080, reg_0080_ir_tx_0 */
    REG_0084_IR_TX_0_T                               reg_0084_ir_tx_0; /* offset: 0x00000084, reg_0084_ir_tx_0 */
    REG_0088_IR_TX_0_T                               reg_0088_ir_tx_0; /* offset: 0x00000088, reg_0088_ir_tx_0 */
    REG_008C_IR_TX_0_T                               reg_008c_ir_tx_0; /* offset: 0x0000008C, reg_008C_ir_tx_0 */
    REG_0090_IR_TX_0_T                               reg_0090_ir_tx_0; /* offset: 0x00000090, reg_0090_ir_tx_0 */
    REG_0094_IR_TX_0_T                               reg_0094_ir_tx_0; /* offset: 0x00000094, reg_0094_ir_tx_0 */
    REG_0098_IR_TX_0_T                               reg_0098_ir_tx_0; /* offset: 0x00000098, reg_0098_ir_tx_0 */
    REG_009C_IR_TX_0_T                               reg_009c_ir_tx_0; /* offset: 0x0000009C, reg_009C_ir_tx_0 */
    REG_00A0_IR_TX_0_T                               reg_00a0_ir_tx_0; /* offset: 0x000000A0, reg_00A0_ir_tx_0 */
    REG_00A4_IR_TX_0_T                               reg_00a4_ir_tx_0; /* offset: 0x000000A4, reg_00A4_ir_tx_0 */
    REG_00A8_IR_TX_0_T                               reg_00a8_ir_tx_0; /* offset: 0x000000A8, reg_00A8_ir_tx_0 */
    REG_00AC_IR_TX_0_T                               reg_00ac_ir_tx_0; /* offset: 0x000000AC, reg_00AC_ir_tx_0 */
    REG_00B0_IR_TX_0_T                               reg_00b0_ir_tx_0; /* offset: 0x000000B0, reg_00B0_ir_tx_0 */
    REG_00B4_IR_TX_0_T                               reg_00b4_ir_tx_0; /* offset: 0x000000B4, reg_00B4_ir_tx_0 */
    REG_00B8_IR_TX_0_T                               reg_00b8_ir_tx_0; /* offset: 0x000000B8, reg_00B8_ir_tx_0 */
    uint32_t                                        __reserved_00[17]; /* offset: 0x000000BC, padding size: 0x00000044 */
    REG_0100_IR_TX_0_T                               reg_0100_ir_tx_0; /* offset: 0x00000100, reg_0100_ir_tx_0 */
    REG_0104_IR_TX_0_T                               reg_0104_ir_tx_0; /* offset: 0x00000104, reg_0104_ir_tx_0 */
    uint32_t                                       __reserved_01[959]; /* offset: 0x00000108, padding size: 0x00000EFC */
    REG_1004_IR_TX_MEM_0_T                       reg_1004_ir_tx_mem_0; /* offset: 0x00001004, reg_1004_ir_tx_mem_0 */
    uint32_t                                        __reserved_02[64]; /* offset: 0x00001008, padding size: 0x00000100 */
    REG_1108_IR_TX_MEM_0_T                       reg_1108_ir_tx_mem_0; /* offset: 0x00001108, reg_1108_ir_tx_mem_0 */
    uint32_t                                         __reserved_03[3]; /* offset: 0x0000110C, padding size: 0x0000000C */
    REG_1118_IR_TX_MEM_0_T                       reg_1118_ir_tx_mem_0; /* offset: 0x00001118, reg_1118_ir_tx_mem_0 */
    uint32_t                                         __reserved_04[1]; /* offset: 0x0000111C, padding size: 0x00000004 */
    REG_1120_IR_TX_MEM_0_T                       reg_1120_ir_tx_mem_0; /* offset: 0x00001120, reg_1120_ir_tx_mem_0 */
} IRTX_REGISTER_T;

#define IRTX_CLOCK_FREQUENCY     32000000 /* 32Mhz */

#endif /*__IRTX_REG_DEFINITION_H__*/
