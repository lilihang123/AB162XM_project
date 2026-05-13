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

#ifndef __SPI_MASTER_0_REG_DEFINITION_H__
#define __SPI_MASTER_0_REG_DEFINITION_H__


/* SPI Master Trigger Register */
typedef union {
    struct {
        __IO uint32_t SPIM_RESUME                     :1;    /* bits:0-0, Resume transfer */
        __I  uint32_t __reserved_00                   :7;
        __IO uint32_t SPIM_RST                        :1;    /* bits:8-8, Software reset */
        __I  uint32_t __reserved_01                   :23;
    } field;
    __IO uint32_t word;
} SPIMST_TRIG_T;

#define SPIMST_TRIG_SPIM_RESUME_OFFSET                                   (0U)
#define SPIMST_TRIG_SPIM_RESUME_MASK                                     (0x1U << SPIMST_TRIG_SPIM_RESUME_OFFSET)
#define SPIMST_TRIG_SPIM_RST_OFFSET                                      (8U)
#define SPIMST_TRIG_SPIM_RST_MASK                                        (0x1U << SPIMST_TRIG_SPIM_RST_OFFSET)


/* SPI Master Interrupt */
typedef union {
    struct {
        __I  uint32_t SPIM_INT                        :2;    /* bits:0-1, Interrupt status [1] - PAUSE_INT, SPI master completes the transfer and enters PAUSE state [0] - FINISH_INT, SPI master completes the transfer and enters IDLE state */
        __I  uint32_t __reserved_00                   :30;
    } field;
    __IO uint32_t word;
} SPIMST_INT_T;

#define SPIMST_INT_SPIM_INT_OFFSET                                       (0U)
#define SPIMST_INT_SPIM_INT_MASK                                         (0x3U << SPIMST_INT_SPIM_INT_OFFSET)


/* SPI Master TX Source Address Register */
typedef union {
    struct {
        __IO uint32_t SPIM_TX_SRC                     :32;    /* bits:0-31, TX data source address This register defines the memory address from which SPI master starts to read RX data. The address must be aligned to word boundary. */
    } field;
    __IO uint32_t word;
} SPIMST_TX_SRC_T;

#define SPIMST_TX_SRC_SPIM_TX_SRC_OFFSET                                 (0U)
#define SPIMST_TX_SRC_SPIM_TX_SRC_MASK                                   (0xFFFFFFFFU << SPIMST_TX_SRC_SPIM_TX_SRC_OFFSET)


/* SPI Master RX Destination Address Register */
typedef union {
    struct {
        __IO uint32_t SPIM_RX_DST                     :32;    /* bits:0-31, RX data destination address This register defines the memory address to which the SPI master starts to store RX data. The address must be aligned to word boundary. */
    } field;
    __IO uint32_t word;
} SPIMST_RX_DST_T;

#define SPIMST_RX_DST_SPIM_RX_DST_OFFSET                                 (0U)
#define SPIMST_RX_DST_SPIM_RX_DST_MASK                                   (0xFFFFFFFFU << SPIMST_RX_DST_SPIM_RX_DST_OFFSET)


/* SPI Master Control 0 Register */
typedef union {
    struct {
        __IO uint32_t SPIM_CTRL0                      :7;    /* bits:0-6, SPI master general configure register */
        __I  uint32_t __reserved_00                   :1;
        __IO uint32_t SPIM_DEASSERT_EN                :1;    /* bits:8-8, Deassert mode enable */
        __I  uint32_t __reserved_01                   :7;
        __IO uint32_t SPIM_PAUSE_EN                   :1;    /* bits:16-16, Pause mode enable */
        __I  uint32_t __reserved_02                   :7;
        __IO uint32_t SPIM_DEBUG_EN                   :1;    /* bits:24-24, Debug monitor enable */
        __I  uint32_t __reserved_03                   :7;
    } field;
    __IO uint32_t word;
} SPIMST_CTRL0_T;

#define SPIMST_CTRL0_SPIM_CTRL0_OFFSET                                   (0U)
#define SPIMST_CTRL0_SPIM_CTRL0_MASK                                     (0x7FU << SPIMST_CTRL0_SPIM_CTRL0_OFFSET)
#define SPIMST_CTRL0_SPIM_DEASSERT_EN_OFFSET                             (8U)
#define SPIMST_CTRL0_SPIM_DEASSERT_EN_MASK                               (0x1U << SPIMST_CTRL0_SPIM_DEASSERT_EN_OFFSET)
#define SPIMST_CTRL0_SPIM_PAUSE_EN_OFFSET                                (16U)
#define SPIMST_CTRL0_SPIM_PAUSE_EN_MASK                                  (0x1U << SPIMST_CTRL0_SPIM_PAUSE_EN_OFFSET)
#define SPIMST_CTRL0_SPIM_DEBUG_EN_OFFSET                                (24U)
#define SPIMST_CTRL0_SPIM_DEBUG_EN_MASK                                  (0x1U << SPIMST_CTRL0_SPIM_DEBUG_EN_OFFSET)


/* SPI Master Control 1 Register */
typedef union {
    struct {
        __IO uint32_t SPIM_CTRL1                      :4;    /* bits:0-3, SPI master general configure register */
        __I  uint32_t __reserved_00                   :4;
        __IO uint32_t SPIM_GET_DLY                    :3;    /* bits:8-10, Rx data sampling delay in read mode Total delay = SPIM_GET_DLY * 12.8ns */
        __I  uint32_t __reserved_01                   :5;
        __IO uint32_t SPIM_TXDMA_EN                   :1;    /* bits:16-16, TX DMA enable */
        __I  uint32_t __reserved_02                   :7;
        __IO uint32_t SPIM_RXDMA_EN                   :1;    /* bits:24-24, RX DMA enable */
        __I  uint32_t __reserved_03                   :7;
    } field;
    __IO uint32_t word;
} SPIMST_CTRL1_T;

#define SPIMST_CTRL1_SPIM_CTRL1_OFFSET                                   (0U)
#define SPIMST_CTRL1_SPIM_CTRL1_MASK                                     (0xFU << SPIMST_CTRL1_SPIM_CTRL1_OFFSET)
#define SPIMST_CTRL1_SPIM_GET_DLY_OFFSET                                 (8U)
#define SPIMST_CTRL1_SPIM_GET_DLY_MASK                                   (0x7U << SPIMST_CTRL1_SPIM_GET_DLY_OFFSET)
#define SPIMST_CTRL1_SPIM_TXDMA_EN_OFFSET                                (16U)
#define SPIMST_CTRL1_SPIM_TXDMA_EN_MASK                                  (0x1U << SPIMST_CTRL1_SPIM_TXDMA_EN_OFFSET)
#define SPIMST_CTRL1_SPIM_RXDMA_EN_OFFSET                                (24U)
#define SPIMST_CTRL1_SPIM_RXDMA_EN_MASK                                  (0x1U << SPIMST_CTRL1_SPIM_RXDMA_EN_OFFSET)


/* SPI Master Configuration 0 Register */
typedef union {
    struct {
        __IO uint32_t SPIM_CS_HOLD_CNT                :16;    /* bits:0-15, Chip select hold time Hold time = (SPIM_CS_HOLD_COUNT+3) * CLK_PERIOD */
        __IO uint32_t SPIM_CS_SETUP_CNT               :16;    /* bits:16-31, Chip select setup time Setup time = (SPIM_CS_SETUP_CNT+1) * CLK_PERIOD */
    } field;
    __IO uint32_t word;
} SPIMST_CFG0_T;

#define SPIMST_CFG0_SPIM_CS_HOLD_CNT_OFFSET                              (0U)
#define SPIMST_CFG0_SPIM_CS_HOLD_CNT_MASK                                (0xFFFFU << SPIMST_CFG0_SPIM_CS_HOLD_CNT_OFFSET)
#define SPIMST_CFG0_SPIM_CS_SETUP_CNT_OFFSET                             (16U)
#define SPIMST_CFG0_SPIM_CS_SETUP_CNT_MASK                               (0xFFFFU << SPIMST_CFG0_SPIM_CS_SETUP_CNT_OFFSET)


/* SPI Master Configuration 1 Register */
typedef union {
    struct {
        __IO uint32_t SPIM_SCK_HIGH_CNT               :16;    /* bits:0-15, SPI matser clock high time SCK high time = (SPIM_SCK_HIGH_CNT+1) * CLK_PERIOD */
        __IO uint32_t SPIM_SCK_LOW_CNT                :16;    /* bits:16-31, SPI matser clock low time SCK low time = (SPIM_SCK_LOW_CNT+1) * CLK_PERIOD */
    } field;
    __IO uint32_t word;
} SPIMST_CFG1_T;

#define SPIMST_CFG1_SPIM_SCK_HIGH_CNT_OFFSET                             (0U)
#define SPIMST_CFG1_SPIM_SCK_HIGH_CNT_MASK                               (0xFFFFU << SPIMST_CFG1_SPIM_SCK_HIGH_CNT_OFFSET)
#define SPIMST_CFG1_SPIM_SCK_LOW_CNT_OFFSET                              (16U)
#define SPIMST_CFG1_SPIM_SCK_LOW_CNT_MASK                                (0xFFFFU << SPIMST_CFG1_SPIM_SCK_LOW_CNT_OFFSET)


/* SPI Master Configuration 2 Register */
typedef union {
    struct {
        __IO uint32_t SPIM_CS_IDLE_CNT                :8;    /* bits:0-7, Chip select idle time  Time between consecutive transfer = (CS_HOLD_COUNT+1) * CLK_PERIOD */
        __IO uint32_t SPIM_PACKET_LOOP_CNT            :8;    /* bits:8-15, Transfer loop times The number of packets in one transfer = PACKET_LOOP_CNT + 1 */
        __IO uint32_t SPIM_PACKET_LENGTH_CNT          :16;    /* bits:16-31, Transfer packet length The number of bytes in one packet = PACKET_LENGTH + 1. Total bytes of one transfer = (PACKET_LENGTH+1) * (PACKET_LOOP_CNT+1). */
    } field;
    __IO uint32_t word;
} SPIMST_CFG2_T;

#define SPIMST_CFG2_SPIM_CS_IDLE_CNT_OFFSET                              (0U)
#define SPIMST_CFG2_SPIM_CS_IDLE_CNT_MASK                                (0xFFU << SPIMST_CFG2_SPIM_CS_IDLE_CNT_OFFSET)
#define SPIMST_CFG2_SPIM_PACKET_LOOP_CNT_OFFSET                          (8U)
#define SPIMST_CFG2_SPIM_PACKET_LOOP_CNT_MASK                            (0xFFU << SPIMST_CFG2_SPIM_PACKET_LOOP_CNT_OFFSET)
#define SPIMST_CFG2_SPIM_PACKET_LENGTH_CNT_OFFSET                        (16U)
#define SPIMST_CFG2_SPIM_PACKET_LENGTH_CNT_MASK                          (0xFFFFU << SPIMST_CFG2_SPIM_PACKET_LENGTH_CNT_OFFSET)


/* SPI Master Configuration 3 Register */
typedef union {
    struct {
        __IO uint32_t SPIM_COMMAND_CNT                :4;    /* bits:0-3, Command count The number of command bytes in one packet. Command phase is the first transmission of packet before dummy phase and data phase. Command phase is always single SPI. */
        __I  uint32_t __reserved_00                   :4;
        __IO uint32_t SPIM_DUMMY_CNT                  :4;    /* bits:8-11, Dummy count The number of dummy bits in one packet. Dummy phase is the second transmission of packet between command phase and data phase. */
        __I  uint32_t __reserved_01                   :4;
        __IO uint32_t SPIM_BT_HW_EN                   :1;    /* bits:16-16, empty description */
        __I  uint32_t __reserved_02                   :7;
        __IO uint32_t SPIM_TX_MOSI_CLR_EN             :1;    /* bits:24-24, empty description */
        __IO uint32_t SPIM_TX_MOSI_CLR_DATA           :1;    /* bits:25-25, empty description */
        __I  uint32_t __reserved_03                   :6;
    } field;
    __IO uint32_t word;
} SPIMST_CFG3_T;

#define SPIMST_CFG3_SPIM_COMMAND_CNT_OFFSET                              (0U)
#define SPIMST_CFG3_SPIM_COMMAND_CNT_MASK                                (0xFU << SPIMST_CFG3_SPIM_COMMAND_CNT_OFFSET)
#define SPIMST_CFG3_SPIM_DUMMY_CNT_OFFSET                                (8U)
#define SPIMST_CFG3_SPIM_DUMMY_CNT_MASK                                  (0xFU << SPIMST_CFG3_SPIM_DUMMY_CNT_OFFSET)
#define SPIMST_CFG3_SPIM_BT_HW_EN_OFFSET                                 (16U)
#define SPIMST_CFG3_SPIM_BT_HW_EN_MASK                                   (0x1U << SPIMST_CFG3_SPIM_BT_HW_EN_OFFSET)
#define SPIMST_CFG3_SPIM_TX_MOSI_CLR_EN_OFFSET                           (24U)
#define SPIMST_CFG3_SPIM_TX_MOSI_CLR_EN_MASK                             (0x1U << SPIMST_CFG3_SPIM_TX_MOSI_CLR_EN_OFFSET)
#define SPIMST_CFG3_SPIM_TX_MOSI_CLR_DATA_OFFSET                         (25U)
#define SPIMST_CFG3_SPIM_TX_MOSI_CLR_DATA_MASK                           (0x1U << SPIMST_CFG3_SPIM_TX_MOSI_CLR_DATA_OFFSET)


/* SPI Master Configuration 4 Register */
typedef union {
    struct {
        __IO uint32_t SPIM_SEL_ADDR                   :4;    /* bits:0-3, SPI master selection address */
        __I  uint32_t __reserved_00                   :4;
        __IO uint32_t SPIM_SEL_WDATA                  :3;    /* bits:8-10, SPI master selection write data */
        __I  uint32_t __reserved_01                   :5;
        __I  uint32_t SPIM_SEL_RDATA                  :3;    /* bits:16-18, SPI master selection read data */
        __I  uint32_t __reserved_02                   :5;
        __IO uint32_t SPIM_IE                         :2;    /* bits:24-25, Interrupt enable [1] - PAUSE_INT, SPI master completes the transfer and enters PAUSE state [0] - FINISH_INT, SPI master completes the transfer and enters IDLE state */
        __I  uint32_t __reserved_03                   :6;
    } field;
    __IO uint32_t word;
} SPIMST_CFG4_T;

#define SPIMST_CFG4_SPIM_SEL_ADDR_OFFSET                                 (0U)
#define SPIMST_CFG4_SPIM_SEL_ADDR_MASK                                   (0xFU << SPIMST_CFG4_SPIM_SEL_ADDR_OFFSET)
#define SPIMST_CFG4_SPIM_SEL_WDATA_OFFSET                                (8U)
#define SPIMST_CFG4_SPIM_SEL_WDATA_MASK                                  (0x7U << SPIMST_CFG4_SPIM_SEL_WDATA_OFFSET)
#define SPIMST_CFG4_SPIM_SEL_RDATA_OFFSET                                (16U)
#define SPIMST_CFG4_SPIM_SEL_RDATA_MASK                                  (0x7U << SPIMST_CFG4_SPIM_SEL_RDATA_OFFSET)
#define SPIMST_CFG4_SPIM_IE_OFFSET                                       (24U)
#define SPIMST_CFG4_SPIM_IE_MASK                                         (0x3U << SPIMST_CFG4_SPIM_IE_OFFSET)


/* SPI Master Configuration 5 Register */
typedef union {
    struct {
        __IO uint32_t SPIM_B2B_DELAY_CNT              :16;    /* bits:0-15, unit: bclk */
        __IO uint32_t SPIM_SB2NB_CNT                  :5;    /* bits:16-20, unit: bclk,one latency location */
        __I  uint32_t __reserved_00                   :3;
        __IO uint32_t SPIM_B2B_DELAY_EN               :1;    /* bits:24-24, empty description */
        __I  uint32_t __reserved_01                   :7;
    } field;
    __IO uint32_t word;
} SPIMST_CFG5_T;

#define SPIMST_CFG5_SPIM_B2B_DELAY_CNT_OFFSET                            (0U)
#define SPIMST_CFG5_SPIM_B2B_DELAY_CNT_MASK                              (0xFFFFU << SPIMST_CFG5_SPIM_B2B_DELAY_CNT_OFFSET)
#define SPIMST_CFG5_SPIM_SB2NB_CNT_OFFSET                                (16U)
#define SPIMST_CFG5_SPIM_SB2NB_CNT_MASK                                  (0x1FU << SPIMST_CFG5_SPIM_SB2NB_CNT_OFFSET)
#define SPIMST_CFG5_SPIM_B2B_DELAY_EN_OFFSET                             (24U)
#define SPIMST_CFG5_SPIM_B2B_DELAY_EN_MASK                               (0x1U << SPIMST_CFG5_SPIM_B2B_DELAY_EN_OFFSET)


/* SPI Master COMMAND ACTIVE */
typedef union {
    struct {
        __IO uint32_t SPIM_CMD_ACT                    :1;    /* bits:0-0, Start transfer */
        __I  uint32_t __reserved_00                   :31;
    } field;
    __IO uint32_t word;
} SPIMST_CMD_ACT_T;

#define SPIMST_CMD_ACT_SPIM_CMD_ACT_OFFSET                               (0U)
#define SPIMST_CMD_ACT_SPIM_CMD_ACT_MASK                                 (0x1U << SPIMST_CMD_ACT_SPIM_CMD_ACT_OFFSET)


/* SPI Master RX Data */
typedef union {
    struct {
        __I  uint32_t SPIM_RX_DATA                    :32;    /* bits:0-31, RX data The depth of the RX FIFO is 32 bytes. Read from this register to read 4 bytes from RX FIFO. The RX FIFO pointer will automatically move toward the next four bytes. */
    } field;
    __IO uint32_t word;
} SPIMST_RX_DATA_T;

#define SPIMST_RX_DATA_SPIM_RX_DATA_OFFSET                               (0U)
#define SPIMST_RX_DATA_SPIM_RX_DATA_MASK                                 (0xFFFFFFFFU << SPIMST_RX_DATA_SPIM_RX_DATA_OFFSET)


/* SPI Master TX Data */
typedef union {
    struct {
        __IO uint32_t SPIM_TX_DATA                    :32;    /* bits:0-31, TX data The depth of the TX FIFO is 32 bytes. Write to this register to write 4 bytes to TX FIFO. The TX FIFO pointer will automatically move toward the next four bytes. */
    } field;
    __IO uint32_t word;
} SPIMST_TX_DATA_T;

#define SPIMST_TX_DATA_SPIM_TX_DATA_OFFSET                               (0U)
#define SPIMST_TX_DATA_SPIM_TX_DATA_MASK                                 (0xFFFFFFFFU << SPIMST_TX_DATA_SPIM_TX_DATA_OFFSET)


/* SPI Master Status */
typedef union {
    struct {
        __I  uint32_t SPIM_BUSY                       :1;    /* bits:0-0, SPI matser status */
        __I  uint32_t __reserved_00                   :7;
        __I  uint32_t SPIM_BT_TRIG_STA                :1;    /* bits:8-8, empty description */
        __I  uint32_t __reserved_01                   :23;
    } field;
    __IO uint32_t word;
} SPIMST_STA_T;

#define SPIMST_STA_SPIM_BUSY_OFFSET                                      (0U)
#define SPIMST_STA_SPIM_BUSY_MASK                                        (0x1U << SPIMST_STA_SPIM_BUSY_OFFSET)
#define SPIMST_STA_SPIM_BT_TRIG_STA_OFFSET                               (8U)
#define SPIMST_STA_SPIM_BT_TRIG_STA_MASK                                 (0x1U << SPIMST_STA_SPIM_BT_TRIG_STA_OFFSET)


typedef struct {
    SPIMST_TX_SRC_T                                     spimst_tx_src; /* offset: 0x00000008, SPI Master TX Source Address Register */
    SPIMST_RX_DST_T                                     spimst_rx_dst; /* offset: 0x0000000C, SPI Master RX Destination Address Register */
    SPIMST_CTRL0_T                                       spimst_ctrl0; /* offset: 0x00000010, SPI Master Control 0 Register */
    SPIMST_CTRL1_T                                       spimst_ctrl1; /* offset: 0x00000014, SPI Master Control 1 Register */
    SPIMST_CFG0_T                                         spimst_cfg0; /* offset: 0x00000018, SPI Master Configuration 0 Register */
    SPIMST_CFG1_T                                         spimst_cfg1; /* offset: 0x0000001C, SPI Master Configuration 1 Register */
    SPIMST_CFG2_T                                         spimst_cfg2; /* offset: 0x00000020, SPI Master Configuration 2 Register */
    SPIMST_CFG3_T                                         spimst_cfg3; /* offset: 0x00000024, SPI Master Configuration 3 Register */
    SPIMST_CFG4_T                                         spimst_cfg4; /* offset: 0x00000028, SPI Master Configuration 4 Register */
    SPIMST_CFG5_T                                         spimst_cfg5; /* offset: 0x0000002C, SPI Master Configuration 5 Register */
    SPIMST_CMD_ACT_T                                   spimst_cmd_act; /* offset: 0x00000030, SPI Master COMMAND ACTIVE */
    SPIMST_RX_DATA_T                                   spimst_rx_data; /* offset: 0x00000034, SPI Master RX Data */
    SPIMST_TX_DATA_T                                   spimst_tx_data; /* offset: 0x00000038, SPI Master TX Data */
    SPIMST_STA_T                                           spimst_sta; /* offset: 0x0000003C, SPI Master Status */
    SPIMST_TRIG_T                                         spimst_trig; /* offset: 0x00000000, SPI Master Trigger Register */
    SPIMST_INT_T                                           spimst_int; /* offset: 0x00000004, SPI Master Interrupt */
} SPIM_REGISTER_T;



/* SPIM_INT register definitions */
#define SPIM_INT_FINISH_INT_OFFSET              (0)
#define SPIM_INT_FINISH_INT_MASK                (0x1<<SPIM_INT_FINISH_INT_OFFSET)
#define SPIM_INT_PAUSE_INT_OFFSET               (1)
#define SPIM_INT_PAUSE_INT_MASK                 (0x1<<SPIM_INT_PAUSE_INT_OFFSET)

/* SPIM_STATUS register definitions */
#define SPIM_STATUS_BUSY_OFFSET                 (0)
#define SPIM_STATUS_BUSY_MASK                   (0x1<<SPIM_STATUS_BUSY_OFFSET)

/* SPIM_CFG1 register definitions */
#define SPIM_CFG1_SCK_HIGH_COUNT_OFFSET         (0)
#define SPIM_CFG1_SCK_HIGH_COUNT_MASK           (0xffff<<SPIM_CFG1_SCK_HIGH_COUNT_OFFSET)
#define SPIM_CFG1_SCK_LOW_COUNT_OFFSET          (16)
#define SPIM_CFG1_SCK_LOW_COUNT_MASK            (0xffff<<SPIM_CFG1_SCK_LOW_COUNT_OFFSET)


/* SPIM_CTRL0 register definitions */
#define SPIM_CTRL0_CPHA_OFFSET                  (0)
#define SPIM_CTRL0_CPHA_MASK                    (0x1<<SPIM_CTRL0_CPHA_OFFSET)
#define SPIM_CTRL0_CPOL_OFFSET                  (1)
#define SPIM_CTRL0_CPOL_MASK                    (0x1<<SPIM_CTRL0_CPOL_OFFSET)
#define SPIM_CTRL0_TXMSBF_OFFSET                (2)
#define SPIM_CTRL0_TXMSBF_MASK                  (0x1<<SPIM_CTRL0_TXMSBF_OFFSET)
#define SPIM_CTRL0_RXMSBF_OFFSET                (3)
#define SPIM_CTRL0_RXMSBF_MASK                  (0x1<<SPIM_CTRL0_RXMSBF_OFFSET)
#define SPIM_CTRL0_MSBF_OFFSET                  (2)
#define SPIM_CTRL0_MSBF_MASK                    (0x3<<SPIM_CTRL0_MSBF_OFFSET)
#define SPIM_CTRL0_TYPE_OFFSET                  (4)
#define SPIM_CTRL0_TYPE_MASK                    (0x3<<SPIM_CTRL0_TYPE_OFFSET)
#define SPIM_CTRL0_RW_MODE_OFFSET               (6)
#define SPIM_CTRL0_RW_MODE_MASK                 (0x1<<SPIM_CTRL0_RW_MODE_OFFSET)

/* SPIM_CTRL1 register definitions */
#define SPIM_CTRL1_SAMPLE_SEL_OFFSET            (0)
#define SPIM_CTRL1_SAMPLE_SEL_MASK              (0x1<<SPIM_CTRL1_SAMPLE_SEL_OFFSET)
#define SPIM_CTRL1_CS_POL_OFFSET                (1)
#define SPIM_CTRL1_CS_POL_MASK                  (0x1<<SPIM_CTRL1_CS_POL_OFFSET)
#define SPIM_CTRL1_TX_ENDIAN_OFFSET             (2)
#define SPIM_CTRL1_TX_ENDIAN_MASK               (0x1<<SPIM_CTRL1_TX_ENDIAN_OFFSET)
#define SPIM_CTRL1_RX_ENDIAN_OFFSET             (3)
#define SPIM_CTRL1_RX_ENDIAN_MASK               (0x1<<SPIM_CTRL1_RX_ENDIAN_OFFSET)
#define SPIM_CTRL1_ENDIAN_OFFSET                (2)
#define SPIM_CTRL1_ENDIAN_MASK                  (0x3<<SPIM_CTRL1_ENDIAN_OFFSET)


/* SPIM_CFG0 register definitions */
#define SPIM_CFG0_CS_HOLD_COUNT_OFFSET          (0)
#define SPIM_CFG0_CS_HOLD_COUNT_MASK            (0xffff<<SPIM_CFG0_CS_HOLD_COUNT_OFFSET)
#define SPIM_CFG0_CS_SETUP_COUNT_OFFSET         (16)
#define SPIM_CFG0_CS_SETUP_COUNT_MASK           (0xffff<<SPIM_CFG0_CS_SETUP_COUNT_OFFSET)

/* SPIM_CFG1 register definitions */
#define SPIM_CFG1_SCK_HIGH_COUNT_OFFSET         (0)
#define SPIM_CFG1_SCK_HIGH_COUNT_MASK           (0xffff<<SPIM_CFG1_SCK_HIGH_COUNT_OFFSET)
#define SPIM_CFG1_SCK_LOW_COUNT_OFFSET          (16)
#define SPIM_CFG1_SCK_LOW_COUNT_MASK            (0xffff<<SPIM_CFG1_SCK_LOW_COUNT_OFFSET)

/* SPIM_CFG2 register definitions */
#define SPIM_CFG2_CS_IDLE_COUNT_OFFSET          (0)
#define SPIM_CFG2_CS_IDLE_COUNT_MASK            (0xff<<SPIM_CFG2_CS_IDLE_COUNT_OFFSET)
#define SPIM_CFG2_PACKET_LOOP_COUNT_OFFSET      (8)
#define SPIM_CFG2_PACKET_LOOP_COUNT_MASK        (0xff<<SPIM_CFG2_PACKET_LOOP_COUNT_OFFSET)
#define SPIM_CFG2_PACKET_LENGTH_OFFSET          (16)
#define SPIM_CFG2_PACKET_LENGTH_MASK            (0xffff<<SPIM_CFG2_PACKET_LENGTH_OFFSET)

/* SPIM_CFG3 register definitions */
#define SPIM_CFG3_COMMAND_COUNT_OFFSET          (0)
#define SPIM_CFG3_COMMAND_COUNT_MASK            (0xff<<SPIM_CFG3_COMMAND_COUNT_OFFSET)
#define SPIM_CFG3_DUMMY_COUNT_OFFSET            (8)
#define SPIM_CFG3_DUMMY_COUNT_MASK              (0xff<<SPIM_CFG3_DUMMY_COUNT_OFFSET)

/* SPIMST_CFG4 register definitions */
#define SPIM_CFG4_SEL_ADDR_OFFSET               (0)
#define SPIM_CFG4_SEL_ADDR_MASK                 (0xf<<SPIM_CFG4_SEL_ADDR_OFFSET)
#define SPIM_CFG4_SEL_WDATA_OFFSET              (8)
#define SPIM_CFG4_SEL_WDATA_MASK                (0x7<<SPIM_CFG4_SEL_WDATA_OFFSET)
#define SPIM_CFG4_SEL_RDATA_OFFSET              (16)
#define SPIM_CFG4_SEL_RDATA_MASK                (0x7<<SPIM_CFG4_SEL_RDATA_OFFSET)
#define SPIM_IE_OFFSET                          (24)
#define SPIM_IE_MASK                            (0x3<<SPIM_IE_OFFSET)
#define SPIM_IE_FINISH_IE_OFFSET                (24)
#define SPIM_IE_FINISH_IE_MASK                  (0x1<<SPIM_IE_FINISH_IE_OFFSET)
#define SPIM_IE_PAUSE_IE_OFFSET                 (25)
#define SPIM_IE_PAUSE_IE_MASK                   (0x1<<SPIM_IE_PAUSE_IE_OFFSET)

#endif /*__SPI_MASTER_0_REG_DEFINITION_H__*/
