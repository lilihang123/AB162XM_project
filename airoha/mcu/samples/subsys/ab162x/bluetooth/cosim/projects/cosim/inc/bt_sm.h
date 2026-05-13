/* Copyright Statement:
 *
 * (C) 2005-2016  MediaTek Inc. All rights reserved.
 *
 * This software/firmware and related documentation ("MediaTek Software") are
 * protected under relevant copyright laws. The information contained herein
 * is confidential and proprietary to MediaTek Inc. ("MediaTek") and/or its licensors.
 * Without the prior written permission of MediaTek and/or its licensors,
 * any reproduction, modification, use or disclosure of MediaTek Software,
 * and information contained herein, in whole or in part, shall be strictly prohibited.
 * You may only use, reproduce, modify, or distribute (as applicable) MediaTek Software
 * if you have agreed to and been bound by the applicable license agreement with
 * MediaTek ("License Agreement") and been granted explicit permission to do so within
 * the License Agreement ("Permitted User").  If you are not a Permitted User,
 * please cease any access or use of MediaTek Software immediately.
 * BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 * THAT MEDIATEK SOFTWARE RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES
 * ARE PROVIDED TO RECEIVER ON AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL
 * WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
 * NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
 * SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
 * SUPPLIED WITH MEDIATEK SOFTWARE, AND RECEIVER AGREES TO LOOK ONLY TO SUCH
 * THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. RECEIVER EXPRESSLY ACKNOWLEDGES
 * THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES
 * CONTAINED IN MEDIATEK SOFTWARE. MEDIATEK SHALL ALSO NOT BE RESPONSIBLE FOR ANY MEDIATEK
 * SOFTWARE RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
 * STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND
 * CUMULATIVE LIABILITY WITH RESPECT TO MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
 * AT MEDIATEK'S OPTION, TO REVISE OR REPLACE MEDIATEK SOFTWARE AT ISSUE,
 * OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY RECEIVER TO
 * MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
 */
/* MediaTek restricted information */

#ifndef __BT_SM_H__
#define __BT_SM_H__

#include "bt_type_def.h"


/* +---------+-----------------------------+
 * |Module ID| BT_SM_EVENT                 |
 * +---------+-----------------------------+ */
#define BT_SM_EVENT_START_PAIRING   (BT_MODULE_SM | 0xFFFFF0)
#define BT_SM_EVENT_START_ENCRYPT   (BT_MODULE_SM | 0xFFFFF1)
#define BT_SM_EVENT_KEY_DIST        (BT_MODULE_SM | 0xFFFFF2)
#define BT_SM_EVENT_APP_INPUT       (BT_MODULE_SM | 0xFFFFF3)
#define BT_SM_EVENT_LESC_SEND_CONFIRM (BT_MODULE_SM | 0xFFFFF4)
#define BT_SM_EVENT_LESC_WAIT_APP_INPUT (BT_MODULE_SM | 0xFFFFF5)
#define BT_SM_EVENT_LESC_SEND_DHKEY_CHECK (BT_MODULE_SM | 0xFFFFF6)
#define BT_SM_EVENT_FAILED          (BT_MODULE_SM | 0xFFFFFE)
#define BT_SM_EVENT_COMPLETE        (BT_MODULE_SM | 0xFFFFFF)
#define BT_SM_EVENT(code)           (BT_MODULE_SM | (code))

#define BT_SM_SUBSTATE_SUCCESS                          BT_SMP_STATUS_SUCCESS
#define BT_SM_SUBSTATE_PASSKEY_ENTRY_FAILED             BT_SMP_STATUS_PASSKEY_ENTRY_FAILED
#define BT_SM_SUBSTATE_OOB_NOT_AVAILABLE                BT_SMP_STATUS_OOB_NOT_AVAILABLE
#define BT_SM_SUBSTATE_AUTHENTICATION_REQUIREMENTS      BT_SMP_STATUS_AUTHENTICATION_REQUIREMENTS
#define BT_SM_SUBSTATE_CONFIRM_VALUE_FAILED             BT_SMP_STATUS_CONFIRM_VALUE_FAILED
#define BT_SM_SUBSTATE_PAIRING_NOT_SUPPORTED            BT_SMP_STATUS_PAIRING_NOT_SUPPORTED
#define BT_SM_SUBSTATE_ENCRYPTION_KEY_SIZE              BT_SMP_STATUS_ENCRYPTION_KEY_SIZE
#define BT_SM_SUBSTATE_COMMAND_NOT_SUPPORTED            BT_SMP_STATUS_COMMAND_NOT_SUPPORTED
#define BT_SM_SUBSTATE_UNSPECIFIED_REASON               BT_SMP_STATUS_UNSPECIFIED_REASON
#define BT_SM_SUBSTATE_REPEATED_ATTEMPTS                BT_SMP_STATUS_REPEATED_ATTEMPTS
#define BT_SM_SUBSTATE_INVALID_PARAMETERS               BT_SMP_STATUS_INVALID_PARAMETERS
#define BT_SM_SUBSTATE_DHKEY_CHECK_FAILED               BT_SMP_STATUS_DHKEY_CHECK_FAILED
#define BT_SM_SUBSTATE_NUMERIC_COMPARISON_FAILED        BT_SMP_STATUS_NUMERIC_COMPARISON_FAILED
#define BT_SM_SUBSTATE_BR_EDR_PAIRING_IN_PROGRESS       BT_SMP_STATUS_BR_EDR_PAIRING_IN_PROGRESS
#define BT_SM_SUBSTATE_CROSS_TRANSPORT_KEY_NOT_ALLOWED  BT_SMP_STATUS_CROSS_TRANSPORT_KEY_NOT_ALLOWED

#define BT_SM_SUBSTATE_TIMEOUT               0xFE
#define BT_SM_SUBSTATE_LESC_PK_CONFIRM_COUNT (BT_MODULE_SM | 0x000000)
#define BT_SM_SUBSTATE_MESSAGE_ONLY (BT_MODULE_SM | 0xFFFFFF)

#define BT_SM_CONN_HAS_LTK(connection) (((connection)->bonding_info->key_security_mode & (BT_GAP_LE_SECURITY_ENCRYPTION_MASK | BT_GAP_LE_SECURITY_BONDED_MASK)) == (BT_GAP_LE_SECURITY_ENCRYPTION_MASK | BT_GAP_LE_SECURITY_BONDED_MASK))
#define BT_SM_CONN_KEY_CHECK_MITM(connection) ((connection)->bonding_info->key_security_mode & BT_GAP_LE_SECURITY_AUTHENTICATION_MASK)
#define BT_SM_AUTH_REQ_CHECK_MITM(auth_req) ((auth_req) & BT_GAP_LE_SMP_AUTH_REQ_MITM)
#define BT_SM_CONN_KEY_CHECK_LESC(connection) ((connection)->bonding_info->key_security_mode & BT_GAP_LE_SECURITY_LESC_MASK)
#define BT_SM_AUTH_REQ_CHECK_LESC(auth_req) ((auth_req) & BT_GAP_LE_SMP_AUTH_REQ_SECURE_CONNECTION)

#define BT_SM_SEND_NONE 0
#define BT_SM_SEND_SMP  1
#define BT_SM_SEND_CMD  2

#define BT_SM_NC_YES    (-1)
#define BT_SM_NC_NO     (-2)

#ifdef BT_DEBUG
#define BT_SM_GUARD_STR "HUMMINGBIRDXX"
#define BT_SM_GUARD_STR_LEN 13
#define BT_SM_BUFFER_OVERFLOW_CHECK(guard) { BT_ASSERT(bt_memcmp(guard, BT_SM_GUARD_STR, BT_SM_GUARD_STR_LEN)==0 && "buffer overflowed"); }
#else
#define BT_SM_BUFFER_OVERFLOW_CHECK(x)
#endif

BT_EXTERN_C_BEGIN

bt_status_t bt_sm_pairing_complete_ind(uint32_t substate);
bt_status_t bt_sm_slave_pairing_proc(uint32_t is_timeout, uint32_t timer_id,
                                     uint32_t substate, const void *packet);
bt_status_t bt_sm_master_pairing_proc(uint32_t is_timeout, uint32_t timer_id,
                                      uint32_t substate, const void *packet);

BT_EXTERN_C_END

#endif /* __BT_SM_H__ */

