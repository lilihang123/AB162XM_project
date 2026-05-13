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

#ifndef __IRRX_REG_DEFINITION_H__
#define __IRRX_REG_DEFINITION_H__


#include <stdint.h>

/*************************** IRRX register definition start line  *******************************
 */
 typedef struct {
    __IO uint32_t PDREG_IRH;                       /*IR COUNT HIGH REGISTER*/
    __IO uint32_t PDREG_IRM;                       /*IR COUNT MIDIUM REGISTER*/
    __IO uint32_t PDREG_IRL;                       /*IR COUNT LOW REGISTER*/
    __IO uint32_t PDREG_IRCFGH;                    /*IR CONFIGURATION HIGH REGISTER*/
    __IO uint32_t PDREG_IRCFGL;                    /*IR CONFIGURATION LOW REGISTER*/
    __IO uint32_t PDREG_IRTHD;                     /*IR THRESHOLD REGISTER*/
    __IO uint32_t PDREG_IRRCM_THD;                 /*RCMM THRESHOLD REGISTER*/
    __IO uint32_t PDREG_IRRCM_THD_0;               /*RCMM THRESHOLD REGISTER*/
    __IO uint32_t PDREG_IRCLR;                     /*IR CLEAR REGISTER*/
    __IO uint32_t PDREG_IREXP_EN;                  /*IR EXPECTATION REGISTER*/
    __IO uint32_t PDREG_EXP_BCNT;                  /*BITCNT EXPECTED VALUE REGISTER*/
    __IO uint32_t PDREG_ENEXP_IRM;                 /*IRM EXPECT VALUE BIT MASK REGISTER*/
    __IO uint32_t PDREG_ENEXP_IRL;                 /*IRM EXPECT VALUE BIT MASK REGISTER*/
    __IO uint32_t PDREG_EXP_IRL0;                  /*IRL EXPECT VALUE 0 REGISTER*/
    __IO uint32_t PDREG_EXP_IRL1;                  /*IRL EXPECT VALUE 1 REGISTER*/
    __IO uint32_t PDREG_EXP_IRL2;                  /*IRL EXPECT VALUE 2 REGISTER*/
    __IO uint32_t PDREG_EXP_IRL3;                  /*IRL EXPECT VALUE 3 REGISTER*/
    __IO uint32_t PDREG_EXP_IRL4;                  /*IRL EXPECT VALUE 4 REGISTER*/
    __IO uint32_t PDREG_EXP_IRL5;                  /*IRL EXPECT VALUE 5 REGISTER*/
    __IO uint32_t PDREG_EXP_IRL6;                  /*IRL EXPECT VALUE 6 REGISTER*/
    __IO uint32_t PDREG_EXP_IRL7;                  /*IRL EXPECT VALUE 7 REGISTER*/
    __IO uint32_t PDREG_EXP_IRL8;                  /*IRL EXPECT VALUE 8 REGISTER*/
    __IO uint32_t PDREG_EXP_IRL9;                  /*IRL EXPECT VALUE 9 REGISTER*/
    __IO uint32_t PDREG_EXP_IRM0;                  /*IRM EXPECT VALUE 0 REGISTE*/
    __IO uint32_t PDREG_EXP_IRM1;                  /*IRM EXPECT VALUE 1 REGISTE*/
    __IO uint32_t PDREG_EXP_IRM2;                  /*IRM EXPECT VALUE 2 REGISTE*/
    __IO uint32_t PDREG_EXP_IRM3;                  /*IRM EXPECT VALUE 3 REGISTE*/
    __IO uint32_t PDREG_EXP_IRM4;                  /*IRM EXPECT VALUE 4 REGISTE*/
    __IO uint32_t PDREG_EXP_IRM5;                  /*IRM EXPECT VALUE 5 REGISTE*/
    __IO uint32_t PDREG_EXP_IRM6;                  /*IRM EXPECT VALUE 6 REGISTE*/
    __IO uint32_t PDREG_EXP_IRM7;                  /*IRM EXPECT VALUE 7 REGISTE*/
    __IO uint32_t PDREG_EXP_IRM8;                  /*IRM EXPECT VALUE 8 REGISTE*/
    __IO uint32_t PDREG_EXP_IRM9;                  /*IRM EXPECT VALUE 9 REGISTE*/
    __IO uint32_t PDREG_IRINT_EN;                  /*IR INTERRUPT ENABLE REGISTER*/
    __IO uint32_t PDREG_IR_INTCLR;                 /*PDWNC INTERRUPT CLEAR REGISTER*/
    __IO uint32_t PDREG_WAKEEN;                    /*WAKE UP ENABLE REGISTER*/

    __IO uint32_t PDREG_WAKECLR;                   /*WAKE UP CLEAR REGISTER*/
    __IO uint32_t RESERVER;
    __IO uint32_t PDREG_SOFTEN;                    /*SOFTWARE MODE ENABLE REGISTER*/
    __IO uint32_t PDREG_SELECT;                    /*INTERRUPT AND WAKEUP SELECT REGISTE*/

    __IO uint32_t PDREG_CHK_DATA0;                 /*IR Pulse Width Length Value*/
    __IO uint32_t PDREG_CHK_DATA1;                 /*IR Pulse Width Length Value*/
    __IO uint32_t PDREG_CHK_DATA2;                 /*IR Pulse Width Length Value*/
    __IO uint32_t PDREG_CHK_DATA3;                 /*IR Pulse Width Length Value*/
    __IO uint32_t PDREG_CHK_DATA4;                 /*IR Pulse Width Length Value*/
    __IO uint32_t PDREG_CHK_DATA5;                 /*IR Pulse Width Length Value*/
    __IO uint32_t PDREG_CHK_DATA6;                 /*IR Pulse Width Length Value*/
    __IO uint32_t PDREG_CHK_DATA7;                 /*IR Pulse Width Length Value*/
    __IO uint32_t PDREG_CHK_DATA8;                 /*IR Pulse Width Length Value*/
    __IO uint32_t PDREG_CHK_DATA9;                 /*IR Pulse Width Length Value*/
    __IO uint32_t PDREG_CHK_DATA10;                /*IR Pulse Width Length Value*/
    __IO uint32_t PDREG_CHK_DATA11;                /*IR Pulse Width Length Value*/
    __IO uint32_t PDREG_CHK_DATA12;                /*IR Pulse Width Length Value*/
    __IO uint32_t PDREG_CHK_DATA13;                /*IR Pulse Width Length Value*/
    __IO uint32_t PDREG_CHK_DATA14;                /*IR Pulse Width Length Value*/
    __IO uint32_t PDREG_CHK_DATA15;                /*IR Pulse Width Length Value*/
    __IO uint32_t PDREG_CHK_DATA16;                /*IR Pulse Width Length Value*/
    __IO uint32_t PDREG_CHK_DATA17;                /*IR Pulse Width Length Value*/
    __IO uint32_t PDREG_CHK_DATA18;                /*IR Pulse Width Length Value*/
    __IO uint32_t PDREG_CHK_DATA19;                /*IR Pulse Width Length Value*/
    __IO uint32_t PDREG_CHK_DATA20;                /*IR Pulse Width Length Value*/
    __IO uint32_t PDREG_CHK_DATA21;                /*IR Pulse Width Length Value*/
    __IO uint32_t PDREG_CHK_DATA22;                /*IR Pulse Width Length Value*/
    __IO uint32_t PDREG_CHK_DATA23;                /*IR Pulse Width Length Value*/
    __IO uint32_t PDREG_CHK_DATA24;                /*IR Pulse Width Length Value*/
    __IO uint32_t PDREG_CHK_DATA25;                /*IR Pulse Width Length Value*/
    __IO uint32_t PDREG_CHK_DATA26;                /*IR Pulse Width Length Value*/
    __IO uint32_t PDREG_CHK_DATA27;                /*IR Pulse Width Length Value*/
    __IO uint32_t PDREG_CHK_DATA28;                /*IR Pulse Width Length Value*/
    __IO uint32_t PDREG_CHK_DATA29;                /*IR Pulse Width Length Value*/
    __IO uint32_t PDREG_CHK_DATA30;                /*IR Pulse Width Length Value*/
    __IO uint32_t PDREG_CHK_DATA31;                /*IR Pulse Width Length Value*/
}IRRX_REGISTER_T;

/*the bit value in PDREG_IRH register*/
#define PDREG_IRH_BIT_CNT_OFFSET   (0)
#define PDREG_IRH_RES_ONE_OFFSET   (8)
#define PDREG_IRH_RES_TWO_OFFSET   (16)
#define PDREG_IRH_RES_THREE_OFFSET (24)

#define PDREG_IRH_BIT_CNT_MASK (0x3f << PDREG_IRH_BIT_CNT_OFFSET)
#define PDREG_IRH_RES_ONE_MASK (0xff << PDREG_IRH_RES_ONE_OFFSET)
#define PDREG_IRH_RES_TWO_MASK (0xff << PDREG_IRH_RES_TWO_OFFSET)
#define PDREG_IRH_RES_THREE_MASK (0xff << PDREG_IRH_RES_THREE_OFFSET)

/*the bit value in PDREG_IRM register*/
#define PDREG_IRM_BIT_REG0_OFFSET (0)
#define PDREG_IRM_BIT_REG1_OFFSET (8)
#define PDREG_IRM_BIT_REG2_OFFSET (16)
#define PDREG_IRM_BIT_REG3_OFFSET (24)

#define PDREG_IRM_BIT_REG0_MASK (0xff << PDREG_IRM_BIT_REG0_OFFSET)
#define PDREG_IRM_BIT_REG1_MASK (0xff << PDREG_IRM_BIT_REG1_OFFSET)
#define PDREG_IRM_BIT_REG2_MASK (0xff << PDREG_IRM_BIT_REG2_OFFSET)
#define PDREG_IRM_BIT_REG3_MASK (0xff << PDREG_IRM_BIT_REG3_OFFSET)

/*the bit value in PDREG_IRL register*/
#define PDREG_IRL_BIT_REG4_OFFSET (0)
#define PDREG_IRL_BIT_REG5_OFFSET (8)
#define PDREG_IRL_BIT_REG6_OFFSET (16)

#define PDREG_IRM_BIT_REG4_MASK (0xff << PDREG_IRL_BIT_REG4_OFFSET)
#define PDREG_IRM_BIT_REG5_MASK (0xff << PDREG_IRL_BIT_REG5_OFFSET)
#define PDREG_IRM_BIT_REG6_MASK (0xff << PDREG_IRL_BIT_REG6_OFFSET)

/*the bit value in PDREG_IRCFGH register*/
#define PDREG_IRCFGH_IREN_OFFSET (0)
#define PDREG_IRCFGH_IRINV_OFFSET (1)
#define PDREG_IRCFGH_RC5_OFFSET (2)
#define PDREG_IRCFGH_RC5_1ST_OFFSET (3)
#define PDREG_IRCFGH_ORDINV_OFFSET (4)
#define PDREG_IRCFGH_IGN_1ST_OFFSET (5)
#define PDREG_IRCFGH_DISL_OFFSET (6)
#define PDREG_IRCFGH_DISH_OFFSET (7)
#define PDREG_IRCFGH_CHK_EN_OFFSET (13)
#define PDREG_IRCFGH_IGB0_OFFSET (14)
#define PDREG_IRCFGH_DISPD_OFFSET (15)
#define PDREG_IRCFGH_OK_PERIOD_OFFSET (16)

#define PDREG_IRCFGH_IREN_MASK (0x01 << PDREG_IRCFGH_IREN_OFFSET)
#define PDREG_IRCFGH_IRINV_MASK (0x01 << PDREG_IRCFGH_IRINV_OFFSET)
#define PDREG_IRCFGH_RC5_MASK (0x01 << PDREG_IRCFGH_RC5_OFFSET)
#define PDREG_IRCFGH_RC5_1ST_MASK (0x01 << PDREG_IRCFGH_RC5_1ST_OFFSET)
#define PDREG_IRCFGH_ORDINV_MASK (0x01 << PDREG_IRCFGH_ORDINV_OFFSET)
#define PDREG_IRCFGH_IGN_1ST_MASK (0x01 << PDREG_IRCFGH_IGN_1ST_OFFSET)
#define PDREG_IRCFGH_DISL_MASK (0x01 << PDREG_IRCFGH_DISL_OFFSET)
#define PDREG_IRCFGH_DISH_MASK (0x01 << PDREG_IRCFGH_DISH_OFFSET)
#define PDREG_IRCFGH_CHK_EN_MASK (0x01 << PDREG_IRCFGH_CHK_EN_OFFSET)
#define PDREG_IRCFGH_IGB0_MASK (0x01 << PDREG_IRCFGH_IGB0_OFFSET)
#define PDREG_IRCFGH_DISPD_MASK (0x01 << PDREG_IRCFGH_DISPD_OFFSET)
#define PDREG_IRCFGH_OK_PERIOD_MASK (0x7f << PDREG_IRCFGH_OK_PERIOD_OFFSET)

/*the bit value in PDREG_IRCFGL register*/
#define PDREG_IRCFGL_SAPERIOD_OFFSET (0)
#define PDREG_IRCFGL_CHECKPERIOD_OFFSET (8)

#define PDREG_IRCFGL_SAPERIOD_MASK (0xff << PDREG_IRCFGL_SAPERIOD_OFFSET)
#define PDREG_IRCFGL_CHECKPERIOD_MASK (0x1fff << PDREG_IRCFGL_CHECKPERIOD_OFFSET)

/*the bit value in PDREG_IRTHD register*/
#define PDREG_IRTHD_IRTHD_OFFSET (0)
#define PDREG_IRTHD_ICLR_OFFSET (7)
#define PDREG_IRTHD_DE_SEL_OFFSET (8)

#define PDREG_IRTHD_IRTHD_MASK (0x7f << PDREG_IRTHD_IRTHD_OFFSET)
#define PDREG_IRTHD_ICLR_MASK (0x01 << PDREG_IRTHD_ICLR_OFFSET)
#define PDREG_IRTHD_DE_SEL_MASK (0x1f << PDREG_IRTHD_DE_SEL_OFFSET)

/*the bit value in PDREG_IRRCM_THD register*/
#define PDREG_IRRCM_THD_IRRCM_THD_00_OFFSET (0)
#define PDREG_IRRCM_THD_IRRCM_THD_01_OFFSET (7)
#define PDREG_IRRCM_THD_IRRCM_THD_10_OFFSET (14)
#define PDREG_IRRCM_THD_IRRCM_THD_11_OFFSET (21)
#define PDREG_IRRCM_THD_IRRCM_OFFSET (31)

#define PDREG_IRRCM_THD_IRRCM_THD_00_MASK (0x7f << PDREG_IRRCM_THD_IRRCM_THD_00_OFFSET)
#define PDREG_IRRCM_THD_IRRCM_THD_01_MASK (0x7f << PDREG_IRRCM_THD_IRRCM_THD_01_OFFSET)
#define PDREG_IRRCM_THD_IRRCM_THD_10_MASK (0x7f << PDREG_IRRCM_THD_IRRCM_THD_10_OFFSET)
#define PDREG_IRRCM_THD_IRRCM_THD_11_MASK (0x7f << PDREG_IRRCM_THD_IRRCM_THD_11_OFFSET)
#define PDREG_IRRCM_THD_IRRCM_MASK (0x01 << PDREG_IRRCM_THD_IRRCM_OFFSET)

/*the bit value in PDREG_IRRCM_THD_0 register*/
#define PDREG_IRRCM_THD_0_IRRCM_THD_20_OFFSET (0)
#define PDREG_IRRCM_THD_0_IRRCM_THD_21_OFFSET (7)

#define PDREG_IRRCM_THD_0_IRRCM_THD_20_MASK (0x7f << PDREG_IRRCM_THD_0_IRRCM_THD_20_OFFSET)
#define PDREG_IRRCM_THD_0_IRRCM_THD_21_MASK (0x7f << PDREG_IRRCM_THD_0_IRRCM_THD_21_OFFSET)

/*the bit value in PDREG_IRCLR register*/
#define PDREG_IRCLR_IRCLR_OFFSET (0)

#define PDREG_IRCLR_IRCLR_MASK (0x01 << PDREG_IRCLR_IRCLR_OFFSET)

/*the bit value in PDREG_IREXP_EN register*/
#define PDREG_IREXP_EN_IREXPEN_OFFSET (0)
#define PDREG_IREXP_EN_BCEPEN_OFFSET (8)
#define PDREG_IREXP_EN_IRPDWNEN_OFFSET (9)
#define PDREG_IREXP_EN_PD_IREXPEN_OFFSET (10)

#define PDREG_IREXP_EN_IREXPEN_MASK (0xff << PDREG_IREXP_EN_IREXPEN_OFFSET)
#define PDREG_IREXP_EN_BCEPEN_MASK (0x01 << PDREG_IREXP_EN_BCEPEN_OFFSET)
#define PDREG_IREXP_EN_IRPDWNEN_MASK (0x01 << PDREG_IREXP_EN_IRPDWNEN_OFFSET)
#define PDREG_IREXP_EN_PD_IREXPEN_MASK (0x03 << PDREG_IREXP_EN_PD_IREXPEN_OFFSET)

/*the bit value in PDREG_XP_BCNT register*/
#define PDREG_XP_BCNT_EXP_BITCNT_OFFSET (0)
#define PDREG_XP_BCNT_CHK_CNT_OFFSET (6)

#define PDREG_XP_BCNT_EXP_BITCNT_MASK (0x3d << PDREG_XP_BCNT_EXP_BITCNT_OFFSET)
#define PDREG_XP_BCNT_CHK_CNT_MASK (0x3d << PDREG_XP_BCNT_CHK_CNT_OFFSET)

/*the bit value in PDREG_PDWNCNT register*/
#define PDREG_PDWNCNT_PDWNCNT_OFFSET (0)

#define PDREG_PDWNCNT_PDWNCNT_MASK (0xff << PDREG_PDWNCNT_PDWNCNT_OFFSET)

/*the bit value in PDREG_IRINT_EN register*/
#define PDREG_IRINT_EN_IRINT_EN_OFFSET (0)

#define PDREG_IRINT_EN_IRINT_EN_MASK (0x01 << PDREG_IRINT_EN_IRINT_EN_OFFSET)

/*the bit value in PDREG_IR_INTCLR register*/
#define PDREG_IR_INTCLR_IR_INTCLR_OFFSET (0)

#define PDREG_IR_INTCLR_IR_INTCLR_MASK (0x01 << PDREG_IR_INTCLR_IR_INTCLR_OFFSET)

/*the bit value in PDREG_WDTSET register*/
#define PDREG_WDTSET_WDT_EN_OFFSET (0)
#define PDREG_WDTSET_DBG_STOP_OFFSET (1)
#define PDREG_WDTSET_WDTMODE_OFFSET (4)

#define PDREG_WDTSET_WDT_EN_MASK (0x01 << PDREG_WDTSET_WDT_EN_OFFSET)
#define PDREG_WDTSET_DBG_STOP_MASK (0x01 << PDREG_WDTSET_DBG_STOP_OFFSET)
#define PDREG_WDTSET_WDTMODE_MASK (0x07 << PDREG_WDTSET_WDTMODE_OFFSET)



/* *************************  IRRX register definition end line**********************************
*/


#endif /* __IRRX_REG_DEFINITION_H__ */