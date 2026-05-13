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

#ifndef __UART_REG_DEFINITION_H__
#define __UART_REG_DEFINITION_H__


#include <stdint.h>


/* Register definitions for UART */
typedef struct {
    union {
        struct {
            __IO uint8_t SW_FLOW_CONT; /* Software flow control */
            __IO uint8_t HW_FLOW_CONT; /* Hardware flow control */
            __O uint8_t SEND_XOFF; /* Send XOFF */
            __O uint8_t SEND_XON; /* Send XON */
        } EFR_CELLS;
        __O uint32_t EFR; /*00: Interrupt enable register */
    } EFR_UNION;

    union {
        struct {
            __IO uint8_t XOFF; /* XON character for software flow control */
            __IO uint8_t XON; /* XOFF character for software flow control */
            __I uint8_t RESERVED[2];
        } XON_XOFF_CELLS;
        __IO uint32_t XON_XOFF; /*04: XON & XOFF register */
    } XON_XOFF_UNION;

    union {
        struct {
            __IO uint8_t ESCAPE_CHAR; /* Escape character setting */
            __IO uint8_t ESCAPE_EN; /* Enable escape character */
            __I uint8_t RESERVED[2];
        } ESCAPE_REG_CELLS;
        __IO uint32_t ESCAPE_REG; /*08: Escape character register */
    } ESCAPE_REG_UNION;

    union {
        struct {
            __IO uint8_t SLEEP_IDLE_FC_EN;
            __IO uint8_t SLEEP_SEND_XOFF_RTS_EN;
            __IO uint8_t SLEEP_FC_EN;
            __I uint8_t RESERVED[1];
        } SLEEP_REG_CELLS;
        __IO uint32_t SLEEP_REG;/*0C: sleep register */
    } SLEEP_REG_UNION;

    union {
        struct {
            __IO uint8_t AUTOBAUD_EN; /* Enable auto-baud */
            __IO uint8_t AUTOBAUD_SEL; /* Auto-baud mode */
            __IO uint8_t AUTOBAUD_SLEEP_ACK; /* Enable auto-baud sleep ack */
            __I uint8_t RESERVED;
        } AUTOBAUD_CON_CELLS;
        __IO uint32_t AUTOBAUD_CON; /*10: Autoband control register */
    } AUTOBAUD_CON_UNION;

    union {
        struct {
            __IO uint8_t AUTOBAUD_SAMPLE; /* Clock division for auto-baud detection */
            __IO uint8_t AUTOBAUD_RATEFIX; /* System clock rate for auto-baud detection */
            __IO uint8_t RATEFIX; /* System clock rate for Tx/Rx */
            __I uint8_t RESERVED;
        } RATEFIX_CELLS;
        __IO uint32_t RATEFIX; /*14: Clock rate fix register */
    } RATEFIX_UNION;

    union {
        struct {
            __I uint8_t AUTOBAUD_RATE; /* Auto-baud baudrate */
            __I uint8_t AUTOBAUD_STAT; /* Auto-baud state */
            __I uint8_t RESERVED[2];
        } AUTOBAUD_REG_CELLS;
        __I uint32_t AUTOBAUD_REG; /*18: Autobaud monitor register */
    } AUTOBAUD_REG_UNION;

    __IO uint32_t DLM_DLL; /*1C: Divisor latch register */

    union {
        struct {
            __IO uint8_t SPEED;/*Sample counter period*/
            __I uint8_t RESERVED[1];
            __IO uint8_t SAMPLE_COUNT; /* Sample counter */
            __IO uint8_t SAMPLE_POINT; /* Sample point */
        } SAMPLE_REG_CELLS;
        __IO uint32_t SAMPLE_REG; /*20: Sample counter & sample point register */
    } SAMPLE_REG_UNION;

    __IO uint32_t FRACDIV; /*24: Fractional divider register */

    union {
        struct {
            __IO uint8_t RX_DMA_EN; /* Enable Rx DMA mode */
            __IO uint8_t TX_DMA_EN; /* Enable Tx DMA mode */
            __IO uint8_t FIFO_LSR_SEL; /* FIFO LSR mode */
            __IO uint8_t CLR_DMA_MODE_TO;/*CLE_DMA_MODE_TO*/
        } DMA_CON_CELLS;
        __IO uint32_t DMA_CON; /*28: DMA mode control register */
    } DMA_CON_UNION;

    union {
        struct {
            __IO uint8_t FIFOE; /* Enable Rx & Tx FIFOs */
            __IO uint8_t RFTL_TFTL; /* Rx & Tx FIFO trigger threshold */
            __O uint8_t CLRR; /* Clear Rx FIFO */
            __O uint8_t CLRT; /* Clear Tx FIFO */
        } FCR_CELLS;
        __O uint32_t FCR; /*2C: FIFO control register */
    } FCR_UNION;

    __IO uint32_t RXTRIG; /*30: Rx FIFO trigger threshold register */

    union {
        struct {
            __IO uint8_t PAR_STB_WLS; /* Parity, stop bits, & word length setting */
            __IO uint8_t SB; /* Set break */
            __IO uint8_t GUARD; /* Guard interval setting */
            __I uint8_t RESERVED[1];
        } LCR_CELLS;
        __IO uint32_t LCR; /*34: Line control register */
    } LCR_UNION;

    union {
        struct {
            __IO uint8_t RX_TO_MODE; /* Rx timeout mode */
            __IO uint8_t TO_CNT_AUTORST; /* Time-out counter auto reset */
            __IO uint8_t FC_TOC_DIS; /* FC_TOC_DIS */
            __I uint8_t RESERVED[1];
        } RX_TO_CON_CELLS;
        __IO uint32_t RX_TO_CON; /*38: Rx timeout mode control register */
    } RX_TO_CON_UNION;

    __IO uint32_t RX_TOC_DEST; /*3C: Rx timeout counter destination value register */

    union {
        struct {
            __IO uint8_t ETSEI_ETBEI; /* Tx interrupt */
            __IO uint8_t ELSI_ERBFI; /* Rx interrupt */
            __IO uint8_t DETCI_XOFFI; /* DETCI/XOFF interrupt */
            __IO uint8_t CTSI_RTSI; /* CTS & RTS interrupt */
        } IER_CELLS;
        __IO uint32_t IER; /*40: Interrupt enable register */
    } IER_UNION;

    __IO uint32_t DETC; /*44: Special character for detect */

    __I uint32_t RBR; /*48: RX buffer register */

    __O uint32_t THR; /*4C: TX holding register */

    __I uint32_t IIR; /*50: Interrupt identification register */

    union {
        struct {
            __IO uint8_t RTS; /* RTS state */
            __IO uint8_t LOOP; /* Enable loop-back mode */
            __I uint8_t XOFF_STATUS; /* XOFF status */
            __IO uint8_t XOFF_CLEAR; /* Clear XOFF status */
        } MCR_CELLS;
        __IO uint32_t MCR; /*54: Modem control register */
    } MCR_UNION;

    __I uint32_t LSR; /*58: Line status register */

    __IO uint32_t SCR; /*5C: Scratch register */

    // __IO uint32_t DLY_SEL; /*60: Rx data delay */

    // __I uint32_t DEBUG_0_ADDR; /*70: DEBUG_0_ADDR */

    // __I uint32_t DEBUG_1_ADDR; /*74: DEBUG_0_ADDR */

    // __I uint32_t DEBUG_2_ADDR; /*78: DEBUG_0_ADDR */

    // __I uint32_t DEBUG_3_ADDR; /*7C: DEBUG_0_ADDR */

    // __I uint32_t DEBUG_SEL; /*80: DEBUG_SEL */
} UART_REGISTER_T;

#define UART0   ((UART_REGISTER_T *)(UART0_BASE))
#define UART1   ((UART_REGISTER_T *)(UART1_BASE))
#define UART2   ((UART_REGISTER_T *)(UART2_BASE))

/* Total register field bit definition */
/* Bit definition for Interrupt Enable Register */
// #define UART_IER_ETBEI_OFFSET   (0) /* generated if RBR has data or the RX Trigger Level is reached */
// #define UART_IER_ETBEI_MASK     (0x1<<UART_IER_ETBEI_OFFSET)

/* Bit definition for Interrupt Identification Register */
#define UART_IIR_ID_OFFSET      (0) /* Interrupt Source Identification */
#define UART_IIR_ID_MASK        (0xFF<<UART_IIR_ID_OFFSET)

/* Bit definition for FIFO Control Register */
#define UART_FCR_CLRT_OFFSET    (24) /* control bit to clear tx fifo */
#define UART_FCR_CLRT_MASK      (0x1<<UART_FCR_CLRT_OFFSET)
#define UART_FCR_CLRR_OFFSET    (16) /* control bit to clear rx fifo */
#define UART_FCR_CLRR_MASK      (0x1<<UART_FCR_CLRR_OFFSET)
#define UART_FCR_RFTL_OFFSET    (10) /* RX FIFO trigger threshold */
#define UART_FCR_RFTL_MASK      (0x3<<UART_FCR_RFTL_OFFSET)
#define UART_FCR_TFTL_OFFSET    (8) /* TX FIFO trigger threshold */
#define UART_FCR_TFTL_MASK      (0x3<<UART_FCR_TFTL_OFFSET)
#define UART_FCR_FIFOE_OFFSET   (0) /* Enable Rx & Tx FIFOs */
#define UART_FCR_FIFOE_MASK     (0x1<<UART_FCR_FIFOE_OFFSET)

/* Bit definition for Line Control Register */
#define UART_LCR_GUARD_EN_OFFSET  (20) /* Guard interval add enable signal */
#define UART_LCR_GUARD_EN_MASK    (0x1<<UART_GUARD_GUARD_EN_OFFSET)
#define UART_LCR_GUARD_CNT_OFFSET (16) /* Guard interval count value */
#define UART_LCR_GUARD_CNT_MASK   (0x0F<<UART_GUARD_GUARD_CNT_OFFSET)
#define UART_LCR_SB_OFFSET      (8) /* Set Break */
#define UART_LCR_SB_MASK        (0x1<<UART_LCR_SB_OFFSET)
#define UART_LCR_PARITY_OFFSET  (3) /* Parity */
#define UART_LCR_PARITY_MASK    (0x7<<UART_LCR_PARITY_OFFSET)
#define UART_LCR_STB_OFFSET     (2) /* Number of STOP bits */
#define UART_LCR_STB_MASK       (0x1<<UART_LCR_STB_OFFSET)
#define UART_LCR_WORD_OFFSET    (0) /* Word Length */
#define UART_LCR_WORD_MASK      (0x3<<UART_LCR_WORD_OFFSET)

/* Bit definition for Modem Control Register */
#define UART_MCR_XOFF_CLEAR_OFFSET (24) /* whether an XOFF character is received */
#define UART_MCR_XOFF_CLEAR_MASK   (0x1<<UART_MCR_XOFF_CLEAR_OFFSET)
#define UART_MCR_XOFF_STATUS_OFFSET (16) /* whether an XON character is received */
#define UART_MCR_XOFF_STATUS_MASK   (0x1<<UART_MCR_XOFF_STATUS_OFFSET)
#define UART_MCR_LOOP_OFFSET        (8) /* Loop-back control bit */
#define UART_MCR_LOOP_MASK          (0x1<<UART_MCR_LOOP_OFFSET)
#define UART_MCR_RTS_OFFSET         (0) /* Controls the state of the output RTS, even in loop mode */
#define UART_MCR_RTS_MASK           (0x1<<UART_MCR_RTS_OFFSET)

/* Bit definition for XON & XOFF character Register */
#define UART_XON_XOFF_XONCHAR_OFFSET (8) /* define XON character */
#define UART_XON_XOFF_XONCHAR_MASK   (0xff<<UART_XON_XOFF_XONCHAR_OFFSET)
#define UART_XON_XOFF_XOFFCHAR_OFFSET (0) /* define XOFF character */
#define UART_XON_XOFF_XOFFCHAR_MASK   (0xff<<UART_XON_XOFF_XOFFCHAR_OFFSET)

/* Bit definition for Line Status Register */
#define UART_LSR_FIFOERR_OFFSET (7) /* RX FIFO Error Indicator */
#define UART_LSR_FIFOERR_MASK   (0x1<<UART_LSR_FIFOERR_OFFSET)
#define UART_LSR_TEMT_OFFSET    (6) /* TX Holding Register (or TX FIFO) and the TX Shift Register are empty */
#define UART_LSR_TEMT_MASK      (0x1<<UART_LSR_TEMT_OFFSET)
#define UART_LSR_THRE_OFFSET    (5) /* Indicates if there is room for TX Holding Register or TX FIFO is reduced to its Trigger Level */
#define UART_LSR_THRE_MASK      (0x1<<UART_LSR_THRE_OFFSET)
#define UART_LSR_BI_OFFSET  (4) /* Break Interrupt */
#define UART_LSR_BI_MASK    (0x1<<UART_LSR_BI_OFFSET)
#define UART_LSR_FE_OFFSET  (3) /* Framing Error */
#define UART_LSR_FE_MASK    (0x1<<UART_LSR_FE_OFFSET)
#define UART_LSR_PE_OFFSET  (2) /* Parity Error */
#define UART_LSR_PE_MASK    (0x1<<UART_LSR_PE_OFFSET)
#define UART_LSR_OE_OFFSET  (1) /* Overrun Error */
#define UART_LSR_OE_MASK    (0x1<<UART_LSR_OE_OFFSET)
#define UART_LSR_DR_OFFSET  (0) /* Data Ready */
#define UART_LSR_DR_MASK    (0x1<<UART_LSR_DR_OFFSET)

/* Bit definition for Auto Baud Detect Enable Register */
#define UART_AUTOBAUD_CON_SLEEP_ACK_SEL_OFFSET   (16) /* Sleep ack select when autobaud_en */
#define UART_AUTOBAUD_CON_SLEEP_ACK_SEL_MASK     (0x1<<UART_AUTOBAUD_CON_SLEEP_ACK_SEL_OFFSET)
#define UART_AUTOBAUD_CON_AUTOBAUD_SEL_OFFSET    (8) /* Auto-baud select */
#define UART_AUTOBAUD_CON_AUTOBAUD_SEL_MASK      (0x1<<UART_AUTOBAUD_CON_AUTOBAUD_SEL_OFFSET)
#define UART_AUTOBAUD_CON_AUTOBAUD_EN_OFFSET     (0) /* Auto-baud enable signal */
#define UART_AUTOBAUD_CON_AUTOBAUD_EN_MASK       (0x1<<UART_AUTOBAUD_CON_AUTOBAUD_EN_OFFSET)

/* Bit definition for High Speed Mode Register */
#define UART_HIGHSPEED_SPEED_OFFSET (0) /* UART sample counter base */
#define UART_HIGHSPEED_SPEED_MASK   (0x3<<UART_HIGHSPEED_SPEED_OFFSET)

/* Bit definition for Sample counter & sample point register */
#define UART_SAMPLE_REG_SAMPLE_POINT_OFFSET (24) /* Sample point */
#define UART_SAMPLE_REG_SAMPLE_POINT_MASK   (0xff<<UART_SAMPLE_REG_SAMPLE_POINT_OFFSET)
#define UART_SAMPLE_REG_SAMPLE_COUNT_OFFSET (16) /* Sample counter */
#define UART_SAMPLE_REG_SAMPLE_COUNT_MASK   (0xff<<UART_SAMPLE_REG_SAMPLE_COUNT_OFFSET)
#define UART_SAMPLE_REG_SPEED_OFFSET (0) /* UART sample counter base */
#define UART_SAMPLE_REG_SPEED_MASK   (0x3<<UART_SAMPLE_REG_SPEED_OFFSET)

/* Bit definition for Auto Baud Monitor Register */
#define UART_AUTOBAUD_REG_BAUD_STAT_OFFSET  (8) /* frame detect result */
#define UART_AUTOBAUD_REG_BAUD_STAT_MASK    (0x0F<<UART_AUTOBAUD_REG_BAUD_STAT_OFFSET)
#define UART_AUTOBAUD_REG_BAUD_RATE_OFFSET  (0) /* baudrate detect result */
#define UART_AUTOBAUD_REG_BAUD_RATE_MASK    (0x0F<<UART_AUTOBAUD_REG_BAUD_RATE_OFFSET)

/* Bit definition for Clock Rate Fix Register */
#define UART_RATEFIX_RATEFIX_OFFSET (16) /* System clock rate for Tx/Rx */
#define UART_RATEFIX_RATEFIX_MASK   (0x1<<UART_RATEFIX_RATEFIX_OFFSET)
#define UART_RATEFIX_AUTOBAUD_RATEFIX_OFFSET (8) /* System clock rate for auto-baud detection */
#define UART_RATEFIX_AUTOBAUD_RATEFIX_MASK   (0x1<<UART_RATEFIX_AUTOBAUD_RATEFIX_OFFSET)
#define UART_RATEFIX_AUTOBAUD_SAMPLE_OFFSET (0) /* Clock division for auto-baud detection */
#define UART_RATEFIX_AUTOBAUD_SAMPLE_MASK   (0x3f<<UART_RATEFIX_AUTOBAUD_SAMPLE_OFFSET)

/* Bit definition for Escape character register */
#define UART_ESCAPE_REG_EN_OFFSET     (8) /* Add escape character when TX and remove escape character when RX */
#define UART_ESCAPE_REG_EN_MASK       (0x1<<UART_ESCAPE_REG_EN_OFFSET)
#define UART_ESCAPE_REG_CHAR_OFFSET   (0) /* define escape character */
#define UART_ESCAPE_REG_CHAR_MASK     (0xff<<UART_ESCAPE_REG_CHAR_OFFSET)

/* Bit definition for Sleep enable register */
#define UART_SLEEP_EN_OFFSET    (0) /* Sleep enable bit */
#define UART_SLEEP_EN_MASK      (0x1<<UART_SLEEP_EN_OFFSET)
#define UART_SLEEP_IDLE_FC_EN_OFFSET    (8) /* Sleep idle flow control enable bit */
#define UART_SLEEP_IDLE_FC_EN_MASK      (0x1<<UART_SLEEP_IDLE_FC_EN_OFFSET)

/* Bit definition for Rx Trigger Address register */
#define UART_RXTRIG_OFFSET (0) /* When {rtm,rtl}=2'b11, The Rx FIFO threshold will be Rxtrig */
#define UART_RXTRIG_MASK   (0x0F<<UART_RXTRIG_OFFSET)

/* Bit definition for Fractional Divider Address register */
#define UART_FRACDIV_OFFSET   (0) /* Add sampling count when in state stop to parity */
#define UART_FRACDIV_MASK     (0x3ff<<UART_FRACDIV_OFFSET)

/* Bit definition for Rx timeout mode control register */
#define UART_RX_TO_CON_FC_TO_DIS_OFFSET (16) /* Time-out counter auto reset */
#define UART_RX_TO_CON_FC_TO_DIS_MASK   (0x1<<UART_RX_TO_CON_FC_TO_DIS_OFFSET)
#define UART_RX_TO_CON_TO_CNT_AUTORST_OFFSET (8) /* Time-out counter auto reset */
#define UART_RX_TO_CON_TO_CNT_AUTORST_MASK   (0x1<<UART_RX_TO_CON_TO_CNT_AUTORST_OFFSET)
#define UART_RX_TO_CON_RX_TO_MODE_OFFSET (0) /* Rx timeout mode */
#define UART_RX_TO_CON_RX_TO_MODE_MASK   (0x1<<UART_RX_TO_CON_RX_TO_MODE_OFFSET)

/* Bit definition from BTA view */
/* Bit definition for Interrupt Enable Register */
#define UART_IER_CTSI_OFFSET    (1) /* generated when a rising edge is detected on the CTS modem control line */
#define UART_IER_CTSI_MASK      (0x1<<UART_IER_CTSI_OFFSET)
#define UART_IER_RTSI_OFFSET    (0) /* generated when a rising edge is detected on the RTS modem control line */
#define UART_IER_RTSI_MASK      (0x1<<UART_IER_RTSI_OFFSET)
#define UART_IER_DETCI_OFFSET   (1) /* generated when an DEAD character is received */
#define UART_IER_DETCI_MASK     (0x1<<UART_IER_DETCI_OFFSET)
#define UART_IER_XOFFI_OFFSET   (0) /* generated when an XOFF character is received */
#define UART_IER_XOFFI_MASK     (0x1<<UART_IER_XOFFI_OFFSET)
#define UART_IER_ELSI_OFFSET    (1) /* generated if BI, FE, PE or OE (LSR[4:1]) becomes set */
#define UART_IER_ELSI_MASK      (0x1<<UART_IER_ELSI_OFFSET)
#define UART_IER_ERBFI_OFFSET   (0) /* generated if RBR has data or the RX Trigger Level is reached */
#define UART_IER_ERBFI_MASK     (0x1<<UART_IER_ERBFI_OFFSET)
#define UART_IER_ETSEI_OFFSET   (1) /* generated if the TSR is empty */
#define UART_IER_ETSEI_MASK     (0x1<<UART_IER_ETSEI_OFFSET)
#define UART_IER_ETBEI_OFFSET   (0) /* generated if the THR is empty or TX FIFO reduced to its Trigger Level */
#define UART_IER_ETBEI_MASK     (0x1<<UART_IER_ETBEI_OFFSET)

/* Bit definition for Enhanced Feature Register */
#define UART_EFR_SEND_XON_OFFSET    (0) /* Send XON */
#define UART_EFR_SEND_XON_MASK      (0x1<<UART_EFR_SEND_XON_OFFSET)
#define UART_EFR_SEND_XOFF_OFFSET   (0) /* Send XOFF */
#define UART_EFR_SEND_XOFF_MASK     (0x1<<UART_EFR_SEND_XOFF_OFFSET)
#define UART_EFR_HW_TX_FLOWCTRL_OFFSET (1) /* Hardware flow control */
#define UART_EFR_HW_TX_FLOWCTRL_MASK   (0x1<<UART_EFR_HW_TX_FLOWCTRL_OFFSET)
#define UART_EFR_HW_RX_FLOWCTRL_OFFSET (0) /* Hardware flow control */
#define UART_EFR_HW_RX_FLOWCTRL_MASK   (0x1<<UART_EFR_HW_RX_FLOWCTRL_OFFSET)
#define UART_EFR_SW_TX_FLOWCTRL_OFFSET (1) /* Software flow control */
#define UART_EFR_SW_TX_FLOWCTRL_MASK   (0x1<<UART_EFR_SW_TX_FLOWCTRL_OFFSET)
#define UART_EFR_SW_RX_FLOWCTRL_OFFSET (0) /* Software flow control */
#define UART_EFR_SW_RX_FLOWCTRL_MASK   (0x1<<UART_EFR_SW_RX_FLOWCTRL_OFFSET)

/* Bit definition for DMA mode control register */
#define UART_DMA_CON_CLR_DMA_MODE_TO_OFFSET (24) /* fifo lsr mode selection */
#define UART_DMA_CON_CLR_DMA_MODE_TO_MASK   (0x1<<UART_DMA_CON_CLR_DMA_MODE_TO_OFFSET)
#define UART_DMA_CON_FIFO_LSR_SEL_OFFSET (16) /* fifo lsr mode selection */
#define UART_DMA_CON_FIFO_LSR_SEL_MASK   (0x1<<UART_DMA_CON_FIFO_LSR_SEL_OFFSET)
#define UART_DMA_CON_TX_DMA_EN_OFFSET    (0) /* TX_DMA mechanism enable signal */
#define UART_DMA_CON_TX_DMA_EN_MASK      (0x1<<UART_DMA_CON_TX_DMA_EN_OFFSET)
#define UART_DMA_CON_RX_DMA_EN_OFFSET    (0) /* RX_DMA mechanism enable signal */
#define UART_DMA_CON_RX_DMA_EN_MASK      (0x1<<UART_DMA_CON_RX_DMA_EN_OFFSET)

#define UART_IIR_NONE      (0x0) /* No interrupt pending */
#define UART_IIR_LSR       (0x1<<UART_IIR_ID_OFFSET) /* Line Status Interrupt */
#define UART_IIR_RDT       (0x8<<UART_IIR_ID_OFFSET) /* RX Data Timeout */
#define UART_IIR_RDR       (0x4<<UART_IIR_ID_OFFSET) /* RX Data Received */
#define UART_IIR_THRE      (0x2<<UART_IIR_ID_OFFSET) /* TX Holding Register Empty */
#define UART_IIR_TSRE      (0x80<<UART_IIR_ID_OFFSET) /* TX Shift Register Empty */
#define UART_IIR_DETC      (0x40<<UART_IIR_ID_OFFSET) /* DETC interrupt*/
#define UART_IIR_RCVXOFF   (0x10<<UART_IIR_ID_OFFSET) /* Software Flow Control */
#define UART_IIR_CTSRTS    (0x20<<UART_IIR_ID_OFFSET) /* Hardware Flow Control */

#define UART_FCR_RXTRIG_1       (0x0<<UART_FCR_RFTL_OFFSET) /* RX FIFO trigger = 1 */
#define UART_FCR_RXTRIG_6       (0x1<<UART_FCR_RFTL_OFFSET) /* RX FIFO trigger = 6 */
#define UART_FCR_RXTRIG_12      (0x2<<UART_FCR_RFTL_OFFSET) /* RX FIFO trigger = 12 */
#define UART_FCR_RXTRIG_USER    (0x3<<UART_FCR_RFTL_OFFSET) /* RX FIFO trigger = RXTRIG */
#define UART_FCR_TXTRIG_1       (0x0<<UART_FCR_TFTL_OFFSET) /* RX FIFO trigger = 1 */
#define UART_FCR_TXTRIG_4       (0x1<<UART_FCR_TFTL_OFFSET) /* RX FIFO trigger = 4 */
#define UART_FCR_TXTRIG_8       (0x2<<UART_FCR_TFTL_OFFSET) /* RX FIFO trigger = 8 */
#define UART_FCR_TXTRIG_14      (0x3<<UART_FCR_TFTL_OFFSET) /* RX FIFO trigger = 14 */

#define UART_LCR_PAR_NONE      (0x4<<UART_LCR_PARITY_OFFSET) /* Odd Even Parity */
#define UART_LCR_PAR_ODD       (0x1<<UART_LCR_PARITY_OFFSET) /* Even Parity Select */
#define UART_LCR_PAR_EVEN      (0x0<<UART_LCR_PARITY_OFFSET) /* Even Parity Select */
#define UART_LCR_STB_1      (0x0<<UART_LCR_STB_OFFSET) /* 1 STOP bits */
#define UART_LCR_STB_2      (0x1<<UART_LCR_STB_OFFSET) /* 2 STOP bits */
#define UART_LCR_WORD_5BITS (0x0<<UART_LCR_WORD_OFFSET) /* Word Length = 5BITS */
#define UART_LCR_WORD_6BITS (0x1<<UART_LCR_WORD_OFFSET) /* Word Length = 6BITS */
#define UART_LCR_WORD_7BITS (0x2<<UART_LCR_WORD_OFFSET) /* Word Length = 7BITS */
#define UART_LCR_WORD_8BITS (0x3<<UART_LCR_WORD_OFFSET) /* Word Length = 8BITS */

#define UART_HIGHSPEED_SPEED_MODE0  (0x0<<UART_HIGHSPEED_SPEED_OFFSET)  /* baud_rate = system clock frequency/16/{DLH, DLL} */
#define UART_HIGHSPEED_SPEED_MODE1  (0x1<<UART_HIGHSPEED_SPEED_OFFSET)  /* baud_rate = system clock frequency/8/{DLH, DLL} */
#define UART_HIGHSPEED_SPEED_MODE2  (0x2<<UART_HIGHSPEED_SPEED_OFFSET)  /* baud_rate = system clock frequency/14/{DLH, DLL} */
#define UART_HIGHSPEED_SPEED_MODE3  (0x3<<UART_HIGHSPEED_SPEED_OFFSET)  /* baud_rate = system clock frequency/(sampe_count+1)/{DLM, DLL} */


#endif /* __UART_REG_DEFINITION_H__ */