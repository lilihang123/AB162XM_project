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
#ifdef AIR_BTD_IC_PREMIUM_G1

#ifndef __RACE_CMD_AUDIO_H__
#define __RACE_CMD_AUDIO_H__

#include "race_cmd_feature.h"
#include "race_cmd.h"

#ifdef RACE_AUDIO_RACE_CMD_ENABLE

#if 1
// #define INFRA_MISC_CFG                             (0x422F0000)
// #define INFRA_CFG_AUDIO_SYS_TOP_PORT_EN            ((volatile uint32_t*)(INFRA_MISC_CFG + 0x0060))
// #define INFRA_CFG_AUDIO_SYS_TOP_PORT_RDY           ((volatile uint32_t*)(INFRA_MISC_CFG + 0x0064))

/****************************Audio top*******************************/
#define AFE_BASE                            (0xC0000000)

#define AUDIO_TOP_CON0              (AFE_BASE + 0x0000) //KH:OK
#define AUDIO_TOP_CON1              (AFE_BASE + 0x0004) //KH:OK
#define AUDIO_TOP_CON2              (AFE_BASE + 0x0008) //add by jilin
#define AFE_DAC_CON0                (AFE_BASE + 0x0010) //KH:OK
#define AFE_DAC_CON1                (AFE_BASE + 0x0014) //KH:OK
#define AFE_DAC_CON2                (AFE_BASE + 0x02e0) //KH:OK
#define AFE_DAC_MON                 (AFE_BASE + 0x02Ec)
#define AFUNC_AUD_CON4              (AFE_BASE + 0x0910)
#define AFUNC_AUD_CON4_2            (AFE_BASE + 0x0920)
#define AFUNC_AUD_CON4_3            (AFE_BASE + 0x0924)
#define AFE_GENERAL_REG0              (AFE_BASE + 0x0800)
#define AFE_GENERAL_REG1              (AFE_BASE + 0x0804)
#define AFE_GENERAL_REG2              (AFE_BASE + 0x0808)
#define AFE_GENERAL_REG3              (AFE_BASE + 0x080C)
#define AFE_CBIP_CFG0                 (AFE_BASE + 0x0840)
#define AFE_CBIP_MON0                 (AFE_BASE + 0x0844)
#define AFE_CBIP_SLV_MUX_MON0         (AFE_BASE + 0x0848)
#define AFE_CBIP_SLV_DECODER_MON0     (AFE_BASE + 0x084C)
#define AFE_BUS_CFG                   (AFE_BASE + 0x0240)
#define AFE_BUS_MON0                  (AFE_BASE + 0x0244)
#define AFE_BUS_MON1                  (AFE_BASE + 0x0248)
#define AFE_BUS_MON2                  (AFE_BASE + 0x024C)
#define TOP_DMIC_CK_SEL               (AFE_BASE + 0x0f48)
#define TOP_DMIC_DAT_SEL              (AFE_BASE + 0x0f4c)
#define AFE_AUDIO_BT_SYNC_CON0        (AFE_BASE + 0x0FD0)
#define AFE_AUDIO_BT_SYNC_MON0        (AFE_BASE + 0x0FD4)
#define AFE_AUDIO_BT_SYNC_MON1        (AFE_BASE + 0x0FD8)
#define AFE_AUDIO_BT_SYNC_MON2        (AFE_BASE + 0x0FDC)
#define AFE_AUDIO_BT_SYNC_MON3        (AFE_BASE + 0x0FE0)
#define AFE_AUDIO_BT_SYNC_MON4        (AFE_BASE + 0x0FE4)
#define AFE_AUDIO_BT_SYNC_1_CON0      (AFE_BASE + 0x0FE8)
#define AFE_AUDIO_BT_SYNC_1_MON0      (AFE_BASE + 0x0FEC)
#define AFE_AUDIO_BT_SYNC_1_MON1      (AFE_BASE + 0x0FF0)
#define AFE_AUDIO_BT_SYNC_1_MON3      (AFE_BASE + 0x0FF4)
#define AFE_AUDIO_BT_SYNC_1_MON4      (AFE_BASE + 0x0FF8)
#define AFE_UL1_WR_COUNTER            (AFE_BASE + 0x0FFC)
#define AFE_UL2_WR_COUNTER            (AFE_BASE + 0x1000)
#define AFE_MON_DEBUG0                (AFE_BASE + 0x0930)
#define AFE_ANC_PWR_THR_L             (AFE_BASE + 0x0960)
#define AFE_ANC_PWR_DET_L             (AFE_BASE + 0x0964)
#define AFE_ANC_PWR_THR_R             (AFE_BASE + 0x0968)
#define AFE_ANC_PWR_DET_R             (AFE_BASE + 0x096C)
#define AFE_PWR_DET_TO_MON_L          (AFE_BASE + 0x0970)
#define AFE_PWR_DET_TO_MON_R          (AFE_BASE + 0x0974)
#define AFE_DL_UP_PTR_SEL             (AFE_BASE + 0x0FA0)
#define AFE_DL1_UP_PTR_MON            (AFE_BASE + 0x0FA4)
#define AFE_DL2_UP_PTR_MON            (AFE_BASE + 0x0FA8)
#define AFE_DL3_UP_PTR_MON            (AFE_BASE + 0x0FC4)
#define AFE_DL_UP_LEVEL_MON           (AFE_BASE + 0x0FAC)
#define AFE_SRC_CONT_CON0             (AFE_BASE + 0x13f8)
#define AFE_I2S_SLV_ENGEN_CON0        (AFE_BASE + 0x1400)
#define AFE_I2S_SLV_ENGEN_CON1        (AFE_BASE + 0x1404)
#define AFE_I2S_SLV_ENGEN_CON2        (AFE_BASE + 0x1408)
#define AFE_I2S_SLV_ENGEN_CON3        (AFE_BASE + 0x140c)
#define AFE_I2S_SLV_ENGEN_CON4        (AFE_BASE + 0x1410)
#define AFE_DATE_CODE                 (AFE_BASE + 0x0250)
/************************************************************/


/*************************Register MemIF******************************/
#define AFE_MEMIF_MINLEN              (AFE_BASE + 0x03D0)
#define AFE_MEMIF_MAXLEN              (AFE_BASE + 0x03D4)
#define AFE_MEMIF_PBUF_SIZE           (AFE_BASE + 0x03D8)
#define AFE_MEMIF_HD_MODE             (AFE_BASE + 0x03F8)
#define AFE_MEMIF_HDALIGN             (AFE_BASE + 0x03FC)
#define AFE_DL1_BASE                  (AFE_BASE + 0x0040)
#define AFE_DL1_CUR                   (AFE_BASE + 0x0044)
#define AFE_DL1_END                   (AFE_BASE + 0x0048)
#define AFE_HD_ENGEN_ENABLE           (AFE_BASE + 0x0DD0)
#define AFE_DL2_BASE                  (AFE_BASE + 0x0050)
#define AFE_DL2_CUR                   (AFE_BASE + 0x0054)
#define AFE_DL2_END                   (AFE_BASE + 0x0058)
#define AFE_DL3_BASE                  (AFE_BASE + 0x0360)
#define AFE_DL3_CUR                   (AFE_BASE + 0x0364)
#define AFE_DL3_END                   (AFE_BASE + 0x0368)
#define AFE_AWB_BASE                  (AFE_BASE + 0x0070)
#define AFE_AWB_END                   (AFE_BASE + 0x0078)
#define AFE_AWB_CUR                   (AFE_BASE + 0x007C)
#define AFE_VUL_BASE                  (AFE_BASE + 0x0080)
#define AFE_VUL_END                   (AFE_BASE + 0x0088)
#define AFE_VUL_CUR                   (AFE_BASE + 0x008C)
#define AFE_MEMIF_MSB                 (AFE_BASE + 0x00CC)
#define AFE_MEMIF_MON0                (AFE_BASE + 0x00d0)
#define AFE_MEMIF_MON1                (AFE_BASE + 0x00d4)
#define AFE_MEMIF_MON2                (AFE_BASE + 0x00d8)
#define AFE_MEMIF_MON3                (AFE_BASE + 0x00dc)
#define AFE_MEMIF_MON8                (AFE_BASE + 0x00f0)
#define AFE_MEMIF_MON9                (AFE_BASE + 0x00f4)
#define AFE_MEMIF_MON12               (AFE_BASE + 0x0d70)
#define AFE_MEMIF_MON13               (AFE_BASE + 0x0d74)
#define AFE_MEMIF_MON14               (AFE_BASE + 0x0d78)
#define AFE_MEMIF_MON15               (AFE_BASE + 0x0d7c)
#define AFE_MEMIF_MON18               (AFE_BASE + 0x0d88)
#define AFE_MEMIF_MON19               (AFE_BASE + 0x0d8c)
#define AFE_VUL2_BASE                 (AFE_BASE + 0x02F0)
#define AFE_VUL2_END                  (AFE_BASE + 0x02F8)
#define AFE_VUL2_CUR                  (AFE_BASE + 0x02FC)
#define AFE_AWB_CHK_SUM1              (AFE_BASE + 0x0210)
#define AFE_AWB_CHK_SUM2              (AFE_BASE + 0x0214)
#define AFE_AWB_CHK_SUM3              (AFE_BASE + 0x0218)
#define AFE_DL1_CHK_SUM1              (AFE_BASE + 0x0220)
#define AFE_DL1_CHK_SUM2              (AFE_BASE + 0x0224)
#define AFE_DL1_CHK_SUM3              (AFE_BASE + 0x0228)
#define AFE_DL1_CHK_SUM4              (AFE_BASE + 0x022c)
#define AFE_DL1_CHK_SUM5              (AFE_BASE + 0x0324)
#define AFE_DL1_CHK_SUM6              (AFE_BASE + 0x0238)
#define AFE_VUL_CHK_SUM1              (AFE_BASE + 0x0230)
#define AFE_MEMIF_RD_MON              (AFE_BASE + 0x0d64)
#define AFE_MEMIF_WR_MON              (AFE_BASE + 0x0d68)
#define AFE_MEMIF_CFG_MON             (AFE_BASE + 0x0f60)
#define AFE_DL1_RD_COUNTER            (AFE_BASE + 0x0fb0)
#define AFE_DL2_RD_COUNTER            (AFE_BASE + 0x0fb4)
#define AFE_DL3_RD_COUNTER            (AFE_BASE + 0x0fb8)
#define AFE_DL_COUNTER_RST            (AFE_BASE + 0x0fc0)
/************************************************************/
/*************************Register IRQ******************************/
#define AFE_IRQ_MCU_CON0              (AFE_BASE + 0x03A0)
#define AFE_IRQ_MCU_CON1              (AFE_BASE + 0x02E4)
#define AFE_IRQ_MCU_CON2              (AFE_BASE + 0x02E8)
#define AFE_IRQ_MCU_STATUS            (AFE_BASE + 0x03A4)
#define AFE_IRQ_MCU_EN                (AFE_BASE + 0x03B4)
#define AFE_IRQ_MCU_EN1               (AFE_BASE + 0x030C)
#define AFE_IRQ_MCU_CLR               (AFE_BASE + 0x03A8)
#define AFE_IRQ_MCU_CNT0              (AFE_BASE + 0x0300)
#define AFE_IRQ_MCU_CNT1              (AFE_BASE + 0x03AC)
#define AFE_IRQ_MCU_CNT2              (AFE_BASE + 0x03B0)
#define AFE_IRQ_MCU_CNT3              (AFE_BASE + 0x03E4)
#define AFE_IRQ_MCU_CNT4              (AFE_BASE + 0x03E8)
#define AFE_IRQ_MCU_CNT5              (AFE_BASE + 0x03BC)
#define AFE_IRQ_MCU_CNT6              (AFE_BASE + 0x0304)
#define AFE_IRQ_MCU_CNT7              (AFE_BASE + 0x03DC)
#define AFE_IRQ_MCU_CNT11             (AFE_BASE + 0x03EC)
#define AFE_IRQ_MCU_CNT12             (AFE_BASE + 0x040C)
#define AFE_IRQ0_MCU_CNT_MON          (AFE_BASE + 0x0310)
#define AFE_IRQ1_MCU_CNT_MON          (AFE_BASE + 0x03C0)
#define AFE_IRQ2_MCU_CNT_MON          (AFE_BASE + 0x03C4)
#define AFE_IRQ3_MCU_CNT_MON          (AFE_BASE + 0x0398)
#define AFE_IRQ4_MCU_CNT_MON          (AFE_BASE + 0x039C)
#define AFE_IRQ5_MCU_CNT_MON          (AFE_BASE + 0x03CC)
#define AFE_IRQ6_MCU_CNT_MON          (AFE_BASE + 0x0314)
#define AFE_IRQ7_MCU_CNT_MON          (AFE_BASE + 0x03E0)
#define AFE_IRQ11_MCU_CNT_MON         (AFE_BASE + 0x05E8)
#define AFE_IRQ12_MCU_CNT_MON         (AFE_BASE + 0x05EC)
#define AFE_IRQ_MCU_MON2              (AFE_BASE + 0x03B8)
/************************************************************/
/*************************Register I2S******************************/
#define AFE_I2S0_CON                  (AFE_BASE + 0x0860)
#define AFE_I2S_TOP_CON               (AFE_BASE + 0x0870)
#define AFE_I2S_CK_ENABLE_MON         (AFE_BASE + 0x0874)
#define AFE_I2S_BCOUNT_MON            (AFE_BASE + 0x0878)
/************************************************************/
/*************************Register Sidetone******************************/
#define AFE_SGEN_CON0               (AFE_BASE + 0x01f0) //KH:OK
#define AFE_SGEN_CON2               (AFE_BASE + 0x01dc) //KH:OK
/************************************************************/



/*************************Register Top******************************/
#define AFE_ADDA_UL_SRC_CON0          (AFE_BASE + 0x0114)
#define AFE_ADDA_UL_SRC_CON1          (AFE_BASE + 0x0118)
#define AFE_ADDA_UL_DL_CON0           (AFE_BASE + 0x0124)
#define AFE_ADDA_DEBUG_CON0           (AFE_BASE + 0x0130)
#define AFE_ADDA_DEBUG_MON0           (AFE_BASE + 0x0134)
#define AFE_ADDA_DEBUG_MON1           (AFE_BASE + 0x0138)
#define AFE_ADDA_DEBUG_MON2           (AFE_BASE + 0x013C)
#define AFE_ADDA_UL_SRC_RST           (AFE_BASE + 0x0120)
/************************************************************/


/*************************Register Interconn******************************/
#define AFE_CONN0                   (AFE_BASE + 0x0020) //KH:OK
#define AFE_CONN1                   (AFE_BASE + 0x0024) //KH:OK
#define AFE_CONN2                   (AFE_BASE + 0x0028) //KH:OK
#define AFE_CONN3                   (AFE_BASE + 0x002c) //KH:OK
#define AFE_CONN4                   (AFE_BASE + 0x0030) //KH:OK
#define AFE_CONN5                   (AFE_BASE + 0x005c) //KH:OK
#define AFE_CONN6                   (AFE_BASE + 0x00bc) //KH:OK
#define AFE_CONN7                   (AFE_BASE + 0x0420) //KH:OK
#define AFE_CONN8                   (AFE_BASE + 0x0438) //KH:OK
#define AFE_CONN9                   (AFE_BASE + 0x0440) //KH:OK
#define AFE_CONN10                  (AFE_BASE + 0x0444) //KH:OK
#define AFE_CONN11                  (AFE_BASE + 0x0448) //KH:OK
#define AFE_CONN12                  (AFE_BASE + 0x044c) //KH:OK
#define AFE_CONN13                  (AFE_BASE + 0x0450) //KH:OK
#define AFE_CONN14                  (AFE_BASE + 0x0454) //KH:OK
#define AFE_CONN15                  (AFE_BASE + 0x0458) //KH:OK
#define AFE_CONN16                  (AFE_BASE + 0x045c) //KH:OK
#define AFE_CONN17                  (AFE_BASE + 0x0460) //KH:OK
#define AFE_CONN18                  (AFE_BASE + 0x0464) //KH:OK
#define AFE_CONN19                  (AFE_BASE + 0x0468) //KH:OK
#define AFE_CONN20                  (AFE_BASE + 0x046c) //KH:OK
#define AFE_CONN21                  (AFE_BASE + 0x0470) //KH:OK
#define AFE_CONN22                  (AFE_BASE + 0x0474) //KH:OK
#define AFE_CONN23                  (AFE_BASE + 0x0478) //KH:OK
#define AFE_CONN_RS                 (AFE_BASE + 0x0494) //KH:OK
#define AFE_CONN_DI                 (AFE_BASE + 0x0498) //KH:OK
#define AFE_CONN_24BIT              (AFE_BASE + 0x006C)
#define AFE_CONN24                  (AFE_BASE + 0x1300) //MC:Add
#define AFE_CONN25                  (AFE_BASE + 0x1304) //MC:Add
#define AFE_CONN26                  (AFE_BASE + 0x1308) //MC:Add
#define AFE_CONN27                  (AFE_BASE + 0x130c) //MC:Add
#define AFE_CONN28                  (AFE_BASE + 0x1310) //MC:Add
#define AFE_CONN29                  (AFE_BASE + 0x1314) //MC:Add
#define AFE_CONN30                  (AFE_BASE + 0x1318) //MC:Add
#define AFE_CONN31                  (AFE_BASE + 0x131c) //MC:Add
#define AFE_CONN32                  (AFE_BASE + 0x1320) //MC:Add
#define AFE_CONN33                  (AFE_BASE + 0x1324) //MC:Add
#define AFE_CONN34                  (AFE_BASE + 0x1328) //MC:Add
#define AFE_CONN35                  (AFE_BASE + 0x132c) //MC:Add
#define AFE_CONN36                  (AFE_BASE + 0x1330) //MC:Add
#define AFE_CONN37                  (AFE_BASE + 0x1334) //MC:Add
#define AFE_CONN38                  (AFE_BASE + 0x1598) //KEN:add
#define AFE_CONN39                  (AFE_BASE + 0x159c) //KEN:add
#define AFE_CONN40                  (AFE_BASE + 0x15a0) //KEN:add
#define AFE_CONN41                  (AFE_BASE + 0x15a4) //KEN:add
#define AFE_CONN42                  (AFE_BASE + 0x15a8) //KEN:add
#define AFE_CONN43                  (AFE_BASE + 0x15ac) //KEN add
#define AFE_CONN0_1                 (AFE_BASE + 0x1340) //MC:Add
#define AFE_CONN1_1                 (AFE_BASE + 0x1344) //MC:Add
#define AFE_CONN2_1                 (AFE_BASE + 0x1348) //MC:Add
#define AFE_CONN3_1                 (AFE_BASE + 0x134c) //MC:Add
#define AFE_CONN4_1                 (AFE_BASE + 0x1350) //MC:Add
#define AFE_CONN5_1                 (AFE_BASE + 0x1354) //MC:Add
#define AFE_CONN6_1                 (AFE_BASE + 0x1358) //MC:Add
#define AFE_CONN7_1                 (AFE_BASE + 0x135c) //MC:Add
#define AFE_CONN8_1                 (AFE_BASE + 0x1360) //MC:Add
#define AFE_CONN9_1                 (AFE_BASE + 0x1364) //MC:Add
#define AFE_CONN10_1                (AFE_BASE + 0x1368) //MC:Add
#define AFE_CONN11_1                 (AFE_BASE + 0x136c) //MC:Add
#define AFE_CONN12_1                 (AFE_BASE + 0x1370) //MC:Add
#define AFE_CONN13_1                 (AFE_BASE + 0x1374) //MC:Add
#define AFE_CONN14_1                 (AFE_BASE + 0x1378) //MC:Add
#define AFE_CONN15_1                 (AFE_BASE + 0x137c) //MC:Add
#define AFE_CONN16_1                 (AFE_BASE + 0x1380) //MC:Add
#define AFE_CONN17_1                 (AFE_BASE + 0x1384) //MC:Add
#define AFE_CONN18_1                 (AFE_BASE + 0x1388) //MC:Add
#define AFE_CONN19_1                 (AFE_BASE + 0x138c) //MC:Add
#define AFE_CONN20_1                 (AFE_BASE + 0x1390) //MC:Add
#define AFE_CONN21_1                 (AFE_BASE + 0x1394) //MC:Add
#define AFE_CONN22_1                 (AFE_BASE + 0x1398) //MC:Add
#define AFE_CONN23_1                 (AFE_BASE + 0x139c) //MC:Add
#define AFE_CONN24_1                 (AFE_BASE + 0x13a0) //MC:Add
#define AFE_CONN25_1                 (AFE_BASE + 0x13a4) //MC:Add
#define AFE_CONN26_1                 (AFE_BASE + 0x13a8) //MC:Add
#define AFE_CONN27_1                 (AFE_BASE + 0x13ac) //MC:Add
#define AFE_CONN28_1                 (AFE_BASE + 0x13b0) //MC:Add
#define AFE_CONN29_1                 (AFE_BASE + 0x13b4) //MC:Add
#define AFE_CONN30_1                 (AFE_BASE + 0x13b8) //MC:Add
#define AFE_CONN31_1                 (AFE_BASE + 0x13bc) //MC:Add
#define AFE_CONN32_1                 (AFE_BASE + 0x13c0) //MC:Add
#define AFE_CONN33_1                 (AFE_BASE + 0x13c4) //MC:Add
#define AFE_CONN34_1                 (AFE_BASE + 0x13c8) //MC:Add
#define AFE_CONN35_1                 (AFE_BASE + 0x13cc) //MC:Add
#define AFE_CONN36_1                 (AFE_BASE + 0x13d0) //MC:Add
#define AFE_CONN37_1                 (AFE_BASE + 0x13d4) //MC:Add
#define AFE_CONN38_1                 (AFE_BASE + 0x15b0) //KEN add
#define AFE_CONN39_1                 (AFE_BASE + 0x15b4) //KEN add
#define AFE_CONN40_1                 (AFE_BASE + 0x15b8) //KEN add
#define AFE_CONN41_1                 (AFE_BASE + 0x15bc) //KEN add
#define AFE_CONN42_1                 (AFE_BASE + 0x15c0) //KEN add
#define AFE_CONN43_1                 (AFE_BASE + 0x15c4) //KEN add
#define AFE_CONN_RS_1               (AFE_BASE + 0x13d8) //MC:Add
#define AFE_CONN_DI_1               (AFE_BASE + 0x13dc) //MC:Add
#define AFE_CONN_24BIT_1            (AFE_BASE + 0x13e0) //MC:Add
#define AFE_CONN_MON0                 (AFE_BASE + 0x0280)
#define AFE_CONN_MON1                 (AFE_BASE + 0x0284)
#define AFE_CONN_MON2                 (AFE_BASE + 0x0288)
#define AFE_CONN_MON3                 (AFE_BASE + 0x028C)
#define AFE_CONN_CLR_0                (AFE_BASE + 0x1aa0)
#define AFE_CONN_CLR_1                (AFE_BASE + 0x1aa4)
/************************************************************/


/*************************Register iSRC******************************/
#define AFE_DEC_INT_CON0            (AFE_BASE + 0x1570) //MC:Add
#define AFE_DEC_INT_CON0_DN_SAMPLE_CH01_ENABLE_POS  (0)
#define AFE_DEC_INT_CON0_DN_SAMPLE_CH01_ENABLE_MASK (0x03<<AFE_DEC_INT_CON0_DN_SAMPLE_CH01_ENABLE_POS)
#define AFE_DEC_INT_CON0_DN_SAMPLE_CH23_ENABLE_POS  (2)
#define AFE_DEC_INT_CON0_DN_SAMPLE_CH23_ENABLE_MASK (0x03<<AFE_DEC_INT_CON0_DN_SAMPLE_CH23_ENABLE_POS)
#define AFE_DEC_INT_CON0_UP_SAMPLE_CH01_ENABLE_POS  (4)
#define AFE_DEC_INT_CON0_UP_SAMPLE_CH01_ENABLE_MASK (0x03<<AFE_DEC_INT_CON0_UP_SAMPLE_CH01_ENABLE_POS)
#define AFE_DEC_INT_CON0_UP_SAMPLE_CH23_ENABLE_POS  (6)
#define AFE_DEC_INT_CON0_UP_SAMPLE_CH23_ENABLE_MASK (0x03<<AFE_DEC_INT_CON0_UP_SAMPLE_CH01_ENABLE_POS)
#define AFE_DEC_INT_CON1            (AFE_BASE + 0x1574) //MC:Add
#define AFE_DEC_INT_CON1_DN_SAMPLE_CH01_OUTPUT_RATE_POS  (0)
#define AFE_DEC_INT_CON1_DN_SAMPLE_CH01_OUTPUT_RATE_MASK (0x0F<<AFE_DEC_INT_CON1_DN_SAMPLE_CH01_OUTPUT_RATE_POS)
#define AFE_DEC_INT_CON1_DN_SAMPLE_CH23_OUTPUT_RATE_POS  (4)
#define AFE_DEC_INT_CON1_DN_SAMPLE_CH23_OUTPUT_RATE_MASK (0x0F<<AFE_DEC_INT_CON1_DN_SAMPLE_CH23_OUTPUT_RATE_POS)
#define AFE_DEC_INT_CON1_UP_SAMPLE_CH01_OUTPUT_RATE_POS  (8)
#define AFE_DEC_INT_CON1_UP_SAMPLE_CH01_OUTPUT_RATE_MASK (0x0F<<AFE_DEC_INT_CON1_UP_SAMPLE_CH01_OUTPUT_RATE_POS)
#define AFE_DEC_INT_CON1_DN_SAMPLE_CH01_INPUT_RATE_POS   (12)
#define AFE_DEC_INT_CON1_DN_SAMPLE_CH01_INPUT_RATE_MASK  (0x0F<<AFE_DEC_INT_CON1_DN_SAMPLE_CH01_INPUT_RATE_POS)
#define AFE_DEC_INT_CON1_DN_SAMPLE_CH23_INPUT_RATE_POS   (16)
#define AFE_DEC_INT_CON1_DN_SAMPLE_CH23_INPUT_RATE_MASK  (0x0F<<AFE_DEC_INT_CON1_DN_SAMPLE_CH23_INPUT_RATE_POS)
#define AFE_DEC_INT_CON1_UP_SAMPLE_CH01_INPUT_RATE_POS   (20)
#define AFE_DEC_INT_CON1_UP_SAMPLE_CH01_INPUT_RATE_MASK  (0x0F<<AFE_DEC_INT_CON1_UP_SAMPLE_CH01_INPUT_RATE_POS)
#define AFE_DEC_INT_CON1_UP_SAMPLE_CH23_OUTPUT_RATE_POS  (24)
#define AFE_DEC_INT_CON1_UP_SAMPLE_CH23_OUTPUT_RATE_MASK  (0x0F<<AFE_DEC_INT_CON1_UP_SAMPLE_CH23_OUTPUT_RATE_POS)
#define AFE_DEC_INT_CON1_UP_SAMPLE_CH23_INPUT_RATE_POS   (28)
#define AFE_DEC_INT_CON1_UP_SAMPLE_CH23_INPUT_RATE_MASK  (0x0F<<AFE_DEC_INT_CON1_UP_SAMPLE_CH23_INPUT_RATE_POS)
#define AFE_DEC_INT_CON2            (AFE_BASE + 0x1578) //MC:Add
#define AFE_DEC_INT_CON2_DN_SAMPLE_CH01_RATIO_POS        (0)
#define AFE_DEC_INT_CON2_DN_SAMPLE_CH01_RATIO_MASK       (0x07<<AFE_DEC_INT_CON2_DN_SAMPLE_CH01_RATIO_POS)
#define AFE_DEC_INT_CON2_DN_SAMPLE_CH23_RATIO_POS        (4)
#define AFE_DEC_INT_CON2_DN_SAMPLE_CH23_RATIO_MASK       (0x07<<AFE_DEC_INT_CON2_DN_SAMPLE_CH23_RATIO_POS)
#define AFE_DEC_INT_CON2_UP_SAMPLE_CH01_RATIO_POS        (8)
#define AFE_DEC_INT_CON2_UP_SAMPLE_CH01_RATIO_MASK       (0x07<<AFE_DEC_INT_CON2_UP_SAMPLE_CH01_RATIO_POS)
#define AFE_DEC_INT_CON2_UP_SAMPLE_CH01_CIC_POS          (11)
#define AFE_DEC_INT_CON2_UP_SAMPLE_CH01_CIC_MASK         (0x01<<AFE_DEC_INT_CON2_UP_SAMPLE_CH01_CIC_POS)
#define AFE_DEC_INT_CON2_UP_SAMPLE_CH23_RATIO_POS        (12)
#define AFE_DEC_INT_CON2_UP_SAMPLE_CH23_RATIO_MASK       (0x07<<AFE_DEC_INT_CON2_UP_SAMPLE_CH23_RATIO_POS)
/************************************************************/


/*************************Register Gain******************************/
#define AFE_GAIN1_CON0                (AFE_BASE + 0x0410)
#define AFE_GAIN1_CON1                (AFE_BASE + 0x0414)
#define AFE_GAIN1_CON2                (AFE_BASE + 0x0418)
#define AFE_GAIN1_CON3                (AFE_BASE + 0x041C)
#define AFE_GAIN1_SET_CUR             (AFE_BASE + 0x0520)
#define AFE_GAIN1_CUR_MON             (AFE_BASE + 0x0524)
#define AFE_GAIN2_CON0                (AFE_BASE + 0x0428)
#define AFE_GAIN2_CON1                (AFE_BASE + 0x042C)
#define AFE_GAIN2_CON2                (AFE_BASE + 0x0430)
#define AFE_GAIN2_CON3                (AFE_BASE + 0x0434)
#define AFE_GAIN2_SET_CUR             (AFE_BASE + 0x0528)
#define AFE_GAIN2_CUR_MON             (AFE_BASE + 0x052C)
/************************************************************/
#endif

// Interconnection related
typedef enum {
    I00 = 0,
    I01 = 1,
    I02 = 2,
    I03 = 3,
    I04 = 4,
    I05 = 5,
    I06 = 6,
    I07 = 7,
    I08 = 8,
    I09 = 9,
    I10 = 10,
    I11 = 11,
    I12 = 12,
    I13 = 13,
    I14 = 14,
    I15 = 15,
    I16 = 16,
    I17 = 17,
    I18 = 18,
    I19 = 19,
    I20 = 20,
    I21 = 21,
    I22 = 22,
    I23 = 23,
    I24 = 24,
    I25 = 25,
    I26 = 26,
    I27 = 27,
    I28 = 28,
    I29 = 29,
    I30 = 30,
    I31 = 31,
    I32 = 32,
    I33 = 33,
    I34 = 34,
    I35 = 35,
    I36 = 36,
    I37 = 37,
    I38 = 38,
    I39 = 39,
    I40 = 40,  // KEN ADD
    I41 = 41,  // KEN ADD
    I42 = 42,  // KEN ADD
    I43 = 43,  // KEN ADD
    I44 = 44,  // KEN ADD
    I45 = 45,  // KEN ADD
    I46 = 46,  // KEN ADD
    I47 = 47,  // KEN ADD
    I48 = 48,  // KEN ADD
    I49 = 49,  // KEN ADD
    I50 = 50,  // KEN ADD
    I51 = 51,  // KEN ADD

    IN_MAX,
    IN_TINY_MAX = 14
} ITRCON_IN_T;

typedef enum {
    O00 = 0,
    O01 = 1,
    O02 = 2,
    O03 = 3,
    O04 = 4,
    O05 = 5,
    O06 = 6,
    O07 = 7,
    O08 = 8,
    O09 = 9,
    O10 = 10,
    O11 = 11,
    O12 = 12,
    O13 = 13,
    O14 = 14,
    O15 = 15,
    O16 = 16,
    O17 = 17,
    O18 = 18,
    O19 = 19,
    O20 = 20,
    O21 = 21,
    O22 = 22,
    O23 = 23,
    O24 = 24,
    O25 = 25,
    O26 = 26,
    O27 = 27,
    O28 = 28,
    O29 = 29,
    O30 = 30,
    O31 = 31,
    O32 = 32,
    O33 = 33,
    O34 = 34,
    O35 = 35,
    O36 = 36,
    O37 = 37,
    O38 = 38,
    O39 = 39,
    O40 = 40,  // KEN ADD
    O41 = 41,  // KEN ADD
    O42 = 42,  // KEN ADD
    O43 = 43,  // KEN ADD
    OUT_MAX,
    OUT_TINY_MAX = 14
} ITRCON_OUT_T;

typedef enum {
    HD_AUDIO_WLEN_16_BIT = 0,
    HD_AUDIO_WLEN_24_BIT = 1,  // 24_8 or 8_24 are the same for normal mode
    HD_AUDIO_WLEN_24_BIT_COMPACT_24_8 = 2,
    HD_AUDIO_WLEN_24_BIT_COMPACT_8_24 = 3,
    HD_AUDIO_WLEN_24_BIT_COMPACT_8_24_SIGNED = 4,
    HD_AUDIO_WLEN_NUM
} HD_AUDIO_MEM_TYPE;

typedef enum {
    AFE_8000HZ = 0,
    AFE_11025HZ = 1,
    AFE_12000HZ = 2,
    AFE_16000HZ = 3,
    AFE_22050HZ = 4,
    AFE_24000HZ = 5,
    AFE_32000HZ = 6,
    AFE_44100HZ = 7,
    AFE_48000HZ = 8,
    AFE_88200HZ = 9,
    AFE_96000HZ = 10,
    AFE_176400HZ = 11,
    AFE_192000HZ = 12,
    AFE_260000HZ = 13,
    AFE_48000HDHZ = 14,
    AFE_384000HZ = 15,
    AFE_130000HZ = 16,
} SAMPLINGRATE_T;

//**************************************i2S_module_t************************************************/
typedef enum {
    I2S_EIAJ = 0x0,
    I2S_I2S = 0x1,
    I2S_LJ = 0x2,  // Left-justified
    I2S_RJ = 0x3   // Right-justified
} I2SFMT_T;

typedef enum {
    I2S_0 = 0x0,
    I2S_1 = 0x1,
    I2S_2 = 0x2,
    I2S_3 = 0x3,
    I2S_4 = 0x4
} I2S_MODULE;

typedef enum {
    I2S_16BIT = 0x0,
    I2S_32BIT = 0x1
} I2SWLEN_T;

typedef struct{
    I2S_MODULE i2s_device;
    I2SFMT_T i2s_format;/**< for i2s_format */
    I2SWLEN_T word_length;/**< for word_length */
    SAMPLINGRATE_T sampling_rate;/**< for sampling_rate */
    bool is_rx_swap;/**< for is_rx_swap */
    bool is_tx_swap;/**< for is_tx_swap */
    bool is_internal_loopback;/**< for is_internal_loopback */
} I2S_CONFIG_T;
//**************************************************************************************/

typedef enum {
    UP_LINK_1 = 1,
    UP_LINK_2 = 2,
    UP_LINK_3 = 3,
    UP_LINK_4 = 4,
} UPLINK_PATH_T;

typedef enum {
    Dmic_4m = 0,
    Dmic_2m = 1,
    Dmic_1m = 2,
    Dmic_500k = 3
} Dmic_Input_Mode_T;

typedef enum {
    UL_VOICE_MODE_8k = 0,
    UL_VOICE_MODE_16k = 0,
    UL_VOICE_MODE_24k = 1,
    UL_VOICE_MODE_32k = 2,
    UL_VOICE_MODE_48k = 3,
    UL_VOICE_MODE_96k = 4,
    UL_VOICE_MODE_192k = 5,
    UL_VOICE_MODE_48kHD = 6,
    AMIC_6p5M_VOICE_MODE = 8,       // ul if = 260K
    DMIC_3p25M_VOICE_MODE = 9,      // ul if = 130K
    DMIC_1p625M_VOICE_MODE = 10,    // ul if = 65K
    DMIC_0p8125M_VOICE_MODE = 11,   // ul if = 32.5K
    DMIC_0p40625M_VOICE_MODE = 12,  // ul if = 16.5K
} UL_VOICE_MODE_T;

typedef enum {
    AFE_ADDA_UL_SAMPLERATE_16K   = 0,
    AFE_ADDA_UL_SAMPLERATE_24K   = 1,
    AFE_ADDA_UL_SAMPLERATE_32K   = 2,
    AFE_ADDA_UL_SAMPLERATE_48K   = 3,
} afe_samplerate_adda_ul_t;

typedef enum {
    RACE_AUDIO_COMMON_SLT_TEST   = 0,
} audio_common_sub_id_t;

#if 1
void hal_aduio_set_register_32bit(uint32_t addr, uint32_t val, uint32_t msk);
void hal_aduio_set_register_16bit(uint32_t addr, uint32_t val, uint32_t msk);


#define AFE_READ(addr)                  *((volatile uint32_t *)(addr))
#define AFE_WRITE(addr, val)            *((volatile uint32_t *)(addr)) = val
#define AFE_SET_REG(addr, val, msk)     hal_aduio_set_register_32bit(addr, val, msk)//AFE_WRITE((addr), ((AFE_READ(addr) & (~(msk))) | ((val) & (msk))))
#define AFE_GET_REG(addr)               AFE_READ(addr)

#define ANA_READ(addr)                  *((volatile uint16_t *)(addr))
#define ANA_WRITE(addr, val)            *((volatile uint16_t *)(addr)) = val
#define ANA_SET_REG(addr, val, msk)     hal_aduio_set_register_16bit(addr, val, msk)//ANA_WRITE((addr), ((ANA_READ(addr) & (~(msk))) | ((val) & (msk))))
#define ANA_GET_REG(addr)               ANA_READ(addr)

#define AFE_READ8(addr)                 *((volatile uint8_t *)(addr))
#define AFE_WRITE8(addr, val)           *((volatile uint8_t *)(addr)) = val
#endif



////////////////////////////////////////////////////////////////////////////////
// CONSTANT DEFINITIONS ////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#define RACE_AUDIO_HQA_LOOPBACK_OPEN        0x3113
#define RACE_AUDIO_HQA_LOOPBACK_CLOSE       0x3114
#define RACE_AUDIO_COMMON_CMD               0x3115



////////////////////////////////////////////////////////////////////////////////
// FUNCTION DECLARATIONS ///////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void *RACE_CmdHandler_audio(ptr_race_pkt_t pCmdMsg, uint16_t length, uint8_t channel_id);


#endif /* RACE_AUDIO_RACE_CMD_ENABLE */
#endif /* __RACE_CMD_AUDIO_H__ */
#endif



