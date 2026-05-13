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

#ifndef _ASSERT_H_
#define _ASSERT_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined(AIR_EXCEPTION_HANDLER_ENABLE)

/* Includes ------------------------------------------------------------------*/
#if defined(AIR_LOGGING_ENABLE)
#include "air_logging.h"
#else
#ifndef ATTR_LOG_STRING
#define ATTR_LOG_STRING                static const char             //    __attribute__ ((__section__(".log_string"))) static const char
#endif
#endif
#include "exception_handler.h"
#include "memory_attribute.h"

/* Public define -------------------------------------------------------------*/
#if !defined(__cplusplus)
#define assert( x ) if( (x) == 0 ) { \
    ATTR_LOG_STRING exp[] = #x; \
    ATTR_LOG_STRING file[] = __FILE__; \
    light_assert(exp, file, __LINE__); \
}
#define static_assert _Static_assert
#else
#define EXPAND_CONCAT(x, y)    x##y
#define EXP_AT_LINE(name, line) EXPAND_CONCAT(name##_at_line_, line)
#define assert( x ) if( (x) == 0 ) { \
    static const char EXP_AT_LINE(exp, __LINE__)[] ATTR_DATA_DECLARE(".log_string") = #x; \
    static const char EXP_AT_LINE(file, __LINE__)[] ATTR_DATA_DECLARE(".log_string") = __FILE__; \
    light_assert(EXP_AT_LINE(exp, __LINE__), EXP_AT_LINE(file, __LINE__), __LINE__); \
}
#endif /* __cplusplus */

/* Public typedef ------------------------------------------------------------*/
/* Public macro --------------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/

#endif /* AIR_EXCEPTION_HANDLER_ENABLE */

#ifdef __cplusplus
}
#endif

#endif /* _ASSERT_H_ */
