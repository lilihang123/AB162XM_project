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

#ifndef __SPI_SLAVE_REG_DEFINITION_H__
#define __SPI_SLAVE_REG_DEFINITION_H__


#include <stdint.h>


/* ----------------------------------------------------------------------------
-- SPI Slave Pad register
---------------------------------------------------------------------------- */
/* SPI Slave Pad Command Define 0 */
typedef union {
    struct {
        __IO uint32_t SPIS_PAD_DUMMY_CNT              :4;    /* bits:0-3, Dummy count The number of dummy bits in one packet. Dummy phase is the second transmission of packet between command phase and data phase. */
        __I  uint32_t __reserved_00                   :20;
        __IO uint32_t SPIS_PAD_CMD_CT                 :8;    /* bits:24-31, Defines  Configure Type (CT) command value */
    } field;
    __IO uint32_t word;
} SPISLV_PAD_CMD_DEF0_T;

#define SPISLV_PAD_CMD_DEF0_SPIS_PAD_DUMMY_CNT_OFFSET                    (0U)
#define SPISLV_PAD_CMD_DEF0_SPIS_PAD_DUMMY_CNT_MASK                      (0xFU << SPISLV_PAD_CMD_DEF0_SPIS_PAD_DUMMY_CNT_OFFSET)
#define SPISLV_PAD_CMD_DEF0_SPIS_PAD_CMD_CT_OFFSET                       (24U)
#define SPISLV_PAD_CMD_DEF0_SPIS_PAD_CMD_CT_MASK                         (0xFFU << SPISLV_PAD_CMD_DEF0_SPIS_PAD_CMD_CT_OFFSET)


/* SPI Slave Pad Command Define 1 */
typedef union {
    struct {
        __IO uint32_t SPIS_PAD_CMD_PWOFF              :8;    /* bits:0-7, Defines Power-OFF (PWOFF) command value */
        __IO uint32_t SPIS_PAD_CMD_PWON               :8;    /* bits:8-15, Defines Power-ON (PWON) command value */
        __IO uint32_t SPIS_PAD_CMD_RS                 :8;    /* bits:16-23, Defines  Read Status (RS) command value */
        __IO uint32_t SPIS_PAD_CMD_WS                 :8;    /* bits:24-31, Defines Write Status (WS) command value */
    } field;
    __IO uint32_t word;
} SPISLV_PAD_CMD_DEF1_T;

#define SPISLV_PAD_CMD_DEF1_SPIS_PAD_CMD_PWOFF_OFFSET                    (0U)
#define SPISLV_PAD_CMD_DEF1_SPIS_PAD_CMD_PWOFF_MASK                      (0xFFU << SPISLV_PAD_CMD_DEF1_SPIS_PAD_CMD_PWOFF_OFFSET)
#define SPISLV_PAD_CMD_DEF1_SPIS_PAD_CMD_PWON_OFFSET                     (8U)
#define SPISLV_PAD_CMD_DEF1_SPIS_PAD_CMD_PWON_MASK                       (0xFFU << SPISLV_PAD_CMD_DEF1_SPIS_PAD_CMD_PWON_OFFSET)
#define SPISLV_PAD_CMD_DEF1_SPIS_PAD_CMD_RS_OFFSET                       (16U)
#define SPISLV_PAD_CMD_DEF1_SPIS_PAD_CMD_RS_MASK                         (0xFFU << SPISLV_PAD_CMD_DEF1_SPIS_PAD_CMD_RS_OFFSET)
#define SPISLV_PAD_CMD_DEF1_SPIS_PAD_CMD_WS_OFFSET                       (24U)
#define SPISLV_PAD_CMD_DEF1_SPIS_PAD_CMD_WS_MASK                         (0xFFU << SPISLV_PAD_CMD_DEF1_SPIS_PAD_CMD_WS_OFFSET)


/* SPI Slave Pad Command Define 2 */
typedef union {
    struct {
        __IO uint32_t SPIS_PAD_CMD_CR                 :8;    /* bits:0-7, Defines Configure Read (CR) command value */
        __IO uint32_t SPIS_PAD_CMD_CW                 :8;    /* bits:8-15, Defines Configure Write (CW) command value */
        __IO uint32_t SPIS_PAD_CMD_RD                 :8;    /* bits:16-23, Defines  Read Data (RD) command value */
        __IO uint32_t SPIS_PAD_CMD_WR                 :8;    /* bits:24-31, Defines  Write Data (WR) command value */
    } field;
    __IO uint32_t word;
} SPISLV_PAD_CMD_DEF2_T;

#define SPISLV_PAD_CMD_DEF2_SPIS_PAD_CMD_CR_OFFSET                       (0U)
#define SPISLV_PAD_CMD_DEF2_SPIS_PAD_CMD_CR_MASK                         (0xFFU << SPISLV_PAD_CMD_DEF2_SPIS_PAD_CMD_CR_OFFSET)
#define SPISLV_PAD_CMD_DEF2_SPIS_PAD_CMD_CW_OFFSET                       (8U)
#define SPISLV_PAD_CMD_DEF2_SPIS_PAD_CMD_CW_MASK                         (0xFFU << SPISLV_PAD_CMD_DEF2_SPIS_PAD_CMD_CW_OFFSET)
#define SPISLV_PAD_CMD_DEF2_SPIS_PAD_CMD_RD_OFFSET                       (16U)
#define SPISLV_PAD_CMD_DEF2_SPIS_PAD_CMD_RD_MASK                         (0xFFU << SPISLV_PAD_CMD_DEF2_SPIS_PAD_CMD_RD_OFFSET)
#define SPISLV_PAD_CMD_DEF2_SPIS_PAD_CMD_WR_OFFSET                       (24U)
#define SPISLV_PAD_CMD_DEF2_SPIS_PAD_CMD_WR_MASK                         (0xFFU << SPISLV_PAD_CMD_DEF2_SPIS_PAD_CMD_WR_OFFSET)


/* SPI Slave Pad Delay Select 0 Register */
typedef union {
    struct {
        __IO uint32_t SPIS_PAD_MOSI0_DLYSEL           :3;    /* bits:0-2, MOSI0 delay select The register can configure MOSI0 output signal delay. The delay = SPIS_MOSI0_DLYSEL * 2 ns */
        __I  uint32_t __reserved_00                   :5;
        __IO uint32_t SPIS_PAD_MOSI1_DLYSEL           :3;    /* bits:8-10, MOSI1 delay select The register can configure MOSI1 output signal delay. The delay = SPIS_MOSI1_DLYSEL * 2 ns */
        __I  uint32_t __reserved_01                   :5;
        __IO uint32_t SPIS_PAD_MOSI2_DLYSEL           :3;    /* bits:16-18, MOSI2 delay select The register can configure MOSI2 output signal delay. The delay = SPIS_MOSI2_DLYSEL * 2 ns */
        __I  uint32_t __reserved_02                   :5;
        __IO uint32_t SPIS_PAD_MOSI3_DLYSEL           :3;    /* bits:24-26, MOSI3 delay select The register can configure MOSI3 output signal delay. The delay = SPIS_MOSI3_DLYSEL * 2 ns */
        __I  uint32_t __reserved_03                   :5;
    } field;
    __IO uint32_t word;
} SPISLV_PAD_DLYSEL0_T;

#define SPISLV_PAD_DLYSEL0_SPIS_PAD_MOSI0_DLYSEL_OFFSET                  (0U)
#define SPISLV_PAD_DLYSEL0_SPIS_PAD_MOSI0_DLYSEL_MASK                    (0x7U << SPISLV_PAD_DLYSEL0_SPIS_PAD_MOSI0_DLYSEL_OFFSET)
#define SPISLV_PAD_DLYSEL0_SPIS_PAD_MOSI1_DLYSEL_OFFSET                  (8U)
#define SPISLV_PAD_DLYSEL0_SPIS_PAD_MOSI1_DLYSEL_MASK                    (0x7U << SPISLV_PAD_DLYSEL0_SPIS_PAD_MOSI1_DLYSEL_OFFSET)
#define SPISLV_PAD_DLYSEL0_SPIS_PAD_MOSI2_DLYSEL_OFFSET                  (16U)
#define SPISLV_PAD_DLYSEL0_SPIS_PAD_MOSI2_DLYSEL_MASK                    (0x7U << SPISLV_PAD_DLYSEL0_SPIS_PAD_MOSI2_DLYSEL_OFFSET)
#define SPISLV_PAD_DLYSEL0_SPIS_PAD_MOSI3_DLYSEL_OFFSET                  (24U)
#define SPISLV_PAD_DLYSEL0_SPIS_PAD_MOSI3_DLYSEL_MASK                    (0x7U << SPISLV_PAD_DLYSEL0_SPIS_PAD_MOSI3_DLYSEL_OFFSET)


/* SPI Slave Pad Delay Select 1 Register */
typedef union {
    struct {
        __IO uint32_t SPIS_PAD_MISO0_DLYSEL           :3;    /* bits:0-2, MISO0 delay select The register can configure MISO0 input signal delay. The delay = SPIS_MISO0_DLYSEL * 2 ns */
        __I  uint32_t __reserved_00                   :5;
        __IO uint32_t SPIS_PAD_MISO1_DLYSEL           :3;    /* bits:8-10, MISO1 delay select The register can configure MISO1 input signal delay. The delay = SPIS_MISO1_DLYSEL * 2 ns */
        __I  uint32_t __reserved_01                   :5;
        __IO uint32_t SPIS_PAD_MISO2_DLYSEL           :3;    /* bits:16-18, MISO2 delay select The register can configure MISO2 input signal delay. The delay = SPIS_MISO2_DLYSEL * 2 ns */
        __I  uint32_t __reserved_02                   :5;
        __IO uint32_t SPIS_PAD_MISO3_DLYSEL           :3;    /* bits:24-26, MISO3 delay select The register can configure MISO3 input signal delay. The delay = SPIS_MISO3_DLYSEL * 2 ns */
        __I  uint32_t __reserved_03                   :5;
    } field;
    __IO uint32_t word;
} SPISLV_PAD_DLYSEL1_T;

#define SPISLV_PAD_DLYSEL1_SPIS_PAD_MISO0_DLYSEL_OFFSET                  (0U)
#define SPISLV_PAD_DLYSEL1_SPIS_PAD_MISO0_DLYSEL_MASK                    (0x7U << SPISLV_PAD_DLYSEL1_SPIS_PAD_MISO0_DLYSEL_OFFSET)
#define SPISLV_PAD_DLYSEL1_SPIS_PAD_MISO1_DLYSEL_OFFSET                  (8U)
#define SPISLV_PAD_DLYSEL1_SPIS_PAD_MISO1_DLYSEL_MASK                    (0x7U << SPISLV_PAD_DLYSEL1_SPIS_PAD_MISO1_DLYSEL_OFFSET)
#define SPISLV_PAD_DLYSEL1_SPIS_PAD_MISO2_DLYSEL_OFFSET                  (16U)
#define SPISLV_PAD_DLYSEL1_SPIS_PAD_MISO2_DLYSEL_MASK                    (0x7U << SPISLV_PAD_DLYSEL1_SPIS_PAD_MISO2_DLYSEL_OFFSET)
#define SPISLV_PAD_DLYSEL1_SPIS_PAD_MISO3_DLYSEL_OFFSET                  (24U)
#define SPISLV_PAD_DLYSEL1_SPIS_PAD_MISO3_DLYSEL_MASK                    (0x7U << SPISLV_PAD_DLYSEL1_SPIS_PAD_MISO3_DLYSEL_OFFSET)


/* SPI Slave Pad Delay Select 2 Register */
typedef union {
    struct {
        __IO uint32_t SPIS_PAD_SCK_DLYSEL             :3;    /* bits:0-2, SCK delay select The register can configure SCK output signal delay. The delay = SPIS_SCK_DLYSEL * 2 ns */
        __I  uint32_t __reserved_00                   :29;
    } field;
    __IO uint32_t word;
} SPISLV_PAD_DLYSEL2_T;

#define SPISLV_PAD_DLYSEL2_SPIS_PAD_SCK_DLYSEL_OFFSET                    (0U)
#define SPISLV_PAD_DLYSEL2_SPIS_PAD_SCK_DLYSEL_MASK                      (0x7U << SPISLV_PAD_DLYSEL2_SPIS_PAD_SCK_DLYSEL_OFFSET)


/* SPI Slave Pad Debug Enable */
typedef union {
    struct {
        __IO uint32_t SPIS_PAD_DEBUG_EN               :1;    /* bits:0-0, empty description */
        __I  uint32_t __reserved_00                   :7;
        __IO uint32_t SPIS_PAD_CTRL0                  :2;    /* bits:8-9, SPI slave general configure register AO Ctrl0 CMD [2:0] =  [reg_cpol, reg_cpha] */
        __I  uint32_t __reserved_01                   :22;
    } field;
    __IO uint32_t word;
} SPISLV_PAD_DEBUG_EN_T;

#define SPISLV_PAD_DEBUG_EN_SPIS_PAD_DEBUG_EN_OFFSET                     (0U)
#define SPISLV_PAD_DEBUG_EN_SPIS_PAD_DEBUG_EN_MASK                       (0x1U << SPISLV_PAD_DEBUG_EN_SPIS_PAD_DEBUG_EN_OFFSET)
#define SPISLV_PAD_DEBUG_EN_SPIS_PAD_CTRL0_OFFSET                        (8U)
#define SPISLV_PAD_DEBUG_EN_SPIS_PAD_CTRL0_MASK                          (0x3U << SPISLV_PAD_DEBUG_EN_SPIS_PAD_CTRL0_OFFSET)


typedef struct {
    SPISLV_PAD_CMD_DEF0_T                         spislv_pad_cmd_def0; /* offset: 0x00000000, SPI Slave Pad Command Define 0 */
    SPISLV_PAD_CMD_DEF1_T                         spislv_pad_cmd_def1; /* offset: 0x00000004, SPI Slave Pad Command Define 1 */
    SPISLV_PAD_CMD_DEF2_T                         spislv_pad_cmd_def2; /* offset: 0x00000008, SPI Slave Pad Command Define 2 */
    SPISLV_PAD_DLYSEL0_T                           spislv_pad_dlysel0; /* offset: 0x0000000C, SPI Slave Pad Delay Select 0 Register */
    SPISLV_PAD_DLYSEL1_T                           spislv_pad_dlysel1; /* offset: 0x00000010, SPI Slave Pad Delay Select 1 Register */
    SPISLV_PAD_DLYSEL2_T                           spislv_pad_dlysel2; /* offset: 0x00000014, SPI Slave Pad Delay Select 2 Register */
    SPISLV_PAD_DEBUG_EN_T                         spislv_pad_debug_en; /* offset: 0x00000018, SPI Slave Pad Debug Enable */
} SPIS_PAD_REGISTER_T;


#define SPIS_CTRL_CPOL_OFFSET           (1)
#define SPIS_CTRL_CPOL_MASK             (0x1<<SPIS_CTRL_CPOL_OFFSET)
#define SPIS_CTRL_CPHA_OFFSET           (0)
#define SPIS_CTRL_CPHA_MASK             (0x1<<SPIS_CTRL_CPHA_OFFSET)
/* ----------------------------------------------------------------------------
-- SPI Slave register
---------------------------------------------------------------------------- */

/* SPI Slave Direct Mode FIFO Control */
typedef union {
    struct {
        __IO uint32_t SPIS_TX_FIFO_THRE               :6;    /* bits:0-5, TX FIFO threshold in direct mode An IRQ is asserted when SPIS_TX_FIFO_CNT is less or equal than this value */
        __I  uint32_t __reserved_00                   :2;
        __IO uint32_t SPIS_RX_FIFO_THRE               :6;    /* bits:8-13, RX FIFO threshold in direct mode An IRQ is asserted when SPIS_RX_FIFO_CNT is larger than this value */
        __I  uint32_t __reserved_01                   :18;
    } field;
    __IO uint32_t word;
} SPISLV_DIR_MODE_FIFO_CON_T;

#define SPISLV_DIR_MODE_FIFO_CON_SPIS_TX_FIFO_THRE_OFFSET                (0U)
#define SPISLV_DIR_MODE_FIFO_CON_SPIS_TX_FIFO_THRE_MASK                  (0x3FU << SPISLV_DIR_MODE_FIFO_CON_SPIS_TX_FIFO_THRE_OFFSET)
#define SPISLV_DIR_MODE_FIFO_CON_SPIS_RX_FIFO_THRE_OFFSET                (8U)
#define SPISLV_DIR_MODE_FIFO_CON_SPIS_RX_FIFO_THRE_MASK                  (0x3FU << SPISLV_DIR_MODE_FIFO_CON_SPIS_RX_FIFO_THRE_OFFSET)


/* SPI Slave Direct Mode RX DMA Start Address */
typedef union {
    struct {
        __IO uint32_t SPIS_RXDMA_STR_ADDR             :32;    /* bits:0-31, RX DMA start address in direct mode */
    } field;
    __IO uint32_t word;
} SPISLV_RXDMA_START_ADDR_T;

#define SPISLV_RXDMA_START_ADDR_SPIS_RXDMA_STR_ADDR_OFFSET               (0U)
#define SPISLV_RXDMA_START_ADDR_SPIS_RXDMA_STR_ADDR_MASK                 (0xFFFFFFFFU << SPISLV_RXDMA_START_ADDR_SPIS_RXDMA_STR_ADDR_OFFSET)


/* SPI Slave Direct Mode RX DMA Size */
typedef union {
    struct {
        __IO uint32_t SPIS_RXDMA_SIZE                 :16;    /* bits:0-15, RX DMA size in direct mode */
        __IO uint32_t SPIS_RXDMA_THRE                 :16;    /* bits:16-31, RX DMA threshold in directmode An IRQ is asserted when SPIS_RXDMA_FIFO_CNT is larger than this value */
    } field;
    __IO uint32_t word;
} SPISLV_RXDMA_SIZE_T;

#define SPISLV_RXDMA_SIZE_SPIS_RXDMA_SIZE_OFFSET                         (0U)
#define SPISLV_RXDMA_SIZE_SPIS_RXDMA_SIZE_MASK                           (0xFFFFU << SPISLV_RXDMA_SIZE_SPIS_RXDMA_SIZE_OFFSET)
#define SPISLV_RXDMA_SIZE_SPIS_RXDMA_THRE_OFFSET                         (16U)
#define SPISLV_RXDMA_SIZE_SPIS_RXDMA_THRE_MASK                           (0xFFFFU << SPISLV_RXDMA_SIZE_SPIS_RXDMA_THRE_OFFSET)


/* SPI Slave Direct Mode RX DMA Software Control */
typedef union {
    struct {
        __IO uint32_t SPIS_RXDMA_SW_MV_BYTE           :17;    /* bits:0-16, Write this register to move RX DMA read pointer */
        __I  uint32_t __reserved_00                   :15;
    } field;
    __IO uint32_t word;
} SPISLV_RXDMA_SW_CON_T;

#define SPISLV_RXDMA_SW_CON_SPIS_RXDMA_SW_MV_BYTE_OFFSET                 (0U)
#define SPISLV_RXDMA_SW_CON_SPIS_RXDMA_SW_MV_BYTE_MASK                   (0x1FFFFU << SPISLV_RXDMA_SW_CON_SPIS_RXDMA_SW_MV_BYTE_OFFSET)


/* SPI Slave Direct Mode TX DMA Start Address */
typedef union {
    struct {
        __IO uint32_t SPIS_TXDMA_STR_ADDR             :32;    /* bits:0-31, TX DMA start address in direct mode */
    } field;
    __IO uint32_t word;
} SPISLV_TXDMA_START_ADDR_T;

#define SPISLV_TXDMA_START_ADDR_SPIS_TXDMA_STR_ADDR_OFFSET               (0U)
#define SPISLV_TXDMA_START_ADDR_SPIS_TXDMA_STR_ADDR_MASK                 (0xFFFFFFFFU << SPISLV_TXDMA_START_ADDR_SPIS_TXDMA_STR_ADDR_OFFSET)


/* SPI Slave Direct Mode TX DMA Size */
typedef union {
    struct {
        __IO uint32_t SPIS_TXDMA_SIZE                 :16;    /* bits:0-15, TX DMA size in direct mode */
        __IO uint32_t SPIS_TXDMA_THRE                 :16;    /* bits:16-31, TX DMA threshold in directmode An IRQ is asserted when SPIS_TXDMA_FIFO_CNT is less or equal than this value */
    } field;
    __IO uint32_t word;
} SPISLV_TXDMA_SIZE_T;

#define SPISLV_TXDMA_SIZE_SPIS_TXDMA_SIZE_OFFSET                         (0U)
#define SPISLV_TXDMA_SIZE_SPIS_TXDMA_SIZE_MASK                           (0xFFFFU << SPISLV_TXDMA_SIZE_SPIS_TXDMA_SIZE_OFFSET)
#define SPISLV_TXDMA_SIZE_SPIS_TXDMA_THRE_OFFSET                         (16U)
#define SPISLV_TXDMA_SIZE_SPIS_TXDMA_THRE_MASK                           (0xFFFFU << SPISLV_TXDMA_SIZE_SPIS_TXDMA_THRE_OFFSET)


/* SPI Slave Direct Mode TX DMA Software Control */
typedef union {
    struct {
        __IO uint32_t SPIS_TXDMA_SW_MV_BYTE           :17;    /* bits:0-16, Write this register to move TX DMA write pointer */
        __I  uint32_t __reserved_00                   :15;
    } field;
    __IO uint32_t word;
} SPISLV_TXDMA_SW_CON_T;

#define SPISLV_TXDMA_SW_CON_SPIS_TXDMA_SW_MV_BYTE_OFFSET                 (0U)
#define SPISLV_TXDMA_SW_CON_SPIS_TXDMA_SW_MV_BYTE_MASK                   (0x1FFFFU << SPISLV_TXDMA_SW_CON_SPIS_TXDMA_SW_MV_BYTE_OFFSET)


/* SPI Slave Control Register */
typedef union {
    struct {
        __IO uint32_t SPIS_CTRL0                      :7;    /* bits:0-6, SPI slave general configure register Bit[1],Bit[0] no used, default 0. */
        __I  uint32_t __reserved_00                   :1;
        __IO uint32_t SPIS_CTRL1                      :2;    /* bits:8-9, SPI slave general configure register */
        __I  uint32_t __reserved_01                   :6;
        __IO uint32_t SPIS_MISO_EARLY_TRANS           :1;    /* bits:16-16, Early transmission */
        __I  uint32_t __reserved_02                   :7;
        __IO uint32_t SPIS_DIR_MODE                   :1;    /* bits:24-24, Direct mode */
        __I  uint32_t __reserved_03                   :7;
    } field;
    __IO uint32_t word;
} SPISLV_CTRL_T;

#define SPISLV_CTRL_SPIS_CTRL0_OFFSET                                    (0U)
#define SPISLV_CTRL_SPIS_CTRL0_MASK                                      (0x7FU << SPISLV_CTRL_SPIS_CTRL0_OFFSET)
#define SPISLV_CTRL_SPIS_CTRL1_OFFSET                                    (8U)
#define SPISLV_CTRL_SPIS_CTRL1_MASK                                      (0x3U << SPISLV_CTRL_SPIS_CTRL1_OFFSET)
#define SPISLV_CTRL_SPIS_MISO_EARLY_TRANS_OFFSET                         (16U)
#define SPISLV_CTRL_SPIS_MISO_EARLY_TRANS_MASK                           (0x1U << SPISLV_CTRL_SPIS_MISO_EARLY_TRANS_OFFSET)
#define SPISLV_CTRL_SPIS_DIR_MODE_OFFSET                                 (24U)
#define SPISLV_CTRL_SPIS_DIR_MODE_MASK                                   (0x1U << SPISLV_CTRL_SPIS_DIR_MODE_OFFSET)


/* SPI Slave Timeout Threshold Register */
typedef union {
    struct {
        __IO uint32_t SPIS_TMOUT_THR                  :32;    /* bits:0-31, Timeout interrupt threshold Maximum period between CS and the first SCK. An interrupt is generated if the time exceed this period. */
    } field;
    __IO uint32_t word;
} SPISLV_TMOUT_THR_T;

#define SPISLV_TMOUT_THR_SPIS_TMOUT_THR_OFFSET                           (0U)
#define SPISLV_TMOUT_THR_SPIS_TMOUT_THR_MASK                             (0xFFFFFFFFU << SPISLV_TMOUT_THR_SPIS_TMOUT_THR_OFFSET)


/* SPI Slave Buffer Base Address Register */
typedef union {
    struct {
        __IO uint32_t SPIS_BUFFER_BASE_ADDR           :32;    /* bits:0-31, Buffer base address Configurable DMA address to access memory. */
    } field;
    __IO uint32_t word;
} SPISLV_BUFFER_BASE_ADDR_T;

#define SPISLV_BUFFER_BASE_ADDR_SPIS_BUFFER_BASE_ADDR_OFFSET             (0U)
#define SPISLV_BUFFER_BASE_ADDR_SPIS_BUFFER_BASE_ADDR_MASK               (0xFFFFFFFFU << SPISLV_BUFFER_BASE_ADDR_SPIS_BUFFER_BASE_ADDR_OFFSET)


/* SPI Slave Buffer Size Register */
typedef union {
    struct {
        __IO uint32_t SPIS_BUFFER_SIZE                :32;    /* bits:0-31, Buffer base size Configurable buffer size indicating whether SPI master is configured successfully. */
    } field;
    __IO uint32_t word;
} SPISLV_BUFFER_SIZE_T;

#define SPISLV_BUFFER_SIZE_SPIS_BUFFER_SIZE_OFFSET                       (0U)
#define SPISLV_BUFFER_SIZE_SPIS_BUFFER_SIZE_MASK                         (0xFFFFFFFFU << SPISLV_BUFFER_SIZE_SPIS_BUFFER_SIZE_OFFSET)


/* SPI Slave Interrupt Enable */
typedef union {
    struct {
        __IO uint32_t SPIS_IE                         :16;    /* bits:0-15, Interrupt enable [13] - RX_OVERRUN_IE [12] - RX_DMA_IE [11] - TX_DMA_IE [10] - RX_FIFO_FULL_IE [9] - TX_FIFO_EMPTY_IE [8] - TMOUT_ERR_IE [7] - WR_DATA_ERR_IE [6] - RD_DATA_ERR_IE [5] - POWER_ON_IE [4] - POWER_OFF_IE [3] - WR_TRANS_FINISH_IE [2] - RD_TRANS_FINISH_IE [1] - WR_CFG_FINISH_IE [0] - RD_CFG_FINISH_IE */
        __I  uint32_t __reserved_00                   :16;
    } field;
    __IO uint32_t word;
} SPISLV_IE_T;

#define SPISLV_IE_SPIS_IE_OFFSET                                         (0U)
#define SPISLV_IE_SPIS_IE_MASK                                           (0xFFFFU << SPISLV_IE_SPIS_IE_OFFSET)


/* SPI Slave Trigger Register */
typedef union {
    struct {
        __IO uint32_t SPIS_SW_ON                      :1;    /* bits:0-0, Software ON */
        __I  uint32_t __reserved_00                   :7;
        __IO uint32_t SPIS_SW_RST                     :2;    /* bits:8-9, Software reset */
        __I  uint32_t __reserved_01                   :6;
        __IO uint32_t SPIS_TXDMA_SW_RDY               :1;    /* bits:16-16, Ready to transmit data */
        __I  uint32_t __reserved_02                   :7;
        __IO uint32_t SPIS_RXDMA_SW_RDY               :1;    /* bits:24-24, Ready to receive data */
        __I  uint32_t __reserved_03                   :7;
    } field;
    __IO uint32_t word;
} SPISLV_TRIG_T;

#define SPISLV_TRIG_SPIS_SW_ON_OFFSET                                    (0U)
#define SPISLV_TRIG_SPIS_SW_ON_MASK                                      (0x1U << SPISLV_TRIG_SPIS_SW_ON_OFFSET)
#define SPISLV_TRIG_SPIS_SW_RST_OFFSET                                   (8U)
#define SPISLV_TRIG_SPIS_SW_RST_MASK                                     (0x3U << SPISLV_TRIG_SPIS_SW_RST_OFFSET)
#define SPISLV_TRIG_SPIS_TXDMA_SW_RDY_OFFSET                             (16U)
#define SPISLV_TRIG_SPIS_TXDMA_SW_RDY_MASK                               (0x1U << SPISLV_TRIG_SPIS_TXDMA_SW_RDY_OFFSET)
#define SPISLV_TRIG_SPIS_RXDMA_SW_RDY_OFFSET                             (24U)
#define SPISLV_TRIG_SPIS_RXDMA_SW_RDY_MASK                               (0x1U << SPISLV_TRIG_SPIS_RXDMA_SW_RDY_OFFSET)


/* SPI Slave Direct Mode DMA control */
typedef union {
    struct {
        __IO uint32_t SPIS_TX_DMA_START               :1;    /* bits:0-0, empty description */
        __I  uint32_t __reserved_00                   :7;
        __IO uint32_t SPIS_TXDMA_TRANS_TYPE           :2;    /* bits:8-9, TX DMA transaction type in direct mode */
        __I  uint32_t __reserved_01                   :6;
        __IO uint32_t SPIS_RX_DMA_START               :1;    /* bits:16-16, empty description */
        __I  uint32_t __reserved_02                   :7;
        __IO uint32_t SPIS_RXDMA_TRANS_TYPE           :2;    /* bits:24-25, RX DMA transaction type in direct mode */
        __I  uint32_t __reserved_03                   :6;
    } field;
    __IO uint32_t word;
} SPISLV_DIR_MODE_DMA_CON_T;

#define SPISLV_DIR_MODE_DMA_CON_SPIS_TX_DMA_START_OFFSET                 (0U)
#define SPISLV_DIR_MODE_DMA_CON_SPIS_TX_DMA_START_MASK                   (0x1U << SPISLV_DIR_MODE_DMA_CON_SPIS_TX_DMA_START_OFFSET)
#define SPISLV_DIR_MODE_DMA_CON_SPIS_TXDMA_TRANS_TYPE_OFFSET             (8U)
#define SPISLV_DIR_MODE_DMA_CON_SPIS_TXDMA_TRANS_TYPE_MASK               (0x3U << SPISLV_DIR_MODE_DMA_CON_SPIS_TXDMA_TRANS_TYPE_OFFSET)
#define SPISLV_DIR_MODE_DMA_CON_SPIS_RX_DMA_START_OFFSET                 (16U)
#define SPISLV_DIR_MODE_DMA_CON_SPIS_RX_DMA_START_MASK                   (0x1U << SPISLV_DIR_MODE_DMA_CON_SPIS_RX_DMA_START_OFFSET)
#define SPISLV_DIR_MODE_DMA_CON_SPIS_RXDMA_TRANS_TYPE_OFFSET             (24U)
#define SPISLV_DIR_MODE_DMA_CON_SPIS_RXDMA_TRANS_TYPE_MASK               (0x3U << SPISLV_DIR_MODE_DMA_CON_SPIS_RXDMA_TRANS_TYPE_OFFSET)


/* SPI Slave Direct Mode RX Data */
typedef union {
    struct {
        __I  uint32_t SPIS_RX_DATA                    :8;    /* bits:0-7, RX data in direct mode */
        __I  uint32_t __reserved_00                   :24;
    } field;
    __IO uint32_t word;
} SPISLV_DIR_MODE_RX_DATA_T;

#define SPISLV_DIR_MODE_RX_DATA_SPIS_RX_DATA_OFFSET                      (0U)
#define SPISLV_DIR_MODE_RX_DATA_SPIS_RX_DATA_MASK                        (0xFFU << SPISLV_DIR_MODE_RX_DATA_SPIS_RX_DATA_OFFSET)


/* SPI Slave Direct Mode TX Data */
typedef union {
    struct {
        __IO uint32_t SPIS_TX_DATA                    :8;    /* bits:0-7, TX data in direct mode */
        __I  uint32_t __reserved_00                   :24;
    } field;
    __IO uint32_t word;
} SPISLV_DIR_MODE_TX_DATA_T;

#define SPISLV_DIR_MODE_TX_DATA_SPIS_TX_DATA_OFFSET                      (0U)
#define SPISLV_DIR_MODE_TX_DATA_SPIS_TX_DATA_MASK                        (0xFFU << SPISLV_DIR_MODE_TX_DATA_SPIS_TX_DATA_OFFSET)


/* SPI Slave Interrupt */
typedef union {
    struct {
        __IO uint32_t SPIS_INT                        :16;    /* bits:0-15, Interrupt status [13] - RX_OVERRUN_INT, overrun error interrupt [12] - RX_DMA_INT, RX DMA virtual FIFO full interrupt [11] - TX_DMA_INT, TX DMA virtual FIFO EMPTY interrupt [10] - RX_FIFO_FULL_INT, RX FIFO full interupt [9] - TX_FIFO_EMPTY_INT, TX FIFO empty interrupt [8] - TMOUT_ERR_INT, timeout error interrupt [7] - WR_DATA_ERR_INT, SPI master write data error interrupt [6] - RD_DATA_ERR_INT, SPI master read data error interrupt [5] - POWER_ON_INT,SPI slave receive power-on command interrupt [4] - POWER_OFF_INT, SPI slave receive power-off command interrupt [3] - WR_TRANS_FINISH_INT, SPI master write data finish interrupt [2] - RD_TRANS_FINISH_INT, SPI master read data finish interrupt [1] - WR_CFG_FINISH_INT, SPI master configure write finish interrupt [0] - RD_CFG_FINISH_INT, SPI master configure read finish interrupt */
        __I  uint32_t __reserved_00                   :16;
    } field;
    __IO uint32_t word;
} SPISLV_INT_T;

#define SPISLV_INT_SPIS_INT_OFFSET                                       (0U)
#define SPISLV_INT_SPIS_INT_MASK                                         (0xFFFFU << SPISLV_INT_SPIS_INT_OFFSET)


/* SPI Slave Status */
typedef union {
    struct {
        __I  uint32_t SPIS_STA                        :14;    /* bits:0-13, SPI slave staus [13]: SR_POWER_ON SPI slave receives power-on command. Cleared after set SPIS_SW_ON = 1. [12]: SR_POWER_OFF SPI slave receives power-off command. Cleared after set SPIS_SW_ON = 0. [11]: SR_WR_FINISH SPI master write data finish. Cleared after the next CW/CR command. [10]: SR_RD_FINISH SPI master read data finish. Cleared after the next CW/CR command. [9]: SR_CFG_WRITE_FINISH SPI slave receive CW command is finished. Cleared after SR_TXRX_FIFO_RDY = 1. [8]: SR_CFG_READ_FINISH SPI slave receive CR command is finished. Cleared after SR_TXRX_FIFO_RDY = 1. [7]: SR_CMD_ERROR Used for SPI master to debug. Cleared after SPI master sends a correct command. [6]: SR_TIMOUT_ERR SPI slave do not receive sck signal for some time when chip select signal active. If there is error, master must send WS command to clear this bit and poll this bit until this bit turns to 0. [5]: SR_RDWR_FINISH The bit is set to 1 when SPI slave receives/sends all data finished Cleared after SPI slave receives CR/CW command. [4]: SR_WR_ERR After a WR command, master can read this bit to know if there is error in the write transfer through RS command. If there is error, master must send WS command to clear this bit and poll this bit until this bit turns to 0. [3]: SR_RD_ERR After a RD command, master can read this bit to know if there is error in the read transfer through RS. If there is timeout error, master must send WS command to clear this bit and poll this bit until this bit turns to 0. [2]: SR_TXRX_FIFO_RDY When CR, this bit used to indicate whether TX FIFO is ready. Master polls this bit to know if the slave is ready to send data, then master can send RD command. When CW, this bit used to indicate whether RX FIFO is ready. Master polls this bit to know if the slave is ready to send data, then master can send WD command. This bit will be cleared after SPI slave receives CR/CW command. [1]: SR_CFG_SUCESS SPI master configure package address/length successfully. [0]: SR_SLV_ON SPI slave controller enable by set SPIS_SW_ON = 1. After SPI slave receive POWER-ON command, slave software can set this bit by control SPIS_SW_ON. */
        __I  uint32_t __reserved_00                   :2;
        __I  uint32_t SPIS_AHB_STA                    :4;    /* bits:16-19, SPI slave AHB status */
        __I  uint32_t __reserved_01                   :4;
        __I  uint32_t SPIS_FIFO_STA                   :4;    /* bits:24-27, empty description */
        __I  uint32_t __reserved_02                   :4;
    } field;
    __IO uint32_t word;
} SPISLV_STA_T;

#define SPISLV_STA_SPIS_STA_OFFSET                                       (0U)
#define SPISLV_STA_SPIS_STA_MASK                                         (0x3FFFU << SPISLV_STA_SPIS_STA_OFFSET)
#define SPISLV_STA_SPIS_AHB_STA_OFFSET                                   (16U)
#define SPISLV_STA_SPIS_AHB_STA_MASK                                     (0xFU << SPISLV_STA_SPIS_AHB_STA_OFFSET)
#define SPISLV_STA_SPIS_FIFO_STA_OFFSET                                  (24U)
#define SPISLV_STA_SPIS_FIFO_STA_MASK                                    (0xFU << SPISLV_STA_SPIS_FIFO_STA_OFFSET)


/* SPI Slave Transfer Length Register */
typedef union {
    struct {
        __I  uint32_t SPIS_TRANS_LENGTH               :32;    /* bits:0-31, Transfer length  SPI master transfer packet length (byte). */
    } field;
    __IO uint32_t word;
} SPISLV_TRANS_LENGTH_T;

#define SPISLV_TRANS_LENGTH_SPIS_TRANS_LENGTH_OFFSET                     (0U)
#define SPISLV_TRANS_LENGTH_SPIS_TRANS_LENGTH_MASK                       (0xFFFFFFFFU << SPISLV_TRANS_LENGTH_SPIS_TRANS_LENGTH_OFFSET)


/* SPI Slave Transfer Address Register */
typedef union {
    struct {
        __I  uint32_t SPIS_TRANS_ADDR                 :32;    /* bits:0-31, Transfer address SPI master transfer packet start address. */
    } field;
    __IO uint32_t word;
} SPISLV_TRANS_ADDR_T;

#define SPISLV_TRANS_ADDR_SPIS_TRANS_ADDR_OFFSET                         (0U)
#define SPISLV_TRANS_ADDR_SPIS_TRANS_ADDR_MASK                           (0xFFFFFFFFU << SPISLV_TRANS_ADDR_SPIS_TRANS_ADDR_OFFSET)


/* SPI Slave CMD Received */
typedef union {
    struct {
        __I  uint32_t SPIS_CMD_RECEIVED               :8;    /* bits:0-7, Command received */
        __I  uint32_t __reserved_00                   :24;
    } field;
    __IO uint32_t word;
} SPISLV_CMD_RECEIVED_T;

#define SPISLV_CMD_RECEIVED_SPIS_CMD_RECEIVED_OFFSET                     (0U)
#define SPISLV_CMD_RECEIVED_SPIS_CMD_RECEIVED_MASK                       (0xFFU << SPISLV_CMD_RECEIVED_SPIS_CMD_RECEIVED_OFFSET)


/* SPI Slave Direct Mode FIFO Status */
typedef union {
    struct {
        __I  uint32_t SPIS_TX_FIFO_CNT                :7;    /* bits:0-6, The amount of data in TX FIFO */
        __I  uint32_t __reserved_00                   :9;
        __I  uint32_t SPIS_RX_FIFO_CNT                :7;    /* bits:16-22, The amount of data in RX FIFO */
        __I  uint32_t __reserved_01                   :9;
    } field;
    __IO uint32_t word;
} SPISLV_DIR_MODE_FIFO_STA_T;

#define SPISLV_DIR_MODE_FIFO_STA_SPIS_TX_FIFO_CNT_OFFSET                 (0U)
#define SPISLV_DIR_MODE_FIFO_STA_SPIS_TX_FIFO_CNT_MASK                   (0x7FU << SPISLV_DIR_MODE_FIFO_STA_SPIS_TX_FIFO_CNT_OFFSET)
#define SPISLV_DIR_MODE_FIFO_STA_SPIS_RX_FIFO_CNT_OFFSET                 (16U)
#define SPISLV_DIR_MODE_FIFO_STA_SPIS_RX_FIFO_CNT_MASK                   (0x7FU << SPISLV_DIR_MODE_FIFO_STA_SPIS_RX_FIFO_CNT_OFFSET)


/* SPI Slave Direct Mode RX DMA Pointer */
typedef union {
    struct {
        __I  uint32_t SPIS_RXDMA_WPTR                 :16;    /* bits:0-15, RX DMA write pointer */
        __I  uint32_t SPIS_RXDMA_RPTR                 :16;    /* bits:16-31, RX DMA read pointer */
    } field;
    __IO uint32_t word;
} SPISLV_RXDMA_PTR_T;

#define SPISLV_RXDMA_PTR_SPIS_RXDMA_WPTR_OFFSET                          (0U)
#define SPISLV_RXDMA_PTR_SPIS_RXDMA_WPTR_MASK                            (0xFFFFU << SPISLV_RXDMA_PTR_SPIS_RXDMA_WPTR_OFFSET)
#define SPISLV_RXDMA_PTR_SPIS_RXDMA_RPTR_OFFSET                          (16U)
#define SPISLV_RXDMA_PTR_SPIS_RXDMA_RPTR_MASK                            (0xFFFFU << SPISLV_RXDMA_PTR_SPIS_RXDMA_RPTR_OFFSET)


/* SPI Slave Direct Mode RX DMA FIFO Count */
typedef union {
    struct {
        __I  uint32_t SPIS_RXDMA_FIFO_CNT             :17;    /* bits:0-16, The amount of data in RX DMA vritual FIFO */
        __I  uint32_t __reserved_00                   :15;
    } field;
    __IO uint32_t word;
} SPISLV_RXDMA_FIFO_CNT_T;

#define SPISLV_RXDMA_FIFO_CNT_SPIS_RXDMA_FIFO_CNT_OFFSET                 (0U)
#define SPISLV_RXDMA_FIFO_CNT_SPIS_RXDMA_FIFO_CNT_MASK                   (0x1FFFFU << SPISLV_RXDMA_FIFO_CNT_SPIS_RXDMA_FIFO_CNT_OFFSET)


/* SPI Slave Direct Mode RX DMA Byte Available */
typedef union {
    struct {
        __I  uint32_t SPIS_RXDMA_BYTE_AVAIL           :17;    /* bits:0-16, The amount of available bytes in RX DMA virtual FIFO */
        __I  uint32_t __reserved_00                   :15;
    } field;
    __IO uint32_t word;
} SPISLV_RXDMA_BYTE_AVAIL_T;

#define SPISLV_RXDMA_BYTE_AVAIL_SPIS_RXDMA_BYTE_AVAIL_OFFSET             (0U)
#define SPISLV_RXDMA_BYTE_AVAIL_SPIS_RXDMA_BYTE_AVAIL_MASK               (0x1FFFFU << SPISLV_RXDMA_BYTE_AVAIL_SPIS_RXDMA_BYTE_AVAIL_OFFSET)


/* SPI Slave Direct Mode TX DMA Pointer */
typedef union {
    struct {
        __I  uint32_t SPIS_TXDMA_WPTR                 :16;    /* bits:0-15, TX DMA write pointer */
        __I  uint32_t SPIS_TXDMA_RPTR                 :16;    /* bits:16-31, TX DMA read pointer */
    } field;
    __IO uint32_t word;
} SPISLV_TXDMA_PTR_T;

#define SPISLV_TXDMA_PTR_SPIS_TXDMA_WPTR_OFFSET                          (0U)
#define SPISLV_TXDMA_PTR_SPIS_TXDMA_WPTR_MASK                            (0xFFFFU << SPISLV_TXDMA_PTR_SPIS_TXDMA_WPTR_OFFSET)
#define SPISLV_TXDMA_PTR_SPIS_TXDMA_RPTR_OFFSET                          (16U)
#define SPISLV_TXDMA_PTR_SPIS_TXDMA_RPTR_MASK                            (0xFFFFU << SPISLV_TXDMA_PTR_SPIS_TXDMA_RPTR_OFFSET)


/* SPI Slave Direct Mode TX DMA FIFO Count */
typedef union {
    struct {
        __I  uint32_t SPIS_TXDMA_FIFO_CNT             :17;    /* bits:0-16, The amount of data in TX DMA vritual FIFO */
        __I  uint32_t __reserved_00                   :15;
    } field;
    __IO uint32_t word;
} SPISLV_TXDMA_FIFO_CNT_T;

#define SPISLV_TXDMA_FIFO_CNT_SPIS_TXDMA_FIFO_CNT_OFFSET                 (0U)
#define SPISLV_TXDMA_FIFO_CNT_SPIS_TXDMA_FIFO_CNT_MASK                   (0x1FFFFU << SPISLV_TXDMA_FIFO_CNT_SPIS_TXDMA_FIFO_CNT_OFFSET)


/* SPI Slave Direct Mode TX DMA Byte Available */
typedef union {
    struct {
        __I  uint32_t SPIS_TXDMA_BYTE_AVAIL           :17;    /* bits:0-16, The amount of available bytes in TX DMA virtual FIFO */
        __I  uint32_t __reserved_00                   :15;
    } field;
    __IO uint32_t word;
} SPISLV_TXDMA_BYTE_AVAIL_T;

#define SPISLV_TXDMA_BYTE_AVAIL_SPIS_TXDMA_BYTE_AVAIL_OFFSET             (0U)
#define SPISLV_TXDMA_BYTE_AVAIL_SPIS_TXDMA_BYTE_AVAIL_MASK               (0x1FFFFU << SPISLV_TXDMA_BYTE_AVAIL_SPIS_TXDMA_BYTE_AVAIL_OFFSET)


/* SPI Slave Debug Register */
typedef union {
    struct {
        __I  uint32_t SPIS_TX_FIFO_WPTR_H             :6;    /* bits:0-5, empty description */
        __I  uint32_t __reserved_00                   :2;
        __I  uint32_t SPIS_TX_FIFO_RPTR_H             :6;    /* bits:8-13, empty description */
        __I  uint32_t __reserved_01                   :2;
        __I  uint32_t SPIS_RX_FIFO_WPTR_H             :6;    /* bits:16-21, empty description */
        __I  uint32_t __reserved_02                   :2;
        __I  uint32_t SPIS_RX_FIFO_RPTR_H             :6;    /* bits:24-29, empty description */
        __I  uint32_t __reserved_03                   :2;
    } field;
    __IO uint32_t word;
} SPISLV_DEBUG1_T;

#define SPISLV_DEBUG1_SPIS_TX_FIFO_WPTR_H_OFFSET                         (0U)
#define SPISLV_DEBUG1_SPIS_TX_FIFO_WPTR_H_MASK                           (0x3FU << SPISLV_DEBUG1_SPIS_TX_FIFO_WPTR_H_OFFSET)
#define SPISLV_DEBUG1_SPIS_TX_FIFO_RPTR_H_OFFSET                         (8U)
#define SPISLV_DEBUG1_SPIS_TX_FIFO_RPTR_H_MASK                           (0x3FU << SPISLV_DEBUG1_SPIS_TX_FIFO_RPTR_H_OFFSET)
#define SPISLV_DEBUG1_SPIS_RX_FIFO_WPTR_H_OFFSET                         (16U)
#define SPISLV_DEBUG1_SPIS_RX_FIFO_WPTR_H_MASK                           (0x3FU << SPISLV_DEBUG1_SPIS_RX_FIFO_WPTR_H_OFFSET)
#define SPISLV_DEBUG1_SPIS_RX_FIFO_RPTR_H_OFFSET                         (24U)
#define SPISLV_DEBUG1_SPIS_RX_FIFO_RPTR_H_MASK                           (0x3FU << SPISLV_DEBUG1_SPIS_RX_FIFO_RPTR_H_OFFSET)


/* SPI Slave Debug Register */
typedef union {
    struct {
        __I  uint32_t SPIS_TX_FIFO_WPTR_B             :6;    /* bits:0-5, empty description */
        __I  uint32_t __reserved_00                   :2;
        __I  uint32_t SPIS_TX_FIFO_RPTR_B             :6;    /* bits:8-13, empty description */
        __I  uint32_t __reserved_01                   :2;
        __I  uint32_t SPIS_RX_FIFO_WPTR_B             :6;    /* bits:16-21, empty description */
        __I  uint32_t __reserved_02                   :2;
        __I  uint32_t SPIS_RX_FIFO_RPTR_B             :6;    /* bits:24-29, empty description */
        __I  uint32_t __reserved_03                   :2;
    } field;
    __IO uint32_t word;
} SPISLV_DEBUG2_T;

#define SPISLV_DEBUG2_SPIS_TX_FIFO_WPTR_B_OFFSET                         (0U)
#define SPISLV_DEBUG2_SPIS_TX_FIFO_WPTR_B_MASK                           (0x3FU << SPISLV_DEBUG2_SPIS_TX_FIFO_WPTR_B_OFFSET)
#define SPISLV_DEBUG2_SPIS_TX_FIFO_RPTR_B_OFFSET                         (8U)
#define SPISLV_DEBUG2_SPIS_TX_FIFO_RPTR_B_MASK                           (0x3FU << SPISLV_DEBUG2_SPIS_TX_FIFO_RPTR_B_OFFSET)
#define SPISLV_DEBUG2_SPIS_RX_FIFO_WPTR_B_OFFSET                         (16U)
#define SPISLV_DEBUG2_SPIS_RX_FIFO_WPTR_B_MASK                           (0x3FU << SPISLV_DEBUG2_SPIS_RX_FIFO_WPTR_B_OFFSET)
#define SPISLV_DEBUG2_SPIS_RX_FIFO_RPTR_B_OFFSET                         (24U)
#define SPISLV_DEBUG2_SPIS_RX_FIFO_RPTR_B_MASK                           (0x3FU << SPISLV_DEBUG2_SPIS_RX_FIFO_RPTR_B_OFFSET)


typedef struct {
    SPISLV_DIR_MODE_FIFO_CON_T               spislv_dir_mode_fifo_con; /* offset: 0x00000000, SPI Slave Direct Mode FIFO Control */
    SPISLV_RXDMA_START_ADDR_T                 spislv_rxdma_start_addr; /* offset: 0x00000004, SPI Slave Direct Mode RX DMA Start Address */
    SPISLV_RXDMA_SIZE_T                             spislv_rxdma_size; /* offset: 0x00000008, SPI Slave Direct Mode RX DMA Size */
    SPISLV_RXDMA_SW_CON_T                         spislv_rxdma_sw_con; /* offset: 0x0000000C, SPI Slave Direct Mode RX DMA Software Control */
    SPISLV_TXDMA_START_ADDR_T                 spislv_txdma_start_addr; /* offset: 0x00000010, SPI Slave Direct Mode TX DMA Start Address */
    SPISLV_TXDMA_SIZE_T                             spislv_txdma_size; /* offset: 0x00000014, SPI Slave Direct Mode TX DMA Size */
    SPISLV_TXDMA_SW_CON_T                         spislv_txdma_sw_con; /* offset: 0x00000018, SPI Slave Direct Mode TX DMA Software Control */
    SPISLV_CTRL_T                                         spislv_ctrl; /* offset: 0x0000001C, SPI Slave Control Register */
    SPISLV_TMOUT_THR_T                               spislv_tmout_thr; /* offset: 0x00000020, SPI Slave Timeout Threshold Register */
    SPISLV_BUFFER_BASE_ADDR_T                 spislv_buffer_base_addr; /* offset: 0x00000024, SPI Slave Buffer Base Address Register */
    SPISLV_BUFFER_SIZE_T                           spislv_buffer_size; /* offset: 0x00000028, SPI Slave Buffer Size Register */
    SPISLV_IE_T                                             spislv_ie; /* offset: 0x0000002C, SPI Slave Interrupt Enable */
    SPISLV_TRIG_T                                         spislv_trig; /* offset: 0x00000030, SPI Slave Trigger Register */
    SPISLV_DIR_MODE_DMA_CON_T                 spislv_dir_mode_dma_con; /* offset: 0x00000034, SPI Slave Direct Mode DMA control */
    SPISLV_DIR_MODE_RX_DATA_T                 spislv_dir_mode_rx_data; /* offset: 0x00000038, SPI Slave Direct Mode RX Data */
    SPISLV_DIR_MODE_TX_DATA_T                 spislv_dir_mode_tx_data; /* offset: 0x0000003C, SPI Slave Direct Mode TX Data */
    SPISLV_INT_T                                           spislv_int; /* offset: 0x00000040, SPI Slave Interrupt */
    SPISLV_STA_T                                           spislv_sta; /* offset: 0x00000044, SPI Slave Status */
    SPISLV_TRANS_LENGTH_T                         spislv_trans_length; /* offset: 0x00000048, SPI Slave Transfer Length Register */
    SPISLV_TRANS_ADDR_T                             spislv_trans_addr; /* offset: 0x0000004C, SPI Slave Transfer Address Register */
    SPISLV_CMD_RECEIVED_T                         spislv_cmd_received; /* offset: 0x00000050, SPI Slave CMD Received */
    SPISLV_DIR_MODE_FIFO_STA_T               spislv_dir_mode_fifo_sta; /* offset: 0x00000054, SPI Slave Direct Mode FIFO Status */
    SPISLV_RXDMA_PTR_T                               spislv_rxdma_ptr; /* offset: 0x00000058, SPI Slave Direct Mode RX DMA Pointer */
    SPISLV_RXDMA_FIFO_CNT_T                     spislv_rxdma_fifo_cnt; /* offset: 0x0000005C, SPI Slave Direct Mode RX DMA FIFO Count */
    SPISLV_RXDMA_BYTE_AVAIL_T                 spislv_rxdma_byte_avail; /* offset: 0x00000060, SPI Slave Direct Mode RX DMA Byte Available */
    SPISLV_TXDMA_PTR_T                               spislv_txdma_ptr; /* offset: 0x00000064, SPI Slave Direct Mode TX DMA Pointer */
    SPISLV_TXDMA_FIFO_CNT_T                     spislv_txdma_fifo_cnt; /* offset: 0x00000068, SPI Slave Direct Mode TX DMA FIFO Count */
    SPISLV_TXDMA_BYTE_AVAIL_T                 spislv_txdma_byte_avail; /* offset: 0x0000006C, SPI Slave Direct Mode TX DMA Byte Available */
    uint32_t                                        __reserved_00[12]; /* offset: 0x00000070, padding size: 0x00000030 */
    SPISLV_DEBUG1_T                                     spislv_debug1; /* offset: 0x000000A0, SPI Slave Debug Register */
    SPISLV_DEBUG2_T                                     spislv_debug2; /* offset: 0x000000A4, SPI Slave Debug Register */
} SPIS_REGISTER_T;


/* Bit definition for SPIS Control0 Register */
#define SPIS_CTRL_SIZE_OF_ADDR_OFFSET   (6)
#define SPIS_CTRL_SIZE_OF_ADDR_MASK     (0x1<<SPIS_CTRL_SIZE_OF_ADDR_OFFSET)
#define SPIS_CTRL_TYPE_OFFSET           (4)
#define SPIS_CTRL_TYPE_MASK             (0x3<<SPIS_CTRL_TYPE_OFFSET)
#define SPIS_CTRL_RXMSBF_OFFSET         (3)
#define SPIS_CTRL_RXMSBF_MASK           (0x1<<SPIS_CTRL_RXMSBF_OFFSET)
#define SPIS_CTRL_TXMSBF_OFFSET         (2)
#define SPIS_CTRL_TXMSBF_MASK           (0x1<<SPIS_CTRL_TXMSBF_OFFSET)


/* Bit definition for SPIS Control1 Register */
#define SPIS_CTRL_DEC_ADDR_EN_OFFSET    (1)
#define SPIS_CTRL_DEC_ADDR_EN_MASK      (0x1<<SPIS_CTRL_DEC_ADDR_EN_OFFSET)
#define SPIS_CTRL_SW_RDY_EN_OFFSET      (0)
#define SPIS_CTRL_SW_RDY_EN_MASK        (0x1<<SPIS_CTRL_SW_RDY_EN_OFFSET)
/* Bit definition for SPIS Interrupt Enable Register */
#define SPIS_IE_OFFSET                  (0)
#define SPIS_IE_MASK                    (0x1ff<<SPIS_IE_OFFSET)
#define SPIS_IE_RD_CFG_FINISH_OFFSET    (0)
#define SPIS_IE_RD_CFG_FINISH_MASK      (0x1<<SPIS_IE_RD_CFG_FINISH_OFFSET)
#define SPIS_IE_WR_CFG_FINISH_OFFSET    (1)
#define SPIS_IE_WR_CFG_FINISH_MASK      (0x1<<SPIS_IE_WR_CFG_FINISH_OFFSET)
#define SPIS_IE_RD_TRANS_FINISH_OFFSET  (2)
#define SPIS_IE_RD_TRANS_FINISH_MASK    (0x1<<SPIS_IE_RD_TRANS_FINISH_OFFSET)
#define SPIS_IE_WR_TRANS_FINISH_OFFSET  (3)
#define SPIS_IE_WR_TRANS_FINISH_MASK    (0x1<<SPIS_IE_WR_TRANS_FINISH_OFFSET)
#define SPIS_IE_POWER_OFF_OFFSET        (4)
#define SPIS_IE_POWER_OFF_MASK          (0x1<<SPIS_IE_POWER_OFF_OFFSET)
#define SPIS_IE_POWER_ON_OFFSET         (5)
#define SPIS_IE_POWER_ON_MASK           (0x1<<SPIS_IE_POWER_ON_OFFSET)
#define SPIS_IE_RD_DATA_ERR_OFFSET      (6)
#define SPIS_IE_RD_DATA_ERR_MASK        (0x1<<SPIS_IE_RD_DATA_ERR_OFFSET)
#define SPIS_IE_WR_DATA_ERR_OFFSET      (7)
#define SPIS_IE_WR_DATA_ERR_MASK        (0x1<<SPIS_IE_WR_DATA_ERR_OFFSET)
#define SPIS_IE_TMOUT_ERR_OFFSET        (8)
#define SPIS_IE_TMOUT_ERR_MASK          (0x1<<SPIS_IE_TMOUT_ERR_OFFSET)
#define SPIS_IE_DIRECT_MODE_OFFSET      (8)
#define SPIS_IE_DIRECT_MODE_MASK        (0x3f<<SPIS_IE_DIRECT_MODE_OFFSET)
#define SPIS_IE_IDLE_TMOUT_OFFSET       (8)
#define SPIS_IE_IDLE_TMOUT_MASK         (0x1<<SPIS_IE_IDLE_TMOUT_OFFSET)
#define SPIS_IE_TX_FIFO_EMPTY_OFFSET    (9)
#define SPIS_IE_TX_FIFO_EMPTY_MASK      (0x1<<SPIS_IE_TX_FIFO_EMPTY_OFFSET)
#define SPIS_IE_RX_FIFO_FULL_OFFSET     (10)
#define SPIS_IE_RX_FIFO_FULL_MASK       (0x1<<SPIS_IE_RX_FIFO_FULL_OFFSET)
#define SPIS_IE_TX_DMA_EMPTY_OFFSET     (11)
#define SPIS_IE_TX_DMA_EMPTY_MASK       (0x1<<SPIS_IE_TX_DMA_EMPTY_OFFSET)
#define SPIS_IE_RX_DMA_FULL_OFFSET      (12)
#define SPIS_IE_RX_DMA_FULL_MASK        (0x1<<SPIS_IE_RX_DMA_FULL_OFFSET)
#define SPIS_IE_RX_OVERRUN_OFFSET       (13)
#define SPIS_IE_RX_OVERRUN_MASK         (0x1<<SPIS_IE_RX_OVERRUN_OFFSET)

/* Bit definition for SPIS Interrupt Register */
#define SPIS_INT_OFFSET                  (0)
#define SPIS_INT_MASK                    (0x1ff<<SPIS_INT_OFFSET)
#define SPIS_INT_RD_CFG_FINISH_OFFSET    (0)
#define SPIS_INT_RD_CFG_FINISH_MASK      (0x1<<SPIS_INT_RD_CFG_FINISH_OFFSET)
#define SPIS_INT_WR_CFG_FINISH_OFFSET    (1)
#define SPIS_INT_WR_CFG_FINISH_MASK      (0x1<<SPIS_INT_WR_CFG_FINISH_OFFSET)
#define SPIS_INT_RD_TRANS_FINISH_OFFSET  (2)
#define SPIS_INT_RD_TRANS_FINISH_MASK    (0x1<<SPIS_INT_RD_TRANS_FINISH_OFFSET)
#define SPIS_INT_WR_TRANS_FINISH_OFFSET  (3)
#define SPIS_INT_WR_TRANS_FINISH_MASK    (0x1<<SPIS_INT_WR_TRANS_FINISH_OFFSET)
#define SPIS_INT_POWER_OFF_OFFSET        (4)
#define SPIS_INT_POWER_OFF_MASK          (0x1<<SPIS_INT_POWER_OFF_OFFSET)
#define SPIS_INT_POWER_ON_OFFSET         (5)
#define SPIS_INT_POWER_ON_MASK           (0x1<<SPIS_INT_POWER_ON_OFFSET)
#define SPIS_INT_RD_DATA_ERR_OFFSET      (6)
#define SPIS_INT_RD_DATA_ERR_MASK        (0x1<<SPIS_INT_RD_DATA_ERR_OFFSET)
#define SPIS_INT_WR_DATA_ERR_OFFSET      (7)
#define SPIS_INT_WR_DATA_ERR_MASK        (0x1<<SPIS_INT_WR_DATA_ERR_OFFSET)
#define SPIS_INT_TMOUT_ERR_OFFSET        (8)
#define SPIS_INT_TMOUT_ERR_MASK          (0x1<<SPIS_INT_TMOUT_ERR_OFFSET)
#define SPIS_INT_DIRECT_MODE_OFFSET      (8)
#define SPIS_INT_DIRECT_MODE_MASK        (0x3f<<SPIS_INT_DIRECT_MODE_OFFSET)
#define SPIS_INT_IDLE_TMOUT_OFFSET       (8)
#define SPIS_INT_IDLE_TMOUT_MASK         (0x1<<SPIS_INT_IDLE_TMOUT_OFFSET)
#define SPIS_INT_TX_FIFO_EMPTY_OFFSET    (9)
#define SPIS_INT_TX_FIFO_EMPTY_MASK      (0x1<<SPIS_INT_TX_FIFO_EMPTY_OFFSET)
#define SPIS_INT_RX_FIFO_FULL_OFFSET     (10)
#define SPIS_INT_RX_FIFO_FULL_MASK       (0x1<<SPIS_INT_RX_FIFO_FULL_OFFSET)
#define SPIS_INT_TX_DMA_EMPTY_OFFSET     (11)
#define SPIS_INT_TX_DMA_EMPTY_MASK       (0x1<<SPIS_INT_TX_DMA_EMPTY_OFFSET)
#define SPIS_INT_RX_DMA_FULL_OFFSET      (12)
#define SPIS_INT_RX_DMA_FULL_MASK        (0x1<<SPIS_INT_RX_DMA_FULL_OFFSET)
#define SPIS_INT_RX_OVERRUN_OFFSET      (13)
#define SPIS_INT_RX_OVERRUN_MASK        (0x1<<SPIS_INT_RX_OVERRUN_OFFSET)

/* Bit definition for SPIS Interrupt Register */
#define SPIS_STA_SLV_ON_OFFSET           (0)
#define SPIS_STA_SLV_ON_MASK             (0x1<<SPIS_STA_SLV_ON_OFFSET)
#define SPIS_STA_CFG_SUCCESS_OFFSET      (1)
#define SPIS_STA_CFG_SUCCESS_MASK        (0x1<<SPIS_STA_CFG_SUCCESS_OFFSET)
#define SPIS_STA_TXRX_FIFO_RDY_OFFSET    (2)
#define SPIS_STA_TXRX_FIFO_RDY_MASK      (0x1<<SPIS_STA_TXRX_FIFO_RDY_OFFSET)
#define SPIS_STA_RD_ERR_OFFSET           (3)
#define SPIS_STA_RD_ERR_MASK             (0x1<<SPIS_STA_RD_ERR_OFFSET)
#define SPIS_STA_WR_ERR_OFFSET           (4)
#define SPIS_STA_WR_ERR_MASK             (0x1<<SPIS_STA_WR_ERR_OFFSET)
#define SPIS_STA_RDWR_FINISH_OFFSET      (5)
#define SPIS_STA_RDWR_FINISH_MASK        (0x1<<SPIS_STA_RDWR_FINISH_OFFSET)
#define SPIS_STA_TIMOUT_ERR_OFFSET       (6)
#define SPIS_STA_TIMOUT_ERR_MASK         (0x1<<SPIS_STA_TIMOUT_ERR_OFFSET)
#define SPIS_STA_CMD_ERR_OFFSET          (7)
#define SPIS_STA_CMD_ERR_MASK            (0x1<<SPIS_STA_CMD_ERR_OFFSET)
#define SPIS_STA_CFG_READ_FINISH_OFFSET  (8)
#define SPIS_STA_CFG_READ_FINISH_MASK    (0x1<<SPIS_STA_CFG_READ_FINISH_OFFSET)
#define SPIS_STA_CFG_WRITE_FINISH_OFFSET (9)
#define SPIS_STA_CFG_WRITE_FINISH_MASK   (0x1<<SPIS_STA_CFG_WRITE_FINISH_OFFSET)
#define SPIS_STA_RD_FINISH_OFFSET        (10)
#define SPIS_STA_RD_FINISH_MASK          (0x1<<SPIS_STA_RD_FINISH_OFFSET)
#define SPIS_STA_WR_FINISH_OFFSET        (11)
#define SPIS_STA_WR_FINISH_MASK          (0x1<<SPIS_STA_WR_FINISH_OFFSET)
#define SPIS_STA_POWER_OFF_OFFSET        (12)
#define SPIS_STA_POWER_OFF_MASK          (0x1<<SPIS_STA_POWER_OFF_OFFSET)
#define SPIS_STA_POWER_ON_OFFSET         (13)
#define SPIS_STA_POWER_ON_MASK           (0x1<<SPIS_STA_POWER_ON_OFFSET)

#endif /* __SPI_SLAVE_REG_DEFINITION_H__ */