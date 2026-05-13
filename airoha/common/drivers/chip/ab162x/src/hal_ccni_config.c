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

#include "hal_ccni.h"

#ifdef HAL_CCNI_MODULE_ENABLED
#include "hal_ccni_config.h"

#if defined(CORE_MCU)
#include "hal_log.h"
#endif

#include "memory_attribute.h"

#ifdef __cplusplus
extern "C" {
#endif


/* If individual projects have special needs, developer can define the strong symbol
 * of ccni_event_callback at the project level to override the default handler.
 */
ATTR_WEAK_SYMBOL void CCNI_DEF_HANDLER(0)(hal_ccni_event_t event, hal_ccni_message_t *msg) { ; }
ATTR_WEAK_SYMBOL void CCNI_DEF_HANDLER(1)(hal_ccni_event_t event, hal_ccni_message_t *msg) { ; }
ATTR_WEAK_SYMBOL void CCNI_DEF_HANDLER(2)(hal_ccni_event_t event, hal_ccni_message_t *msg) { ; }
ATTR_WEAK_SYMBOL void CCNI_DEF_HANDLER(3)(hal_ccni_event_t event, hal_ccni_message_t *msg) { ; }
ATTR_WEAK_SYMBOL void CCNI_DEF_HANDLER(4)(hal_ccni_event_t event, hal_ccni_message_t *msg) { ; }
ATTR_WEAK_SYMBOL void CCNI_DEF_HANDLER(5)(hal_ccni_event_t event, hal_ccni_message_t *msg) { ; }
ATTR_WEAK_SYMBOL void CCNI_DEF_HANDLER(6)(hal_ccni_event_t event, hal_ccni_message_t *msg) { ; }
ATTR_WEAK_SYMBOL void CCNI_DEF_HANDLER(7)(hal_ccni_event_t event, hal_ccni_message_t *msg) { ; }
ATTR_WEAK_SYMBOL void CCNI_DEF_HANDLER(8)(hal_ccni_event_t event, hal_ccni_message_t *msg) { ; }
ATTR_WEAK_SYMBOL void CCNI_DEF_HANDLER(9)(hal_ccni_event_t event, hal_ccni_message_t *msg) { ; }
ATTR_WEAK_SYMBOL void CCNI_DEF_HANDLER(10)(hal_ccni_event_t event, hal_ccni_message_t *msg) { ; }
ATTR_WEAK_SYMBOL void CCNI_DEF_HANDLER(11)(hal_ccni_event_t event, hal_ccni_message_t *msg) { ; }
ATTR_WEAK_SYMBOL void CCNI_DEF_HANDLER(12)(hal_ccni_event_t event, hal_ccni_message_t *msg) { ; }
ATTR_WEAK_SYMBOL void CCNI_DEF_HANDLER(13)(hal_ccni_event_t event, hal_ccni_message_t *msg) { ; }
ATTR_WEAK_SYMBOL void CCNI_DEF_HANDLER(14)(hal_ccni_event_t event, hal_ccni_message_t *msg) { ; }
ATTR_WEAK_SYMBOL void CCNI_DEF_HANDLER(15)(hal_ccni_event_t event, hal_ccni_message_t *msg) { ; }
ATTR_WEAK_SYMBOL void CCNI_DEF_HANDLER(16)(hal_ccni_event_t event, hal_ccni_message_t *msg) { ; }
ATTR_WEAK_SYMBOL void CCNI_DEF_HANDLER(17)(hal_ccni_event_t event, hal_ccni_message_t *msg) { ; }
ATTR_WEAK_SYMBOL void CCNI_DEF_HANDLER(18)(hal_ccni_event_t event, hal_ccni_message_t *msg) { ; }
ATTR_WEAK_SYMBOL void CCNI_DEF_HANDLER(19)(hal_ccni_event_t event, hal_ccni_message_t *msg) { ; }
ATTR_WEAK_SYMBOL void CCNI_DEF_HANDLER(20)(hal_ccni_event_t event, hal_ccni_message_t *msg) { ; }
ATTR_WEAK_SYMBOL void CCNI_DEF_HANDLER(21)(hal_ccni_event_t event, hal_ccni_message_t *msg) { ; }
ATTR_WEAK_SYMBOL void CCNI_DEF_HANDLER(22)(hal_ccni_event_t event, hal_ccni_message_t *msg) { ; }
ATTR_WEAK_SYMBOL void CCNI_DEF_HANDLER(23)(hal_ccni_event_t event, hal_ccni_message_t *msg) { ; }
ATTR_WEAK_SYMBOL void CCNI_DEF_HANDLER(24)(hal_ccni_event_t event, hal_ccni_message_t *msg) { ; }
ATTR_WEAK_SYMBOL void CCNI_DEF_HANDLER(25)(hal_ccni_event_t event, hal_ccni_message_t *msg) { ; }
ATTR_WEAK_SYMBOL void CCNI_DEF_HANDLER(26)(hal_ccni_event_t event, hal_ccni_message_t *msg) { ; }
ATTR_WEAK_SYMBOL void CCNI_DEF_HANDLER(27)(hal_ccni_event_t event, hal_ccni_message_t *msg) { ; }
ATTR_WEAK_SYMBOL void CCNI_DEF_HANDLER(28)(hal_ccni_event_t event, hal_ccni_message_t *msg) { ; }
ATTR_WEAK_SYMBOL void CCNI_DEF_HANDLER(29)(hal_ccni_event_t event, hal_ccni_message_t *msg) { ; }
ATTR_WEAK_SYMBOL void CCNI_DEF_HANDLER(30)(hal_ccni_event_t event, hal_ccni_message_t *msg) { ; }
ATTR_WEAK_SYMBOL void CCNI_DEF_HANDLER(31)(hal_ccni_event_t event, hal_ccni_message_t *msg) { ; }

const hal_ccni_function_t ccni_callback[HAL_CCNI_EVENT_MAX] = {
    hal_ccni_event_callback0,
    hal_ccni_event_callback1,
    hal_ccni_event_callback2,
    hal_ccni_event_callback3,
    hal_ccni_event_callback4,
    hal_ccni_event_callback5,
    hal_ccni_event_callback6,
    hal_ccni_event_callback7,
    hal_ccni_event_callback8,
    hal_ccni_event_callback9,
    hal_ccni_event_callback10,
    hal_ccni_event_callback11,
    hal_ccni_event_callback12,
    hal_ccni_event_callback13,
    hal_ccni_event_callback14,
    hal_ccni_event_callback15,
    hal_ccni_event_callback16,
    hal_ccni_event_callback17,
    hal_ccni_event_callback18,
    hal_ccni_event_callback19,
    hal_ccni_event_callback20,
    hal_ccni_event_callback21,
    hal_ccni_event_callback22,
    hal_ccni_event_callback23,
    hal_ccni_event_callback24,
    hal_ccni_event_callback25,
    hal_ccni_event_callback26,
    hal_ccni_event_callback27,
    hal_ccni_event_callback28,
    hal_ccni_event_callback29,
    hal_ccni_event_callback30,
    hal_ccni_event_callback31,
};

#ifdef __cplusplus
}
#endif

#endif /* HAL_CCNI_MODULE_ENABLED */

