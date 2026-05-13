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

#ifndef __BT_L2CAP_SPEC_H__
#define __BT_L2CAP_SPEC_H__

BT_EXTERN_C_BEGIN

#define BT_L2CAP_CHANNEL_ATT                    0x0004
#define BT_L2CAP_CHANNEL_SIGNAL                 0x0005
#define BT_L2CAP_CHANNEL_SMP                    0x0006
#define BT_L2CAP_CHANNEL_BREDR_SMP              0x0007

#ifdef BT_EATT_ENABLE
#define BT_L2CAP_CHANNEL_FIXED_MAX              0x003F
#endif

#define BT_L2CAP_CMD_COMMAND_REJECT             0x01
#define BT_L2CAP_CMD_DISCONNECTION_REQ          0x06
#define BT_L2CAP_CMD_DISCONNECTION_RSP          0x07
#define BT_L2CAP_CMD_CONN_PARAM_UPDATE_REQ      0x12
#define BT_L2CAP_CMD_CONN_PARAM_UPDATE_RSP      0x13
#define BT_L2CAP_CMD_LE_CREDIT_BASED_CONN_REQ   0x14
#define BT_L2CAP_CMD_LE_CREDIT_BASED_CONN_RSP   0x15
#define BT_L2CAP_CMD_LE_FLOW_CONTROL_CREDIT     0x16
#ifdef BT_EATT_ENABLE
#define BT_L2CAP_CMD_FLOW_CONTROL_CREDIT_IND    BT_L2CAP_CMD_LE_FLOW_CONTROL_CREDIT
#define BT_L2CAP_CMD_CREDIT_BASED_CONN_REQ      0x17
#define BT_L2CAP_CMD_CREDIT_BASED_CONN_RSP      0x18
#define BT_L2CAP_CMD_CREDIT_BASED_RECONFIG_REQ  0x19
#define BT_L2CAP_CMD_CREDIT_BASED_RECONFIG_RSP  0x1A

#define BT_L2CAP_CREDIT_BASED_CONN_CMD_MAX_CID_NUM      5
#endif

#ifdef __BT_HB_DUO__
/*
 * -- L2CAP Signal command Codes --------------------------------------------
 * The opcodes of the respective L2CAP signalling commands.
 * The codes 0x01 through 0x0B are also used as events to the L2CAP state machine.
 */
#define BT_L2CAP_CMD_REJECT                     0x01
#define BT_L2CAP_CMD_CONN_REQ                   0x02
#define BT_L2CAP_CMD_CONN_RSP                   0x03
#define BT_L2CAP_CMD_CONFIG_REQ                 0x04
#define BT_L2CAP_CMD_CONFIG_RSP                 0x05
#define BT_L2CAP_CMD_ECHO_REQ                   0x08
#define BT_L2CAP_CMD_ECHO_RSP                   0x09
#define BT_L2CAP_CMD_INFO_REQ                   0x0A
#define BT_L2CAP_CMD_INFO_RSP                   0x0B
#endif
typedef uint8_t bt_l2cap_cmd_opcode_t;

#define BT_L2CAP_CONNECTION_UPDATE_ACCEPT       0x0000
#define BT_L2CAP_CONNECTION_UPDATE_REJECT       0x0001
typedef uint16_t bt_l2cap_connection_update_result_t;

#define BT_L2CAP_CMD_REJ_COMMAND_NOT_UNDERSTAND 0x0000
#define BT_L2CAP_CMD_REJ_SIGNALING_MTU_EXCEEDED 0x0001
#define BT_L2CAP_CMD_REJ_INVALID_CID_IN_REQ     0x0002
typedef uint16_t bt_l2cap_command_reject_reason_t;

#define BT_L2CAP_CONFIG_QOS_TYPE_NO_TRAFFIC    0x00
#define BT_L2CAP_CONFIG_QOS_TYPE_BEST_EFFORT   0x01 /*Default*/
#define BT_L2CAP_CONFIG_QOS_TYPE_GUARANTEED    0x02


/* L2cap signaling command structure */
#ifdef BT_EATT_ENABLE
BT_PACKED(
typedef struct {
    uint16_t        spsm;
    uint16_t        source_cid;
    uint16_t        mtu;
    uint16_t        mps;
    uint16_t        initial_credits;
}) bt_l2cap_cmd_le_credit_based_conn_req_t;

BT_PACKED(
typedef struct {
    uint16_t        destination_cid;
    uint16_t        mtu;
    uint16_t        mps;
    uint16_t        initial_credits;
    uint16_t        result;
}) bt_l2cap_cmd_le_credit_based_conn_rsp_t;

BT_PACKED(
typedef struct {
    uint16_t        cid;
    uint16_t        credits;
}) bt_l2cap_cmd_flow_control_credit_ind_t;


BT_PACKED(
typedef struct {
    uint16_t        spsm;
    uint16_t        mtu;
    uint16_t        mps;
    uint16_t        initial_credits;
    uint16_t        source_cid[BT_L2CAP_CREDIT_BASED_CONN_CMD_MAX_CID_NUM];
}) bt_l2cap_cmd_credit_based_conn_req_t;

BT_PACKED(
typedef struct {
    uint16_t        mtu;
    uint16_t        mps;
    uint16_t        initial_credits;
    uint16_t        result;
    uint16_t        destination_cid[BT_L2CAP_CREDIT_BASED_CONN_CMD_MAX_CID_NUM];
}) bt_l2cap_cmd_credit_based_conn_rsp_t;

BT_PACKED(
typedef struct {
    uint16_t        mtu;
    uint16_t        mps;
    uint16_t        destination_cid[BT_L2CAP_CREDIT_BASED_CONN_CMD_MAX_CID_NUM];
}) bt_l2cap_cmd_credit_based_reconfig_req_t;

BT_PACKED(
typedef struct {
    uint16_t        result;
}) bt_l2cap_cmd_credit_based_reconfig_rsp_t;
#endif

BT_PACKED(
typedef struct {
    bt_l2cap_command_reject_reason_t    reason;
    BT_PACKED(union{
        uint16_t    actual_mtu;
        uint32_t    requested_cid;
    });
}) bt_l2cap_cmd_command_reject_t;

BT_PACKED(
typedef struct {
    uint16_t        interval_min;
    uint16_t        interval_max;
    uint16_t        slave_latency;
    uint16_t        timeout_multiplier;
}) bt_l2cap_cmd_conn_param_update_req_t;

BT_PACKED(
typedef struct {
    bt_l2cap_connection_update_result_t result;
}) bt_l2cap_cmd_conn_param_update_rsp_t;

BT_PACKED(
typedef struct {
    uint16_t       destination_cid;
    uint16_t       source_cid;
}) bt_l2cap_cmd_disconnect_req_rsp_t;


/* L2cap signaling cmd format */
typedef struct {
    bt_l2cap_cmd_opcode_t   opcode;
    uint8_t         identifier;
    uint16_t        length;
    const void      *data;
} bt_l2cap_cmd_t;

#ifdef __BT_HB_DUO__
BT_PACKED(
typedef struct {
    uint16_t        psm;
    uint16_t        source_cid;
}) bt_l2cap_cmd_conn_req_t;

BT_PACKED(
typedef struct {
    uint16_t       destination_cid;
    uint16_t       source_cid;
    uint16_t       result;
    uint16_t       status;
}) bt_l2cap_cmd_conn_rsp_t;

BT_PACKED(
typedef struct {
    uint8_t       type;
    uint8_t       length;
    uint16_t      mtu;
}) bt_l2cap_cmd_config_mtu_t;

BT_PACKED(
typedef struct {
    uint8_t    type;
    uint8_t    length;
    uint8_t    mode;
    uint8_t    tx_window_size;
    uint8_t    max_transmit;
    uint16_t   retransmission_timeout;
    uint16_t   monitor_timeout;
    uint16_t   maximum_pdu_size;
}) bt_l2cap_cmd_config_flow_control_t;

BT_PACKED(
typedef struct {
    uint8_t       type;
    uint8_t       length;
    uint8_t      fcs_type;
}) bt_l2cap_cmd_config_fcs_t;

BT_PACKED(
typedef struct {
    uint8_t       type;
    uint8_t       length;
    uint8_t       mhdt_support;
}) bt_l2cap_cmd_config_mhdt_t;

BT_PACKED(
typedef struct {
    uint8_t       type;
    uint8_t       length;
    uint8_t       flags;
    uint8_t       service_type;
    uint32_t      token_rate;
    uint32_t      token_bucket_size; //octets
    uint32_t      peak_bandwidth; //octets/second
    uint32_t      latency; //microseconds
    uint32_t      delay_variation; //microseconds
}) bt_l2cap_cmd_config_qos_t;


BT_PACKED(
typedef struct {
    uint16_t       destination_cid;
    uint16_t       flags;
    const void     *config_option;
}) bt_l2cap_cmd_config_req_t;

BT_PACKED(
typedef struct {
    uint16_t       source_cid;
    uint16_t       flags;
    uint16_t       result;
    const void     *config_option;
}) bt_l2cap_cmd_config_rsp_t;

BT_PACKED(
typedef struct {
    const void     *data;
}) bt_l2cap_cmd_echo_req_rsp_t;

BT_PACKED(
typedef struct {
    uint16_t       info_type;
}) bt_l2cap_cmd_information_req_t;

BT_PACKED(
typedef struct {
    uint16_t       info_type;
    uint16_t       result;
    const void     *data;
}) bt_l2cap_cmd_information_rsp_t;



BT_PACKED(
typedef struct {
    BT_PACKED(union{
        BT_PACKED(struct {
            uint16_t frame_type: 1;
            uint16_t tx_seq: 6;
            uint16_t f_bit: 1;
            uint16_t req_seq: 6;
            uint16_t sar: 2;
        }) i_frame;
        BT_PACKED(struct {
            uint16_t frame_type: 1;
            uint16_t reserve_1: 1;
            uint16_t type: 2;
            uint16_t p_bit: 1;
            uint16_t reserve_2: 2;
            uint16_t f_bit: 1;
            uint16_t req_seq: 6;
            uint16_t reserve_3: 2;
        }) s_frame;
    });
}) bt_l2cap_ertm_enhanced_control_field_t;


BT_PACKED(
typedef struct {
    bt_l2cap_ertm_enhanced_control_field_t control_field;
    BT_PACKED(union{
        BT_PACKED(struct {
            uint16_t SDU_length;
            const void     *data;
        }) sar_start;
        BT_PACKED(struct {
            const void     *data;
        }) sar_others;
    });
}) bt_l2cap_ertm_i_frame_t;

BT_PACKED(
typedef struct {
    bt_l2cap_ertm_enhanced_control_field_t control_field;
}) bt_l2cap_ertm_s_frame_t;



#endif

BT_EXTERN_C_END

#endif /* __BT_L2CAP_SPEC_H__ */

