/* Copyright Statement:
 *
 * (C) 2017  Airoha Technology Corp. All rights reserved.
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

#include <stdio.h>
#include <stdarg.h>

#include "cosim_mdm.h"

extern void handmade_printf(char *buf, const char *fmt, va_list ap);

static char mdm_printf_buf[MAX_MDM_STR_LEN];

static void MDM_TM_STR_N(U32 str_n, const char *str)
{
    U32 i = 0;
    U32 mdm_str_n_reg = (MDM_STR0 + str_n*4);

    for(i=0; i<MAX_MDM_STR_LEN && '\0'!=*str; i++, str++) {
        *((P_U32)mdm_str_n_reg) = *str;
    }
}

void MDM_TM_STR(const char *str)
{
    MDM_TM_STR_CLEAR(0);
    MDM_TM_STR_N(0, str);
    MDM_TM_STR_DISPLAY(0);
}

void MDM_TM_PRINTF(const char *fmt,...)
{
    va_list ap;

    va_start(ap, fmt);
    //vsprintf(mdm_printf_buf, fmt, ap);
    handmade_printf(mdm_printf_buf, fmt, ap);
    //mdm_printf_buf[MAX_MDM_STR_LEN-1] = '\0';  // for safety
    va_end(ap);

    //MDM_TM_TRACE;
    MDM_TM_STR(mdm_printf_buf);
}

void MDM_TM_DUMP(char *buf, int len)
{
    int i;
    for (i = 0; i < len; i += 8) {
        MDM_TM_PRINTF("%x %x %x %x %x %x %x %x",
                buf[i+0], buf[i+1], buf[i+2], buf[i+3],
                buf[i+4], buf[i+5], buf[i+6], buf[i+7]);
    }
}

void MDM_TM_WAIT_MS(unsigned int time)
{
    MDM_TM_SET_WAIT_US(time*1000);
    while(MDM_TM_GET_WAIT_US != 0);
}

void MDM_InstTestSuccess(void)
{
    MDM_TM_ENDSIM;
}

void MDM_InstTestFail(void)
{
    MDM_TM_ENDFAIL;
}

