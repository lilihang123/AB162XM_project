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

#ifndef __SFC_REG_DEFINITION_H__
#define __SFC_REG_DEFINITION_H__


#include <stdint.h>


/* *************************flash hardware definition start line**********************************
*/

/*flash register structure definition*/
typedef struct {
    __IO uint32_t RW_SF_MAC_CTL;                    /*!<  SFC control register address offset: 0x00 */
    __IO uint32_t RW_SF_DIRECT_CTL;                 /*!<  SFC control register address offset: 0x04 */
    __IO uint32_t RW_SF_MISC_CTL;                   /*!<  SFC control register address offset: 0x08 */
    __IO uint32_t RW_SF_MISC_CTL2;                  /*!<  SFC control register address offset: 0x0C */
    __IO uint32_t RW_SF_MAC_OUTL;                   /*!<  SFC control register address offset: 0x10 */
    __IO uint32_t RW_SF_MAC_INL;                    /*!<  SFC control register address offset: 0x14 */
    __IO uint32_t RW_SF_RESET_CTL;                  /*!<  SFC control register address offset: 0x18 */
    __IO uint32_t RW_SF_STA2_CTL;                   /*!<  SFC control register address offset: 0x1C */
    __IO uint32_t RW_SF_DLY_CTL1;                   /*!<  SFC control register address offset: 0x20*/
    __IO uint32_t RW_SF_DLY_CTL2;                   /*!<  SFC control register address offset: 0x24 */
    __IO uint32_t RW_SF_DLY_CTL3;                   /*!<  SFC control register address offset: 0x28 */
    __IO uint32_t RW_SF_DUMMY1;                     /*!<  SFC control register address offset: 0x2C */
    __IO uint32_t RW_SF_DLY_CTL4;                   /*!<  SFC control register address offset: 0x30 */
    __IO uint32_t RW_SF_DLY_CTL5;                   /*!<  SFC control register address offset: 0x34 */
    __IO uint32_t RW_SF_DLY_CTL6;                   /*!<  SFC control register address offset: 0x38 */
    __IO uint32_t RW_SF_DUMMY2;                     /*!<  SFC control register address offset: 0x3C */
    __IO uint32_t RW_SF_DIRECT_CTL2;                /*!<  SFC control register address offset: 0x40 */
    __IO uint32_t RW_SF_MISC_CTL3;                  /*!<  SFC control register address offset: 0x44 */
    __IO uint32_t RW_SF_STA3;                       /*!<  SFC control register address offset: 0x48 */
    __I  uint32_t __RESERVED_1[13];                 /*!<  SFC control register address offset: 0x4C~0x80 */
    __IO uint32_t RW_SF_CHECK_PERF;                 /*!<  SFC control register address offset: 0x80 */
    __I  uint32_t __RESERVED_2[44];                 /*!<  SFC control register address offset: 0x84~0x134 */
    __I  uint32_t RW_SF_PERF_MONITOR[3];            /*!<  SFC control register address offset: 0x134~0x13C */
} SFC_REGISTER_T;

typedef struct {
    __IO uint32_t RW_SF_GPRAM_DATA;                 /*!<  SFC control register address offset: 0x800 */
    __IO uint32_t RW_SF_GPRAM_DATA_OF_4;            /*!<  SFC control register address offset: 0x804 */
} SFC_GPRAM_REGISTER_T;


#define SFC_GPRAM_ADDR                              (SFC_BASE + 0x800)
#define SFC                                         ((SFC_REGISTER_T *) (SFC_BASE))
#define SFC_GPRAM                                   ((SFC_GPRAM_REGISTER_T *) (SFC_GPRAM_ADDR))
#define SFC_PERF_MONITOR_MCU_CH                     (0)
#define SFC_PERF_MONITOR_DMA_CH                     (1)
#define SFC_PERF_MONITOR_GMC_CH                     (2)

/* SFC generic offset definition */
#define SFC_GENERIC_1_BIT_OFFSET                    (1)
#define SFC_GENERIC_2_BIT_OFFSET                    (2)
#define SFC_GENERIC_4_BIT_OFFSET                    (4)
#define SFC_GENERIC_8_BIT_OFFSET                    (8)
#define SFC_GENERIC_10_BIT_OFFSET                   (10)
#define SFC_GENERIC_16_BIT_OFFSET                   (16)
#define SFC_GENERIC_24_BIT_OFFSET                   (24)
#define SFC_GENERIC_31_BIT_OFFSET                   (31)

/* SFC generic mask definition */
#define SFC_GENERIC_0x1_MASK                        (0x1)
#define SFC_GENERIC_0x0F_MASK                       (0x0F)
#define SFC_GENERIC_0xF0_MASK                       (0xF0)
#define SFC_GENERIC_0xFF_MASK                       (0xFF)
#define SFC_GENERIC_0xF000_MASK                     (0xF000)
#define SFC_GENERIC_0x00FF_MASK                     (0x00FF)
#define SFC_GENERIC_0x0FFFFFFF_MASK                 (0x0FFFFFFF)
#define SFC_GENERIC_0x000000FF_MASK                 (0x000000FF)
#define SFC_GENERIC_0x0000FF00_MASK                 (0x0000FF00)
#define SFC_GENERIC_0x00FF0000_MASK                 (0x00FF0000)
#define SFC_GENERIC_0xFF000000_MASK                 (0xFF000000)
#define SFC_GENERIC_0xFFFFFF00_MASK                 (0xFFFFFF00)
#ifdef AIR_CPU_IN_SECURITY_MODE
#define SFC_GENERIC_FLASH_BANK_MASK                 (0x08000000)
#else
#define SFC_GENERIC_FLASH_BANK_MASK                 (0x18000000)
#endif
#define SFC_GENERIC_DPD_SW_MASK                     (0x000F0F00)
#define SFC_GENERIC_DPD_SW_IO_MASK                  (0x0F0F0F0F)


#endif /* __SFC_REG_DEFINITION_H__ */