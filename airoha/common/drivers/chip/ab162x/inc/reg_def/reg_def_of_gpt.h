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

#ifndef __GPT_REG_DEFINITION_H__
#define __GPT_REG_DEFINITION_H__


#include <stdint.h>

/************************ GPT end register definition start line  ********************************/
typedef struct {
    __I   uint32_t GPT_IRQSTA;
    __IO  uint32_t GPT_IRQMSK0;
    __IO  uint32_t GPT_IRQMSK1;
    __IO  uint32_t GPT_WAKEUPMSK0;
    __IO  uint32_t GPT_WAKEUPMSK1;
    __I   uint32_t GPT_CLRSTA;
    __I   uint32_t GPT_WCOMPSTA;
} GPT_REGISTER_GLOABL_T;

typedef struct {
    union {
        struct {
            __IO uint8_t EN;
            __IO uint8_t MODE;
            __IO uint8_t SW_CG;
            __I  uint8_t RESERVED[1];
        } GPT_CON_CELLS;
        __IO uint32_t GPT_CON;
    } GPT_CON_UNION; /*!< timer enable and mode config*/
    __O uint32_t GPT_CLR ;
    __IO uint32_t GPT_CLK ; /*!< clock select and prescale config*/
    __IO uint32_t GPT_IRQ_EN ; /*!< interrupt enable*/
    __I uint32_t GPT_IRQ_STA ; /*!< interrupt status*/
    __O uint32_t GPT_IRQ_ACK; /*!< interrupt ack*/
    __IO uint32_t GPT_COUNT ; /*!< gpt0~4 count,gpt5 low word*/
    __IO uint32_t GPT_COMPARE ; /*!< gpt0~4 threshold,gpt5 low word*/
} GPT_REGISTER_T;


#define _GPT_BASE_ (GPT_BASE)
#define _GPT_BASEADDR_ (_GPT_BASE_ + 0x000)

#define GPT0 ((GPT_REGISTER_T*)(_GPT_BASE_ + 0x000))
#define GPT1 ((GPT_REGISTER_T*)(_GPT_BASE_ + 0x100))
#define GPT2 ((GPT_REGISTER_T*)(_GPT_BASE_ + 0x200))
#define GPT3 ((GPT_REGISTER_T*)(_GPT_BASE_ + 0x300))
#define GPT4 ((GPT_REGISTER_T*)(_GPT_BASE_ + 0x400))
#define GPT5 ((GPT_REGISTER_T*)(_GPT_BASE_ + 0x500))
#define GPT6 ((GPT_REGISTER_T*)(_GPT_BASE_ + 0x600))
#define GPTGLB ((GPT_REGISTER_GLOABL_T*)(_GPT_BASE_ + 0xC00))
#define GPT(x) ((GPT_REGISTER_T*)(_GPT_BASE_ + (0x100*x)))


typedef struct {
    __I   uint32_t OS_GPT_IRQSTA;
    __IO  uint32_t OS_GPT_IRQMSK;
    __IO  uint32_t OS_GPT_WAKEUPMSK;
    __I   uint32_t OS_GPT_CLRSTA;
    __I   uint32_t OS_GPT_WCOMPSTA;
} OS_GPT_REGISTER_GLOABL_T;

#define OS_GPT0     ((GPT_REGISTER_T*)(OS_GPT_BASE + 0x0))
#define OS_GPTGLB   ((OS_GPT_REGISTER_GLOABL_T*)(OS_GPT_BASE + 0x100))


/************************ GPT end register definition end line  ********************************/



#endif /* __GPT_REG_DEFINITION_H__ */