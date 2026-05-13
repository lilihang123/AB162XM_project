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

#ifndef __I3C_REG_DEFINITION_H__
#define __I3C_REG_DEFINITION_H__


#include <stdint.h>


/*************************** I3C register definition end line  *******************************/
typedef struct {
    __IO    uint32_t    SOFT_RESET;             /*0x0*/
    __IO    uint32_t    IO_CONFIG;              /*0x4*/
    __IO    uint32_t    CLOCK_DIV;              /*0x8*/
    __IO    uint32_t    H_TIMING;               /*0xC*/
    __IO    uint32_t    L_TIMING;               /*0x10*/
    __IO    uint32_t    HS;                     /*0x14*/
    __IO    uint32_t    EXT_CONF;               /*0x18*/
    __IO    uint32_t    CONTROL;                /*0x1C*/
    __IO    uint32_t    MULTIMAS;               /*0x20*/
    __IO    uint32_t    TRANSFER_LEN;           /*0x24*/
    __IO    uint32_t    TRANSFER_LEN_AUX;       /*0x28*/
    __IO    uint32_t    TRANSAC_LEN;            /*0x2C*/
    __IO    uint32_t    FIFO_THRESH;            /*0x30*/
    __IO    uint32_t    DATA_TIMING;            /*0x34*/
    __IO    uint32_t    TIMEOUT_DIV;            /*0x38*/
    __IO    uint32_t    IBI_TIMING;             /*0x3C*/
    __IO    uint32_t    SLAVE_ADDR;             /*0x40*/
    __IO    uint32_t    DELAY_LEN;              /*0x44*/
    __IO    uint32_t    INTR_MASK;              /*0x48*/
    __IO    uint32_t    START;                  /*0x4C*/
    __IO    uint8_t     DATA_PORT;              /*0x50*/
    __IO    uint8_t     RESERVE_0x[3];
    __IO    uint32_t    FIFO_ADDR_CLR;          /*0x54*/
    __IO    uint32_t    INTR_STA;               /*0x58*/
    __IO    uint32_t    DEF_DA;                 /*0x5C*/
    __IO    uint32_t    HFIFO_DATA;             /*0x60*/
    __IO    uint32_t    TRAFFIC;                /*0x64*/
    __IO    uint32_t    SHAPE;                  /*0x68*/
    __IO    uint32_t    ERROR;                  /*0x6C*/
    __IO    uint32_t    DEBUG_STAT;             /*0x70*/
    __IO    uint32_t    DEBUG_CTRL;             /*0x74*/
    __IO    uint32_t    FIFO_STAT;              /*0x78*/
    __IO    uint32_t    HFIFO_STAT;             /*0x7C*/
}I3C_MASTER_REGISTER_T;

/* 0x00: SOFTRESET */
#define     I3C_SOFTRESET_SOFT_RESET_OFFSET     (0)
#define     I3C_SOFTRESET_FSM_RESET_OFFSET      (1)
#define     I3C_SOFTRESET_GRAIN_RESET_OFFSET    (2)
#define     I3C_SOFTRESET_ERROR_RESET_OFFSET    (3)
#define     I3C_SOFTRESET_SIDE_RESET_OFFSET     (4)
#define     I3C_SOFTRESET_WARM_RESET_OFFSET     (5)


#define     I3C_SOFTRESET_SOFT_RESET_MASK       (1<<0)
#define     I3C_SOFTRESET_FSM_RESET_MASK        (1<<1)
#define     I3C_SOFTRESET_GRAIN_RESET_MASK      (1<<2)
#define     I3C_SOFTRESET_ERROR_RESET_MASK      (1<<3)
#define     I3C_SOFTRESET_SIDE_RESET_MASK       (1<<4)
#define     I3C_SOFTRESET_WARM_RESET_MASK       (1<<5)

/* 0x04: IO_CONFIG */
#define     I3C_IO_CONFIG_SCL_OFFSET            (0)
#define     I3C_IO_CONFIG_SDA_OFFSET            (1)
#define     I3C_IO_CONFIG_IO_SYNC_EN_OFFSET     (2)
#define     I3C_IO_CONFIF_IDLE_PE_EN_OFFSET     (3)
#define     I3C_IO_CONFIG_AED_DIV_OFFSET        (4)
#define     I3C_IO_CONFIG_AED_EN_OFFSET         (5)
#define     I3C_IO_CONFIG_AED_STEP_ADJ_OFFSET   (9)
#define     I3C_IO_CONFIG_CLK_EXT_EN_OFFSET     (15)
#define     I3C_IO_CONFIG_AED_STEP_EN_OFFSET    (16)

#define     I3C_IO_CONFIG_SCL_MASK              (1<<0)
#define     I3C_IO_CONFIG_SDA_MASK              (1<<1)
#define     I3C_IO_CONFIG_IO_SYNC_EN_MASK       (1<<2)
#define     I3C_IO_CONFIF_IDLE_OE_EN_MASK       (1<<3)
#define     I3C_IO_CONFIG_AED_DIV_MASK          (1<<4)
#define     I3C_IO_CONFIG_AED_EN_MASK           (0x3<<5)
#define     I3C_IO_CONFIG_AED_STEP_ADJ_MASK     (0x3F<<9)
#define     I3C_IO_CONFIG_CLK_EXT_EN_MASK       (0x1<<15)
#define     I3C_IO_CONFIG_AED_STEP_EN_MASK      (0x1<<16)

/* 0x08: CLOCK_DIV */
#define     I3C_CLOCK_DIV_SMP_DIV_OFFFSET       (0)
#define     I3C_CLOCK_DIV_HS_DIV_OFFFSET        (8)
#define     I3C_CLOCK_DIV_SMP_DIV_MASK          (0x1F)
#define     I3C_CLOCK_DIV_HS_DIV_MASK           (0x1F<<8)

/* 0x0C: HTIMING */
#define     I3C_HTIMING_HSTEP_CNT_DIV_OFFSET    (0)   /*for 6 bits*/
#define     I3C_HTIMING_DELAY_TIME_DET_OFFSET   (6)   /*for 2 bits */
#define     I3C_HTIMING_HSAMPLE_CNT_DIV_OFFSET  (8)   /*for 3 bits*/
#define     I3C_HTIMING_TIMEOUT_EN_OFFSET       (11)  /*for 1 bit*/

#define     I3C_HTIMING_HSTEP_CNT_DIV_MASK      (0x3F<<I3C_HTIMING_HSTEP_CNT_DIV_OFFSET)
#define     I3C_HTIMING_DELAY_TIME_DET_MASK     (0x3<<I3C_HTIMING_DELAY_TIME_DET_OFFSET)
#define     I3C_HTIMING_HSAMPLE_CNT_DIV_MASK    (0x7<<I3C_HTIMING_HSAMPLE_CNT_DIV_OFFSET)
#define     I3C_HTIMING_TIMEOUT_EN_MASK         (0x1<<I3C_HTIMING_TIMEOUT_EN_OFFSET)

/* 0x10: LTIMING */
#define     I3C_LTIMING_LSTEP_CNT_DIV_OFFSET    (0)
#define     I3C_LTIMING_LSMAPLE_CNT_DIV_OFFSET  (6)
#define     I3C_LTIMING_LHS_STEP_CNT_DIV_OFFSET (9)
#define     I3C_LTIMING_LHS_SAMPLE_CNT_DIV_OFFSET (12)

#define     I3C_LTIMING_LSTEP_CNT_DIV_MASK      (0x3F<<I3C_LTIMING_LSTEP_CNT_DIV_OFFSET)
#define     I3C_LTIMING_LSMAPLE_CNT_DIV_MASK    (0x7<<I3C_LTIMING_LSMAPLE_CNT_DIV_OFFSET)
#define     I3C_LTIMING_LHS_STEP_CNT_DIV_MASK   (0x7<<I3C_LTIMING_LHS_STEP_CNT_DIV_OFFSET)
#define     I3C_LTIMING_LHS_SAMPLE_CNT_DIV_MASK (0x7<<I3C_LTIMING_LHS_SAMPLE_CNT_DIV_OFFSET)

/* 0x14: HS */
#define     I3C_HS_EN_OFFSET                    (0)
#define     I3C_HS_NACKERR_DET_EN_OFFSET        (1)
#define     I3C_HS_HOLD_TIME_OFFSET             (2)
#define     I3C_HS_FC_STEP_OFFSET               (4)
#define     I3C_HS_SPEED_OFFSET                 (7)
#define     I3C_HS_STEP_CNT_DIV_OFFSET          (8)
#define     I3C_HS_SAMPLE_CNT_DIV_OFFSET        (12)
#define     I3C_HS_HOLD_EN_OFFSET               (15)

#define     I3C_HS_EN_MASK                      (0x1<<0)
#define     I3C_HS_NACKERR_DET_EN_MASK          (0x1<<1)
#define     I3C_HS_HOLD_TIME_MASK               (0x3<<2)
#define     I3C_HS_FC_STEP_MASK                 (0x7<<4)
#define     I3C_HS_SPEED_MASK                   (0x1<<7)
#define     I3C_HS_STEP_CNT_DIV_MASK            (0x7<<8)
#define     I3C_HS_SAMPLE_CNT_DIV_MASK          (0x7<<12)
#define     I3C_HS_HOLD_EN_MASK                 (0x1<<15)

/* 0x18: EXT_CONFIG */
#define     I3C_EXT_CONFIG_EXT_EN_OFFSET        (0)
#define     I3C_EXT_CONFIG_HS_EXT_TIME_OFFSET   (1)
#define     I3C_EXT_CONFIG_EXT_TIME_OFFSET      (8)

#define     I3C_EXT_CONFIG_EXT_EN_MASK          (0x1)
#define     I3C_EXT_CONFIG_HS_EXT_TIME_MASK     (0x3F<<1)
#define     I3C_EXT_CONFIG_EXT_TIME_MASK        (0xFF<<8)

/* 0x1C: CONTROL */
#define     I3C_CONTROL_RS_STOP_OFFSET          (1)
#define     I3C_CONTROL_DMA_EN_OFFSET           (2)
#define     I3C_CONTROL_DIR_CHANGE_OFFSET       (4)
#define     I3C_CONTROL_ACKERR_DET_EN_OFFSET    (5)
#define     I3C_CONTROL_TRANSFER_LEN_CHANGE_OFFSER (6)

#define     I3C_CONTROL_RS_STOP_MASK            (1<<1)
#define     I3C_CONTROL_DMA_EN_MASK             (1<<2)

#define     I3C_CONTROL_DIR_CHANGE_MASK         (1<<4)
#define     I3C_CONTROL_ACKERR_DET_EN_MASK      (1<<5)
#define     I3C_CONTROL_TRANSFER_LEN_CHANGE_MASK (1<<6)

/* 0x48: INTR_MASK */
#define     I3C_INTR_MASK_TRANS_COMP_OFFSET     (0)
#define     I3C_INTR_MASK_ACKERR_OFFSET         (1)
#define     I3C_INTR_MASK_HS_NACKERR_OFFSET     (2)
#define     I3C_INTR_MASK_ARB_LOST_OFFSET       (3)
#define     I3C_INTR_MASK_RS_MULTI_OFFSET       (4)
#define     I3C_INTR_MASK_TIMEOUT_OFFSET        (5)
#define     I3C_INTR_MASK_MDA_ERR_OFFSET        (6)
#define     I3C_INTR_MASK_IBI_OFFSET            (7)
#define     I3C_INTR_MASK_ERR_OFFSET            (8)

#define     I3C_INTR_MASK_TRANS_COMP_MASK       (0x1<<0)
#define     I3C_INTR_MASK_ACKERR_MASK           (0x1<<1)
#define     I3C_INTR_MASK_HS_NACKERR_MASK       (0x1<<2)
#define     I3C_INTR_MASK_ARB_LOST_MASK         (0x1<<3)
#define     I3C_INTR_MASK_RS_MULTI_MASK         (0x1<<4)
#define     I3C_INTR_MASK_TIMEOUT_MASK          (0x1<<5)
#define     I3C_INTR_MASK_MDA_ERR_MASK          (0x1<<6)
#define     I3C_INTR_MASK_IBI_MASK              (0x1<<7)
#define     I3C_INTR_MASK_ERR_MASK              (0x1<<8)

/* 0x4C: START */
#define     I3C_START_EN_START_OFFSET           (0)
#define     I3C_START_MUL_TRIG_CLR_OFFSET       (13)
#define     I3C_START_MUL_TRIG_EN_OFFSET        (14)
#define     I3C_START_MUL_CONF_OFFSET           (15)

#define     I3C_START_EN_START_MASK             (0x1)
#define     I3C_START_MUL_HS_CNF_MASK           (0x1<<12)
#define     I3C_START_MUL_TRIG_CLR_MASK         (0x1<<13)
#define     I3C_START_MUL_TRIG_EN_MASK          (0x1<<14)
#define     I3C_START_MUL_CONF_MASK             (0x1<<15)

/* 0x60: HFIFO_DATA */
#define     I3C_HFIFO_DATA_INST_DATA_OFFSET     (0)
#define     I3C_HFIFO_DATA_NINTH_BIT_OFFSET     (8)
#define     I3C_HFIFO_DATA_INST_SPEED_OFFSET    (10)

#define     I3C_HFIFO_DATA_INST_DATA_MASK       (0xFF<<0)
#define     I3C_HFIFO_DATA_NINTH_BIT_MASK       (0x3<<8)
#define     I3C_HFIFO_DATA_INST_SPEED_MASK      (0x1<<10)

/* 0x64: TRAFFIC */
#define     I3C_TRAFFIC_HDR_DECODE_OFFSET       (0)
#define     I3C_TRAFFIC_DAA_EN_OFFSET           (4)
#define     I3C_TRAFFIC_TERNARY_EXIT_OFFSET     (5)
#define     I3C_TRAFFIC_PRE_AMBLE_EXIT_OFFSET   (6)
#define     I3C_TRAFFIC_TBIT_EN_OFFSET          (7)
#define     I3C_TRAFFIC_PARITY_EXIT_OFFSET      (8)
#define     I3C_TRAFFIC_HEAD_ONLY_OFFSET        (9)
#define     I3C_TRAFFIC_SKIP_LV_ADDR_OFFSET     (10)
#define     I3C_TRAFFIC_FORCE_RW_OFFSET         (11)
#define     I3C_TRAFFIC_IBI_EN_OFFSET           (13)
#define     I3C_TRAFFIC_HANDOFF_OFFSET          (14)
#define     I3C_TRAFFIC_DDR_FLEX_OFFSET         (15)

#define     I3C_TRAFFIC_HDR_DECODE_MASK         (0xF<<0)
#define     I3C_TRAFFIC_DAA_EN_MASK             (0x1<<4)
#define     I3C_TRAFFIC_TERNARY_EXIT_MASK       (0x1<<5)
#define     I3C_TRAFFIC_PRE_AMBLE_EXIT_MASK     (0x1<<6)
#define     I3C_TRAFFIC_TBIT_EN_MASK            (0x1<<7)
#define     I3C_TRAFFIC_PARITY_EXIT_MASK        (0x1<<8)
#define     I3C_TRAFFIC_HEAD_ONLY_MASK          (0x1<<9)
#define     I3C_TRAFFIC_SKIP_LV_ADDR_MASK       (0x1<<10)
#define     I3C_TRAFFIC_FORCE_RW_MASK           (0x3<<11)
#define     I3C_TRAFFIC_IBI_EN_MASK             (0x1<<13)
#define     I3C_TRAFFIC_HANDOFF_MASK            (0x1<<14)
#define     I3C_TRAFFIC_DDR_FLEX_MASK           (0x1<<15)

/* 0x68: SHAPE */
#define     I3C_SHAPE_TBIT_FILL_OFFSET          (0)
#define     I3C_SHAPE_TBIT_STALL_OFFSET         (1)
#define     I3C_SHAPE_TBIT_PARITY_OFFSET        (2)
#define     I3C_SHAPE_TBIT_RS_OFFSET            (3)
#define     I3C_SHAPE_HDR_STRETCH_OFFSET        (4)

#define     I3C_SHAPE_TBIT_FILL_MASK            (1<<0)
#define     I3C_SHAPE_TBIT_STALL_MASK           (1<<1)
#define     I3C_SHAPE_TBIT_PARITY_MASK          (1<<2)
#define     I3C_SHAPE_TBIT_RS_MASK              (1<<3)
#define     I3C_SHAPE_HDR_STRETCH_MASK          (0xF<<4)


enum    {
    I3C_HFIFO_DATA_NINTH_BIT_IGNORE = 0,
    I3C_HFIFO_DATA_NINTH_BIT_ACK,
    I3C_HFIFO_DATA_NINTH_BIT_NACK,
    I3C_HFIFO_DATA_NINTH_BIT_PARITY
};


/* 0x71: HFIFO */
#define     I3C_HFIFO_WR_EN_MASK                (1 << 15)
#define     I3C_HFIFO_HS_SPEED_MASK             (1 << 10)

#define     I3C_HFIFO_9BIT_IGNORE               (0)
#define     I3C_HFIFO_9BIT_ACK                  (1 << 8)
#define     I3C_HFIFO_9BIT_NACK                 (2 << 8)
#define     I3C_HFIFO_9BIT_PARITY               (3 << 8)

/* 0x74: DEBUGCTRL */
#define     I3C_DEBUGCTRL_ERR_DET_OFFSET        (2)

#define     I3C_DEBUGCTRL_ERR_DET_MASK          (0x1 << I3C_DEBUGCTRL_ERR_DET_OFFSET)

/* 0xF4: FIFO_STAT */
#define     I3C_FIFO_STAT_FIFO_OFS_OFFSET       (0)
#define     I3C_FIFO_STAT_WR_ADDR_OFFSET        (5)
#define     I3C_FIFO_STAT_RD_ADDR_OFFSET        (10)

#define     I3C_FIFO_STAT_FIFO_OFS_MASK         (0x1F)
#define     I3C_FIFO_STAT_WR_ADDR_MASK          (0x1F<<5)
#define     I3C_FIFO_STAT_RD_ADDR_MASK          (0x1F<<10)




/*************************** I3C register definition end line  *******************************
 */
typedef struct {
    __IO    uint32_t    GLB_STA;                /* 0x0000 */
    __IO    uint32_t    RESERVE_0004;           /* 0x0004 */
    __IO    uint32_t    GLB_CPU0_CFG;           /* 0x0008 */
    __IO    uint32_t    GLB_CPU0_SET;           /* 0x000C */

    __IO    uint32_t    GLB_CPU0_CLR;           /* 0x0010 */
    __IO    uint32_t    GLB_CPU1_CFG;           /* 0x0014 */
    __IO    uint32_t    GLB_CPU1_SET;           /* 0x0018 */
    __IO    uint32_t    GLB_CPU1_CLR;           /* 0x001C */

    __IO    uint32_t    GLB_SWRST;              /* 0x0020 */
    __IO    uint32_t    RESERVE_24;             /* 0x0024 */
    __IO    uint32_t    GLB_LIMITER;            /* 0x0028 */
    __IO    uint32_t    RESERVE_002C;           /* 0x002C */

    __IO    uint32_t    GLB_DBG;                /* 0x0030 */
    __IO    uint32_t    RESERVE_003X[3];        /* 0x003x */

    __IO    uint32_t    GLB_BUSY;               /* 0x0040 */
    __IO    uint32_t    GLB_INTR;               /* 0x0044 */
    __IO    uint32_t    RESERVE_004X[2];        /* 0x003x */

    __IO    uint32_t    GLB_CPU2_CFG;           /* 0x0050 */
    __IO    uint32_t    GLB_CPU2_SET;           /* 0x0054 */
    __IO    uint32_t    GLB_CPU2_CLR;           /* 0x0058 */
    __IO    uint32_t    RESERVE_005C;           /* 0x005C */

    __IO    uint32_t    GLB_CPU3_CFG;           /* 0x0060 */
    __IO    uint32_t    GLB_CPU3_SET;           /* 0x0064 */
    __IO    uint32_t    GLB_CPU3_CLR;           /* 0x0068 */
    __IO    uint32_t    RESERVE_006C;           /* 0x006C */

    __IO    uint32_t    GLB_CLK_CFG;            /* 0x0070 */
    __IO    uint32_t    GLB_CLK_SET;            /* 0x0074 */
    __IO    uint32_t    GLB_CLK_CLR;            /* 0x0078 */
    __IO    uint32_t    RESERVE_007C;           /* 0x007C */

    __IO    uint32_t    RESERVE_008X[4];        /* 0x008X */
    __IO    uint32_t    RESERVE_009X[4];        /* 0x009X */
    __IO    uint32_t    RESERVE_00AX[4];        /* 0x00AX */
    __IO    uint32_t    RESERVE_00BX[4];        /* 0x00BX */
    __IO    uint32_t    RESERVE_00CX[4];        /* 0x00CX */
    __IO    uint32_t    RESERVE_00DX[4];        /* 0x00DX */
    __IO    uint32_t    RESERVE_00EX[4];        /* 0x00EX */
    __IO    uint32_t    RESERVE_00FX[4];        /* 0x00F0 */

    __IO    uint32_t    RESERVE_010X[2];        /* 0x010x */
    __IO    uint32_t    PDMA1_WPPT;             /* 0x0108 */
    __IO    uint32_t    PDMA1_WPTO;             /* 0x010C */

    __IO    uint32_t    PDMA1_COUNT;            /* 0x0110 */
    __IO    uint32_t    PDMA1_CON;              /* 0x0114 */
    __IO    uint32_t    PDMA1_START;            /* 0x0118 */
    __IO    uint32_t    PDMA1_INTSTA;           /* 0x011C */

    __IO    uint32_t    PDMA1_ACKINT;           /* 0x0120 */
    __IO    uint32_t    PDMA1_RLCT;             /* 0x0124 */
    __IO    uint32_t    PDMA1_LIMITER;          /* 0x0128 */
    __IO    uint32_t    PDMA1_PGMADDR;          /* 0x012C */

    __IO    uint32_t    RESERVE_01XX[52];       /* 0x01xx */

    __IO    uint32_t    RESERVE_02XX[2];        /* 0x02xx */
    __IO    uint32_t    PDMA2_WPPT;             /* 0x0208 */
    __IO    uint32_t    PDMA2_WPTO;             /* 0x020C */

    __IO    uint32_t    PDMA2_COUNT;            /* 0x0210 */
    __IO    uint32_t    PDMA2_CON;              /* 0x0214 */
    __IO    uint32_t    PDMA2_START;            /* 0x0218 */
    __IO    uint32_t    PDMA2_INTSTA;           /* 0x021C */

    __IO    uint32_t    PDMA2_ACKINT;           /* 0x0220 */
    __IO    uint32_t    PDMA2_RLCT;             /* 0x0224 */
    __IO    uint32_t    PDMA2_LIMITER;          /* 0x0228 */
    __IO    uint32_t    PDMA2_PGMADDR;          /* 0x022C */

}I2C_PDMA_REGISTER_T;


#define I2C_AO_CLOCK_FREQUENCY  26000000  /* 26Mhz */
// #define I2C_CLOCK_FREQUENCY     104000000 /* 104Mhz */
#define I2C_CLOCK_FREQUENCY     26000000 /* 26Mhz */
#define I3C_CLOCK_FREQUENCY     104000000 /* 104Mhz */

#endif /* __I3C_REG_DEFINITION_H__ */