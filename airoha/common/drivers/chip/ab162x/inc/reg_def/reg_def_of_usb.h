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

#ifndef __USB_REG_DEFINITION_H__
#define __USB_REG_DEFINITION_H__


#include <stdint.h>


/*************************** USB register definition start line  ********************************/
#ifndef USB_HW_H
#define USB_HW_H

// #define PLATFORM_1568   1

#define USB_BASE             0x41020000 /*USB*/
#define USB_SIFSLV_BASE      0x41030000 /*USB PHY, SIFSLV*/
#define USB_PHY_MSTAR        0x41030000 /*USB PHY*/

#if (defined(DRV_USB_IP_V4))
//=============Controller===================//
#define USB_FADDR  (USB_BASE+0x00) /* RW */
#define USB_POWER  (USB_BASE+0x01)
#define USB_INTRTX  (USB_BASE+0x02) /* 16-bit, status, read only */
#define USB_INTRRX  (USB_BASE+0x04)  /* 16-bit, status, read only */
#define USB_INTRTXE  (USB_BASE+0x06) /* 16-bit, RW */
#define USB_INTRRXE  (USB_BASE+0x08)  /* 16-bit, RW */
#define USB_INTRUSB  (USB_BASE+0x0A)  /* 8-bit, status, read only*/
#define USB_INTRUSBE (USB_BASE+0x0B) /* 8-bit, RW */
#define USB_FRAME  (USB_BASE+0x0C) /* 16-bit, read only */ /*Max Frame length = 11 bits*/
#define USB_INDEX  (USB_BASE+0x0E) /* RW, 4bit available*/
#define USB_TESTMODE (USB_BASE+0x0F) /* RW, 8-bit  */

#define USB_CSR0  (USB_BASE+0x12) /* 16-bit */
#define USB_COUNT0  (USB_BASE+0x18) /* RO, EP0 only*/
#define USB_NAKLIMIT0 (USB_BASE+0x1B) /* RW, host mode only*/
#define USB_TXMAXP  (USB_BASE+0x10) /* 16-bit, RW*/
#define USB_TXCSR  (USB_BASE+0x12)
#define USB_RXMAXP  (USB_BASE+0x14) /* 16-bit, RW*/
#define USB_RXCSR  (USB_BASE+0x16)
#define USB_RXCOUNT (USB_BASE+0x18) /* RO, 14bits */
#define USB_TXTYPE  (USB_BASE+0x1A) /* RW, host mode only */
#define USB_TXINTERVAL (USB_BASE+0x1B) /* RW, host mode only */
#define USB_RXTYPE  (USB_BASE+0x1C) /* RW, host mode only */
#define USB_RXINTERVAL (USB_BASE+0x1D) /* RW, host mode only */

#define USB_EP0   (USB_BASE+0x20) /* 4 byte as 1 queue */
#define USB_EP1   (USB_BASE+0x24)
#define USB_EP2   (USB_BASE+0x28)
#define USB_EP3   (USB_BASE+0x32)
#define USB_EP4   (USB_BASE+0x40)

#define USB_DEVCTL  (USB_BASE+0x60) /* 8-bit  */
#define USB_PWRUPCNT (USB_BASE+0x61) /* RW */
#define USB_TXFIFOSZ (USB_BASE+0x62) /* RW */
#define USB_RXFIFOSZ (USB_BASE+0x63) /* RW */
#define USB_TXFIFOADD (USB_BASE+0x64) /* RW */
#define USB_RXFIFOADD (USB_BASE+0x66) /* RW */

#define USB_BUSPERF3  (USB_BASE+0x74) /* RW */

#define USB_VPLEN  (USB_BASE+0x7B) /* RW, 8-bits */
#define USB_RSTINFO  (USB_BASE+0x7F) /* RW */


#define USB_L1INTS  (USB_BASE+0xA0) /* RW */
#define USB_L1INTM  (USB_BASE+0xA4) /* RW */
#define USB_L1INTP  (USB_BASE+0xA8) /* RW */
#define USB_L1INTC  (USB_BASE+0xAC) /* RW */


#define USB_DMA_INTR_STATUS   (USB_BASE+0x200)     /* 8-bits, W1C */
#define USB_DMA_INTR_UNMASK   (USB_BASE+0x201)     /* 8-bits, R only */
#define USB_DMA_INTR_UNMASK_CLEAR (USB_BASE+0x202)     /* 8-bits, W1S */
#define USB_DMA_INTR_UNMASK_SET  (USB_BASE+0x203)     /* 8-bits, W1S */


#define USB_DMALIMITER   (USB_BASE+0x210)     /* 8-bits, RW */
#define USB_DMA_CONFIG   (USB_BASE+0x220)     /* 8-bits, RW */

#define USB_DMACNTL(_n)   (USB_BASE+0x1F4+(0x10*(_n)))  /* RW, _n = 1~6 */
#define USB_DMAADDR(_n)  (USB_BASE+0x1F8+(0x10*(_n)))  /* RW, _n = 1~6 */
#define USB_DMACNT(_n)   (USB_BASE+0x1FC+(0x10*(_n)))  /* RW, _n = 1~6 */

#define USB_DMA_REALCNT(_n)  (USB_BASE+0x270+(0x10*(_n)))  /* RO, _n = 1~6, 32bits  */
#define USB_DMA_TIMER(_n)   (USB_BASE+0x274+(0x10*(_n)))  /* RW, _n = 1~6, 16bits */


#define USB_RQPKTCOUNT(_n)  (USB_BASE+0x300+(0x04*(_n)))  /* RW, 16bits,  _n = 1~3, host mode RX ep only */

//===================Controller variable===========================//
/* USB_POWER */
#define USB_POWER_ENABLESUSPENDM (0x01)   /* RW */
#define USB_POWER_SUSPENDMODE  (0x02)   /* P: RO ; H: WO */ /*Read clear by the intr. register*/
#define USB_POWER_RESUME    (0x04)   /* RW */
#define USB_POWER_RESET    (0x08)   /* P: RO ; H: RW */
#define USB_POWER_HSMODE    (0x10)   /* RO */
#define USB_POWER_HSENAB    (0x20)   /* RW */
#define USB_POWER_SOFTCONN   (0x40)   /* RW */
#define USB_POWER_ISOUPDATE   (0x80)   /* RW */

/* USB_INTRTX */
#define USB_INTRTX_EP0   (0x01)   /*RO*/
#define USB_INTRTX_EP1   (0x02)   /*RO*/
#define USB_INTRTX_EP2   (0x04)   /*RO*/
#define USB_INTRTX_EP3   (0x08)   /*RO*/
#define USB_INTRTX_EP4   (0x10)   /*RO*/

/* USB_INTRRX */
#define USB_INTRRX_EP1   (0x02)   /*RO*/
#define USB_INTRRX_EP2   (0x04)   /*RO*/
#define USB_INTRRX_EP3   (0x08)   /*RO*/

/* USB_INTRTXE & USB_INTRRXE */
#define USB_INTRE_EPEN   (0x01)   /* RW */
#define USB_INTRE_EPDIS   (0x00)   /* RW */

/* USB_INTRUSB */
#define USB_INTRUSB_SUSPEND (0x01)   /*RO*/
#define USB_INTRUSB_RESUME (0x02)   /*RO*/
#define USB_INTRUSB_RESET  (0x04)   /*RO*/
#define USB_INTRUSB_BABBLE  (0x04)   /*RO*/
#define USB_INTRUSB_SOF  (0x08)   /*RO*/
#define USB_INTRUSB_CONN  (0x10)   /*RO*/
#define USB_INTRUSB_DISCON  (0x20)   /*RO*/
#define USB_INTRUSB_SESSREQ (0x40)   /*RO*/
#define USB_INTRUSB_VBUSERROR (0x80)   /*RO*/

/* USB_INTRUSBE */
#define USB_INTRUSBE_SUSPEND (0x01)   /*RW*/
#define USB_INTRUSBE_RESUME (0x02)   /*RW*/
#define USB_INTRUSBE_RESET  (0x04)   /*RW*/
#define USB_INTRUSBE_BABBLE (0x04)   /*RW*/
#define USB_INTRUSBE_SOF  (0x08)   /*RW*/
#define USB_INTRUSBE_CONN  (0x10)   /*RW*/
#define USB_INTRUSBE_DISCON (0x20)   /*RW*/
#define USB_INTRUSBE_SESSREQ (0x40)   /*RW*/
#define USB_INTRUSBE_VBUSERROR (0x80)   /*RW*/

/* USB_TESTMODE */
#define USB_TESTMODE_TESTSE0NAK  (0x01) /* RW */
#define USB_TESTMODE_TESTJ   (0x02) /* RW */
#define USB_TESTMODE_TESTK   (0x04) /* RW */
#define USB_TESTMODE_TESTPACKET  (0x08) /* RW */
#define USB_TESTMODE_FORCEHS   (0x10) /* RW */
#define USB_TESTMODE_FORCEFS   (0x20) /* RW */
#define USB_TESTMODE_FIFOACCESS  (0x40) /* WO, AC */
#define USB_TESTMODE_FORCEHOST  (0x80) /* RW */

/* USB_DEVCTL */
#define USB_DEVCTL_SESSION   (0x01)  /* RW */
#define USB_DEVCTL_HOSTREQ  (0x02)  /* RW */
#define USB_DEVCTL_HOSTMODE  (0x04)  /* RO */
#define USB_DEVCTL_VBUS   (0x18)  /* RO */
#define USB_DEVCTL_LSDEV   (0x20)  /* RO */
#define USB_DEVCTL_FSDEV   (0x40)  /* RO */
#define USB_DEVCTL_BDEVICE   (0x80)  /* RO */

#define USB_DEVCTL_ABOVE_VBUS_VALID   (0x18)
#define USB_DEVCTL_ABOVE_A_VALID    (0x10)
#define USB_DEVCTL_ABOVE_SESSION_END   (0x01)
#define USB_DEVCTL_BELOW_SESSION_END   (0x00)

/* USB_CSR0 */
#define USB_CSR0_RXPKTRDY    (0x0001)   /* RO */
#define USB_CSR0_TXPKTRDY    (0x0002)   /* RW, AC */
#define USB_CSR0_SENTSTALL    (0x0004)   /* RC */
#define USB_CSR0_DATAEND    (0x0008)   /* WO, AC */
#define USB_CSR0_SETUPEND    (0x0010)   /* RO */
#define USB_CSR0_SENDSTALL    (0x0020)   /* WO, AC */
#define USB_CSR0_SERVICEDRXPKTRDY  (0x0040)   /* WO, AC */
#define USB_CSR0_SERVICEDSETUPEND  (0x0080)   /* WO, AC */
#define USB_CSR0_FLUSHFIFO    (0x0100)   /* WO, AC */
/* in Host mode */
#define USB_CSR0_RXSTALL    (0x0004)
#define USB_CSR0_SETUPPKT    (0x0008)
#define USB_CSR0_ERROR     (0x0010)
#define USB_CSR0_REQPKT    (0x0020)
#define USB_CSR0_STATUSPKT    (0x0040)
#define USB_CSR0_NAKTIMEOUT   (0x0080)
#define USB_CSR0_FLUSHFIFO    (0x0100)
#define USB_CSR0_DISPING    (0x0800)

/* USB_TXMAXP */
#define USB_TXMAXP_MAXPAYLOAD_MASK (0x07FF)
#define USB_TXMAXP_HIGHSPEED_MASK (0xF800)

/* USB_TXCSR */
#define USB_TXCSR_TXPKTRDY    (0x0001)   /* RW */
#define USB_TXCSR_FIFONOTEMPTY  (0x0002)   /* RO */
#define USB_TXCSR_UNDERRUN   (0x0004)   /* RW */
#define USB_TXCSR_FLUSHFIFO   (0x0008)   /* WO */
#define USB_TXCSR_SENDSTALL   (0x0010)   /* RW */
#define USB_TXCSR_SENTSTALL   (0x0020)   /* RC */
#define USB_TXCSR_CLRDATATOG   (0x0040)   /* WO */
#define USB_TXCSR_INCOMPTX    (0x0080)   /* RC */
#define USB_TXCSR_SETTXPKTRDY_TWICE (0x0100)   /* RC */
#define USB_TXCSR_DMAREQMODE   (0x0400)   /* RW */
#define USB_TXCSR_FRCDATATOG   (0x0800)   /* RW */
#define USB_TXCSR_DMAREQENAB   (0x1000)   /* RW */
#define USB_TXCSR_ISO     (0x4000)   /* RW */
#define USB_TXCSR_AUTOSET    (0x8000)   /* RW */
/* in Host mode */
#define USB_TXCSR_ERROR    (0x0004)
#define USB_TXCSR_RXSTALL    (0x0020)
#define USB_TXCSR_NAKTIMEOUT   (0x0080)

/* USB_RXMAXP */
#define USB_RXMAXP_MAXPAYLOAD_MASK (0x07FF)
#define USB_RXMAXP_HIGHSPEED_MASK (0xF800)

/* USB_RXCSR */
#define USB_RXCSR_RXPKTRDY    (0x0001)   /* RC */
#define USB_RXCSR_FIFOFULL    (0x0002)   /* RO, AC */
#define USB_RXCSR_OVERRUN    (0x0004)   /* RC */
#define USB_RXCSR_DATAERROR   (0x0008)   /* RO */
#define USB_RXCSR_FLUSHFIFO   (0x0010)   /* WO, AC */
#define USB_RXCSR_SENDSTALL   (0x0020)   /* RW */
#define USB_RXCSR_SENTSTALL   (0x0040)   /* RC */
#define USB_RXCSR_CLRDATATOG   (0x0080)   /* WO */
#define USB_RXCSR_INCOMPRX    (0x0100)   /* RC */
#define USB_RXCSR_KEEPERRCTATUS  (0x0200)   /* RC */
#define USB_RXCSR_DMAREQMODE   (0x0800)   /* RW */
#define USB_RXCSR_DISNYET    (0x1000)   /* RW */
#define USB_RXCSR_PIDERROR    (0x1000)   /* RO */
#define USB_RXCSR_DMAREQENAB   (0x2000)   /* RW */
#define USB_RXCSR_ISO     (0x4000)   /* RW */
#define USB_RXCSR_AUTOCLEAR   (0x8000)   /* RW */
/* in Host mode */
#define USB_RXCSR_ERROR    (0x0004)
#define USB_RXCSR_NAKTIMEOUT   (0x0008)
#define USB_RXCSR_REQPKT    (0x0020)
#define USB_RXCSR_RXSTALL    (0x0040)
#define USB_RXCSR_SETPEQPKT_TWICE (0x0400)
#define USB_RXCSR_AUTOREQ    (0x4000)

/* USB_TXTYPE */
#define USB_TXTYPE_EPNUM_MASK  (0x0f)
#define USB_TXTYPE_ISO     (0x10)
#define USB_TXTYPE_BULK    (0x20)
#define USB_TXTYPE_INTR    (0x30)
#define USB_TXTYPE_PROTOCOL_MASK  (0x30)

/* USB_RXTYPE */
#define USB_RXTYPE_EPNUM_MASK  (0x0f)
#define USB_RXTYPE_ISO     (0x10)
#define USB_RXTYPE_BULK    (0x20)
#define USB_RXTYPE_INTR    (0x30)
#define USB_RXTYPE_PROTOCOL_MASK  (0x30)

/* USB_PWRUPCNT */
#define USB_PWRUPCNT_MASK    (0x0f)

/* USB_FIFOSZ */
#define USB_FIFOSZ_SIZE_MASK   (0x0F)
#define USB_FIFOSZ_DPB     (0x10)
#define USB_FIFOSZ_SIZE_8    (0x00)
#define USB_FIFOSZ_SIZE_16    (0x01)
#define USB_FIFOSZ_SIZE_32    (0x02)
#define USB_FIFOSZ_SIZE_64    (0x03)
#define USB_FIFOSZ_SIZE_128   (0x04)
#define USB_FIFOSZ_SIZE_256   (0x05)
#define USB_FIFOSZ_SIZE_512   (0x06)
#define USB_FIFOSZ_SIZE_1024   (0x07)
#define USB_FIFOSZ_SIZE_2048   (0x08)
#define USB_FIFOSZ_SIZE_4096   (0x09)

/* USB_FIFOADD */
#define USB_FIFOADD_MASK    (0x1FFF)

/* USB_RXFIFOADD */
#define USB_RXFIFOADD_DATAERRINTREN   (0x8000)
#define USB_RXFIFOADD_OVERRUNINTREN   (0x4000)

/* USB_FIFO2ADD */
#define USB_FIFO2ADD_MASK    (0x1FFF)
#define USB_FIFO2ADD_EN    (0x8000)

/* USB_BUSPERF3 */
#define USB_BUSPERF3_DISUSBRESET   (0x0001)
#define USB_BUSPERF3_SWRST    (0x0002)



/* USB_RSTINFO */
#define USB_RSTINFO_WTFSSE0   (0x00F0)
#define USB_RSTINFO_WTCHRP   (0x000F)



/* USB_L1INTS */
#define USB_L1INTS_TX_INT_STATUS   (0x0001)
#define USB_L1INTS_RX_INT_STATUS   (0x0002)
#define USB_L1INTS_USBCOM_INT_STATUS  (0x0004)
#define USB_L1INTS_DMA_INT_STATUS  (0x0008)

/* USB_L1INTM */
#define USB_L1INTM_TX_INT_UNMASK   (0x0001)
#define USB_L1INTM_RX_INT_UNMASK   (0x0002)
#define USB_L1INTM_USBCOM_INT_UNMASK (0x0004)
#define USB_L1INTM_DMA_INT_UNMASK  (0x0008)
#define USB_L1INTM_PSR_INT_UNMASK  (0x0010)
#define USB_L1INTM_QINT_UNMASK   (0x0020)
#define USB_L1INTM_QHIF_INT_UNMASK  (0x0040)
#define USB_L1INTM_DPDM_INT_UNMASK  (0x0080)
#define USB_L1INTM_VBUSVALID_INT_UNMASK (0x0100)
#define USB_L1INTM_IDDIG_INT_UNMASK  (0x0200)
#define USB_L1INTM_DRVVBUS_INT_UNMASK (0x0400)
#define USB_L1INTM_POWERDOWN_INT_UNMASK (0x0800)


//========================definition of global value===================//
/* descriptor setting limitation */
#define USB_MAX_FIFO_SIZE    4096

#define USB_FIFO_START_ADDRESS  512

#define USB_BULK_FIFO_UNIT_SIZE  64
#ifdef  __ISO_HB__
#define USB_ISO_FIFO_UNIT_SIZE   3072
#else
#define USB_ISO_FIFO_UNIT_SIZE   1024
#endif


#ifdef  __INTR_HB__
#define USB_INTR_FIFO_UNIT_SIZE   3072
#else
#define USB_INTR_FIFO_UNIT_SIZE   1024
#endif


#elif (defined(DRV_USB_IP_V3))
//=============Controller===================//
#define USB_FADDR  (USB_BASE+0x00) /* RW */
#define USB_POWER  (USB_BASE+0x01)
#define USB_INTRTX  (USB_BASE+0x02) /* 16-bit, status, read only */
#define USB_INTRRX  (USB_BASE+0x04)  /* 16-bit, status, read only */
#define USB_INTRTXE  (USB_BASE+0x06) /* 16-bit, RW */
#define USB_INTRRXE  (USB_BASE+0x08)  /* 16-bit, RW */
#define USB_INTRUSB  (USB_BASE+0x0A)  /* 8-bit, status, read only*/
#define USB_INTRUSBE (USB_BASE+0x0B) /* 8-bit, RW */
#define USB_FRAME  (USB_BASE+0x0C) /* 16-bit, read only */ /*Max Frame length = 11 bits*/
#define USB_INDEX  (USB_BASE+0x0E) /* RW, 4bit available*/
#define USB_TESTMODE (USB_BASE+0x0F) /* RW, 8-bit  */

#define USB_CSR0  (USB_BASE+0x12) /* 16-bit */
#define USB_COUNT0  (USB_BASE+0x18) /* RO, EP0 only*/
#define USB_NAKLIMIT0 (USB_BASE+0x1B) /* RW, host mode only*/
#define USB_TXMAXP  (USB_BASE+0x10) /* 16-bit, RW*/
#define USB_TXCSR  (USB_BASE+0x12)
#define USB_RXMAXP  (USB_BASE+0x14) /* 16-bit, RW*/
#define USB_RXCSR  (USB_BASE+0x16)
#define USB_RXCOUNT (USB_BASE+0x18) /* RO, 14bits */
#define USB_TXTYPE  (USB_BASE+0x1A) /* RW, host mode only */
#define USB_TXINTERVAL (USB_BASE+0x1B) /* RW, host mode only */
#define USB_RXTYPE  (USB_BASE+0x1C) /* RW, host mode only */
#define USB_RXINTERVAL (USB_BASE+0x1D) /* RW, host mode only */

#define USB_EP0   (USB_BASE+0x20) /* 4 byte as 1 queue */

#define USB_DEVCTL  (USB_BASE+0x60) /* 8-bit  */
#define USB_PWRUPCNT (USB_BASE+0x61) /* RW */
#define USB_TXFIFOSZ (USB_BASE+0x62) /* RW */
#define USB_RXFIFOSZ (USB_BASE+0x63) /* RW */
#define USB_TXFIFOADD (USB_BASE+0x64) /* RW */
#define USB_RXFIFOADD (USB_BASE+0x66) /* RW */
#define USB_SWRST  (USB_BASE+0x70) /* RW */
#define USB_OPSTATE  (USB_BASE+0x71) /* RW */
#define USB_VPLEN  (USB_BASE+0x7B) /* RW, 8-bits */
#define USB_RSTINFO  (USB_BASE+0x7F) /* RW */


#define USB_EPn_TXCSR(_n)  (USB_BASE+0x102+(0x10*(_n))) /* R */
#define USB_EPn_RXCSR(_n)  (USB_BASE+0x106+(0x10*(_n))) /* R */

#define USB_DMAINTR   (USB_BASE+0x200)     /* 8-bits, W0C */
#define USB_DMALIMITER   (USB_BASE+0x210)     /* 8-bits, RW */
#define USB_DMACNTL(_n)   (USB_BASE+0x1F4+(0x10*(_n)))  /* RW, _n = 1~6 */
#define USB_DMAADDR(_n)  (USB_BASE+0x1F8+(0x10*(_n)))  /* RW, _n = 1~6 */
#define USB_DMACNT(_n)   (USB_BASE+0x1FC+(0x10*(_n)))  /* RW, _n = 1~6 */
#define USB_DMAPPCNTL(_n)  (USB_BASE+0x274+(0x10*(_n)))  /* RW, _n = 1~6 */
#define USB_DMAPPADDR(_n)  (USB_BASE+0x278+(0x10*(_n)))  /* RW, _n = 1~6 */
#define USB_DMAPPCNT(_n)  (USB_BASE+0x27C+(0x10*(_n)))  /* RW, _n = 1~6 */

#define USB_RQPKTCOUNT(_n)  (USB_BASE+0x300+(0x04*(_n)))  /* RW, 16bits,  _n = 1~3, host mode RX ep only */

#define USB_DMA_REALCNT(_n)  (USB_BASE+0x3F0+(0x10*(_n)))  /* RO, _n = 1~6, 32bits  */
#define USB_DMA_PP_REALCNT(_n) (USB_BASE+0x3F4+(0x10*(_n)))  /* RO, _n = 1~6, 32bits  */
#define USB_DMA_TIMER(_n)   (USB_BASE+0x3F8+(0x10*(_n)))  /* RW, _n = 1~6, 16bits */
//===================Controller variable===========================//
/* USB_POWER */
#define USB_POWER_ENABLESUSPENDM (0x01)   /* RW */
#define USB_POWER_SUSPENDMODE  (0x02)   /* P: RO ; H: WO */ /*Read clear by the intr. register*/
#define USB_POWER_RESUME    (0x04)   /* RW */
#define USB_POWER_RESET    (0x08)   /* P: RO ; H: RW */
#define USB_POWER_HSMODE    (0x10)   /* RO */
#define USB_POWER_HSENAB    (0x20)   /* RW */
#define USB_POWER_SOFTCONN   (0x40)   /* RW */
#define USB_POWER_ISOUPDATE   (0x80)   /* RW */

/* USB_INTRTX */
#define USB_INTRTX_EP0   (0x01)   /*RO*/
#define USB_INTRTX_EP1   (0x02)   /*RO*/
#define USB_INTRTX_EP2   (0x04)   /*RO*/
#define USB_INTRTX_EP3   (0x08)   /*RO*/
#define USB_INTRTX_EP4   (0x10)   /*RO*/

/* USB_INTRRX */
#define USB_INTRRX_EP1   (0x02)   /*RO*/
#define USB_INTRRX_EP2   (0x04)   /*RO*/
#define USB_INTRRX_EP3   (0x08)   /*RO*/

/* USB_INTRTXE & USB_INTRRXE */
#define USB_INTRE_EPEN   (0x01)   /* RW */
#define USB_INTRE_EPDIS   (0x00)   /* RW */

/* USB_INTRUSB */
#define USB_INTRUSB_SUSPEND (0x01)   /*RO*/
#define USB_INTRUSB_RESUME (0x02)   /*RO*/
#define USB_INTRUSB_RESET  (0x04)   /*RO*/
#define USB_INTRUSB_BABBLE  (0x04)   /*RO*/
#define USB_INTRUSB_SOF  (0x08)   /*RO*/
#define USB_INTRUSB_CONN  (0x10)   /*RO*/
#define USB_INTRUSB_DISCON  (0x20)   /*RO*/
#define USB_INTRUSB_SESSREQ (0x40)   /*RO*/
#define USB_INTRUSB_VBUSERROR (0x80)   /*RO*/

/* USB_INTRUSBE */
#define USB_INTRUSBE_SUSPEND (0x01)   /*RW*/
#define USB_INTRUSBE_RESUME (0x02)   /*RW*/
#define USB_INTRUSBE_RESET  (0x04)   /*RW*/
#define USB_INTRUSBE_BABBLE (0x04)   /*RW*/
#define USB_INTRUSBE_SOF  (0x08)   /*RW*/
#define USB_INTRUSBE_CONN  (0x10)   /*RW*/
#define USB_INTRUSBE_DISCON (0x20)   /*RW*/
#define USB_INTRUSBE_SESSREQ (0x40)   /*RW*/
#define USB_INTRUSBE_VBUSERROR (0x80)   /*RW*/

/* USB_TESTMODE */
#define USB_TESTMODE_TESTSE0NAK  (0x01) /* RW */
#define USB_TESTMODE_TESTJ   (0x02) /* RW */
#define USB_TESTMODE_TESTK   (0x04) /* RW */
#define USB_TESTMODE_TESTPACKET  (0x08) /* RW */
#define USB_TESTMODE_FORCEHS   (0x10) /* RW */
#define USB_TESTMODE_FORCEFS   (0x20) /* RW */
#define USB_TESTMODE_FIFOACCESS  (0x40) /* WO, AC */
#define USB_TESTMODE_FORCEHOST  (0x80) /* RW */

/* USB_DEVCTL */
#define USB_DEVCTL_SESSION   (0x01)  /* RW */
#define USB_DEVCTL_HOSTREQ  (0x02)  /* RW */
#define USB_DEVCTL_HOSTMODE  (0x04)  /* RO */
#define USB_DEVCTL_VBUS   (0x18)  /* RO */
#define USB_DEVCTL_LSDEV   (0x20)  /* RO */
#define USB_DEVCTL_FSDEV   (0x40)  /* RO */
#define USB_DEVCTL_BDEVICE   (0x80)  /* RO */

#define USB_DEVCTL_ABOVE_VBUS_VALID   (0x18)
#define USB_DEVCTL_ABOVE_A_VALID    (0x10)
#define USB_DEVCTL_ABOVE_SESSION_END   (0x01)
#define USB_DEVCTL_BELOW_SESSION_END   (0x00)

/* USB_CSR0 */
#define USB_CSR0_RXPKTRDY    (0x0001)   /* RO */
#define USB_CSR0_TXPKTRDY    (0x0002)   /* RW, AC */
#define USB_CSR0_SENTSTALL    (0x0004)   /* RC */
#define USB_CSR0_DATAEND    (0x0008)   /* WO, AC */
#define USB_CSR0_SETUPEND    (0x0010)   /* RO */
#define USB_CSR0_SENDSTALL    (0x0020)   /* WO, AC */
#define USB_CSR0_SERVICEDRXPKTRDY  (0x0040)   /* WO, AC */
#define USB_CSR0_SERVICEDSETUPEND  (0x0080)   /* WO, AC */
#define USB_CSR0_FLUSHFIFO    (0x0100)   /* WO, AC */
/* in Host mode */
#define USB_CSR0_RXSTALL    (0x0004)
#define USB_CSR0_SETUPPKT    (0x0008)
#define USB_CSR0_ERROR     (0x0010)
#define USB_CSR0_REQPKT    (0x0020)
#define USB_CSR0_STATUSPKT    (0x0040)
#define USB_CSR0_NAKTIMEOUT   (0x0080)
#define USB_CSR0_FLUSHFIFO    (0x0100)
#define USB_CSR0_DISPING    (0x0800)

/* USB_TXMAXP */
#define USB_TXMAXP_MAXPAYLOAD_MASK (0x07FF)
#define USB_TXMAXP_HIGHSPEED_MASK (0xF800)

/* USB_TXCSR */
#define USB_TXCSR_TXPKTRDY    (0x0001)   /* RW */
#define USB_TXCSR_FIFONOTEMPTY  (0x0002)   /* RO */
#define USB_TXCSR_UNDERRUN   (0x0004)   /* RW */
#define USB_TXCSR_FLUSHFIFO   (0x0008)   /* WO */
#define USB_TXCSR_SENDSTALL   (0x0010)   /* RW */
#define USB_TXCSR_SENTSTALL   (0x0020)   /* RC */
#define USB_TXCSR_CLRDATATOG   (0x0040)   /* WO */
#define USB_TXCSR_INCOMPTX    (0x0080)   /* RC */
#define USB_TXCSR_AUTOSET_SPKT  (0x0200)   /* RW */
#define USB_TXCSR_DMAREQMODE   (0x0400)   /* RW */
#define USB_TXCSR_FRCDATATOG   (0x0800)   /* RW */
#define USB_TXCSR_DMAREQENAB   (0x1000)   /* RW */
#define USB_TXCSR_MODE     (0x2000)   /* RW */
#define USB_TXCSR_ISO     (0x4000)   /* RW */
#define USB_TXCSR_AUTOSET    (0x8000)   /* RW */
/* in Host mode */
#define USB_TXCSR_ERROR    (0x0004)
#define USB_TXCSR_RXSTALL    (0x0020)
#define USB_TXCSR_NAKTIMEOUT   (0x0080)

/* USB_RXMAXP */
#define USB_RXMAXP_MAXPAYLOAD_MASK (0x07FF)
#define USB_RXMAXP_HIGHSPEED_MASK (0xF800)

/* USB_RXCSR */
#define USB_RXCSR_RXPKTRDY    (0x0001)   /* RC */
#define USB_RXCSR_FIFOFULL    (0x0002)   /* RO, AC */
#define USB_RXCSR_OVERRUN    (0x0004)   /* RC */
#define USB_RXCSR_DATAERROR   (0x0008)   /* RO */
#define USB_RXCSR_FLUSHFIFO   (0x0010)   /* WO, AC */
#define USB_RXCSR_SENDSTALL   (0x0020)   /* RW */
#define USB_RXCSR_SENTSTALL   (0x0040)   /* RC */
#define USB_RXCSR_CLRDATATOG   (0x0080)   /* WO */
#define USB_RXCSR_INCOMPRX    (0x0100)   /* RC */
#define USB_RXCSR_INCOMPRXINTREN  (0x0200)   /* RC */
#define USB_RXCSR_AUTOCLREN_SPKT  (0x0400)   /* RC */
#define USB_RXCSR_DMAREQMODE   (0x0800)   /* RW */
#define USB_RXCSR_DISNYET    (0x1000)   /* RW */
#define USB_RXCSR_PIDERROR    (0x1000)   /* RO */
#define USB_RXCSR_DMAREQENAB   (0x2000)   /* RW */
#define USB_RXCSR_ISO     (0x4000)   /* RW */
#define USB_RXCSR_AUTOCLEAR   (0x8000)   /* RW */
/* in Host mode */
#define USB_RXCSR_ERROR    (0x0004)
#define USB_RXCSR_NAKTIMEOUT   (0x0008)
#define USB_RXCSR_REQPKT    (0x0020)
#define USB_RXCSR_RXSTALL    (0x0040)
#define USB_RXCSR_AUTOREQ    (0x4000)

/* USB_TXTYPE */
#define USB_TXTYPE_EPNUM_MASK  (0x0f)
#define USB_TXTYPE_ISO     (0x10)
#define USB_TXTYPE_BULK    (0x20)
#define USB_TXTYPE_INTR    (0x30)
#define USB_TXTYPE_PROTOCOL_MASK  (0x30)

/* USB_RXTYPE */
#define USB_RXTYPE_EPNUM_MASK  (0x0f)
#define USB_RXTYPE_ISO     (0x10)
#define USB_RXTYPE_BULK    (0x20)
#define USB_RXTYPE_INTR    (0x30)
#define USB_RXTYPE_PROTOCOL_MASK  (0x30)

/* USB_PWRUPCNT */
#define USB_PWRUPCNT_MASK    (0x0f)

/* USB_FIFOSZ */
#define USB_FIFOSZ_SIZE_MASK   (0x0F)
#define USB_FIFOSZ_DPB     (0x10)
#define USB_FIFOSZ_SIZE_8    (0x00)
#define USB_FIFOSZ_SIZE_16    (0x01)
#define USB_FIFOSZ_SIZE_32    (0x02)
#define USB_FIFOSZ_SIZE_64    (0x03)
#define USB_FIFOSZ_SIZE_128   (0x04)
#define USB_FIFOSZ_SIZE_256   (0x05)
#define USB_FIFOSZ_SIZE_512   (0x06)
#define USB_FIFOSZ_SIZE_1024   (0x07)
#define USB_FIFOSZ_SIZE_2048   (0x08)
#define USB_FIFOSZ_SIZE_4096   (0x09)

/* USB_FIFOADD */
#define USB_FIFOADD_MASK    (0x1FFF)

/* USB_RXFIFOADD */
#define USB_RXFIFOADD_DATAERRINTREN   (0x8000)
#define USB_RXFIFOADD_OVERRUNINTREN   (0x4000)

/* USB_FIFO2ADD */
#define USB_FIFO2ADD_MASK    (0x1FFF)
#define USB_FIFO2ADD_EN    (0x8000)

/* USB_SWRST */
#define USB_SWRST_DISUSBRESET   (0x0001)
#define USB_SWRST_SWRST    (0x0002)
#define USB_SWRST_FRC_VBUSVALID  (0x0004)
#define USB_SWRST_UNDO_SRPFIX   (0x0008)
#define USB_SWRST_REDUCE_DLY   (0x0010)


/* USB_RSTINFO */
#define USB_RSTINFO_WTFSSE0   (0x00F0)
#define USB_RSTINFO_WTCHRP   (0x000F)

/* USB_DMAINTR */
#define USB_DMA_INTR_MASK    0xFFFFFF00
#define USB_DMA_LIMITER_MASK   0xFFFF00FF
#define USB_DMA_PPFINISH_MASK   0x0000FFFF

/* USB_DMAPPINTR */
#define USB_PPA_FINISH1    (0x01)   /*RO*/
#define USB_PPB_FINISH1     (0x02)   /*RO*/
#define USB_PPA_FINISH2    (0x04)   /*RO*/
#define USB_PPB_FINISH2     (0x08)   /*RO*/
#define USB_PPA_FINISH3    (0x10)   /*RO*/
#define USB_PPB_FINISH3     (0x20)   /*RO*/
#define USB_PPA_FINISH4    (0x40)   /*RO*/
#define USB_PPB_FINISH4     (0x80)   /*RO*/

/* USB_DMACNTL */
#define USB_DMACNTL_DMAEN    (0x0001)
#define USB_DMACNTL_DMADIR   (0x0002)
#define USB_DMACNTL_DMAMODE   (0x0004)
#define USB_DMACNTL_INTEN    (0x0008)
#define USB_DMACNTL_EP_MASK   (0x00F0)
#define USB_DMACNTL_BUSERR   (0x0100)
#define USB_DMACNTL_BURSTMODE_MASK (0x0600)
#define USB_DMACNTL_PPEN    (0x0800)
#define USB_DMACNTL_PPRST    (0x1000)
#define USB_DMACNTL_ENDMAMODE2  (0x2000)

/* USB_DMAPPCNTL */
#define USB_DMAPPCNTL_DMAEN   (0x0001)

/* USB_DMA_TIMER */
#define USB_DMA_TIMER_ENTIMER    (0x0080)
#define USB_DMA_TIMER_TIMEOUT_MASK  (0x007F)
#define USB_DMA_TIMER_TIMEOUT_STATUS (0x0100)

//========================definition of global value===================//
/* descriptor setting limitation */
#define USB_MAX_FIFO_SIZE    4096

#define USB_FIFO_START_ADDRESS  512

#define USB_BULK_FIFO_UNIT_SIZE  64
#ifdef  __ISO_HB__
#define USB_ISO_FIFO_UNIT_SIZE   3072
#else
#define USB_ISO_FIFO_UNIT_SIZE   1024
#endif


#ifdef  __INTR_HB__
#define USB_INTR_FIFO_UNIT_SIZE   3072
#else
#define USB_INTR_FIFO_UNIT_SIZE   1024
#endif


#if (defined(DRV_USB_PHY_COST_DOWN))

//======================USB PHY =============================//
/* USB phy register */
#define USB_PHYCR1_0    (USB_BASE+0x600) /* RW */
#define USB_PHYCR1_1    (USB_BASE+0x601) /* RW */
#define USB_PHYCR1_2    (USB_BASE+0x602) /* RW */
#define USB_PHYCR1_3    (USB_BASE+0x603) /* RW */

#define USB_PHYCR2_0    (USB_BASE+0x604) /* RW */
#define USB_PHYCR2_1    (USB_BASE+0x605) /* RW */
#define USB_PHYCR2_2    (USB_BASE+0x606) /* RW */
#define USB_PHYCR2_3    (USB_BASE+0x607) /* RW */

#define USB_PHYCR3_0    (USB_BASE+0x608) /* RW */
#define USB_PHYCR3_1    (USB_BASE+0x609) /* RW */
#define USB_PHYCR3_2    (USB_BASE+0x60A) /* RW */
#define USB_PHYCR3_3    (USB_BASE+0x60B) /* RW */

#define USB_PHYCR4_0    (USB_BASE+0x60C) /* RW */
//#define USB_PHYCR4_1    (USB_BASE+0x60D) /* RW */
//#define USB_PHYCR4_2    (USB_BASE+0x60E) /* RW */
#define USB_PHYCR4_3    (USB_BASE+0x60F) /* RW */

//#define USB_PHYCR5_0    (USB_BASE+0x610) /* RW */
//#define USB_PHYCR5_1    (USB_BASE+0x611) /* RW */
//#define USB_PHYCR5_2    (USB_BASE+0x612) /* RW */
#define USB_PHYCR5_3    (USB_BASE+0x613) /* RW */

#define USB_PHYIR1_0    (USB_BASE+0x614) /* RW */
#define USB_PHYIR1_1    (USB_BASE+0x615) /* RW */
#define USB_PHYIR1_2    (USB_BASE+0x616) /* RW */
#define USB_PHYIR1_3    (USB_BASE+0x617) /* RW */

#define USB_PHYIR2_0    (USB_BASE+0x618) /* RW */
#define USB_PHYIR2_1    (USB_BASE+0x619) /* RW */
#define USB_PHYIR2_2    (USB_BASE+0x61A) /* RW */
#define USB_PHYIR2_3    (USB_BASE+0x61B) /* RW */

#define USB_PHYIR3_0    (USB_BASE+0x61C) /* RW */
#define USB_PHYIR3_1    (USB_BASE+0x61D) /* RW */
#define USB_PHYIR3_2    (USB_BASE+0x61E) /* RW */
//#define USB_PHYIR3_3    (USB_BASE+0x61F) /* RW */

#define USB_PHYIR4_0    (USB_BASE+0x620) /* RW */
#define USB_PHYIR4_1    (USB_BASE+0x621) /* RW */
#define USB_PHYIR4_2    (USB_BASE+0x622) /* RW */
#define USB_PHYIR4_3    (USB_BASE+0x623) /* RW */

#define USB_PHYIR5_0    (USB_BASE+0x624) /* RW */
#define USB_PHYIR5_1    (USB_BASE+0x625) /* RW */
#define USB_PHYIR5_2    (USB_BASE+0x626) /* RW */
//#define USB_PHYIR5_3    (USB_BASE+0x627) /* RW */

#define USB_PHYIR6_0    (USB_BASE+0x628) /* RW */
#define USB_PHYIR6_1    (USB_BASE+0x629) /* RW */
//#define USB_PHYIR6_2    (USB_BASE+0x62A) /* RW */
//#define USB_PHYIR6_3    (USB_BASE+0x62B) /* RW */

//============================USB PHY variable========================//

/* USB_PHY ALL*/
#define USB_PHY_CLEAR_MASK     (0x00)

/* USB_PHYCR1_0 */
#define USB_PHYCR1_0_BGR_BGR_EN    (0x01)
#define USB_PHYCR1_0_BGR_I_SRC_EN    (0x02)
#define USB_PHYCR1_0_BGR_CHIP_EN    (0x04)
#define USB_PHYCR1_0_IADJ_MASK    (0x70)
#define USB_PHYCR1_0_IADJ_MASK2    (0x40)
#define USB_PHYCR1_0_IADJ_MASK3    (0x50)
#define USB_PHYCR1_0_IADJ_RESISTER_SET      (0x60)
/* USB_PHYCR1_1 */
/* USB_PHYCR1_2 */
#define USB_PHYCR1_2_RG_PLL_DIV  (0x0A)
#define USB_PHYCR1_2_RG_PLL_DIV2  (0x08)
/* USB_PHYCR1_3 */
/* USB_PHYCR2_0 */
/* USB_PHYCR2_1 */
/* USB_PHYCR2_2 */
#define USB_PHYCR2_2_HS_TRIM_TH   (0x08)
#define USB_PHYCR2_2_HSDISC_DEGL  (0x80)
#define USB_PHYCR2_2_HS_DISC_TH   (0x40)
/* USB_PHYCR2_3 */
#define USB_PHYCR2_3_PLL_EN     (0x02)
/* USB_PHYCR3_0 */
#define USB_PHYCR3_0_CDR_FILT     (0x02)
#define USB_PHYCR3_0_EARLY_HSTX_I    (0x40)
#define USB_PHYCR3_0_HS_TX_ANA_SER_EN  (0x80)
/* USB_PHYCR3_1 */
/* USB_PHYCR3_2 */
#define USB_PHYCR3_2_FORCE_DATA_IN   (0x02)
#define USB_PHYCR3_2_FORCE_TX_VALID   (0x01)
#define USB_PHYCR3_2_FORCE_DP_PULLDOWN  (0x04)
#define USB_PHYCR3_2_FORCE_DM_PULLDOWN  (0x08)
#define USB_PHYCR3_2_FORCE_DP_DM_PULLDOWN (0x0C)
#define USB_PHYCR3_2_FORCE_DRV_VBUS   (0x10)
/* USB_PHYCR3_3 */
#define USB_PHYCR3_3_FORCE_OP_MODE   (0x01)
#define USB_PHYCR3_3_FORCE_TERM_SELECT  (0x02)
#define USB_PHYCR3_3_FORCE_SUSPENDM   (0x04)
#define USB_PHYCR3_3_FORCE_XCVR_SELECT  (0x08)
#define USB_PHYCR3_3_FORCE_DP_HIGH   (0x0B)
#define USB_PHYCR3_3_FORCE_IDPULLUP   (0x20)
#define USB_PHYCR3_3_UTMI_MUXSEL    (0x10)
/* USB_PHYCR4_0 */
#define USB_PHYCR4_0_FORCE_USB_CLKOFF    (0x20)
#define USB_PHYCR4_0_FORCE_AUX_EN    (0x80)
#define USB_PHYCR4_0_FORCE_OTG_PROBE    (0x40)
#define USB_PHYCR4_0_FORCE_BVALID       (0x10)
#define USB_PHYCR4_0_FORCE_IDDIG        (0x08)
#define USB_PHYCR4_0_FORCE_VBUSVALID    (0x04)
#define USB_PHYCR4_0_FORCE_SESSEND      (0x02)
#define USB_PHYCR4_0_FORCE_AVALID       (0x01)
/* USB_PHYCR4_1 */
/* USB_PHYCR4_2 */
/* USB_PHYCR4_3 */
#define USB_PHYCR4_3_UART_MODE    (0x08)
/* USB_PHYCR5_0 */
/* USB_PHYCR5_1 */
#define USB_PHYIR5_1_RG_SQTH0 (0x03)
#define USB_PHYIR5_1_RG_RG_RCVB0 (0x20)
#define USB_PHYIR5_1_RG_RG_SQB0 (0x40)
/* USB_PHYCR5_2 */
/* USB_PHYCR5_3 */
#define USB_PHYCR5_3_TERM_SELECT    (0x04)
#define USB_PHYCR5_3_XCVR_SELECT_MASK  (0x30)
#define USB_PHYCR5_3_XCVR_SELECT_L   (0x10)
#define USB_PHYCR5_3_DP_PULL_DOWN   (0x40)
#define USB_PHYCR5_3_DM_PULL_DOWN   (0x80)
#define USB_PHYCR5_3_DP_DM_PULL_DOWN  (0xC0)
#define USB_PHYCR5_3_OP_MODE     (0x01)
#define USB_PHYCR5_3_SUSPENDM   (0x08)
/* USB_PHYIR1_0 */
#define USB_PHYIR1_0_IDPULLUP     (0x01)
#define USB_PHYIR1_0_DRVVBUS     (0x02)
#define USB_PHYIR1_0_TX_VALID     (0x04)
/* USB_PHYIR1_1 */
#define USB_PHYIR1_1_RG_DM1_ABIST_SELE   (0x0A)
#define USB_PHYIR1_1_RG_EN_PD_DM   (0x20)

/* USB_PHYIR1_2 */
/* USB_PHYIR1_3 */
/* USB_PHYIR2_0 */
/* USB_PHYIR2_1 */
#define  USB_PHYIR2_1_RG_USB11_TMODE_EN0  (0x08)
/* USB_PHYIR2_2 */
/* USB_PHYIR2_3 */
/* USB_PHYIR3_0 */
#define USB_PHYIR3_0_LINESTATE_DP    (0x40)
#define USB_PHYIR3_0_LINESTATE_DM    (0x80)
/* USB_PHYIR3_1 */
/* USB_PHYIR3_2 */
/* USB_PHYIR3_3 */
/* USB_PHYIR4_0 */
#define USB_PHYIR4_0_HS_TERMC_MASK  (0x70)
#define USB_PHYIR4_0_RG_CALIB_SELE0_ENABLE  (0xC0)
#define USB_PHYIR4_0_RG_CALIB_SELE0_DISABLE  (0x40)
#define USB_PHYIR4_0_RG_TX_I_TRIM0  (0x03)
#define USB_PHYIR4_0_RG_CALIB_SELE0   (0x50)
/* USB_PHYIR4_1 */
/* USB_PHYIR4_2 */
#define USB_PHYIR4_2_RG_HSTX_SRCTRL0    (0x01)
#define USB_PHYIR4_2_RG_HSTX_DBIST0  (0xC0)
/* USB_PHYIR4_3 */
#define USB_PHYIR4_3_DEGLICH     (0xAA)
#define USB_PHYIR4_3_RG_DISCD   (0x02)
/* USB_PHYIR5_0 */
/* USB_PHYIR5_1 */
#define USB_PHYIR5_1_RG_SQTH0  (0x03)
/* USB_PHYIR5_2 */
/* USB_PHYIR5_3 */
/* USB_PHYIR6_0 */
#define USB_PHYIR6_0_RG_DP_100K_EN  (0x01)
#define USB_PHYIR6_0_RG_DM_100K_EN  (0x02)
/* USB_PHYIR6_1 */
#define USB_PHYIR6_1_BGR_DIV_L    (0x10)
#define USB_PHYIR6_1_RG_OTG_VBUSTH  (0x02)
#define USB_PHYIR6_1_VBUSCMP_EN    (0x04)
/* USB_PHYIR6_2 */
/* USB_PHYIR6_3 */


//////////////////////////////////////////////////////
#define USB_PHYCR2_3_HS_TERMC     (0x08)
#define USB_PHYCR4_1_FORCE_BGR_ON   (0x4F)


#else   // Old PHY  (MT6235 / MT6238 /MT6516 /MT6268A / MT6253T / MT6236)


/* USB phy register */
#define USB_PHYCR1_0    (USB_BASE+0x600) /* RW */
#define USB_PHYCR1_1    (USB_BASE+0x601) /* RW */
#define USB_PHYCR1_2    (USB_BASE+0x602) /* RW */
#define USB_PHYCR1_3    (USB_BASE+0x603) /* RW */

#define USB_PHYCR2_0    (USB_BASE+0x604) /* RW */
#define USB_PHYCR2_1    (USB_BASE+0x605) /* RW */
#define USB_PHYCR2_2    (USB_BASE+0x606) /* RW */
#define USB_PHYCR2_3    (USB_BASE+0x607) /* RW */

#define USB_PHYCR3_0    (USB_BASE+0x608) /* RW */
#define USB_PHYCR3_1    (USB_BASE+0x609) /* RW */
#define USB_PHYCR3_2    (USB_BASE+0x60A) /* RW */
#define USB_PHYCR3_3    (USB_BASE+0x60B) /* RW */

#define USB_PHYCR4_0    (USB_BASE+0x60C) /* RW */
#define USB_PHYCR4_1    (USB_BASE+0x60D) /* RW */
#define USB_PHYCR4_2    (USB_BASE+0x60E) /* RW */
#define USB_PHYCR4_3    (USB_BASE+0x60F) /* RW */

#define USB_PHYCR5_0    (USB_BASE+0x610) /* RW */
#define USB_PHYCR5_1    (USB_BASE+0x611) /* RW */
#define USB_PHYCR5_2    (USB_BASE+0x612) /* RW */
#define USB_PHYCR5_3    (USB_BASE+0x613) /* RW */

#define USB_PHYIR1_0    (USB_BASE+0x614) /* RW */
#define USB_PHYIR1_1    (USB_BASE+0x615) /* RW */
#define USB_PHYIR1_2    (USB_BASE+0x616) /* RW */
#define USB_PHYIR1_3    (USB_BASE+0x617) /* RW */

#define USB_PHYIR2_0    (USB_BASE+0x618) /* RW */
#define USB_PHYIR2_1    (USB_BASE+0x619) /* RW */
#define USB_PHYIR2_2    (USB_BASE+0x61A) /* RW */
#define USB_PHYIR2_3    (USB_BASE+0x61B) /* RW */


/* USB_PHY ALL*/
#define USB_PHY_CLEAR_MASK     (0x00)

/* USB_PHYCR1_0 */
#define USB_PHYCR1_0_PLL_EN     (0x80)

/* USB_PHYCR1_1 */
#define USB_PHYCR1_1_PLL_CCP_SET    (0x30)
#define USB_PHYCR1_1_PLL_CCP_MASK    (0xF0)

/* USB_PHYCR1_2 */
#define USB_PHYCR1_2_PLL_VCOG_H    (0x08)
#define USB_PHYCR1_2_HS_RCVB     (0x40)

/* USB_PHYCR2_0 */
#define USB_PHYCR2_0_HS_SQB_MASK    (0x0F)
#define USB_PHYCR2_0_HS_SQD_MASK    (0xF0)
#define USB_PHYCR2_0_HS_SQD_SET    (0xA0)

/* USB_PHYCR2_2 */
#define USB_PHYCR2_2_FORCE_DATA_IN   (0x40)
#define USB_PHYCR2_2_FORCE_TX_VALID   (0x20)
#define USB_PHYCR2_2_HS_DISCP     (0x01)

/* USB_PHYCR2_3 */
#define USB_PHYCR2_3_HS_TERMC_MASK   (0x1F)
#define USB_PHYCR2_3_FORCE_DP_PULLDOWN  (0x20)
#define USB_PHYCR2_3_FORCE_DM_PULLDOWN  (0x40)
#define USB_PHYCR2_3_FORCE_DP_DM_PULLDOWN (0x60)
#define USB_PHYCR2_3_FORCE_DRV_VBUS   (0x80)
#define USB_PHYCR2_3_HS_TERMC     (0x08)
#define USB_PHYCR2_3_HS_TERMC2     (0x0B)
#define USB_PHYCR2_3_FORCE_SUSPENDM      (0x04)

/* USB_PHYCR3_0 */
#define USB_PHYCR3_0_IADJ_MASK    (0x07)
#define USB_PHYCR3_0_IADJ_MASK2    (0x04)
#define USB_PHYCR3_0_IADJ_RESISTER_SET      (0x06)
#define USB_PHYCR3_0_CLEAR_MASK    (0x00)

/* USB_PHYCR3_2 */
#define USB_PHYCR3_2_TEST_CTRL_MASK   (0x0F)
#define USB_PHYCR3_2_TEST_CTRL1_SET   (0x02)
#define USB_PHYCR3_2_TEST_CTRL2_SET   (0x04)
#define USB_PHYCR3_2_CLK_MODE     (0x80)

/* USB_PHYCR4_1 */
#define USB_PHYCR4_1_BGR_BGR_EN    (0x01)
#define USB_PHYCR4_1_BGR_CLK_EN    (0x02)
#define USB_PHYCR4_1_BGR_I_SRC_EN    (0x04)
#define USB_PHYCR4_1_BGR_CHIP_EN    (0x08)
#define USB_PHYCR4_1_BGR_SELPH    (0x10)
#define USB_PHYCR4_1_BGR_DIV_L    (0x40)
#define USB_PHYCR4_1_FORCE_BGR_ON   (0x4F)

/* USB_PHYCR5_0 */
#define USB_PHYCR5_0_VBUSCMP_EN    (0x80)
#define USB_PHYCR5_0_CDR_FILT     (0x02)

/* USB_PHYCR5_2 */
#define USB_PHYCR5_2_FORCE_OP_MODE   (0x01)
#define USB_PHYCR5_2_FORCE_TERM_SELECT  (0x02)
#define USB_PHYCR5_2_FORCE_SUSPENDM   (0x04)
#define USB_PHYCR5_2_FORCE_XCVR_SELECT  (0x08)
#define USB_PHYCR5_2_FORCE_DP_HIGH   (0x0B)
#define USB_PHYCR5_2_FORCE_IDPULLUP   (0x80)
#define USB_PHYCR5_2_UTMI_MUXSEL    (0x40)

/* USB_PHYCR5_3 */
#define USB_PHYCR5_3_TERM_SELECT    (0x04)
#define USB_PHYCR5_3_XCVR_SELECT_MASK  (0x30)
#define USB_PHYCR5_3_XCVR_SELECT_L   (0x10)
#define USB_PHYCR5_3_DP_PULL_DOWN   (0x40)
#define USB_PHYCR5_3_DM_PULL_DOWN   (0x80)
#define USB_PHYCR5_3_DP_DM_PULL_DOWN  (0xC0)
#define USB_PHYCR5_3_OP_MODE     (0x01)
#define USB_PHYCR5_3_SUSPENDM   (0x08)

/* USB_PHYIR1_0 */
#define USB_PHYIR1_0_IDPULLUP     (0x01)
#define USB_PHYIR1_0_DRVVBUS     (0x02)
#define USB_PHYIR1_0_TX_VALID     (0x04)

/* USB_PHYIR1_3 */
#define USB_PHYIR1_3_LINESTATE_DP    (0x40)
#define USB_PHYIR1_3_LINESTATE_DM    (0x80)

/* USB_PHYIR2_3 */
#define USB_PHYIR2_3_FORCE_USB_CLKOFF    (0x20)
#define USB_PHYIR2_3_FORCE_AUX_EN    (0x80)


#endif // PHY


//USB IP V3
#if (defined(DRV_USB_PHY_COST_DOWN))
#define  USB_LINE_STATE  USB_PHYIR3_0
#endif



//USB IP V3
#elif (defined(DRV_USB_IP_V2))

#define OTG_INT_STAT    (USB_BASE+0x10)
#define OTG_INT_EN     (USB_BASE+0x14)
#define OTG_STATUS     (USB_BASE+0x18)
#define OTG_CTRL     (USB_BASE+0x1c)

#define USB_FM_PKT_NUML    (USB_BASE+0x20)
#define USB_FM_PKT_NUMH    (USB_BASE+0x24)
#define USB_FM_ERR_STAT    (USB_BASE+0x28)
#define USB_FM_CTL     (USB_BASE+0x2c)
#define USB_FM_PKT_CNTL    (USB_BASE+0x30)
#define USB_FM_PKT_CNTH    (USB_BASE+0x34)
#define USB_FM_TIMEOUT    (USB_BASE+0x38)
#define USB_FM_STATUS    (USB_BASE+0x3c)
#define USB_FM_ADDITNL_STAT   (USB_BASE+0x50)
#define USB_FM_ENDPT    (USB_BASE+0x68)
#define USB_FM_INT_MASK    (USB_BASE+0x6c)
#define USB_PHY_EXTRA    (USB_BASE+0x70)

#define USB_INT_STAT    (USB_BASE+0x80)
#define USB_INT_ENB     (USB_BASE+0x84)
#define USB_ERR_STAT    (USB_BASE+0x88)
#define USB_ERR_ENB     (USB_BASE+0x8c)
#define USB_STAT     (USB_BASE+0x90)
#define USB_CTL      (USB_BASE+0x94)
#define USB_ADDR     (USB_BASE+0x98)
#define USB_BDT_PAGE_01    (USB_BASE+0x9c)
#define USB_BDT_PAGE_02    (USB_BASE+0xb0)
#define USB_BDT_PAGE_03    (USB_BASE+0xb4)
#define USB_FRM_NUML    (USB_BASE+0xa0)
#define USB_FRM_NUMH    (USB_BASE+0xa4)
#define USB_TOKEN     (USB_BASE+0xa8)
#define USB_SOF_THLD    (USB_BASE+0xac)
#define USB_ENDPT_CTL_BASE   (USB_BASE+0xc0)
#define USB_ENDPT_CTL(n)   (USB_ENDPT_CTL_BASE+4*n)

#define USB_DMA_ENB     (USB_BASE+0x410)
#define USB_DMA_DIS     (USB_BASE+0x414)
#define USB_DMA_ADDR_CNTER_CLR  (USB_BASE+0x418)
#define USB_DMA_FM_SELECT   (USB_BASE+0x41c)
#define USB_SOFT_RST    (USB_BASE+0x420)
#define USB_PHY_CTL     (USB_BASE+0x450)

#define USB_FIFO_RX0_EVEN   (USB_BASE+0x200)
#define USB_FIFO_RX0_ODD   (USB_BASE+0x208)
#define USB_FIFO_TX0_EVEN   (USB_BASE+0x210)
#define USB_FIFO_TX0_ODD   (USB_BASE+0x218)
#define USB_FIFO_RX1    (USB_BASE+0x220)
#define USB_FIFO_TX1    (USB_BASE+0x260)
#define USB_FIFO_RX2    (USB_BASE+0x2a0)
#define USB_FIFO_TX2    (USB_BASE+0x2e0)
#define USB_FIFO_RX3    (USB_BASE+0x320)
#define USB_FIFO_TX3    (USB_BASE+0x328)


#define USB_BDT_RX0_EVEN   (USB_BASE+0x330)
#define USB_BDT_RX0_ODD    (USB_BASE+0x338)
#define USB_BDT_TX0_EVEN   (USB_BASE+0x340)
#define USB_BDT_TX0_ODD    (USB_BASE+0x348)
#define USB_BDT_RX1     (USB_BASE+0x350)
#define USB_BDT_TX1     (USB_BASE+0x358)
#define USB_BDT_RX2     (USB_BASE+0x360)
#define USB_BDT_TX2     (USB_BASE+0x368)
#define USB_BDT_RX3     (USB_BASE+0x370)
#define USB_BDT_TX3     (USB_BASE+0x378)

/* VUSB Endpoint control register masks */
/* Define the bits within the endpoint control register */
#define VUSB_ENDPT_HSHK_BIT   (0x01)
#define VUSB_ENDPT_STALL_BIT   (0x02)
#define VUSB_ENDPT_TX_EN_BIT  (0x04)
#define VUSB_ENDPT_RX_EN_BIT  (0x08)
#define VUSB_ENDPT_CTL_EP_CTL_DIS (0x10)
#define VUSB_ENDPT_CTL_RETRY_DIS (0x40)
#define VUSB_ENDPT_CTL_HOST_WO_HUB (0x80)

#define VUSB_ENDPT_DISABLE   (0x00)
#define VUSB_ENDPT_CONTROL   (VUSB_ENDPT_HSHK_BIT | VUSB_ENDPT_TX_EN_BIT | \
          VUSB_ENDPT_RX_EN_BIT | VUSB_ENDPT_CTL_RETRY_DIS)
#define VUSB_ENDPT_BULK_RX   (VUSB_ENDPT_HSHK_BIT | VUSB_ENDPT_RX_EN_BIT | \
          VUSB_ENDPT_CTL_EP_CTL_DIS | VUSB_ENDPT_CTL_RETRY_DIS)
#define VUSB_ENDPT_BULK_TX   (VUSB_ENDPT_HSHK_BIT | VUSB_ENDPT_TX_EN_BIT | \
          VUSB_ENDPT_CTL_EP_CTL_DIS | VUSB_ENDPT_CTL_RETRY_DIS)
#define VUSB_ENDPT_BULK_BIDIR  (VUSB_ENDPT_HSHK_BIT | VUSB_ENDPT_TX_EN_BIT | \
          VUSB_ENDPT_RX_EN_BIT | VUSB_ENDPT_CTL_EP_CTL_DIS | VUSB_ENDPT_CTL_RETRY_DIS)
#define VUSB_ENDPT_ISO_RX   (VUSB_ENDPT_RX_EN_BIT | VUSB_ENDPT_CTL_EP_CTL_DIS | \
          VUSB_ENDPT_CTL_RETRY_DIS)
#define VUSB_ENDPT_ISO_TX   (VUSB_ENDPT_TX_EN_BIT | VUSB_ENDPT_CTL_EP_CTL_DIS | \
          VUSB_ENDPT_CTL_RETRY_DIS)
#define VUSB_ENDPT_ISO_BIDIR  (VUSB_ENDPT_RX_EN_BIT | VUSB_ENDPT_TX_EN_BIT | \
          VUSB_ENDPT_CTL_EP_CTL_DIS | VUSB_ENDPT_CTL_RETRY_DIS)

/* VUSB Control register masks */
#define  VUSB_CTL_USB_EN   (0x01)
#define  VUSB_CTL_SOF_EN   (0x01)
#define  VUSB_CTL_ODD_RST   (0x02)
#define  VUSB_CTL_RESUME   (0x04)
#define  VUSB_CTL_HOST_MODE_EN  (0x08)
#define  VUSB_CTL_RESET    (0x10)
#define  VUSB_CTL_TOKEN_BUSY  (0x20)
#define  VUSB_CTL_TXD_SUSPEND  (0x20)
#define  VUSB_CTL_SINGLE_ENDED_0 (0x40)
#define  VUSB_CTL_JSTATE   (0x80)

/* VUSB Interrupt status register masks */
#define VUSB_INT_STAT_RESET   (0x01)
#define VUSB_INT_STAT_ERROR   (0x02)
#define VUSB_INT_STAT_SOF   (0x04)
#define VUSB_INT_STAT_TOKEN_DONE (0x08)
#define VUSB_INT_STAT_SLEEP   (0x10)
#define VUSB_INT_STAT_RESUME  (0x20)
#define VUSB_INT_STAT_ATTACH  (0x40)
#define VUSB_INT_STAT_STALL   (0x80)

/* VUSB Interrupt enable register masks*/
#define VUSB_INT_ENB_RESET   (0x01)
#define VUSB_INT_ENB_ERROR   (0x02)
#define VUSB_INT_ENB_SOF   (0x04)
#define VUSB_INT_ENB_TOKEN_DONE  (0x08)
#define VUSB_INT_ENB_SLEEP   (0x10)
#define VUSB_INT_ENB_RESUME   (0x20)
#define VUSB_INT_ENB_ATTACH   (0x40)
#define VUSB_INT_ENB_STALL   (0x80)

/* VUSB Fast mode error status register masks */
#define USB_FM_ERR_STA_OVR_FLW  (0x80)
#define VUSB_FM_ERR_STAT_TOKEN_DONE (0x40)
#define VUSB_FM_ERR_SUC_ERR   (0x04)
#define VUSB_FM_ERR_NAK_ERR   (0x02)
#define VUSB_FM_ERR_SHORT_ERR  (0x01)

/* VUSB Fast mode control register masks */
#define VUSB_FM_CTL_FMENB   (0x1)
#define VUSB_FM_CTL_SUCERREN  (0x8)
#define VUSB_FM_CTL_EP_RX_ODD_SHIFT  1
#define VUSB_FM_CTL_EP_TX_ODD_SHIFT  2
#define VUSB_FM_CTL_EP_TOG_BIT_SHIFT 6

/* VUSB Fast mode endpoint register masks*/
#define VUSB_FM_EP_TX    (0x10)
#define VUSB_FM_EP_TX_RES   (0x80)
#define VUSB_FM_EP_ENDPT_MASK  (0x0f)

/* VUSB FM DMA index */
#define VUSB_FM_DMA_RX1    0
#define VUSB_FM_DMA_TX1    1
#define VUSB_FM_DMA_RX2    2
#define VUSB_FM_DMA_TX2    3

/* VUSB EXTRA register masks*/
#define VUSB_PHY_RESUME_INT   (0x80)
#define VUSB_PHY_RESUME_INT_ENB  (0x04)
#define VUSB_PHY_SUSPEND   (0x02)

/* VUSB SOFT RST register masks*/
#define VUSB_SOFT_RST_EN   (0x01)

/* VUSB BDT masks */
#define VUSB_BDT_OWNS_BIT   (1 << 7)
#define VUSB_BDT_DATA01_BIT   (1 << 6)
#define VUSB_BDT_KEEP_BIT   (1 << 5)
#define VUSB_BDT_NINC_BIT   (1 << 4)
#define VUSB_BDT_DTS_BIT   (1 << 3)
#define VUSB_BDT_STALL_BIT   (1 << 2)
#define VUSB_BDT_BC_SHIFT   16
#define VUSB_BDT_DATA01_SHIFT  6
#define VUSB_BDT_BC_MASK   0x03ff0000

#define VUSB_BDT_PID_MASKS   (0x3C)
#define VUSB_BDT_NAK_PID   (0x28)
#define VUSB_BDT_ERROR_PID   (0x3c)
#define VUSB_BDT_STALL_PID   (0x38)
#define VUSB_BDT_BUS_TIMEOUT_PID (0x00)


/* OTG Interrupt Status Register Bit Masks */
#define  OTG_INT_STATUS_A_VBUS    (0x01)
#define  OTG_INT_STATUS_B_SESS_END   (0x04)
#define  OTG_INT_STATUS_SESS_VLD   (0x08)
#define  OTG_INT_STATUS_LINE_STATE_CHANGE (0x20)
#define  OTG_INT_STATUS_1_MSEC    (0x40)
#define  OTG_INT_STATUS_ID     (0x80)

/* OTG Interrupt Enable Register Bit Masks */
#define  OTG_INT_ENABLE_A_VBUS    (0x01)
#define  OTG_INT_ENABLE_B_SESS_END   (0x04)
#define  OTG_INT_ENABLE_SESS_VLD   (0x08)
#define  OTG_INT_ENABLE_1_MSEC    (0x40)
#define  OTG_INT_ENABLE_ID     (0x80)

/*OTG Status register masks*/
#define  OTG_STATUS_A_VBUS     (0x01)
#define  OTG_STATUS_B_SESS_END    (0x04)
#define  OTG_STATUS_SESS_VLD    (0x08)
#define  OTG_STATUS_LINE_STATE_CHANGE  (0x20)
#define  OTG_STATUS_1_MSEC     (0x40)
#define  OTG_STATUS_ID      (0x80)

/*OTG Control register masks*/
#define  OTG_CTL_VBUS_DSCHG     (0x01)
#define  OTG_CTL_VBUS_CHG     (0x02)
#define  OTG_CTL_OTG_ENABLE     (0x04)
#define  OTG_CTL_VBUS_ON     (0x08)
#define  OTG_CTL_DM_LOW      (0x10)
#define  OTG_CTL_DP_LOW      (0x20)
#define  OTG_CTL_DM_HIGH     (0x40)
#define  OTG_CTL_DP_HIGH     (0x80)


#define  OTG_CTL_RESET_DP_DM    (~(OTG_CTL_DM_LOW|OTG_CTL_DP_LOW|OTG_CTL_DM_HIGH|OTG_CTL_DP_HIGH))
#define  OTG_CTL_J_STATE     (OTG_CTL_DP_HIGH|OTG_CTL_DM_LOW)
#define  OTG_CTL_K_STATE     (OTG_CTL_DM_HIGH|OTG_CTL_DP_LOW)
#define  OTG_CTL_DP_DM_HIGH    (OTG_CTL_DP_HIGH|OTG_CTL_DM_HIGH)
#define  OTG_CTL_DP_DM_LOW    (OTG_CTL_DP_LOW|OTG_CTL_DM_LOW)


/* Token register masks */
#define  VUSB_TOKEN_ENDPT     (0x0f)
#define  VUSB_TOKEN_PID      (0xf0)
#define  VUSB_TOKEN_OUT      (0x10)
#define  VUSB_TOKEN_IN      (0x90)
#define  VUSB_TOKEN_SETUP     (0xd0)

#elif (defined(DRV_USB_IP_V1))

#define USB_FADDR  (USB_BASE+0x0)
#define USB_POWER  (USB_BASE+0x1)
#define USB_INTRIN1  (USB_BASE+0x2) /*status, read only*/
#define USB_INTRIN2  (USB_BASE+0x3)  /*status, read only*/
#define USB_INTROUT1 (USB_BASE+0x4)  /*status, read only*/
#define USB_INTROUT2 (USB_BASE+0x5)  /*status, read only*/
#define USB_INTRUSB  (USB_BASE+0x6)  /*status, read only*/
#define USB_INTRIN1E (USB_BASE+0x7)
#define USB_INTRIN2E (USB_BASE+0x8)
#define USB_INTROUT1E (USB_BASE+0x9)
#define USB_INTROUT2E (USB_BASE+0xa)
#define USB_INTRUSBE (USB_BASE+0xb)
#define USB_FRAME1  (USB_BASE+0xc) /*read only*/
#define USB_FRAME2  (USB_BASE+0xd) /*read only*/ /*Max Frame length = 11 bits*/
#define USB_INDEX  (USB_BASE+0xe) /*RW, 4bit available*/
#define USB_RSTCTRL  (USB_BASE+0xf)

#define USB_INMAXP  (USB_BASE+0x10) /*RW*/
#define USB_CSR0  (USB_BASE+0x11)
#define USB_INCSR1  (USB_BASE+0x11)
#define USB_INCSR2  (USB_BASE+0x12)
#define USB_OUTMAXP  (USB_BASE+0x13) /*RW*/
#define USB_OUTCSR1  (USB_BASE+0x14)
#define USB_OUTCSR2  (USB_BASE+0x15)
#define USB_COUNT0  (USB_BASE+0x16) /*RO, EP0 only*/
#define USB_OUTCOUNT1 (USB_BASE+0x16)
#define USB_OUTCOUNT2 (USB_BASE+0x17) /*RO,11bits*/

#define USB_EP0   (USB_BASE+0x20) /*4 byte as 1 queue*/

#define USB_ENABLE  (USB_BASE+0x230)
#define USB_SLEWCON (USB_BASE+0x240)

/*USB_FADDR*/
#define USB_FADDR_ADDRMASK  (0x7f)   /*RO*/
#define USB_FADDR_UPDATE  (0x80)   /*RW*/

/*USB_POWER*/
#define USB_POWER_SETSUSPEND (0x01)   /*RW*/
#define USB_POWER_SUSPENDSTAT (0x02)   /*RO*/ /*Read clear by the intr. register*/
#define USB_POWER_RESUME  (0x04)   /*RW*/
#define USB_POWER_RESET   (0x08)   /*RO*/
#define USB_POWER_SWRSTENAB  (0x10)   /*RW*/
#define USB_POWER_ISOUPDATE  (0x80)   /*RW*/

/*USB_RSTCTRL*/
#define USB_RSTCTRL_SWRST  (0x80)  /*RW*/

/*USB_INTRIN1, USB_INTRIN2 is not needed*/
#define USB_INTRIN1_EP0   (0x01)   /*RO*/
#define USB_INTRIN1_EP1   (0x02)   /*RO*/
#define USB_INTRIN1_EP2   (0x04)   /*RO*/
#define USB_INTRIN1_EP3   (0x08)   /*RO*/

/*USB_INTROUT1, USB_INTROUT2 is not needed*/
#define USB_INTROUT1_EP1  (0x02)   /*RO*/
#define USB_INTROUT1_EP2  (0x04)   /*RO*/

/*USB_INTRUSB*/
#define USB_INTRUSB_SUSPEND  (0x01)   /*RO*/
#define USB_INTRUSB_RESUME  (0x02)   /*RO*/
#define USB_INTRUSB_RESET  (0x04)   /*RO*/
#define USB_INTRUSB_SOF   (0x08)   /*RO*/

/*USB_INTRIN1E, USB_INTRIN2E is not needed*/
#define USB_INTRIN1E_EPEN  (0x01)   /*RW*/

/*USB_INTROUT1E, USB_INTROUT2E is not needed*/
#define USB_INTROUT1E_EPEN  (0x01)   /*RW*/

/*USB_INTRUSBE*/
#define USB_INTRUSBE_SUSPEND (0x01)   /*RW*/
#define USB_INTRUSBE_RESUME  (0x02)   /*RW*/
#define USB_INTRUSBE_RESET  (0x04)   /*RW*/
#define USB_INTRUSBE_SOF  (0x08)   /*RW*/

/*USB_INMAXP*/
#define USB_INMAXP_MASK   (0xff)   /*RW*/

/*USB_OUTMAXP*/
#define USB_OUTMAXP_MASK  (0xff)   /*RW*/

/*USB_CSR0*/
#define USB_CSR0_OUTPKTRDY    (0x01)   /*RO*/
#define USB_CSR0_INPKTRDY    (0x02)   /*RW,AC*/
#define USB_CSR0_SENTSTALL    (0x04)   /*RC*/
#define USB_CSR0_DATAEND    (0x08)   /*WO,AC*/
#define USB_CSR0_SETUPEND    (0x10)   /*RO*/
#define USB_CSR0_SENDSTALL    (0x20)   /*WO,AC*/
#define USB_CSR0_SERVICEDOUTPKTRDY  (0x40)   /*WO,AC*/
#define USB_CSR0_SERVICESETUPEND  (0x80)   /*WO,AC*/

/*USB_INCSR1*/
#define USB_INCSR1_INPKTRDY    (0x01)   /*RW*/
#define USB_INCSR1_FIFONOTEMPTY   (0x02)   /*RC*/
#define USB_INCSR1_UNDERRUN    (0x04)   /*RC*/
#define USB_INCSR1_FLUSHFIFO   (0x08)   /*WO*/
#define USB_INCSR1_SENDSTALL   (0x10)   /*RW*/
#define USB_INCSR1_SENTSTALL   (0x20)   /*RC*/
#define USB_INCSR1_CLRDATATOG   (0x40)   /*WO*/

/*USB_INCSR2*/
#define USB_INCSR2_FRCDATATOG   (0x08)   /*RW*/
#define USB_INCSR2_DMAENAB    (0x10)   /*RW*/
#define USB_INCSR2_MODE     (0x20)   /*RW*/
#define USB_INCSR2_ISO     (0x40)   /*RW*/
#define USB_INCSR2_AUTOSET    (0x80)   /*RW*/

/*USB_OUTCSR1*/
#define USB_OUTCSR1_OUTPKTRDY   (0x01)   /*RC*/
#define USB_OUTCSR1_FIFOFULL   (0x02)   /*R,AC*/
#define USB_OUTCSR1_OVERRUN    (0x04)   /*RC*/
#define USB_OUTCSR1_DATAERROR   (0x08)   /*RO*/
#define USB_OUTCSR1_FLUSHFIFO   (0x10)   /*WO,AC*/
#define USB_OUTCSR1_SENDSTALL   (0x20)   /*RW*/
#define USB_OUTCSR1_SENTSTALL   (0x40)   /*RC*/
#define USB_OUTCSR1_CLRDATATOG   (0x80)   /*WO*/

/*USB_OUTCSR2*/
#define USB_OUTCSR2_DMAMODE    (0x10)   /*RW*/
#define USB_OUTCSR2_DMAENAB    (0x20)   /*RW*/
#define USB_OUTCSR2_ISO     (0x40)   /*RW*/
#define USB_OUTCSR2_AUTOCLEAR   (0x80)   /*RW*/

/*USB_ENABLE*/
#define USB_ENABLE_EN     (0x1)
#define USB_ENABLE_DIS     (0x0)

/* USB_SLEWCON */
#define USB_SLEWCON_PUB     (0x01)

#endif

//======================USB PHY =============================//
#define DRV_USB_PHY_T14  // USB_FPGA_DVT : PHY version choosed by DE's setting

#if (defined(DRV_USB_PHY_U65))
/* USB phy register */
#define USB_U2PHYAC0_0    (USB_SIFSLV_BASE+0x800) /* RW */
#define USB_U2PHYAC0_1    (USB_SIFSLV_BASE+0x801) /* RW */
#define USB_U2PHYAC0_2    (USB_SIFSLV_BASE+0x802) /* RW */
#define USB_U2PHYAC0_3    (USB_SIFSLV_BASE+0x803) /* RW */

#define USB_U2PHYAC1_0    (USB_SIFSLV_BASE+0x804) /* RW */
#define USB_U2PHYAC1_1    (USB_SIFSLV_BASE+0x805) /* RW */
#define USB_U2PHYAC1_2    (USB_SIFSLV_BASE+0x806) /* RW */
#define USB_U2PHYAC1_3    (USB_SIFSLV_BASE+0x807) /* RW */

#define USB_U2PHYACR0_0    (USB_SIFSLV_BASE+0x810) /* RW */
#define USB_U2PHYACR0_1    (USB_SIFSLV_BASE+0x811) /* RW */
#define USB_U2PHYACR0_2    (USB_SIFSLV_BASE+0x812) /* RW */
#define USB_U2PHYACR0_3    (USB_SIFSLV_BASE+0x813) /* RW */

#define USB_U2PHYACR1_0    (USB_SIFSLV_BASE+0x814) /* RW */
#define USB_U2PHYACR1_1    (USB_SIFSLV_BASE+0x815) /* RW */
#define USB_U2PHYACR1_2    (USB_SIFSLV_BASE+0x816) /* RW */
#define USB_U2PHYACR1_3    (USB_SIFSLV_BASE+0x817) /* RW */

#define USB_U2PHYACR2_0    (USB_SIFSLV_BASE+0x818) /* RW */
#define USB_U2PHYACR2_1    (USB_SIFSLV_BASE+0x819) /* RW */
#define USB_U2PHYACR2_2    (USB_SIFSLV_BASE+0x81A) /* RW */
#define USB_U2PHYACR2_3    (USB_SIFSLV_BASE+0x81B) /* RW */

#define USB_U2PHYACR3_0    (USB_SIFSLV_BASE+0x81C) /* RW */
#define USB_U2PHYACR3_1    (USB_SIFSLV_BASE+0x81D) /* RW */
#define USB_U2PHYACR3_2    (USB_SIFSLV_BASE+0x81E) /* RW */
#define USB_U2PHYACR3_3    (USB_SIFSLV_BASE+0x81F) /* RW */

#define USB_U2PHYACR4_0    (USB_SIFSLV_BASE+0x820) /* RW */
#define USB_U2PHYACR4_1    (USB_SIFSLV_BASE+0x821) /* RW */
#define USB_U2PHYACR4_2    (USB_SIFSLV_BASE+0x822) /* RW */
#define USB_U2PHYACR4_3    (USB_SIFSLV_BASE+0x823) /* RW */

#define USB_U2PHYACHG_0    (USB_SIFSLV_BASE+0x824) /* RW */
#define USB_U2PHYACHG_1    (USB_SIFSLV_BASE+0x825) /* RW */
#define USB_U2PHYACHG_2    (USB_SIFSLV_BASE+0x826) /* RW */
#define USB_U2PHYACHG_3    (USB_SIFSLV_BASE+0x827) /* RW */

#define USB_U2PHYDCR0_0    (USB_SIFSLV_BASE+0x860) /* RW */
#define USB_U2PHYDCR0_1    (USB_SIFSLV_BASE+0x861) /* RW */
#define USB_U2PHYDCR0_2    (USB_SIFSLV_BASE+0x862) /* RW */
#define USB_U2PHYDCR0_3    (USB_SIFSLV_BASE+0x863) /* RW */

#define USB_U2PHYDCR1_0    (USB_SIFSLV_BASE+0x864) /* RW */
#define USB_U2PHYDCR1_1    (USB_SIFSLV_BASE+0x865) /* RW */
#define USB_U2PHYDCR1_2    (USB_SIFSLV_BASE+0x866) /* RW */
#define USB_U2PHYDCR1_3    (USB_SIFSLV_BASE+0x867) /* RW */

#define USB_U2PHYDTM0_0    (USB_SIFSLV_BASE+0x868) /* RW */
#define USB_U2PHYDTM0_1    (USB_SIFSLV_BASE+0x869) /* RW */
#define USB_U2PHYDTM0_2    (USB_SIFSLV_BASE+0x86A) /* RW */
#define USB_U2PHYDTM0_3    (USB_SIFSLV_BASE+0x86B) /* RW */

#define USB_U2PHYDTM1_0    (USB_SIFSLV_BASE+0x86C) /* RW */
#define USB_U2PHYDTM1_1    (USB_SIFSLV_BASE+0x86D) /* RW */
#define USB_U2PHYDTM1_2    (USB_SIFSLV_BASE+0x86E) /* RW */
#define USB_U2PHYDTM1_3    (USB_SIFSLV_BASE+0x86F) /* RW */

#define USB_U2PHYDMON0_0   (USB_SIFSLV_BASE+0x870) /* RW */
#define USB_U2PHYDMON0_1   (USB_SIFSLV_BASE+0x871) /* RW */
#define USB_U2PHYDMON0_2   (USB_SIFSLV_BASE+0x872) /* RW */
#define USB_U2PHYDMON0_3   (USB_SIFSLV_BASE+0x873) /* RW */

#define USB_U1PHYCR0_0    (USB_SIFSLV_BASE+0x8C0) /* RW */
#define USB_U1PHYCR0_1    (USB_SIFSLV_BASE+0x8C1) /* RW */
#define USB_U1PHYCR0_2    (USB_SIFSLV_BASE+0x8C2) /* RW */
#define USB_U1PHYCR0_3    (USB_SIFSLV_BASE+0x8C3) /* RW */

#define USB_U1PHYCR1_0    (USB_SIFSLV_BASE+0x8C4) /* RW */
#define USB_U1PHYCR1_1    (USB_SIFSLV_BASE+0x8C5) /* RW */
#define USB_U1PHYCR1_2    (USB_SIFSLV_BASE+0x8C6) /* RW */
#define USB_U1PHYCR1_3    (USB_SIFSLV_BASE+0x8C7) /* RW */

#define USB_U1PHYCR2_0    (USB_SIFSLV_BASE+0x8C8) /* RW */
#define USB_U1PHYCR2_1    (USB_SIFSLV_BASE+0x8C9) /* RW */
#define USB_U1PHYCR2_2    (USB_SIFSLV_BASE+0x8CA) /* RW */
#define USB_U1PHYCR2_3    (USB_SIFSLV_BASE+0x8CB) /* RW */

#define USB_U1PHYACHG_0    (USB_SIFSLV_BASE+0x8CC) /* RW */
#define USB_U1PHYACHG_1    (USB_SIFSLV_BASE+0x8CD) /* RW */
#define USB_U1PHYACHG_2    (USB_SIFSLV_BASE+0x8CE) /* RW */
#define USB_U1PHYACHG_3    (USB_SIFSLV_BASE+0x8CF) /* RW */

#define USB_REGFPPC_0     (USB_SIFSLV_BASE+0x8E0) /* RW */
#define USB_REGFPPC_1     (USB_SIFSLV_BASE+0x8E1) /* RW */
#define USB_REGFPPC_2     (USB_SIFSLV_BASE+0x8E2) /* RW */
#define USB_REGFPPC_3     (USB_SIFSLV_BASE+0x8E3) /* RW */

#define USB_VERSIONC_0    (USB_SIFSLV_BASE+0x8F0) /* RW */
#define USB_VERSIONC_1    (USB_SIFSLV_BASE+0x8F1) /* RW */
#define USB_VERSIONC_2    (USB_SIFSLV_BASE+0x8F2) /* RW */
#define USB_VERSIONC_3    (USB_SIFSLV_BASE+0x8F3) /* RW */

#define USB_REGFCOM_0     (USB_SIFSLV_BASE+0x8FC) /* RW */
#define USB_REGFCOM_1     (USB_SIFSLV_BASE+0x8FD) /* RW */
#define USB_REGFCOM_2     (USB_SIFSLV_BASE+0x8FE) /* RW */
#define USB_REGFCOM_3     (USB_SIFSLV_BASE+0x8FF) /* RW */
//============================USB PHY variable========================//

#define U2PHYDCR0_0_RG_EARLY_HSTX_I (0x40)

#define U2PHYACR0_0_RG_LS_CROSS  (0x08)
#define U2PHYACR0_0_RG_FS_CROSS  (0x02)

#define U2PHYACR2_0_RG_SQTH  (0x03)
#define U2PHYACR2_0_RG_SQB    (0x40)
#define U2PHYACR2_0_RG_RCVB  (0x20)
#define U2PHYACR2_0_RG_DISCB  (0x10)

#define U2PHYACR2_3_RG_OTG_VBUSCMP_EN  (0x04)

#define U2PHYDCR1_2_RG_UART_EN       (0x40) //U2PHYDCR1_2
#define U2PHYDCR1_2_RG_USB_CLKEN      (0x20) //U2PHYDCR1_2

#define U2PHYAC0_0_RG_BGR_BGR_EN     (0x01) //U2PHYAC0_0
#define U2PHYAC0_0_RG_BGR_CHP_EN     (0x04) //U2PHYAC0_0
#define U2PHYAC0_0_RG_BGR_ISRC_EN    (0x02)  //U2PHYAC0_0

#define U2PHYDCR0_0_RG_HSTX_ANA_SER_EN  (0x80)

#define USB_U2PHYACR1_2_RG_DISCD    (0x02)

#define U2PHYAC0_2_RG_PLL_DIV      (0x0A) //U2PHYAC0_2

#define U2PHYACR1_1_RG_HSTX_SRCTRL    (0x04) //U2PHYACR1_1


#define U2PHYACR2_3_RG_DM_100K_EN     (0x02) //U2PHYACR2_3
#define U2PHYACR2_3_RG_DP_100K_EN     (0x01) //U2PHYACR2_3
#define U2PHYACR2_3_RG_OTG_VBUSCMP_EN     (0x04) //U2PHYACR2_3

#define U2PHYACR3_0_RG_OTG_VBUSTH         (0x40)
#define U2PHYACR3_2_RG_BC11_DISABLE    (0x04)
#define U2PHYACR3_3_RG_USBRESERVED    (0x20)

#define USB_U2PHYDMON0_3_VBUSVALID_MAC  (0x04)
#define USB_U2PHYDMON0_2_LINESTATE_DP   (0x40)
#define USB_U2PHYDMON0_2_LINESTATE_DM   (0x80)

#define U2PHYDTM_0_RG_SUSPENDM      (0x08) //U2PHYDTM0_0
#define U2PHYDTM0_0_RG_TERMSEL      (0x04) //U2PHYDTM0_0
#define U2PHYDTM0_0_RG_OPMODE       (0x01) //U2PHYDTM0_0

#define U2PHYDTM0_1_UTMI_MUSEL      (0x80) //U2PHYDTM0_1

#define U2PHYDTM0_2_FORCE_SUSPENDM    (0x04) //U2PHYDTM0_2

#define U2PHYDTM0_3_FORCE_UART_EN      (0x04)//U2PHYDTM0_3

#define U1PHYCR0_1_RG_USB11_FSLS_ENBGRI (0x08) //U1PHYCR0_1
#define U1PHYCR1_0_RG_USB11_USBRESERVED (0x01)
#define U1PHYCR1_0_RG_USB11_USBRESERVED_PMU (0x80)

//UNIT IP LINE State (MT6251 (USB1.1) , MT6276(USB2.0))
#define  USB_LINE_STATE  USB_U2PHYDMON0_2

#elif (defined(DRV_USB_PHY_M60_V1)||defined(DRV_USB_PHY_M60_V2))
#define U2PHYAC0 (USB_SIFSLV_BASE+0x800) //USB2.0 PHYA Common Registers
#define U2PHYAC1 (USB_SIFSLV_BASE+0x804) //USB2.0 PHYA Common Registers
#define U2PHYAC2 (USB_SIFSLV_BASE+0x808) //USB2.0 PHYA Common Registers
#define U2PHYACR0 (USB_SIFSLV_BASE+0x810) //USB2.0 PHYA Control Registers
#define U2PHYACR1 (USB_SIFSLV_BASE+0x814) //USB2.0 PHYA Control Registers
#define U2PHYACR2 (USB_SIFSLV_BASE+0x818) //USB2.0 PHYA Control Registers
#define U2PHYACR3 (USB_SIFSLV_BASE+0x81C) //USB2.0 PHYA Control Registers
#define U2PHYACR4 (USB_SIFSLV_BASE+0x820) //USB2.0 PHYA Control Registers
#define U2PHYDCR0 (USB_SIFSLV_BASE+0x860) //USB2.0 PHYD Control Registers
#define U2PHYDCR1 (USB_SIFSLV_BASE+0x864) //USB2.0 PHYD Control Registers
#define U2PHYDTM0 (USB_SIFSLV_BASE+0x868) //USB2.0 PHYD TestMode Registers
#define U2PHYDTM1 (USB_SIFSLV_BASE+0x86C) //USB2.0 PHYD TestMode Registers
#define U2PHYDMON0 (USB_SIFSLV_BASE+0x870) //USB2.0 PHYD Monitor Registers
#define U2PHYDMON1 (USB_SIFSLV_BASE+0x874) //USB2.0 PHYD Monitor Registers
#define U2PHYDMON2 (USB_SIFSLV_BASE+0x878) //USB2.0 PHYD Monitor Registers
#define U1PHYCR0 (USB_SIFSLV_BASE+0x8C0) //USB1.1 PHY Control Registers
#define U1PHYCR1 (USB_SIFSLV_BASE+0x8C4) //USB1.1 PHY Control Registers
#define U1PHYCR2 (USB_SIFSLV_BASE+0x8C8) //USB1.1 PHY Control Registers
#define REGFPPC  (USB_SIFSLV_BASE+0x8E0) //RegFile Per-Page Common Registers
#define VERSIONC (USB_SIFSLV_BASE+0x8F0) //Version Code
#define REGFCOM  (USB_SIFSLV_BASE+0x8FC) //RegFile Common Registers

#define U2PHYDTM0_FORCE_UART_EN     (1<<26)
#define U2PHYDTM0_FORCE_SUSPENDM    (1<<18)
#define U2PHYDTM0_RG_SUSPENDM     (1<<3)
#define U2PHYDTM1_RG_UART_EN     (1<<16)
#define U2PHYAC0_RG_USB20_USBPLL_FBDIV_6_0_CLR (0x7F<<16) //[6:0]
#define U2PHYAC0_RG_USB20_USBPLL_FBDIV_6_0  (9<<16) //[6:0]
#define U2PHYAC0_RG_USB20_INTR_EN    (1<<14)
#define U2PHYACR2_RG_USB20_OTG_VBUSCMP_EN  (1<<27)
#define U2PHYACR3_RG_USB20_PHY_REV_7   (1<<7)
#define U2PHYDTM1_RG_VBUSVALID     (1<<5)

#define U2PHYDTM1_RG_SESSEND     (1<<4)
#define U2PHYDTM1_RG_BVALID      (1<<3)
#define U2PHYDTM1_RG_AVALID      (1<<2)
#define U2PHYDTM1_RG_IDDIG      (1<<1)
#define U2PHYDTM1_force_vbusvalid    (1<<13)
#define U2PHYDTM1_force_sessend     (1<<12)
#define U2PHYDTM1_force_bvalid     (1<<11)
#define U2PHYDTM1_force_avalid     (1<<10)
#define U2PHYDTM1_force_iddig     (1<<9)


#elif (defined(DRV_USB_PHY_U40)||defined(DRV_USB_PHY_U40_V2)||defined(DRV_USB_PHY_T55_V2))
#define USB_U2PHYAC0 (USB_SIFSLV_BASE+0x800)   //USB2.0 PHYA Common Registers
#define USB_U2PHYAC1 (USB_SIFSLV_BASE+0x804)   //USB2.0 PHYA Common Registers
#define USB_U2PHYAC2 (USB_SIFSLV_BASE+0x808)   //USB2.0 PHYA Common Registers
#define USB_U2PHYACR0 (USB_SIFSLV_BASE+0x810)   //USB2.0 PHYA Control Registers
#define USB_U2PHYACR1 (USB_SIFSLV_BASE+0x814)   //USB2.0 PHYA Control Registers
#define USB_U2PHYACR2 (USB_SIFSLV_BASE+0x818)   //USB2.0 PHYA Control Registers
#define USB_U2PHYACR3 (USB_SIFSLV_BASE+0x81C)   //USB2.0 PHYA Control Registers
#define USB_U2PHYACR4 (USB_SIFSLV_BASE+0x820)   //USB2.0 PHYA Control Registers
#define USB_U2PHYDCR0 (USB_SIFSLV_BASE+0x860)   //USB2.0 PHYD Control Registers
#define USB_U2PHYDCR1 (USB_SIFSLV_BASE+0x864)   //USB2.0 PHYD Control Registers
#define USB_U2PHYDTM0 (USB_SIFSLV_BASE+0x868)   //USB2.0 PHYD TestMode Registers
#define USB_U2PHYDTM1 (USB_SIFSLV_BASE+0x86C)   //USB2.0 PHYD TestMode Registers
#define USB_U2PHYDMON0 (USB_SIFSLV_BASE+0x870)   //USB2.0 PHYD Monitor Registers
#define USB_U2PHYDMON1 (USB_SIFSLV_BASE+0x874)   //USB2.0 PHYD Monitor Registers
#define USB_U2PHYDMON2 (USB_SIFSLV_BASE+0x878)   //USB2.0 PHYD Monitor Registers
#define USB_U1PHYCR0 (USB_SIFSLV_BASE+0x8C0)   //USB1.1 PHY Control Registers
#define USB_U1PHYCR1 (USB_SIFSLV_BASE+0x8C4)   //USB1.1 PHY Control Registers
#define USB_U1PHYCR2 (USB_SIFSLV_BASE+0x8C8)   //USB1.1 PHY Control Registers
#define USB_REGFPPC  (USB_SIFSLV_BASE+0x8E0)   //RegFile Per-Page Common Registers
#define USB_VERSIONC (USB_SIFSLV_BASE+0x8F0)   //Version Code
#define USB_REGFCOM  (USB_SIFSLV_BASE+0x8FC)   //RegFile Common Registers

//Rom Code Setup
#define U2PHYDTM0_FORCE_UART_EN    (1<<26) //BIT26
#define U2PHYDTM1_RG_UART_EN    (1<<16) //BIT16
#define U2PHYACR3_RG_USB20_PHY_REV_7  (1<<7) //BIT7
#define U2PHYAC0_RG_USB20_USBPLL_FBDIV  (0x09<<16) //BIT16~22 = 7¡¦b0001001
#define U2PHYDTM0_FORCE_SUSPENDM   (1<<18) //BIT18
#define U2PHYACR2_RG_USB20_OTG_VBUSCMP_EN (1<<27) //BIT27
#define U2PHYAC0_RG_USB20_INTR_EN   (1<<14)
#define U2PHYAC0_RG_USB_LVSH_EN    (1<<31)
#define U2PHYDTM1_RG_VBUSVALID    (1<<5)
#define U2PHYDTM1_RG_SESSEND    (1<<4)
#define U2PHYDTM1_RG_BVALID     (1<<3)
#define U2PHYDTM1_RG_AVALID     (1<<2)
#define U2PHYDTM1_RG_IDDIG     (1<<1)
#define U2PHYDTM1_force_vbusvalid   (1<<13)
#define U2PHYDTM1_force_sessend    (1<<12)
#define U2PHYDTM1_force_bvalid    (1<<11)
#define U2PHYDTM1_force_avalid    (1<<10)
#define U2PHYDTM1_force_iddig    (1<<9)
#define U2PHYACR4_rg_usb20_gpio_ctl    (1<<9)
#define U2PHYACR4_usb20_gpio_mode    (1<<8)

//ROM CODE POWER OFF
#define U2PHYDTM0_RG_SUSPENDM    (1<<3) //BIT3
//U2PHYDTM0_FORCE_SUSPENDM            //BIT18
#elif defined(DRV_USB_PHY_T55)
#define USB_U1PHYCR0      (USB_SIFSLV_BASE+0x8C0)   //USB1.1 PHY Control Registers
#define USB_U1PHYCR1      (USB_SIFSLV_BASE+0x8C4)   //USB1.1 PHY Control Registers
#define USB_U1PHYCR2      (USB_SIFSLV_BASE+0x8C8)   //USB1.1 PHY Control Registers

#define U1PHYCR0_RG_USB_LVSH_EN                 (1<<8) //BIT8
#define U1PHYCR0_RG_USB11_FSLS_ENBGRI  (1<<11) //BIT11
#define U1PHYCR1_RG_USB11_PHY_REV_7   (1<<15) //BIT15

#elif defined(DRV_USB_PHY_T14)
#define USBPHYACR0 (USB_SIFSLV_BASE+0x800)   //USB2.0 PHYA Common Registers
#define USBPHYACR1 (USB_SIFSLV_BASE+0x804)   //USB2.0 PHYA Common Registers
#define USBPHYACR2 (USB_SIFSLV_BASE+0x808)   //USB2.0 PHYA Common Registers
#define USBPHYACR4 (USB_SIFSLV_BASE+0x810)   //USB2.0 PHYA Common Registers
#define USBPHYACR5 (USB_SIFSLV_BASE+0x814)   //USB2.0 PHYA Common Registers
#define USBPHYACR6 (USB_SIFSLV_BASE+0x818)   //USB2.0 PHYA Common Registers
#define U2PHYACR3 (USB_SIFSLV_BASE+0x81C)   //USB20 PHYA Control 3 Register
#define U2PHYACR4 (USB_SIFSLV_BASE+0x820)   //USB20 PHYA Control 4 Register
#define U2PHYAMON0 (USB_SIFSLV_BASE+0x824)   //USB20 PHYA Monitor 0 Register
#define U2PHYDCR0 (USB_SIFSLV_BASE+0x860)   //USB20 PHYD Control 0 Register
#define U2PHYDCR1 (USB_SIFSLV_BASE+0x864)   //USB20 PHYD Control 1 Register
#define U2PHYDTM0 (USB_SIFSLV_BASE+0x868)   //USB20 PHYD Control UTMI 0 Register
#define U2PHYDTM1 (USB_SIFSLV_BASE+0x86C)   //USB20 PHYD Control UTMI 1 Register
#define U2PHYDMON0 (USB_SIFSLV_BASE+0x870)   //USB20 PHYD Monitor 0 Register
#define U2PHYDMON1 (USB_SIFSLV_BASE+0x874)   //USB20 PHYD Monitor 1 Register
#define U2PHYDMON2 (USB_SIFSLV_BASE+0x878)   //USB20 PHYD Monitor 2 Register
#define U2PHYDMON3 (USB_SIFSLV_BASE+0x87C)   //USB20 PHYD Monitor 3 Register
#define U2PHYCR3 (USB_SIFSLV_BASE+0x880)   //USB20 sifslv Control Register
#define REGFCOM     (USB_SIFSLV_BASE+0x8FC)   //USB Common Register
#define FMCR0     (USB_SIFSLV_BASE+0xF00)   //Frequency Meter Control 0 Registers
#define FMCR1     (USB_SIFSLV_BASE+0xF04)   //Frequency Meter Control 1 Registers
#define FMCR2     (USB_SIFSLV_BASE+0xF08)   //Frequency Meter Control 2 Registers
#define FMMONR0     (USB_SIFSLV_BASE+0xF0C)   //Frequency Meter Monitor 0 Registers
#define FMMONR1     (USB_SIFSLV_BASE+0xF10)   //Frequency Meter Monitor 1 Registers

#define U2PHYDTM0_FORCE_UART_EN         (1 << 26)
#define U2PHYDTM1_RG_UART_EN            (1 << 16)
#define U2PHYACR4_RG_USB20_GPIO_CTL     (1 << 9) 
#define U2PHYACR4_USB20_GPIO_MODE       (1 << 8) 
#define USBPHYACR6_RG_USB20_BC11_SW_EN  (1 << 23)
#define USBPHYACR0_RG_USB20_INTR_EN     (1 << 5)
#define U2PHYDTM0_RG_SUSPENDM           (1 << 3)
#define U2PHYDTM0_FORCE_SUSPENDM        (1 << 18)
#define U2PHYDTM1_RG_VBUSVALID          (1 << 5)
#define U2PHYDTM1_RG_SESSEND            (1 << 4)
#define U2PHYDTM1_RG_BVALID             (1 << 3)
#define U2PHYDTM1_RG_AVALID             (1 << 2)
#define U2PHYDTM1_RG_IDDIG              (1 << 1)

#define U2PHYDTM1_FORCE_VBUSVALID       (1 << 13)
#define U2PHYDTM1_FORCE_SESSEND         (1 << 12)
#define U2PHYDTM1_FORCE_BVALID          (1 << 11)
#define U2PHYDTM1_FORCE_AVALID          (1 << 10)
#define U2PHYDTM1_FORCE_IDDIG           (1 << 9)

#else
    //#error please add USB PHY define in usb_hw.h!
#endif
//======================USB PHY =============================//
#endif  /* USB_HW_H */

/************************ USB register definition end line    *******************************/


#endif /* __USB_REG_DEFINITION_H__ */