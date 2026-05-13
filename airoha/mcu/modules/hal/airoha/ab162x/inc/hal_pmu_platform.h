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

#ifndef __HAL_PMU_PLATFORM_H__
#define __HAL_PMU_PLATFORM_H__
#ifdef HAL_PMU_MODULE_ENABLED

#define   UINT8        volatile unsigned char
#define   UINT8P       volatile unsigned char *
#define   UINT16       volatile unsigned short
#define   UINT16P      volatile unsigned short *
#define   UINT32       volatile unsigned int
#define   UINT32P      volatile unsigned int *


#define PMU_DIG_VRTC_BASE                                 (0x42108000)
#define PMU_DIG_RSV0                                      ((UINT32P)(PMU_DIG_VRTC_BASE+0x000))
#define PMU_DIG_RSV0__F_DIG_TOP_RSV0                      ((UINT32P)(PMU_DIG_VRTC_BASE+0x000))  //32

#define PMU_DIG_RSV1                                      ((UINT32P)(PMU_DIG_VRTC_BASE+0x004))
#define PMU_DIG_RSV1__F_DIG_TOP_RSV1                      ((UINT32P)(PMU_DIG_VRTC_BASE+0x004))  //32

#define PMU_DIG_STRUP_RG_CTRL                             ((UINT32P)(PMU_DIG_VRTC_BASE+0x008))
#define PMU_DIG_STRUP_RG_CTRL__F_STRUP_LATCH_DATA         ((UINT16P)(PMU_DIG_VRTC_BASE+0x008))  //16
#define PMU_DIG_STRUP_RG_CTRL__F_STRUP_SEL                ((UINT8P) (PMU_DIG_VRTC_BASE+0x00A))  //6
#define PMU_DIG_STRUP_RG_CTRL__F_STRUP_EN                 ((UINT8P) (PMU_DIG_VRTC_BASE+0x00B))  //1

#define PMU_DIG_STRUP_RDATA                               ((UINT32P)(PMU_DIG_VRTC_BASE+0x00C))
#define PMU_DIG_STRUP_RDATA__F_STRUP_LATCH_RDATA          ((UINT16P)(PMU_DIG_VRTC_BASE+0x00C))  //16

#define PMU_DIG_CTRL0                                     ((UINT32P)(PMU_DIG_VRTC_BASE+0x010))
#define PMU_DIG_CTRL0__F_SW_GO_SLP_CTL                    ((UINT8P) (PMU_DIG_VRTC_BASE+0x010))  //2
#define PMU_DIG_CTRL0__F_SW_GO_EXTSLP_CTL                 ((UINT8P) (PMU_DIG_VRTC_BASE+0x011))  //2
#define PMU_DIG_CTRL0__F_SW_LDO_VCORE_CTRL                ((UINT8P) (PMU_DIG_VRTC_BASE+0x012))  //2
#define PMU_DIG_CTRL0__F_SW_WDT_CTRL                      ((UINT8P) (PMU_DIG_VRTC_BASE+0x013))  //3

#define PMU_DIG_CTRL1                                     ((UINT32P)(PMU_DIG_VRTC_BASE+0x014))
#define PMU_DIG_CTRL1__F_SW_ST_EXTSLP_CTRL                ((UINT8P) (PMU_DIG_VRTC_BASE+0x014))  //2
#define PMU_DIG_CTRL1__F_SW_VBAT_POF                      ((UINT8P) (PMU_DIG_VRTC_BASE+0x015))  //2
#define PMU_DIG_CTRL1__F_CONN_RF_CTRL                     ((UINT8P) (PMU_DIG_VRTC_BASE+0x016))  //3
#define PMU_DIG_CTRL1__F_SW_USB_PWR_RSTB                  ((UINT8P) (PMU_DIG_VRTC_BASE+0x017))  //2

#define PMU_DIG_CTRL2                                     ((UINT32P)(PMU_DIG_VRTC_BASE+0x018))
#define PMU_DIG_CTRL2__F_GO_DEEPSLP                       ((UINT8P) (PMU_DIG_VRTC_BASE+0x018))  //1

#define PMU_DIG_CTRL3                                     ((UINT32P)(PMU_DIG_VRTC_BASE+0x01C))
#define PMU_DIG_CTRL3__F_VLDO18_TO_RET_OPT                ((UINT8P) (PMU_DIG_VRTC_BASE+0x01C))  //2
#define PMU_DIG_CTRL3__F_VCORE_H2L_CYCLE_OPT              ((UINT8P) (PMU_DIG_VRTC_BASE+0x01D))  //3
#define PMU_DIG_CTRL3__F_VRF_H2L_EXTSLP_CYCLE_OPT         ((UINT8P) (PMU_DIG_VRTC_BASE+0x01E))  //4
#define PMU_DIG_CTRL3__F_VRF_H2L_SLP_CYCLE_OPT            ((UINT8P) (PMU_DIG_VRTC_BASE+0x01F))  //2

#define PMU_DIG_CTRL4                                     ((UINT32P)(PMU_DIG_VRTC_BASE+0x020))
#define PMU_DIG_CTRL4__F_PSW_VRF_VRTC_CYCLE_OPT           ((UINT8P) (PMU_DIG_VRTC_BASE+0x020))  //2
#define PMU_DIG_CTRL4__F_VA14_CYCLE_OPT                   ((UINT8P) (PMU_DIG_VRTC_BASE+0x021))  //3
#define PMU_DIG_CTRL4__F_HPBG_CYCLE_OPT                   ((UINT8P) (PMU_DIG_VRTC_BASE+0x022))  //3
#define PMU_DIG_CTRL4__F_VLDO18_EXTSLP_ON_CYCLE_OPT       ((UINT8P) (PMU_DIG_VRTC_BASE+0x023))  //3

#define PMU_DIG_CTRL5                                     ((UINT32P)(PMU_DIG_VRTC_BASE+0x024))
#define PMU_DIG_CTRL5__F_VLDO18_DUMMY_LOAD_CYCLE_OPT      ((UINT8P) (PMU_DIG_VRTC_BASE+0x024))  //2
#define PMU_DIG_CTRL5__F_VCORE_ON_CYCLE_OPT               ((UINT8P) (PMU_DIG_VRTC_BASE+0x025))  //2
#define PMU_DIG_CTRL5__F_PSW_VCORE_VRTC_RDY_CYCLE_OPT     ((UINT8P) (PMU_DIG_VRTC_BASE+0x026))  //2
#define PMU_DIG_CTRL5__F_EXTSLP_VCORE_RDY_CYCLE_OPT       ((UINT8P) (PMU_DIG_VRTC_BASE+0x027))  //2

#define PMU_DIG_CTRL6                                     ((UINT32P)(PMU_DIG_VRTC_BASE+0x028))
#define PMU_DIG_CTRL6__F_VRF_L2H_EXTSLP_CYCLE_OPT         ((UINT8P) (PMU_DIG_VRTC_BASE+0x028))  //2
#define PMU_DIG_CTRL6__F_VRF_L2H_SLP_CYCLE_OPT            ((UINT8P) (PMU_DIG_VRTC_BASE+0x029))  //2
#define PMU_DIG_CTRL6__F_VCORE_L2H_CYCLE_OPT              ((UINT8P) (PMU_DIG_VRTC_BASE+0x02A))  //2
#define PMU_DIG_CTRL6__F_VLDO18_SLP_ON_CYCLE_OPT          ((UINT8P) (PMU_DIG_VRTC_BASE+0x02B))  //2

#define PMU_DIG_CTRL7                                     ((UINT32P)(PMU_DIG_VRTC_BASE+0x02C))
#define PMU_DIG_CTRL7__F_VRF_VSEL_SLP                     ((UINT8P) (PMU_DIG_VRTC_BASE+0x02C))  //8
#define PMU_DIG_CTRL7__F_VRF_VSEL_EXTSLP1                 ((UINT8P) (PMU_DIG_VRTC_BASE+0x02D))  //8
#define PMU_DIG_CTRL7__F_VRF_VSEL_EXTSLP2                 ((UINT8P) (PMU_DIG_VRTC_BASE+0x02E))  //8
#define PMU_DIG_CTRL7__F_VRF_VSEL_RX                      ((UINT8P) (PMU_DIG_VRTC_BASE+0x02F))  //8

#define PMU_DIG_CTRL8                                     ((UINT32P)(PMU_DIG_VRTC_BASE+0x030))
#define PMU_DIG_CTRL8__F_VRF_VSEL_TX                      ((UINT8P) (PMU_DIG_VRTC_BASE+0x030))  //8
#define PMU_DIG_CTRL8__F_SW_BUCK_EXTSLP_VCORE_DMY_LOAD_EN ((UINT8P) (PMU_DIG_VRTC_BASE+0x031))  //2
#define PMU_DIG_CTRL8__F_VRF_VSEL_NORM                    ((UINT8P) (PMU_DIG_VRTC_BASE+0x032))  //8
#define PMU_DIG_CTRL8__F_SW_VRF_VSEL                      ((UINT8P) (PMU_DIG_VRTC_BASE+0x033))  //1

#define PMU_DIG_CTRL9                                     ((UINT32P)(PMU_DIG_VRTC_BASE+0x034))
#define PMU_DIG_CTRL9__F_VCORE_VSEL_SLP                   ((UINT8P) (PMU_DIG_VRTC_BASE+0x034))  //7
#define PMU_DIG_CTRL9__F_VCORE_VSEL_EXTSLP_0P9V           ((UINT8P) (PMU_DIG_VRTC_BASE+0x035))  //7
#define PMU_DIG_CTRL9__F_EXTSLP_VCORE_STEP_DOWN_VOLT      ((UINT8P) (PMU_DIG_VRTC_BASE+0x036))  //2
#define PMU_DIG_CTRL9__F_EXTSLP_VCORE_STEP_CYCLE          ((UINT8P) (PMU_DIG_VRTC_BASE+0x037))  //2

#define PMU_DIG_CTRL10                                    ((UINT32P)(PMU_DIG_VRTC_BASE+0x038))
#define PMU_DIG_CTRL10__F_VLDO18_RET_VSEL_SLP             ((UINT8P) (PMU_DIG_VRTC_BASE+0x038))  //5
#define PMU_DIG_CTRL10__F_VLDO18_RET_VSEL_NORM            ((UINT8P) (PMU_DIG_VRTC_BASE+0x039))  //5
#define PMU_DIG_CTRL10__F_EXTSLP_VIO18_OFF                ((UINT8P) (PMU_DIG_VRTC_BASE+0x03A))  //1
#define PMU_DIG_CTRL10__F_SW_VLDO18_DUMMY_LOAD_EN         ((UINT8P) (PMU_DIG_VRTC_BASE+0x03B))  //2

#define PMU_DIG_CTRL11                                    ((UINT32P)(PMU_DIG_VRTC_BASE+0x03C))
#define PMU_DIG_CTRL11__F_EXT_PG_CTRL                     ((UINT8P) (PMU_DIG_VRTC_BASE+0x03D))  //2
#define PMU_DIG_CTRL11__F_DCXO_RSTB_CNT                   ((UINT8P) (PMU_DIG_VRTC_BASE+0x03E))  //4
#define PMU_DIG_CTRL11__F_DCXO_RSTB_SW_SEL                ((UINT8P) (PMU_DIG_VRTC_BASE+0x03F))  //1

#define PMU_DIG_CTRL12                                    ((UINT32P)(PMU_DIG_VRTC_BASE+0x040))
#define PMU_DIG_CTRL12__F_VCORE_VSEL_NORM                 ((UINT8P) (PMU_DIG_VRTC_BASE+0x040))  //8
#define PMU_DIG_CTRL12__F_SW_VCORE_VSEL                   ((UINT8P) (PMU_DIG_VRTC_BASE+0x041))  //1
#define PMU_DIG_CTRL12__F_SRAM_DELSEL_VOL                 ((UINT8P) (PMU_DIG_VRTC_BASE+0x042))  //1
#define PMU_DIG_CTRL12__F_SW_VCORE_DUMMY_LOAD_EN          ((UINT8P) (PMU_DIG_VRTC_BASE+0x043))  //2

#define PMU_DIG_INT_CTRL0                                 ((UINT32P)(PMU_DIG_VRTC_BASE+0x044))
#define PMU_DIG_INT_CTRL0__F_INT_DOMAIN_EN_VBAT           ((UINT8P) (PMU_DIG_VRTC_BASE+0x044))  //2
#define PMU_DIG_INT_CTRL0__F_INT_DEB_VBAT_POF             ((UINT8P) (PMU_DIG_VRTC_BASE+0x046))  //2

#define PMU_DIG_INT_CTRL1                                 ((UINT32P)(PMU_DIG_VRTC_BASE+0x048))
#define PMU_DIG_INT_CTRL1__F_INT_EN_VBAT_POF              ((UINT8P) (PMU_DIG_VRTC_BASE+0x048))  //2
#define PMU_DIG_INT_CTRL1__F_INT_MASK_VBAT_POF            ((UINT8P) (PMU_DIG_VRTC_BASE+0x04A))  //2

#define PMU_DIG_INT_STATUS                                ((UINT32P)(PMU_DIG_VRTC_BASE+0x04C))
#define PMU_DIG_INT_STATUS__F_INT_RAW_STATUS_VBAT_POF_R   ((UINT8P) (PMU_DIG_VRTC_BASE+0x04C))  //1
#define PMU_DIG_INT_STATUS__F_INT_RAW_STATUS_VBAT_POF_F   ((UINT8P) (PMU_DIG_VRTC_BASE+0x04D))  //1
#define PMU_DIG_INT_STATUS__F_INT_STATUS_VBAT_POF_R       ((UINT8P) (PMU_DIG_VRTC_BASE+0x04E))  //2
#define PMU_DIG_INT_STATUS__F_INT_STATUS_VBAT_POF_F       ((UINT8P) (PMU_DIG_VRTC_BASE+0x04F))  //2

#define PMU_DIG_DEBUG_MON                                 ((UINT32P)(PMU_DIG_VRTC_BASE+0x050))
#define PMU_DIG_DEBUG_MON__F_MON_GRP_SEL                  ((UINT8P) (PMU_DIG_VRTC_BASE+0x050))  //4

#define PMU_DIG_SRAM_CTRL                                 ((UINT32P)(PMU_DIG_VRTC_BASE+0x054))
#define PMU_DIG_SRAM_CTRL__F_SRAM_PG_EN_CTRL              ((UINT8P) (PMU_DIG_VRTC_BASE+0x054))  //2
#define PMU_DIG_SRAM_CTRL__F_SRAM_ON_DONE_CTRL            ((UINT8P) (PMU_DIG_VRTC_BASE+0x055))  //2
#define PMU_DIG_SRAM_CTRL__F_SRAM_OFF_DONE_CTRL           ((UINT8P) (PMU_DIG_VRTC_BASE+0x056))  //2
#define PMU_DIG_SRAM_CTRL__F_SRAM_ON_OFF_DONE_STATUS      ((UINT8P) (PMU_DIG_VRTC_BASE+0x057))  //2

#define PMU_DIG_MISC0                                     ((UINT32P)(PMU_DIG_VRTC_BASE+0x058))
#define PMU_DIG_MISC0__F_XOSC_FIX_IO_CFG                  ((UINT8P) (PMU_DIG_VRTC_BASE+0x058))  //1
#define PMU_DIG_MISC0__F_SLP_BG_LP                        ((UINT8P) (PMU_DIG_VRTC_BASE+0x059))  //1
#define PMU_DIG_MISC0__F_SW_IO_MUX_OUT_SEL                ((UINT8P) (PMU_DIG_VRTC_BASE+0x05A))  //8
#define PMU_DIG_MISC0__F_SW_IO_MUX_OUT                    ((UINT8P) (PMU_DIG_VRTC_BASE+0x05B))  //8

#define PMU_DIG_MISC1                                     ((UINT32P)(PMU_DIG_VRTC_BASE+0x05C))
#define PMU_DIG_MISC1__F_SW_ANA_SEL                       ((UINT16P)(PMU_DIG_VRTC_BASE+0x05C))  //10
#define PMU_DIG_MISC1__F_SW_ANA                           ((UINT16P)(PMU_DIG_VRTC_BASE+0x05E))  //10

#define PMU_ANA_CON0                                      ((UINT32P)(PMU_DIG_VRTC_BASE+0x060))
#define PMU_ANA_CON0__F_VREF_SEL_TM                       ((UINT8P) (PMU_DIG_VRTC_BASE+0x060))  //2
#define PMU_ANA_CON0__F_OSC32_TM                          ((UINT8P) (PMU_DIG_VRTC_BASE+0x061))  //1
#define PMU_ANA_CON0__F_VRF_RSV0                          ((UINT8P) (PMU_DIG_VRTC_BASE+0x062))  //5
#define PMU_ANA_CON0__F_VRF_RSV1                          ((UINT8P) (PMU_DIG_VRTC_BASE+0x063))  //5

#define PMU_ANA_CON1                                      ((UINT32P)(PMU_DIG_VRTC_BASE+0x064))
#define PMU_ANA_CON1__F_LDO_VCORE_CTRL                    ((UINT8P) (PMU_DIG_VRTC_BASE+0x064))  //2
#define PMU_ANA_CON1__F_LDO_VCORE_RVD                     ((UINT8P) (PMU_DIG_VRTC_BASE+0x065))  //8
#define PMU_ANA_CON1__F_PSW_VCORE_VRTC_RVD                ((UINT8P) (PMU_DIG_VRTC_BASE+0x066))  //8
#define PMU_ANA_CON1__F_PSW_VCORE_VRTC_CTRL               ((UINT8P) (PMU_DIG_VRTC_BASE+0x067))  //3

#define PMU_ANA_CON2                                      ((UINT32P)(PMU_DIG_VRTC_BASE+0x068))
#define PMU_ANA_CON2__F_PSW_VRF_VRTC_RVD                  ((UINT8P) (PMU_DIG_VRTC_BASE+0x068))  //8
#define PMU_ANA_CON2__F_PSW_VRF_VRTC_SD_EN                ((UINT8P) (PMU_DIG_VRTC_BASE+0x069))  //1
#define PMU_ANA_CON2__F_PSW_VRF_VRTC_SW_SEL               ((UINT8P) (PMU_DIG_VRTC_BASE+0x06A))  //2

#define PMU_ANA_CON2__F_VRF_CTRL0                         ((UINT8P) (PMU_DIG_VRTC_BASE+0x06B))  //4

#define PMU_ANA_CON3                                      ((UINT32P)(PMU_DIG_VRTC_BASE+0x06C))
#define PMU_ANA_CON3__F_VRF_LGSR                          ((UINT8P) (PMU_DIG_VRTC_BASE+0x06C))  //2
#define PMU_ANA_CON3__F_VRF_OCN_SEL                       ((UINT8P) (PMU_DIG_VRTC_BASE+0x06D))  //3
#define PMU_ANA_CON3__F_VRF_OCP_SEL                       ((UINT8P) (PMU_DIG_VRTC_BASE+0x06E))  //3
#define PMU_ANA_CON3__F_VRF_RPINJ                         ((UINT8P) (PMU_DIG_VRTC_BASE+0x06F))  //3

#define PMU_ANA_CON4                                      ((UINT32P)(PMU_DIG_VRTC_BASE+0x070))
#define PMU_ANA_CON4__F_VRF_TM_EN                         ((UINT8P) (PMU_DIG_VRTC_BASE+0x070))  //1
#define PMU_ANA_CON4__F_VRF_TM_SEL                        ((UINT8P) (PMU_DIG_VRTC_BASE+0x071))  //2
#define PMU_ANA_CON4__F_VRF_UGSR                          ((UINT8P) (PMU_DIG_VRTC_BASE+0x072))  //3
#define PMU_ANA_CON4__F_VRF_CTRL1                         ((UINT8P) (PMU_DIG_VRTC_BASE+0x073))  //4

#define PMU_ANA_CON5                                      ((UINT32P)(PMU_DIG_VRTC_BASE+0x074))
#define PMU_ANA_CON5__F_VRF_OCOS_TRIM                     ((UINT8P) (PMU_DIG_VRTC_BASE+0x074))  //4
#define PMU_ANA_CON5__F_VRF_ZXOS_TRIM                     ((UINT8P) (PMU_DIG_VRTC_BASE+0x075))  //4
#define PMU_ANA_CON5__F_VRF_IQDN_ITH                      ((UINT8P) (PMU_DIG_VRTC_BASE+0x076))  //3
#define PMU_ANA_CON5__F_VRF_VOCAL_LP_TRIM                 ((UINT8P) (PMU_DIG_VRTC_BASE+0x077))  //6

#define PMU_ANA_CON6                                      ((UINT32P)(PMU_DIG_VRTC_BASE+0x078))
#define PMU_ANA_CON6__F_VBAT_POF_CTRL                     ((UINT8P) (PMU_DIG_VRTC_BASE+0x078))  //2
#define PMU_ANA_CON6__F_VBAT_POF_VSENS_SEL                ((UINT8P) (PMU_DIG_VRTC_BASE+0x079))  //5

#define PMU_DIG_STATUS0                                   ((UINT32P)(PMU_DIG_VRTC_BASE+0x090))
#define PMU_DIG_STATUS0__F_ON_STATUS                      ((UINT16P)(PMU_DIG_VRTC_BASE+0x090))  //10
#define PMU_DIG_STATUS0__F_DEBUG_OUT                      ((UINT8P) (PMU_DIG_VRTC_BASE+0x092))  //8

#define PMU_DIG_STATUS1                                   ((UINT32P)(PMU_DIG_VRTC_BASE+0x094))
#define PMU_DIG_STATUS1__F_ANA_STATUS                     ((UINT16P)(PMU_DIG_VRTC_BASE+0x094))  //16

#define ATPG_RSV                                          ((UINT32P)(PMU_DIG_VRTC_BASE+0x0F0))
#define ATPG_RSV__F_ATPG_OB                               ((UINT8P) (PMU_DIG_VRTC_BASE+0x0F0))  //1

#define SRAM_UHDE_DELSEL_LV                               ((UINT32P)(0x4201001C))
#define XO_PDN_AO_SETD0                                   ((UINT32P)(0x42040B40))
#define RTC_DIG_RSV0                                      ((UINT32P)(0x42107040))
#define RTC_DIG_RSV1                                      ((UINT16P)(0x42107044))
#define IO_CFG_0_RTC_IN_EN                                ((UINT32P)(0x420C00E0))
#define IO_CFG_1_RTC_IN_EN                                ((UINT32P)(0x420D00F0))
#define SPM_CFG_DUMMY_REG_C                               ((UINT32P)(0x421300E0))
#define SPM_CFG_DUMMY_REG_D                               ((UINT32P)(0x421300E4))

#define PMU_GPIO_MODE_A                                   ((UINT32P)(0x420B0030))
#define PMU_GPIO_MODE_B                                   ((UINT32P)(0x420B0034))
#define PMU_GPIO_MODE_C                                   ((UINT32P)(0x420B0038))
#define PMU_GPIO_MODE_D                                   ((UINT32P)(0x420B003C))
#define PMU_GPIO_MODE_E                                   ((UINT32P)(0x420B0040))
#define PMU_GPIO_MODE_F                                   ((UINT32P)(0x420B0044))
#define PMU_GPIO_BACKUP                                   ((UINT32P)(0x420B0050))
#define PMU_PD_CFG0                                       ((UINT32P)(0x420C0050))
#define PMU_PU4P7K_CFG0                                   ((UINT32P)(0x420C0060))
#define PMU_PU_CFG0                                       ((UINT32P)(0x420C0070))
#define PMU_RTC_GPIO_MODE0                                ((UINT32P)(0x420C0100))
#define PMU_RTC_GPIO_MODE1                                ((UINT32P)(0x420C0110))

#endif /* HAL_PMU_MODULE_ENABLED */
#endif /* __HAL_PMU_PLATFORM_H__ */
