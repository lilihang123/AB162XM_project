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

#ifndef __CLOCK_REG_DEFINITION_H__
#define __CLOCK_REG_DEFINITION_H__


#include <stdint.h>


typedef struct {
    __IO uint32_t BUS_DCM_CON_0;        /* BUS_DCM_CON_0 @A21D0100 */
    __IO uint32_t BUS_DCM_CON_1;        /* BUS_DCM_CON_1 @A21D0104 */
    __IO uint32_t reserver1[2];         /* alignment for 0x110- 0x108*/
    __IO uint32_t CM4_DCM_CON_0;        /* CM4_DCM_CON_0 @A21D00110 */
    __IO uint32_t CM4_DCM_CON_1;        /* CM4_DCM_CON_1 @A21D00114 */
    __IO uint32_t reserver2[6];         /* alignment for 0x130-0x118*/
    __IO uint32_t SYS_FREE_DCM_CON;     /* SYS_FREE_DCM_CON @A21D130 */
    __IO uint32_t reserver3[3];         /* alignment for 0x140-0x134*/
    __IO uint32_t SFC_DCM_CON_0;        /* SFC_DCM_CON_0 @A21D0140 */
    __IO uint32_t SFC_DCM_CON_1;        /* SFC_DCM_CON_1 @A21D0144 */
    __IO uint32_t reserver4[10];        /* alignment for 0x170-0x148*/
    __IO uint32_t CLK_FREQ_SWCH;        /* CLK_FREQ_SWCH @A21D0170 */
    __IO uint32_t reserver5[99];        /* alignment for 0x300-0x174*/
    __I  uint32_t PDN_COND0;            /* PDN_COND0 @A21D0300 */
    __IO uint32_t reserver6[3];         /* alignment for 0x310-0x304*/
    __IO uint32_t PDN_SETD0;            /* PDN_SETD0 @A21D0310 */
    __IO uint32_t reserver7[3];         /* alignment for 0x320-0x314*/
    __IO uint32_t PDN_CLRD0;            /* PDN_CLRD0 @A21D0320 */
} CKSYS_BUS_CLK_REGISTER_T;

#define _CKSYS_BUS_CLK_BASE_            (CKSYS_BUS_CLK_BASE)
#define _CKSYS_BUS_CLK_BASE_ADDR_       (_CKSYS_BUS_CLK_BASE_ + 0x0100)
#define CKSYS_BUS_CLK ((CKSYS_BUS_CLK_REGISTER_T *)(_CKSYS_BUS_CLK_BASE_ADDR_))

typedef struct {
    __IO uint32_t CKSYS_TST_SEL_0;           /* CKSYS_TST_SEL_0 @A2020220 */
    __IO uint32_t CKSYS_TST_SEL_1;           /* CKSYS_TST_SEL_1 @A2020224 */
    __IO uint32_t reserver1[6];              /* alignment for 0x240- 0x228*/
    __IO uint32_t CKSYS_CLK_CFG_0;           /* CKSYS_CLK_CFG_0 @A2020240 */
    __IO uint32_t CKSYS_CLK_CFG_1;           /* CKSYS_CLK_CFG_1 @A2020244 */
    __IO uint32_t reserver2[2];              /* alignment for 0x250-0x248*/
    __IO uint32_t CKSYS_CLK_UPDATE_0;        /* CKSYS_CLK_UPDATE_0 @A2020250 */
    __IO uint32_t CKSYS_CLK_UPDATE_1;        /* CKSYS_CLK_UPDATE_0 @A2020254 */
    __IO uint32_t reserver3[2];              /* alignment for 0x260-0x258*/
    __I  uint32_t CKSYS_CLK_UPDATE_STATUS_0; /* CKSYS_CLK_UPDATE_STATUS_0 @A2020260 */
    __I  uint32_t CKSYS_CLK_UPDATE_STATUS_1; /* CKSYS_CLK_UPDATE_STATUS_1 @A2020264 */
    __IO uint32_t reserver4[2];              /* alignment for 0x270-0x268*/
    __IO uint32_t CKSYS_CLK_FORCE_ON_0;      /* CKSYS_CLK_FORCE_ON_0 @A2020270 */
    __IO uint32_t CKSYS_CLK_FORCE_ON_1;      /* CKSYS_CLK_FORCE_ON_1 @A2020274 */
    __IO uint32_t reserver5[2];              /* alignment for 0x280-0x278*/
    __IO uint32_t CKSYS_CLK_DIV_0;           /* CKSYS_CLK_DIV_0 @A2020280 */
    __IO uint32_t CKSYS_CLK_DIV_1;           /* CKSYS_CLK_DIV_1 @A2020284 */
    __IO uint32_t CKSYS_CLK_DIV_2;           /* CKSYS_CLK_DIV_2 @A2020288 */
    __IO uint32_t CKSYS_CLK_DIV_3;           /* CKSYS_CLK_DIV_3 @A202028C */
    __IO uint32_t CKSYS_CLK_DIV_4;           /* CKSYS_CLK_DIV_4 @A2020290 */
    __IO uint32_t CKSYS_CLK_DIV_5;           /* CKSYS_CLK_DIV_5 @A2020294 */
    __IO uint32_t reserver6[2];              /* alignment for 0x2A0-0x298*/
    __IO uint32_t CKSYS_XTAL_FREQ;           /* CKSYS_XTAL_FREQ @A20202A0 */
    __IO uint32_t CKSYS_REF_CLK_SEL;         /* CKSYS_REF_CLK_SEL @A20202A4 */
    __IO uint32_t reserver7[86];             /* alignment for 0x400-0x2A8*/
    __IO uint32_t PLL_ABIST_FQMTR_CON0;      /* PLL_ABIST_FQMTR_CON0 @A2020400 */
    __I  uint32_t PLL_ABIST_FQMTR_CON1;      /* PLL_ABIST_FQMTR_CON1 @A2020404 */
    __IO uint32_t PLL_ABIST_FQMTR_CON2;      /* PLL_ABIST_FQMTR_CON2 @A2020408 */
    __I  uint32_t PLL_ABIST_FQMTR_DATA;      /* PLL_ABIST_FQMTR_DATA @A202040C */
} CKSYS_REGISTER_T;

#define _CKSYS_BASE_ADDR_       (CKSYS_BASE + 0x220)
#define CKSYS ((CKSYS_REGISTER_T *)(_CKSYS_BASE_ADDR_))

typedef struct {
    __I uint32_t XO_PDN_COND0;        /* XO_PDN_COND0 @A203B00 */
    __IO uint32_t reserver1[3];       /* alignment for 0xB10- 0xB04*/
    __IO uint32_t XO_PDN_SETD0;       /* XO_PDN_SETD0 @A203B10 */
    __IO uint32_t reserver2[3];       /* alignment for 0xB20- 0xB14*/
    __IO uint32_t XO_PDN_CLRD0;       /* XO_PDN_CLRD0 @A203B20 */
    __IO uint32_t reserver3[55];      /* alignment for 0xC00- 0xB24*/
    __IO uint32_t XO_DCM_CON_0;       /* XO_DCM_CON_0 @A203C00 */
    __IO uint32_t XO_DCM_CON_1;       /* XO_DCM_CON_1 @A203C04 */
} CKSYS_XO_CLK_REGISTER_T;

#define _CKSYS_XO_CLK_BASE_  (CKSYS_XO_CLK_BASE+0xB00)
#define CKSYS_XO_CLK ((CKSYS_XO_CLK_REGISTER_T *)(_CKSYS_XO_CLK_BASE_))

/* CLK_SOURCE_SEL used offset and mask definitions */
#define CLK_SYS_SEL_OFFSET     (0)
#define CLK_SYS_SEL_MASK       (0xFF<<CLK_SYS_SEL_OFFSET)
#define CLK_SFC_SEL_OFFSET     (8)
#define CLK_SFC_SEL_MASK       (0xFF<<CLK_SFC_SEL_OFFSET)
#define CLK_CONN_SEL_OFFSET    (16)
#define CLK_CONN_SEL_MASK      (0xFF<<CLK_CONN_SEL_OFFSET)
#define CLK_SPIMST_SEL_OFFSET  (24)
#define CLK_SPIMST_SEL_MASK    (0xFF<<CLK_SPIMST_SEL_OFFSET)
#define CLK_XTALCTL_SEL_OFFSET (0)
#define CLK_XTALCTL_SEL_MASK   (0xFF<<CLK_XTALCTL_SEL_OFFSET)
#define CLK_SDIOMST_SEL_OFFSET (8)
#define CLK_SDIOMST_SEL_MASK   (0xFF<<CLK_SDIOMST_SEL_OFFSET)


#endif /* __CLOCK_REG_DEFINITION_H__ */