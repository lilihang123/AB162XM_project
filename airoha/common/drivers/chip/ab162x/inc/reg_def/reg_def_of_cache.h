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

#ifndef __CACHE_REG_DEFINITION_H__
#define __CACHE_REG_DEFINITION_H__


#include <stdint.h>


/* structure type to access the CACHE register*/
typedef union {
    struct {
        uint32_t EN                 :1;         /**< Enable bit */
        uint32_t SIZE               :5;         /**< Size of remapped region, 512*pow(2, x) */
        uint32_t __reserved_00      :3;
        uint32_t SRC_ADDR           :23;        /**< Source address of a remapped region */
    } b;
    uint32_t w;
} CACHE_NCREMAP_ENTRY_N_HIGH_Type;

typedef union {
    struct {
        uint32_t __reserved_00      :9;
        uint32_t DEST_ADDR          :23;        /**< Destination address of a remapped region */
    } b;
    uint32_t w;
} CACHE_NCREMAP_ENTRY_N_LOW_Type;

typedef struct {
    CACHE_NCREMAP_ENTRY_N_HIGH_Type high;
    CACHE_NCREMAP_ENTRY_N_LOW_Type low;
} CACHE_NCREMAP_ENTRY_Type;

typedef struct {
    __IO uint32_t CACHE_CON;                    /* offset: 0x00 */
    __IO uint32_t CACHE_OP;                     /* offset: 0x04 */
    __IO uint32_t CACHE_HCNT0L;                 /* offset: 0x08 */
    __IO uint32_t CACHE_HCNT0U;                 /* offset: 0x0C */
    __IO uint32_t CACHE_CCNT0L;                 /* offset: 0x10 */
    __IO uint32_t CACHE_CCNT0U;                 /* offset: 0x14 */
    __IO uint32_t CACHE_HCNT1L;                 /* offset: 0x18 */
    __IO uint32_t CACHE_HCNT1U;                 /* offset: 0x1C */
    __IO uint32_t CACHE_CCNT1L;                 /* offset: 0x20 */
    __IO uint32_t CACHE_CCNT1U;                 /* offset: 0x24 */
    __I  uint32_t __RESERVED_00;                /* padding: 4, offset: 0x28 */
    __IO uint32_t CACHE_REGION_EN;              /* offset: 0x2C */
    __I  uint32_t __RESERVED_01[1012];          /* padding: 4048, offset: [0x30, 0x1000) */
    __IO CACHE_NCREMAP_ENTRY_Type remap[4];     /* offset: [0x1000, 0x1020) */
    __I  uint32_t __RESERVED_02[15352];         /* padding: 61408, offset: [0x1020, 0x10000) */
    __IO uint32_t CACHE_ENTRY_N[16];            /* offset: [0x10000, 0x10040) */
    __IO uint32_t CACHE_END_ENTRY_N[16];        /* offset: [0x10040, 0x10080) */
} CACHE_REGISTER_T;

/* CACHE_CON register definitions
 */
#define CACHE_CON_MCEN_OFFSET                   (0)
#define CACHE_CON_MCEN_MASK                     (0x1UL<<CACHE_CON_MCEN_OFFSET)

#define CACHE_CON_CNTEN0_OFFSET                 (2)
#define CACHE_CON_CNTEN0_MASK                   (0x1UL<<CACHE_CON_CNTEN0_OFFSET)

#define CACHE_CON_CNTEN1_OFFSET                 (3)
#define CACHE_CON_CNTEN1_MASK                   (0x1UL<<CACHE_CON_CNTEN1_OFFSET)

#define CACHE_CON_MDRF_OFFSET                   (7)
#define CACHE_CON_MDRF_MASK                     (0x1UL<<CACHE_CON_MDRF_OFFSET)

#define CACHE_CON_CACHESIZE_OFFSET              (8)
#define CACHE_CON_CACHESIZE_MASK                (0x3UL<<CACHE_CON_CACHESIZE_OFFSET)

/* CACHE_OP register definitions
 */
#define CACHE_OP_EN_OFFSET                      (0)
#define CACHE_OP_EN_MASK                        (0x1UL<<CACHE_OP_EN_OFFSET)

#define CACHE_OP_OP_OFFSET                      (1)
#define CACHE_OP_OP_MASK                        (0xFUL<<CACHE_OP_OP_OFFSET)

#define CACHE_OP_TADDR_OFFSET                   (5)
#define CACHE_OP_TADDR_MASK                     (0x7FFFFFFUL<<CACHE_OP_TADDR_OFFSET)

/* CACHE_HCNT0L register definitions
 */
#define CACHE_HCNT0L_CHIT_CNT0_MASK             (0xFFFFFFFFUL<<0)

/* CACHE_HCNT0U register definitions
 */
#define CACHE_HCNT0U_CHIT_CNT0_MASK             (0xFFFFUL<<0)

/* CACHE_CCNT0L register definitions
 */
#define CACHE_CCNT0L_CACC_CNT0_MASK             (0xFFFFFFFFUL<<0)

/* CACHE_CCNT0U register definitions
 */
#define CACHE_CCNT0U_CACC_CNT0_MASK             (0xFFFFUL<<0)

/* CACHE_HCNT1L register definitions
 */
#define CACHE_HCNT1L_CHIT_CNT1_MASK             (0xFFFFFFFFUL<<0)

/* CACHE_HCNT1U register definitions
 */
#define CACHE_HCNT1U_CHIT_CNT1_MASK             (0xFFFFUL<<0)

/* CACHE_CCNT1L register definitions
 */
#define CACHE_CCNT1L_CACC_CNT1_MASK             (0xFFFFFFFFUL<<0)

/* CACHE_CCNT1U register definitions
 */
#define CACHE_CCNT1U_CACC_CNT1_MASK             (0xFFFFUL<<0)

/* CACHE_ENTRY_N register definitions
 */
#define CACHE_ENTRY_N_C_MASK                    (0x1UL<<8)
#define CACHE_ENTRY_BASEADDR_MASK               (0xFFFFFUL<<12)

/* CACHE_END_ENTRY_N register definitions
 */
#define CACHE_END_ENTRY_N_BASEADDR_MASK         (0xFFFFFUL<<12)

#define CACHE                                   ((CACHE_REGISTER_T *)CMSYS_L1CACHE_BASE)

#endif /* __CACHE_REG_DEFINITION_H__ */