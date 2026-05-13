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

#ifndef __DMA_REG_DEFINITION_H__
#define __DMA_REG_DEFINITION_H__


#include <stdint.h>


/**************************dma hardware definition start line***********************************/

#define DMA_GLB_RUNNING_BIT_MASK(channel)   (1 << (2 * (channel)))
#define DMA_GLB_IRQ_STA_BIT_MASK(channel)   ((1 << (2 * (channel) + 1)))
#define DMA_GLB_IRQ_CFG_BIT_MASK(channel)   (1 << (channel))

typedef struct {
    __I  uint32_t GLB_STA;                      /* offset 0x00 */
    __I  uint32_t GLB_STA2;                     /* offset 0x04 */
    __I  uint32_t GLB_CPU0_CFG;                 /* offset 0x08 */
    __O  uint32_t GLB_CPU0_SET;                 /* offset 0x0C */
    __O  uint32_t GLB_CPU0_CLR;                 /* offset 0x10 */
    __I  uint32_t GLB_CPU1_CFG;                 /* offset 0x14 */
    __O  uint32_t GLB_CPU1_SET;                 /* offset 0x18 */
    __O  uint32_t GLB_CPU1_CLR;                 /* offset 0x1C */
    __I  uint32_t __RESERVED_1[13];             /* padding 0x34 */
    __I  uint32_t GLB_CPU2_CFG;                 /* offset 0x50 */
    __O  uint32_t GLB_CPU2_SET;                 /* offset 0x54 */
    __O  uint32_t GLB_CPU2_CLR;                 /* offset 0x58 */
    __I  uint32_t __RESERVED_2[2];              /* padding 0x8 */
    __I  uint32_t GLB_CPU3_CFG;                 /* offset 0x60 */
    __O  uint32_t GLB_CPU3_SET;                 /* offset 0x64 */
    __O  uint32_t GLB_CPU3_CLR;                 /* offset 0x68 */
} GDMA_0_REG_T;

typedef struct {
    __I  uint32_t RG_GLB_STA;               /* offset + 0x00 */
    __IO uint32_t RESERVE1[1];
    __I  uint32_t RG_GLB_CPU0_INT_CFG;      /* offset + 0x08 */
    __IO uint32_t RG_GLB_CPU0_INT_SET;      /* offset + 0x0C */
    __IO uint32_t RG_GLB_CPU0_INT_CLR;      /* offset + 0x10 */
    __I  uint32_t RG_GLB_CPU1_INT_CFG;      /* offset + 0x14 */
    __IO uint32_t RG_GLB_CPU1_INT_SET;      /* offset + 0x18 */
    __IO uint32_t RG_GLB_CPU1_INT_CLR;      /* offset + 0x1C */
    __I  uint32_t RG_GLB_SWRST;             /* offset + 0x20 */
    __IO uint32_t RESERVE2[1];
    __I  uint32_t RG_GLB_LIMITER;           /* offset + 0x28 */
    __IO uint32_t RESERVE3[5];
    __I  uint32_t RG_GLB_BUSY;              /* offset + 0x40 */
    __I  uint32_t RG_GLB_INTR;              /* offset + 0x44 */
    __IO uint32_t RESERVE4[2];
    __I  uint32_t RG_GLB_CPU2_INT_CFG;      /* offset + 0x50 */
    __IO uint32_t RG_GLB_CPU2_INT_SET;      /* offset + 0x54 */
    __IO uint32_t RG_GLB_CPU2_INT_CLR;      /* offset + 0x58 */
    __IO uint32_t RESERVE5[1];
    __I  uint32_t RG_GLB_CPU3_INT_CFG;      /* offset + 0x60 */
    __IO uint32_t RG_GLB_CPU3_INT_SET;      /* offset + 0x64 */
    __IO uint32_t RG_GLB_CPU3_INT_CLR;      /* offset + 0x68 */
    __IO uint32_t RESERVE6[1];
    __I  uint32_t RG_GLB_CLK_CFG;           /* offset + 0x70 */
    __IO uint32_t RG_GLB_CLK_SET;           /* offset + 0x74 */
    __IO uint32_t RG_GLB_CLK_CLR;           /* offset + 0x78 */
} DMA_REGISTER_GLOABL_T;

/* GDMA channel register definition */
typedef struct {
    __IO uint32_t GDMA_SRC;          /*!<  general dma source address register */
    __IO uint32_t GDMA_DST;          /*!<  general dma destination address register */
    __IO uint32_t GDMA_WPPT;         /*!<  general dma wrap point address register */
    __IO uint32_t GDMA_WPTO;         /*!<  general dma wrap to address register */
    __IO uint32_t GDMA_COUNT;        /*!<  general dma transfer counter  register */
    union {
        struct {
            __IO uint8_t GDMA_DIRECTION ; /* general dma incremental source address */
            __IO uint8_t GDMA_SIZE;       /* general dma data size */
            __IO uint8_t GDMA_SETTING;    /* general dma throttle and handshake control for dma transter */
            __IO uint8_t GDMA_ITEN;       /* general dma interrupt enable */
        } GDMA_CON_CELLS;
        __IO uint32_t GDMA_CON;           /*!<  general dma control register */
    } GDMA_CON_UNION;
    __IO uint32_t GDMA_START;        /*!<  general dma start register */
    __IO uint32_t GDMA_INTSTA;       /*!<  general dma interrupt status register*/
    __O  uint32_t GDMA_ACKINT;       /*!<  generall dma interrupt acknowledge register*/
    __I  uint32_t GDMA_RLCT;         /*!<  general dma remaining length of current transfer register*/
    __IO uint32_t GDMA_LIMITER;      /*!<  general dma bandwidth limiter*/
} GDMA_REGISTER_T;

/* GDMA_CON definition */
#define GDMA_CON_SINC_OFFSET                 (0)
#define GDMA_CON_SINC_MASK                   (0x1 << GDMA_CON_SINC_OFFSET)

#define GDMA_CON_DINC_OFFSET                 (1)
#define GDMA_CON_DINC_MASK                   (0x1 << GDMA_CON_DINC_OFFSET)

#define GDMA_CON_WPSD_OFFSET                 (2)
#define GDMA_CON_WPSD_MASK                   (0x1 << GDMA_CON_WPSD_OFFSET)

#define GDMA_CON_WPEN_OFFSET                 (3)
#define GDMA_CON_WPEN_MASK                   (0x1 << GDMA_CON_WPEN_OFFSET)

#define GDMA_CON_SIZE_OFFSET                 (8)
#define GDMA_CON_SIZE_MASK                   (0x3 << GDMA_CON_SIZE_OFFSET)
#define GDMA_CON_SIZE_BYTE                    0
#define GDMA_CON_SIZE_HALF_WORD               1
#define GDMA_CON_SIZE_WORD                    2

#define GDMA_CON_DREQ_OFFSET                 (16)
#define GDMA_CON_DREQ_MASK                   (0x1 << GDMA_CON_DREQ_OFFSET)

#define GDMA_CON_BURST_OFFSET                (18)
#define GDMA_CON_BURST_MASK                  (0x3 << GDMA_CON_BURST_OFFSET)
#define GDMA_CON_BURST_SINGLE                 0
#define GDMA_CON_BURST_4_BEAT                 2

#define GDMA_CON_ITEN_OFFSET                 (24)
#define GDMA_CON_ITEN_MASK                   (0x1 << GDMA_CON_ITEN_OFFSET)

/* GDMA_COUNT definition */
#define GDMA_COUNT_BIT_OFFSET                (0)
#define GDMA_COUNT_BIT_MASK                  (0xFFFF << GDMA_COUNT_BIT_OFFSET)

/* GDMA_START definition */
#define GDMA_START_BIT_OFFSET                (15)
#define GDMA_START_BIT_MASK                  (0x1 << GDMA_START_BIT_OFFSET)

/* GDMA_INTSTA definition */
#define GDMA_INTSTA_BIT_OFFSET               (15)
#define GDMA_INTSTA_BIT_MASK                 (0x1 << GDMA_INTSTA_BIT_OFFSET)

/* GDMA_ACKINT definition */
#define GDMA_ACKINT_BIT_OFFSET               (15)
#define GDMA_ACKINT_BIT_MASK                 (0x1 << GDMA_ACKINT_BIT_OFFSET)

/* GDMA_GLB index definition */
#define GDMA_GLB_INDEX                       (0)

/* DMA top hierarchy interrupt config */
typedef union {
    struct {
        __IO uint32_t CPU0_CFG_TX                     :1;    /* bits:0-0, Channel TX CPU0 interrupt enable configure */
        __IO uint32_t CPU0_CFG_RX                     :1;    /* bits:1-1, Channel RX CPU0 interrupt enable configure */
        __I  uint32_t __reserved_00                   :30;
    } field;
    __IO uint32_t word;
} DMA_GLB_CPU0_CFG_T;

#define DMA_GLB_CPU0_CFG_CPU0_CFG_TX_OFFSET                              (0U)
#define DMA_GLB_CPU0_CFG_CPU0_CFG_TX_MASK                                (0x1U << DMA_GLB_CPU0_CFG_CPU0_CFG_TX_OFFSET)
#define DMA_GLB_CPU0_CFG_CPU0_CFG_RX_OFFSET                              (1U)
#define DMA_GLB_CPU0_CFG_CPU0_CFG_RX_MASK                                (0x1U << DMA_GLB_CPU0_CFG_CPU0_CFG_RX_OFFSET)


/* DMA top hierarchy interrupt config */
typedef union {
    struct {
        __IO uint32_t CPU1_CFG_TX                     :1;    /* bits:0-0, Channel TX CPU1 interrupt enable configure */
        __IO uint32_t CPU1_CFG_RX                     :1;    /* bits:1-1, Channel RX CPU1 interrupt enable configure */
        __I  uint32_t __reserved_00                   :30;
    } field;
    __IO uint32_t word;
} DMA_GLB_CPU1_CFG_T;

#define DMA_GLB_CPU1_CFG_CPU1_CFG_TX_OFFSET                              (0U)
#define DMA_GLB_CPU1_CFG_CPU1_CFG_TX_MASK                                (0x1U << DMA_GLB_CPU1_CFG_CPU1_CFG_TX_OFFSET)
#define DMA_GLB_CPU1_CFG_CPU1_CFG_RX_OFFSET                              (1U)
#define DMA_GLB_CPU1_CFG_CPU1_CFG_RX_MASK                                (0x1U << DMA_GLB_CPU1_CFG_CPU1_CFG_RX_OFFSET)


/* DMA channel clock config */
typedef union {
    struct {
        __I  uint32_t CLK_CFG_TX                      :1;    /* bits:0-0, Channel TX clock enable configure */
        __I  uint32_t CLK_CFG_RX                      :1;    /* bits:1-1, Channel RX clock enable configure */
        __I  uint32_t __reserved_00                   :30;
    } field;
    __IO uint32_t word;
} DMA_GLB_CLK_CFG_T;

#define DMA_GLB_CLK_CFG_CLK_CFG_TX_OFFSET                                (0U)
#define DMA_GLB_CLK_CFG_CLK_CFG_TX_MASK                                  (0x1U << DMA_GLB_CLK_CFG_CLK_CFG_TX_OFFSET)
#define DMA_GLB_CLK_CFG_CLK_CFG_RX_OFFSET                                (1U)
#define DMA_GLB_CLK_CFG_CLK_CFG_RX_MASK                                  (0x1U << DMA_GLB_CLK_CFG_CLK_CFG_RX_OFFSET)


/* DMA channel TX transfer count */
typedef union {
    struct {
        __IO uint32_t COUNT                           :16;    /* bits:0-15, The amount of total transfer counts This register specifies the amount of total transfer counts the DMA channel must perform. When complete, the DMA channel generates an interrupt request for the processor while ITEN in PDMAn_CON is set to 1. Note: the total size of data transferred by a DMA channel is determined by LEN and the SIZE in PDMAn_CON (i.e. LEN x SIZE). */
        __I  uint32_t __reserved_00                   :16;
    } field;
    __IO uint32_t word;
} PDMA_COUNT_T;

#define PDMA_COUNT_COUNT_OFFSET                                       (0U)
#define PDMA_COUNT_COUNT_MASK                                         (0xFFFFU << PDMA_COUNT_COUNT_OFFSET)


/* DMA channel TX control */
typedef union {
    struct {
        /* bits:0-4
         * [0] Incremental source address. The source addresses increment every transfer.
         *     If the setting of SIZE is byte, the source addresses will increase by 1 every single transfer.
         *     If half-word, it will increase by 2; and if word, increase by 4.
         * [1] Incremental destination address. The destination addresses increases each transfer.
         *     If the setting of SIZE is in bytes, the destination addresses will increase by 1 for each transfer.
         *     If half-word, it will increase by 2; and if word, increase by 4.
         * [2] Wrap select:
         *     The side using address-wrapping function.
         *     Only one side of a DMA channel can activate the address-wrapping function at a time.
         * [3] Wrap enable:
         *     Address-wrapping for ring buffer and double buffer.
         *     The next address of DMA jumps to WRAP TO address when the current address matches WRAP POINT count.
         * [4] Directions of PDMA transfer
         *     The direction is from the perspective of the DMA masters.
         *     WRITE means reading from master and then writing to the address specified in PDMAn_PGMADDR, and vice versa.
         *     No effect on channel 1. */
        __IO uint32_t DIRECTION                       :5;
        __I  uint32_t __reserved_00                   :3;
        /* bits:8-9, Data size of a bus cycle per transfer.
         * These bits restrict the data transfer size between the source and destination to the specified value for one bus cycle.
         * The size is measured in bytes, and the maximum value is 4 bytes.
         * It is mainly decided by the data width of a DMA master. */
        __IO uint32_t SIZE                            :2;
        __I  uint32_t __reserved_01                   :6;
        /* bits:16-19
         * [16] Throttle and handshake control for DMA transfer.
         *     The DMA master can throttle down the transfer rate by the request-grant handshake.
         * [17] Byte to word Word-to-byte or byte-to-word transfer for the application of transferring non-word-aligned-address data to word-aligned-address data.
         *     Note: BURST must be set to 4-beat burst and the SIZE is set to byte to enable this function.
         * [19:18] Transfer type
         *     Burst-type transfers have better bus efficiency.
         *     We recommend using this type of transfer for mass data movement.
         * Note: the burst-type transfer does not stop until all of the beats in a burst are complete, or the transfer length is reached.
         *     The available transfer types are limited by the SIZE. If SIZE is 00b (i.e. byte transfer), all four transfer types can be used.
         *     If SIZE is 01b (i.e. half-word transfer), 16-beat incremental burst cannot be used. If SIZE is 10b (i.e. word transfer),
         *     only single and 4-beat incremental burst can be used. */
        __IO uint32_t SETTING                         :4;
        __I  uint32_t __reserved_02                   :4;
        __IO uint32_t ITEN                            :1;    /* bits:24-24, Enable DMA transfer completion interrupt */
        __I  uint32_t __reserved_03                   :7;
    } field;
    __IO uint32_t word;
} PDMA_CON_T;

#define PDMA_CON_DIRECTION_OFFSET                                     (0U)
#define PDMA_CON_DIRECTION_MASK                                       (0x1FU << PDMA_CON_DIRECTION_OFFSET)
#define PDMA_CON_SIZE_OFFSET                                          (8U)
#define PDMA_CON_SIZE_MASK                                            (0x3U << PDMA_CON_SIZE_OFFSET)
#define PDMA_CON_SETTING_OFFSET                                       (16U)
#define PDMA_CON_SETTING_MASK                                         (0xFU << PDMA_CON_SETTING_OFFSET)
#define PDMA_CON_ITEN_OFFSET                                          (24U)
#define PDMA_CON_ITEN_MASK                                            (0x1U << PDMA_CON_ITEN_OFFSET)

/* PDMA_CON definition */
#define PDMA_CON_SINC_OFFSET                 (0)
#define PDMA_CON_SINC_MASK                   (0x1 << PDMA_CON_SINC_OFFSET)

#define PDMA_CON_DINC_OFFSET                 (1)
#define PDMA_CON_DINC_MASK                   (0x1 << PDMA_CON_DINC_OFFSET)

#define PDMA_CON_WPSD_OFFSET                 (2)
#define PDMA_CON_WPSD_MASK                   (0x1 << PDMA_CON_WPSD_OFFSET)

#define PDMA_CON_WPEN_OFFSET                 (3)
#define PDMA_CON_WPEN_MASK                   (0x1 << PDMA_CON_WPEN_OFFSET)

#define PDMA_CON_DIR_OFFSET                  (4)
#define PDMA_CON_DIR_MASK                    (0x1 << PDMA_CON_DIR_OFFSET)
#define PDMA_CON_DIR_TX                       0
#define PDMA_CON_DIR_RX                       1

#define PDMA_CON_DREQ_OFFSET                 (16)
#define PDMA_CON_DREQ_MASK                   (0x1 << PDMA_CON_DREQ_OFFSET)

#define PDMA_CON_B2W_OFFSET                  (17)
#define PDMA_CON_B2W_MASK                    (0x1 << PDMA_CON_B2W_OFFSET)

#define PDMA_CON_BURST_OFFSET                (18)
#define PDMA_CON_BURST_MASK                  (0x3 << PDMA_CON_BURST_OFFSET)
#define PDMA_CON_BURST_SINGLE                 0
#define PDMA_CON_BURST_4_BEAT                 2

/* DMA channel TX programmable address */
typedef union {
    struct {
        __IO uint32_t PGMADDR                         :32;    /* bits:0-31, PDMA programmable address. These registers specify the address for a half-size DMA channel. This address represents the source address if DIR in DMA_CON is set to 0 and represents the destination address if DIR in PDMAn_CON is set to 1. */
    } field;
    __IO uint32_t word;
} PDMA_PGMADDR_T;

#define PDMA_PGMADDR_PGMADDR_OFFSET                                   (0U)
#define PDMA_PGMADDR_PGMADDR_MASK                                     (0xFFFFFFFFU << PDMA_PGMADDR_PGMADDR_OFFSET)


/* DMA channel TX start */
typedef union {
    struct {
        __I  uint32_t __reserved_00                   :15;
        __IO uint32_t STR                             :1;    /* bits:15-15, Start control for a DMA channel This register controls the activity of a DMA channel. Note that before setting STR to 1, all register settings must be configured. When STR is set to 1, the hardware will not clear it automatically, no matter whether the DMA channel accomplishes the DMA transfer or not. In other words, the value of STR stays at 1, regardless of the completion of the DMA transfer. Therefore, the software program must reset STR to 0 before starting another DMA transfer. If this bit is cleared to 0 when the DMA transfer is active, the software must poll RUNn in DMA_GLBSTA when this bit is cleared to make sure that the current DMA transfer is terminated by the DMA engine. */
        __I  uint32_t __reserved_01                   :16;
    } field;
    __IO uint32_t word;
} PDMA_START_T;

#define PDMA_START_STR_OFFSET                                         (15U)
#define PDMA_START_STR_MASK                                           (0x1U << PDMA_START_STR_OFFSET)


/* DMA global status */
typedef union {
    struct {
        __I  uint32_t RUN_TX                          :1;    /* bits:0-0, Channel TX running status */
        __I  uint32_t IT_TX                           :1;    /* bits:1-1, Channel TX interrupt status */
        __I  uint32_t RUN_RX                          :1;    /* bits:2-2, Channel RX running status */
        __I  uint32_t IT_RX                           :1;    /* bits:3-3, Channel RX interrupt status */
        __I  uint32_t __reserved_00                   :28;
    } field;
    __IO uint32_t word;
} DMA_GLBSTA_T;

#define DMA_GLBSTA_RUN_TX_OFFSET                                         (0U)
#define DMA_GLBSTA_RUN_TX_MASK                                           (0x1U << DMA_GLBSTA_RUN_TX_OFFSET)
#define DMA_GLBSTA_IT_TX_OFFSET                                          (1U)
#define DMA_GLBSTA_IT_TX_MASK                                            (0x1U << DMA_GLBSTA_IT_TX_OFFSET)
#define DMA_GLBSTA_RUN_RX_OFFSET                                         (2U)
#define DMA_GLBSTA_RUN_RX_MASK                                           (0x1U << DMA_GLBSTA_RUN_RX_OFFSET)
#define DMA_GLBSTA_IT_RX_OFFSET                                          (3U)
#define DMA_GLBSTA_IT_RX_MASK                                            (0x1U << DMA_GLBSTA_IT_RX_OFFSET)


/* DMA top hierarchy interrupt set */
typedef union {
    struct {
        __IO uint32_t CPU0_SET_TX                     :1;    /* bits:0-0, Channel TX CPU0 interrupt enable set */
        __IO uint32_t CPU0_SET_RX                     :1;    /* bits:1-1, Channel RX CPU0 interrupt enable set */
        __I  uint32_t __reserved_00                   :30;
    } field;
    __IO uint32_t word;
} DMA_GLB_CPU0_SET_T;

#define DMA_GLB_CPU0_SET_CPU0_SET_TX_OFFSET                              (0U)
#define DMA_GLB_CPU0_SET_CPU0_SET_TX_MASK                                (0x1U << DMA_GLB_CPU0_SET_CPU0_SET_TX_OFFSET)
#define DMA_GLB_CPU0_SET_CPU0_SET_RX_OFFSET                              (1U)
#define DMA_GLB_CPU0_SET_CPU0_SET_RX_MASK                                (0x1U << DMA_GLB_CPU0_SET_CPU0_SET_RX_OFFSET)


/* DMA top hierarchy interrupt clr */
typedef union {
    struct {
        __IO uint32_t CPU0_CLR_TX                     :1;    /* bits:0-0, Channel TX CPU0 interrupt enable clear */
        __IO uint32_t CPU0_CLR_RX                     :1;    /* bits:1-1, Channel RX CPU0 interrupt enable clear */
        __I  uint32_t __reserved_00                   :30;
    } field;
    __IO uint32_t word;
} DMA_GLB_CPU0_CLR_T;

#define DMA_GLB_CPU0_CLR_CPU0_CLR_TX_OFFSET                              (0U)
#define DMA_GLB_CPU0_CLR_CPU0_CLR_TX_MASK                                (0x1U << DMA_GLB_CPU0_CLR_CPU0_CLR_TX_OFFSET)
#define DMA_GLB_CPU0_CLR_CPU0_CLR_RX_OFFSET                              (1U)
#define DMA_GLB_CPU0_CLR_CPU0_CLR_RX_MASK                                (0x1U << DMA_GLB_CPU0_CLR_CPU0_CLR_RX_OFFSET)


/* DMA top hierarchy interrupt set */
typedef union {
    struct {
        __IO uint32_t CPU1_SET_TX                     :1;    /* bits:0-0, Channel TX CPU1 interrupt enable set */
        __IO uint32_t CPU1_SET_RX                     :1;    /* bits:1-1, Channel RX CPU1 interrupt enable set */
        __I  uint32_t __reserved_00                   :30;
    } field;
    __IO uint32_t word;
} DMA_GLB_CPU1_SET_T;

#define DMA_GLB_CPU1_SET_CPU1_SET_TX_OFFSET                              (0U)
#define DMA_GLB_CPU1_SET_CPU1_SET_TX_MASK                                (0x1U << DMA_GLB_CPU1_SET_CPU1_SET_TX_OFFSET)
#define DMA_GLB_CPU1_SET_CPU1_SET_RX_OFFSET                              (1U)
#define DMA_GLB_CPU1_SET_CPU1_SET_RX_MASK                                (0x1U << DMA_GLB_CPU1_SET_CPU1_SET_RX_OFFSET)


/* DMA top hierarchy interrupt clr */
typedef union {
    struct {
        __IO uint32_t CPU1_CLR_TX                     :1;    /* bits:0-0, Channel TX CPU1 interrupt enable clear */
        __IO uint32_t CPU1_CLR_RX                     :1;    /* bits:1-1, Channel RX CPU1 interrupt enable clear */
        __I  uint32_t __reserved_00                   :30;
    } field;
    __IO uint32_t word;
} DMA_GLB_CPU1_CLR_T;

#define DMA_GLB_CPU1_CLR_CPU1_CLR_TX_OFFSET                              (0U)
#define DMA_GLB_CPU1_CLR_CPU1_CLR_TX_MASK                                (0x1U << DMA_GLB_CPU1_CLR_CPU1_CLR_TX_OFFSET)
#define DMA_GLB_CPU1_CLR_CPU1_CLR_RX_OFFSET                              (1U)
#define DMA_GLB_CPU1_CLR_CPU1_CLR_RX_MASK                                (0x1U << DMA_GLB_CPU1_CLR_CPU1_CLR_RX_OFFSET)


/* DMA global software reset */
typedef union {
    struct {
        __I  uint32_t SW_RESET                        :1;    /* bits:0-0, Software reset write 1 reset */
        __I  uint32_t __reserved_00                   :31;
    } field;
    __IO uint32_t word;
} DMA_GLB_SWRST_T;

#define DMA_GLB_SWRST_SW_RESET_OFFSET                                    (0U)
#define DMA_GLB_SWRST_SW_RESET_MASK                                      (0x1U << DMA_GLB_SWRST_SW_RESET_OFFSET)


/* DMA global bandwidth limiter register */
typedef union {
    struct {
        __IO uint32_t LIMITER                         :8;    /* bits:0-7, Utilization suppression This register suppresses the bus utilization of the DMA channel.  From 0 to 255. 0 means no limitation, 255 means totally banned. All other values indicate bus access permission for every (4 x n) AHB clock. */
        __I  uint32_t __reserved_00                   :24;
    } field;
    __IO uint32_t word;
} DMA_GLBLIMITER_T;

#define DMA_GLBLIMITER_LIMITER_OFFSET                                    (0U)
#define DMA_GLBLIMITER_LIMITER_MASK                                      (0xFFU << DMA_GLBLIMITER_LIMITER_OFFSET)


/* DMA current chosen channel */
typedef union {
    struct {
        __I  uint32_t CC                              :32;    /* bits:0-31, Reserved for debug only. This signal indicates the channel that is currently be chosen. */
    } field;
    __IO uint32_t word;
} DMA_GLB_DBG_T;

#define DMA_GLB_DBG_CC_OFFSET                                            (0U)
#define DMA_GLB_DBG_CC_MASK                                              (0xFFFFFFFFU << DMA_GLB_DBG_CC_OFFSET)


/* DMA global busy status */
typedef union {
    struct {
        __I  uint32_t RUN_TX                          :1;    /* bits:0-0, Channel TX running status IT will pull high after RUN pulling down in the same channel */
        __I  uint32_t RUN_RX                          :1;    /* bits:1-1, Channel RX running status IT will pull high after RUN pulling down in the same channel */
        __I  uint32_t __reserved_00                   :30;
    } field;
    __IO uint32_t word;
} DMA_GLB_BUSY_T;

#define DMA_GLB_BUSY_RUN_TX_OFFSET                                       (0U)
#define DMA_GLB_BUSY_RUN_TX_MASK                                         (0x1U << DMA_GLB_BUSY_RUN_TX_OFFSET)
#define DMA_GLB_BUSY_RUN_RX_OFFSET                                       (1U)
#define DMA_GLB_BUSY_RUN_RX_MASK                                         (0x1U << DMA_GLB_BUSY_RUN_RX_OFFSET)


/* DMA global interrupt status */
typedef union {
    struct {
        __I  uint32_t IT_TX                           :1;    /* bits:0-0, Channel TX interrupt status IT will pull high after RUN pulling down in the same channel */
        __I  uint32_t IT_RX                           :1;    /* bits:1-1, Channel RX interrupt status IT will pull high after RUN pulling down in the same channel */
        __I  uint32_t __reserved_00                   :30;
    } field;
    __IO uint32_t word;
} DMA_GLB_INTR_T;

#define DMA_GLB_INTR_IT_TX_OFFSET                                        (0U)
#define DMA_GLB_INTR_IT_TX_MASK                                          (0x1U << DMA_GLB_INTR_IT_TX_OFFSET)
#define DMA_GLB_INTR_IT_RX_OFFSET                                        (1U)
#define DMA_GLB_INTR_IT_RX_MASK                                          (0x1U << DMA_GLB_INTR_IT_RX_OFFSET)


/* DMA channel clock set */
typedef union {
    struct {
        __IO uint32_t CLK_SET_TX                      :1;    /* bits:0-0, Channel TX clock enable set */
        __IO uint32_t CLK_SET_RX                      :1;    /* bits:1-1, Channel RX clock enable set */
        __I  uint32_t __reserved_00                   :30;
    } field;
    __IO uint32_t word;
} DMA_GLB_CLK_SET_T;

#define DMA_GLB_CLK_SET_CLK_SET_TX_OFFSET                                (0U)
#define DMA_GLB_CLK_SET_CLK_SET_TX_MASK                                  (0x1U << DMA_GLB_CLK_SET_CLK_SET_TX_OFFSET)
#define DMA_GLB_CLK_SET_CLK_SET_RX_OFFSET                                (1U)
#define DMA_GLB_CLK_SET_CLK_SET_RX_MASK                                  (0x1U << DMA_GLB_CLK_SET_CLK_SET_RX_OFFSET)


/* DMA channel clock clr */
typedef union {
    struct {
        __IO uint32_t CLK_CLR_TX                      :1;    /* bits:0-0, Channel TX clock enable clear */
        __IO uint32_t CLK_CLR_RX                      :1;    /* bits:1-1, Channel RX clock enable clear */
        __I  uint32_t __reserved_00                   :30;
    } field;
    __IO uint32_t word;
} DMA_GLB_CLK_CLR_T;

#define DMA_GLB_CLK_CLR_CLK_CLR_TX_OFFSET                                (0U)
#define DMA_GLB_CLK_CLR_CLK_CLR_TX_MASK                                  (0x1U << DMA_GLB_CLK_CLR_CLK_CLR_TX_OFFSET)
#define DMA_GLB_CLK_CLR_CLK_CLR_RX_OFFSET                                (1U)
#define DMA_GLB_CLK_CLR_CLK_CLR_RX_MASK                                  (0x1U << DMA_GLB_CLK_CLR_CLK_CLR_RX_OFFSET)

/* DMA channel wrap point address */
typedef union {
    struct {
        __IO uint32_t WPPT                            :16;    /* bits:0-15, Transfer counts before jump The register specifies the transfer count that is necessary to perform before the jump point. This can be used to support the ring buffer or double buffer style memory access. To enable this function, two control bits in the DMA control register (WPEN and WPSD) must be programmed. If the transfer counter in the DMA engine is the same as this value, an address jump occurs, and the next address is the address specified in PDMAn_WPTO. To enable this function, set WPEN in PDMAn_CON. Note: the total size of data specified in the wrap point count in a DMA channel is determined by LEN and the SIZE in PDMAn_CON (i.e. WPPT x SIZE). */
        __I  uint32_t __reserved_00                   :16;
    } field;
    __IO uint32_t word;
} PDMA_WPPT_T;

#define PDMA_WPPT_WPPT_OFFSET                                         (0U)
#define PDMA_WPPT_WPPT_MASK                                           (0xFFFFU << PDMA_WPPT_WPPT_OFFSET)


/* DMA channel wrap to address */
typedef union {
    struct {
        __IO uint32_t WPTO                            :32;    /* bits:0-31, Jump address The register specifies the address of jump destination of a given DMA transfer to support the ring buffer or double buffer style memory access. To enable this function, set the two control bits in the DMA control register, WPEN and WPSD . To enable this function, WPEN in PDMAn_CON must be set. */
    } field;
    __IO uint32_t word;
} PDMA_WPTO_T;

#define PDMA_WPTO_WPTO_OFFSET                                         (0U)
#define PDMA_WPTO_WPTO_MASK                                           (0xFFFFFFFFU << PDMA_WPTO_WPTO_OFFSET)


/* DMA channel interrupt status */
typedef union {
    struct {
        __I  uint32_t __reserved_00                   :15;
        __I  uint32_t INT                             :1;    /* bits:15-15, Interrupt status for DMA channel */
        __I  uint32_t __reserved_01                   :16;
    } field;
    __IO uint32_t word;
} PDMA_INTSTA_T;

#define PDMA_INTSTA_INT_OFFSET                                        (15U)
#define PDMA_INTSTA_INT_MASK                                          (0x1U << PDMA_INTSTA_INT_OFFSET)


/* DMA channel interrupt acknowledge */
typedef union {
    struct {
        __I  uint32_t __reserved_00                   :15;
        __IO uint32_t ACK                             :1;    /* bits:15-15, Interrupt acknowledge for the DMA channel */
        __I  uint32_t __reserved_01                   :16;
    } field;
    __IO uint32_t word;
} PDMA_ACKINT_T;

#define PDMA_ACKINT_ACK_OFFSET                                        (15U)
#define PDMA_ACKINT_ACK_MASK                                          (0x1U << PDMA_ACKINT_ACK_OFFSET)


/* DMA channel remaining length of current transfer */
typedef union {
    struct {
        __I  uint32_t RLCT                            :16;    /* bits:0-15, This register shows the remaining count of the transfer.  Note: this value is transfer count, not the transfer data size. */
        __I  uint32_t __reserved_00                   :16;
    } field;
    __IO uint32_t word;
} PDMA_RLCT_T;

#define PDMA_RLCT_RLCT_OFFSET                                         (0U)
#define PDMA_RLCT_RLCT_MASK                                           (0xFFFFU << PDMA_RLCT_RLCT_OFFSET)


/* DMA channel bandwidth limiter */
typedef union {
    struct {
        __IO uint32_t LIMITER                         :8;    /* bits:0-7, Utilization suppression This register controls the suppression of the bus utilization of the DMA channel.  From 0 to 255. 0 means no limitation, 255 means totally banned. All other values show bus access permission for every (4 x n) AHB clock. */
        __I  uint32_t __reserved_00                   :24;
    } field;
    __IO uint32_t word;
} PDMA_LIMITER_T;

#define PDMA_LIMITER_LIMITER_OFFSET                                   (0U)
#define PDMA_LIMITER_LIMITER_MASK                                     (0xFFU << PDMA_LIMITER_LIMITER_OFFSET)


typedef struct {
    PDMA_WPPT_T                                             pdma_wppt; /* offset: 0x00000000, DMA channel wrap point address */
    PDMA_WPTO_T                                             pdma_wpto; /* offset: 0x00000004, DMA channel wrap to address */
    PDMA_COUNT_T                                           pdma_count; /* offset: 0x00000008, DMA channel TX transfer count */
    PDMA_CON_T                                               pdma_con; /* offset: 0x0000000C, DMA channel TX control */
    PDMA_PGMADDR_T                                       pdma_pgmaddr; /* offset: 0x00000010, DMA channel TX programmable address */
    PDMA_START_T                                           pdma_start; /* offset: 0x00000014, DMA channel TX start */
} PDMA_CFG_REGISTER_T;

typedef struct {
    PDMA_INTSTA_T                                         pdma_intsta; /* offset: 0x00000X1C, DMA channel interrupt status */
    PDMA_ACKINT_T                                         pdma_ackint; /* offset: 0x00000X20, DMA channel interrupt acknowledge */
    PDMA_RLCT_T                                             pdma_rlct; /* offset: 0x00000X24, DMA channel remaining length of current transfer */
    PDMA_LIMITER_T                                       pdma_limiter; /* offset: 0x00000X28, DMA channel bandwidth limiter */
    uint32_t                                        __reserved_00[60]; /* offset: 0x00000X2C, padding size: 0x000000F0 */
} PDMA_STA_REGISTER_T;

typedef struct {
    DMA_GLB_CPU0_CFG_T                               dma_glb_cpu0_cfg; /* offset: 0x00000000, DMA top hierarchy interrupt config */
    DMA_GLB_CPU1_CFG_T                               dma_glb_cpu1_cfg; /* offset: 0x00000004, DMA top hierarchy interrupt config */
    DMA_GLB_CLK_CFG_T                                 dma_glb_clk_cfg; /* offset: 0x00000008, DMA channel clock config */

    PDMA_CFG_REGISTER_T                              dma_config_ch[2]; /* tx offset: 0x00000000C, rx offset 0x000000024 */

    DMA_GLBSTA_T                                           dma_glbsta; /* offset: 0x0000003C, DMA global status */
    DMA_GLB_CPU0_SET_T                               dma_glb_cpu0_set; /* offset: 0x00000040, DMA top hierarchy interrupt set */
    DMA_GLB_CPU0_CLR_T                               dma_glb_cpu0_clr; /* offset: 0x00000044, DMA top hierarchy interrupt clr */
    DMA_GLB_CPU1_SET_T                               dma_glb_cpu1_set; /* offset: 0x00000048, DMA top hierarchy interrupt set */
    DMA_GLB_CPU1_CLR_T                               dma_glb_cpu1_clr; /* offset: 0x0000004C, DMA top hierarchy interrupt clr */
    DMA_GLB_SWRST_T                                     dma_glb_swrst; /* offset: 0x00000050, DMA global software reset */
    DMA_GLBLIMITER_T                                   dma_glblimiter; /* offset: 0x00000054, DMA global bandwidth limiter register */
    DMA_GLB_DBG_T                                         dma_glb_dbg; /* offset: 0x00000058, DMA current chosen channel */
    DMA_GLB_BUSY_T                                       dma_glb_busy; /* offset: 0x0000005C, DMA global busy status */
    DMA_GLB_INTR_T                                       dma_glb_intr; /* offset: 0x00000060, DMA global interrupt status */
    DMA_GLB_CLK_SET_T                                 dma_glb_clk_set; /* offset: 0x00000064, DMA channel clock set */
    DMA_GLB_CLK_CLR_T                                 dma_glb_clk_clr; /* offset: 0x00000068, DMA channel clock clr */
    uint32_t                                        __reserved_00[44]; /* offset: 0x0000006C, padding size: 0x000000B0 */

    PDMA_STA_REGISTER_T                              dma_status_ch[2]; /* tx offset: 0x00000011C, rx offset 0x00000021C */
} I3C_DMA_REGISTER_T;


/* VDMA channel register definition */
typedef struct {
    __IO uint32_t VDMA_COUNT;        /*!<  virtual fifo dma transfer counter  register */
    union {
        struct {
            __IO uint8_t VDMA_DIRECTION ; /* virtual fifo dma incremental source address */
            __IO uint8_t VDMA_SIZE;       /* virtual fifo dma data size */
            __IO uint8_t VDMA_SETTING;    /* virtual fifo dma throttle and handshake control for dma transter */
            __IO uint8_t VDMA_ITEN;      /* virtual fifo dma interrupt enable */
        } VDMA_CON_CELLS;
        __IO uint32_t VDMA_CON;          /*!<  peripheral dma control register */
    } VDMA_CON_UNION;
    __IO uint32_t VDMA_START;        /*!<  virtual fifo dma start register */
    __IO uint32_t VDMA_INTSTA;       /*!<  virtual fifol dma interrupt status register*/
    __O  uint32_t VDMA_ACKINT;       /*!<  virtual fifo dma interrupt acknowledge register*/
    __IO uint32_t DUMMY1_OFFSET[1];  /*!< virtual fifo dma dummy offser register*/
    __O  uint32_t VDMA_LIMITER;      /*!< virtual fifo dma bandwidth register*/
    __IO uint32_t VDMA_PGMADDR;      /*!<  virtual fifo dma programmable address register*/
    __I  uint32_t VDMA_WRPTR;        /*!<  virtual fifo dma write pointer register */
    __I  uint32_t VDMA_RDPTR;        /*!<  virtual fifo dma read  pointer register */
    __I  uint32_t VDMA_FFCNT;        /*!<  virtual fifo dma fifo count register */
    __I  uint32_t VDMA_FFSTA;        /*!<  virtual fifo dma fifo status  register */
    __IO uint32_t VDMA_ALTLEN;       /*!<  virtual fifo dma fifo alert lentgh register */
    __IO uint32_t VDMA_FFSIZE;       /*!<  virtual fifo dma fifo size  register */
    __IO uint32_t DUMMY2_OFFSET[6];  /*!< virtual fifo dma dummy offser register*/
    __IO uint32_t VDMA_SW_MV_BYTE;   /*!<  virtual fifo dma software move byte  register */
    __IO uint32_t VDMA_BNDRY_ADDR;     /*!<  virtual fifo dma boundary address  register */
    __IO uint32_t VDMA_BYTE_TO_BNDRY;  /*!<  virtual fifo dma byte to boundary address register */
    __IO uint32_t VDMA_BYTE_AVAIL;     /*!<  virtual fifo dma fifo byte avaiable in FIFO register */
} VDMA_REGISTER_T;

/* VDMA_CON definition */
#define VDMA_CON_DIR_OFFSET                  (4)
#define VDMA_CON_DIR_MASK                    (0x1 << VDMA_CON_DIR_OFFSET)
#define VDMA_CON_DIR_TX                       0
#define VDMA_CON_DIR_RX                       1

#define VDMA_CON_SIZE_OFFSET                 (8)
#define VDMA_CON_SIZE_MASK                   (0x3 << VDMA_CON_SIZE_OFFSET)
#define VDMA_CON_SIZE_BYTE                    0
#define VDMA_CON_SIZE_HALF_WORD               1
#define VDMA_CON_SIZE_WORD                    2

#define VDMA_CON_DREQ_OFFSET                 (16)
#define VDMA_CON_DREQ_MASK                   (0x1 << VDMA_CON_DREQ_OFFSET)

#define VDMA_CON_ITEN_OFFSET                 (24)
#define VDMA_CON_ITEN_MASK                   (0x1 << VDMA_CON_ITEN_OFFSET)

/* VDMA_START definition */
#define VDMA_START_BIT_OFFSET                (15)
#define VDMA_START_BIT_MASK                  (0x1 << VDMA_START_BIT_OFFSET)

/* VDMA_INTSTA definition */
#define VDMA_INTSTA_BIT_OFFSET               (15)
#define VDMA_INTSTA_BIT_MASK                 (0x1 << VDMA_INTSTA_BIT_OFFSET)

/* VDMA_ACKINT definition */
#define VDMA_ACKINT_BIT_OFFSET               (15)
#define VDMA_ACKINT_BIT_MASK                 (0x1 << VDMA_ACKINT_BIT_OFFSET)

/* VDMA_FFSTA definition */
#define VDMA_FFSTA_FULL_BIT_OFFSET           (0)
#define VDMA_FFSTA_FULL_BIT_MASK             (0x1 << VDMA_FFSTA_FULL_BIT_OFFSET)
#define VDMA_FFSTA_EMPTY_BIT_OFFSET          (1)
#define VDMA_FFSTA_EMPTY_BIT_MASK            (0x1 << VDMA_FFSTA_EMPTY_BIT_OFFSET)
#define VDMA_FFSTA_ALT_BIT_OFFSET            (2)
#define VDMA_FFSTA_ALT_BIT_MASK              (0x1 << VDMA_FFSTA_ALT_BIT_OFFSET)

/* VDMA_GLB index definition */
#define VDMA_GLB_INDEX_OFFSET                (0)
#define VDMA_GLB_INDEX_MASK                  (0x1 << VDMA_GLB_INDEX_OFFSET)

/* base address definition for channels */
#define GDMA_RG_0_0_BASE                     ((GDMA_REGISTER_T *)(DMA_0_BASE + 0x100))
#define GDMA_RG_1_0_BASE                     ((GDMA_REGISTER_T *)(DMA_1_BASE + 0x100))
#define GDMA_RG_1_1_BASE                     ((GDMA_REGISTER_T *)(DMA_1_BASE + 0x200))
#define GDMA_RG_1_2_BASE                     ((GDMA_REGISTER_T *)(DMA_1_BASE + 0x300))

#define VDMA_RG_UART0_TX_BASE                ((VDMA_REGISTER_T *)(UART_DMA_0_BASE + 0x110))
#define VDMA_RG_UART0_RX_BASE                ((VDMA_REGISTER_T *)(UART_DMA_0_BASE + 0x210))
#define VDMA_RG_UART1_TX_BASE                ((VDMA_REGISTER_T *)(UART_DMA_1_BASE + 0x110))
#define VDMA_RG_UART1_RX_BASE                ((VDMA_REGISTER_T *)(UART_DMA_1_BASE + 0x210))
#define VDMA_RG_UART2_TX_BASE                ((VDMA_REGISTER_T *)(UART_DMA_2_BASE + 0x110))
#define VDMA_RG_UART2_RX_BASE                ((VDMA_REGISTER_T *)(UART_DMA_2_BASE + 0x210))

#define PDMA_STA_RG_I3C0_TX_BASE             ((PDMA_STA_REGISTER_T *)(I3C0_PDMA_BASE + 0x11C))
#define PDMA_STA_RG_I3C0_RX_BASE             ((PDMA_STA_REGISTER_T *)(I3C0_PDMA_BASE + 0x21C))
#define PDMA_STA_RG_I3C1_TX_BASE             ((PDMA_STA_REGISTER_T *)(I3C1_PDMA_BASE + 0x11C))
#define PDMA_STA_RG_I3C1_RX_BASE             ((PDMA_STA_REGISTER_T *)(I3C1_PDMA_BASE + 0x21C))

#define PDMA_CFG_RG_I3C0_TX_BASE             ((PDMA_CFG_REGISTER_T *)(I3C0_PDMA_BASE + 0x0C))
#define PDMA_CFG_RG_I3C0_RX_BASE             ((PDMA_CFG_REGISTER_T *)(I3C0_PDMA_BASE + 0x24))
#define PDMA_CFG_RG_I3C1_TX_BASE             ((PDMA_CFG_REGISTER_T *)(I3C1_PDMA_BASE + 0x0C))
#define PDMA_CFG_RG_I3C1_RX_BASE             ((PDMA_CFG_REGISTER_T *)(I3C1_PDMA_BASE + 0x24))
/************************ dma end register definition end line  ********************************/


#endif /* __DMA_REG_DEFINITION_H__ */