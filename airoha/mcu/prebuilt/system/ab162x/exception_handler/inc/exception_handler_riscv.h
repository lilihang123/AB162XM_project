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

#ifndef _EXCEPTION_HANDLER_RISCV_H_
#define _EXCEPTION_HANDLER_RISCV_H_

#if defined(AIR_EXCEPTION_HANDLER_ENABLE)

/* Includes ------------------------------------------------------------------*/
#include "stdio.h"
#include "stdarg.h"
#include "exception_config.h"
#include "exception_handler.h"
#if EXCEPTION_SLAVES_TOTAL > 0
/* Public define -------------------------------------------------------------*/
/* Public typedef ------------------------------------------------------------*/
/* Public macro --------------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/

#if (EXCEPTION_MEMDUMP_MODE & EXCEPTION_MEMDUMP_MINIDUMP)
#define MINIDUMP_ADDRESS_OFFSET_RISCV                   (6 * 1024)
#define MINIDUMP_HEADER_LENGTH_RISCV                    (512)
#define MINIDUMP_CONTEXT_LENGTH_RISCV                   (512)
#define MINIDUMP_CURRENTSTACK_LENGTH_RISCV              (3 * 1024)
#define MINIDUMP_SYSTEMSTACK_LENGTH_RISCV               (2 * 1024)
#define MINIDUMP_DATA_SIZE_RISCV                        (4096)
#endif /* EXCEPTION_MEMDUMP_MODE */

extern void exception_alert_riscv_0(void);
extern exception_slave_status_t exception_check_status_riscv_0(void);
extern void exception_dump_riscv_0(void);
extern void exception_forceddump_riscv_0(void);

#endif /* #if EXCEPTION_SLAVES_TOTAL > 0 */
#endif /* AIR_EXCEPTION_HANDLER_ENABLE */
#endif /* _EXCEPTION_HANDLER_RISCV_H_ */
