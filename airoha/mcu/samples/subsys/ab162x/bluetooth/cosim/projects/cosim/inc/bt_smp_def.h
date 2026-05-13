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

#ifndef __BT_SMP_DEF_H__
#define __BT_SMP_DEF_H__

#include "bt_gap_le.h"

BT_EXTERN_C_BEGIN

#define BT_SMP_KEY_SIZE_MIN 7
#define BT_SMP_KEY_SIZE_MAX 16

#define BT_SMP_F4_CMAC_LENGTH    65
#define BT_SMP_F5_CMAC_LENGTH    53
#define BT_SMP_F6_CMAC_LENGTH    65
#define BT_SMP_G2_CMAC_LENGTH    80

#define BT_SMP_DHKEY_SIZE        32

#define BT_SMP_PUBLIC_KEY_X_SIZE 32
#define BT_SMP_PUBLIC_KEY_Y_SIZE BT_SMP_PUBLIC_KEY_X_SIZE

typedef bt_key_t bt_smp_key_t;

#define BT_SMP_TYPE_LE           0x00
#define BT_SMP_TYPE_BREDR        0x01
typedef uint8_t bt_smp_t;


BT_PACKED (
typedef struct {
    uint8_t x[BT_SMP_PUBLIC_KEY_X_SIZE];
    uint8_t y[BT_SMP_PUBLIC_KEY_X_SIZE];
}) bt_smp_public_key_t;

#define BT_SMP_STATUS_SUCCESS                          0x00
#define BT_SMP_STATUS_PASSKEY_ENTRY_FAILED             0x01
#define BT_SMP_STATUS_OOB_NOT_AVAILABLE                0x02
#define BT_SMP_STATUS_AUTHENTICATION_REQUIREMENTS      0x03
#define BT_SMP_STATUS_CONFIRM_VALUE_FAILED             0x04
#define BT_SMP_STATUS_PAIRING_NOT_SUPPORTED            0x05
#define BT_SMP_STATUS_ENCRYPTION_KEY_SIZE              0x06
#define BT_SMP_STATUS_COMMAND_NOT_SUPPORTED            0x07
#define BT_SMP_STATUS_UNSPECIFIED_REASON               0x08
#define BT_SMP_STATUS_REPEATED_ATTEMPTS                0x09
#define BT_SMP_STATUS_INVALID_PARAMETERS               0x0A
#define BT_SMP_STATUS_DHKEY_CHECK_FAILED               0x0B
#define BT_SMP_STATUS_NUMERIC_COMPARISON_FAILED        0x0C
#define BT_SMP_STATUS_BR_EDR_PAIRING_IN_PROGRESS       0x0D
#define BT_SMP_STATUS_CROSS_TRANSPORT_KEY_NOT_ALLOWED  0x0E
typedef uint8_t bt_smp_status_t;

#define BT_SMP_CODE_PAIRING_REQ                     0x01
#define BT_SMP_CODE_PAIRING_RSP                     0x02
#define BT_SMP_CODE_PAIRING_CONFIRM                 0x03
#define BT_SMP_CODE_PAIRING_RANDOM                  0x04
#define BT_SMP_CODE_PAIRING_FAILED                  0x05
#define BT_SMP_CODE_ENCRYPTION_INFO                 0x06
#define BT_SMP_CODE_MASTER_IDENTIFICATION           0x07
#define BT_SMP_CODE_IDENTITY_INFORMATION            0x08
#define BT_SMP_CODE_IDENTITY_ADDRESS_INFO           0x09
#define BT_SMP_CODE_SIGNING_INFO                    0x0A
#define BT_SMP_CODE_SECURITY_REQ                    0x0B
#define BT_SMP_CODE_PAIRING_PUBLIC_KEY              0x0C
#define BT_SMP_CODE_PAIRING_DHKEY_CHECK             0x0D
#define BT_SMP_CODE_PAIRING_KEYPRESS_NOTIFICATION   0x0E
typedef uint8_t bt_smp_code_t;

/* internal use */
#define BT_SMP_KEY_DISTRIBUTE_STATE_ENCRYPT_INFO      (0x01 << 0)
#define BT_SMP_KEY_DISTRIBUTE_STATE_MASTER_ID         (0x01 << 1)
#define BT_SMP_KEY_DISTRIBUTE_STATE_ID_INFO           (0x01 << 2)
#define BT_SMP_KEY_DISTRIBUTE_STATE_IA_INFO           (0x01 << 3)
#define BT_SMP_KEY_DISTRIBUTE_STATE_SIGNING_INFO      (0x01 << 4)
#define BT_SMP_KEY_DISTRIBUTE_STATE_CTKD_INFO         (0x01 << 5)
#define BT_SMP_KEY_DISTRIBUTE_STATE_NUM               5
typedef uint8_t bt_sm_key_distribute_state_t;

#define BT_SMP_KEY_DISTRIBUTE_STATE_BREDR_MASK    (BT_SMP_KEY_DISTRIBUTE_STATE_ID_INFO |  BT_SMP_KEY_DISTRIBUTE_STATE_IA_INFO | BT_SMP_KEY_DISTRIBUTE_STATE_SIGNING_INFO)


#define BT_SMP_INITIATOR    0
#define BT_SMP_RESPONDER    1
#define BT_SMP_ROLE_NUM     2

extern const uint8_t bt_smp_key_gen_method_table[BT_SMP_ROLE_NUM][BT_GAP_LE_SMP_IO_CAPABILITY_NUM][BT_GAP_LE_SMP_IO_CAPABILITY_NUM];
extern const uint8_t bt_smp_lesc_key_gen_method_table[BT_SMP_ROLE_NUM][BT_GAP_LE_SMP_IO_CAPABILITY_NUM][BT_GAP_LE_SMP_IO_CAPABILITY_NUM];

BT_PACKED(
typedef struct {
    struct _bt_connection_t         *connection;
    struct _bt_gap_connection_t     *edr_connection;
    bt_sm_key_distribute_state_t    initiator_distribute_state;
    bt_sm_key_distribute_state_t    responder_distribute_state;
    uint32_t                        timer_op;
    bt_gap_le_smp_pairing_config_t         local_pairing_config;
    bt_gap_le_smp_pairing_method_t         method;

    BT_PACKED(
    union {
        bt_smp_key_t    Mrand;
        bt_smp_key_t    Na; /* LESC */
    });
    BT_PACKED(
    union {
        bt_smp_key_t    Srand;
        bt_smp_key_t    Nb; /* LESC */
    });
    BT_PACKED(
    union {
        bt_smp_key_t    Mconfirm;
        bt_smp_key_t    Sconfirm;
        bt_smp_key_t    Ca; /* LESC */
        bt_smp_key_t    Cb; /* LESC */
        bt_smp_key_t    Ea; /* LESC */
        bt_smp_key_t    Eb; /* LESC */
    });
    BT_PACKED(
    union {
        bt_smp_key_t    confirm_p1;
        bt_smp_key_t    ltk;
    });
    BT_PACKED(
    union {
        bt_smp_key_t    oob_data;
        uint32_t        passkey: 20;
        bt_smp_key_t    TK;
        bt_smp_key_t    ra; /* LESC */
        bt_smp_key_t    rb; /* LESC */
    });
    /* LESC */
    bt_gap_le_smp_pairing_config_t         peer_pairing_config;
    int32_t             nc_value;
    bt_smp_public_key_t PKa;
    bt_smp_public_key_t PKb;
}) bt_sm_session_t;

BT_PACKED(
typedef struct {
    bt_smp_code_t           code;
    bt_gap_le_smp_pairing_config_t config;
}) bt_smp_pairing_req_t;

typedef bt_smp_pairing_req_t bt_smp_pairing_rsp_t;

BT_PACKED(
typedef struct {
    bt_smp_code_t       code;
    bt_smp_key_t        confirm_value;
}) bt_smp_pairing_confirm_t;

BT_PACKED(
typedef struct {
    bt_smp_code_t       code;
    bt_smp_key_t        random_value;
}) bt_smp_pairing_random_t;

BT_PACKED(
typedef struct {
    bt_smp_code_t       code;
    bt_smp_status_t     reason;
}) bt_smp_pairing_failed_t;

BT_PACKED(
typedef struct {
    bt_smp_code_t       code;
    uint8_t             public_key_x[BT_SMP_PUBLIC_KEY_X_SIZE];
    uint8_t             public_key_y[BT_SMP_PUBLIC_KEY_X_SIZE];
}) bt_smp_pairing_public_key_t;

BT_PACKED(
typedef struct {
    bt_smp_code_t       code;
    bt_smp_key_t         dhkey_check;
}) bt_smp_pairing_dhkey_check_t;

BT_PACKED(
typedef struct {
    bt_smp_code_t       code;
    uint8_t             notification_type;
}) bt_smp_keypress_notification_t;

BT_PACKED(
typedef struct {
    bt_smp_code_t       code;
    bt_smp_key_t         ltk;
}) bt_smp_encryption_info_t;

BT_PACKED(
typedef struct {
    bt_smp_code_t       code;
    uint16_t            ediv;
    uint8_t             rand[8];
}) bt_smp_master_identification_t;

BT_PACKED(
typedef struct {
    bt_smp_code_t       code;
    bt_smp_key_t         irk;
}) bt_smp_identity_info_t;

BT_PACKED(
typedef struct {
    bt_smp_code_t       code;
    bt_addr_t           addr;
}) bt_smp_identity_address_info_t;

BT_PACKED(
typedef struct {
    bt_smp_code_t       code;
    bt_smp_key_t        csrk;
}) bt_smp_signing_info_t;

BT_PACKED(
typedef struct {
    bt_smp_code_t       code;
    bt_gap_le_smp_auth_req_t   auth_req;
}) bt_smp_security_req_t;

BT_PACKED(
typedef struct {
    bt_smp_code_t   code;
    bt_data_t       data;
}) bt_smp_packet_t;

BT_EXTERN_C_END

#endif /* __BT_SMP_DEF_H__ */

