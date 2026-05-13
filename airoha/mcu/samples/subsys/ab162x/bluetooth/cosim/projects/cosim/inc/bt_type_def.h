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

#ifndef __BT_TYPE_DEF_H__
#define __BT_TYPE_DEF_H__

#include <stdio.h>
#include <stddef.h>

#include "bt_config.h"
#include "bt_platform_internal.h"

#include "bt_linknode.h"

#include "bt_type.h"
#include "bt_system.h"

struct _bt_connection_t;

/* Start of profile type. */
#include "bt_hci_def.h"
#include "bt_smp_def.h"
#include "bt_gap_le.h"
#include "bt_gap.h"
#include "bt_uuid.h"
/* End of profile type. */

typedef uint8_t bt_l2cap_pdu_packet_t;
typedef bt_l2cap_pdu_packet_t bt_att_packet_t;
typedef uint8_t bt_gap_bonding_status_t;
typedef uint8_t bt_gap_bonding_type_t;
typedef struct _bt_gap_connection_t bt_gap_connection_t;

#define BT_GAP_LINK_TYPE_SCO     0x00   /**< SCO link type. */
#define BT_GAP_LINK_TYPE_EDR     0x01   /**< EDR link type. */
#define BT_GAP_LINK_TYPE_ESCO    0x02   /**< ESCO link type. */
#define BT_GAP_LINK_TYPE_LE      0x04   /**< LE link type. */
#define BT_GAP_LINK_TYPE_UNKNOW  0xFF   /**< Un-know link type. */
typedef uint8_t bt_gap_link_type_t;     /**< Link types. */

#define BT_GAP_SCO_STATUS_INACTIVE       0
#define BT_GAP_SCO_STATUS_ACTIVE         1
typedef uint8_t bt_gap_sco_status_t;

typedef enum {
    BT_GAP_SCO_EVT_CONNECTED = 1,
    BT_GAP_SCO_EVT_PARAM_REQ,
    BT_GAP_SCO_EVT_DISCONNECTED,
    BT_GAP_SCO_EVT_INACTIVE,
    BT_GAP_SCO_EVT_ACTIVE,
    BT_GAP_SCO_EVT_CONNECT_FAIL,
    BT_GAP_SCO_EVT_REQUEST
} bt_gap_sco_evt_t;


typedef enum {
    BT_QUEUE_TYPE_RX = 0,
    BT_QUEUE_TYPE_TX_ACL,
    BT_QUEUE_TYPE_TX_CMD,
    BT_QUEUE_TYPE_TX_IF_PACKET
} bt_hb_queue_type_t;


/* L2CAP structure */
BT_PACKED(
typedef struct {
    uint16_t    length;
    uint16_t    channel;
    bt_data_t   data;
}) bt_l2cap_packet_t;

BT_PACKED(
typedef struct {
    uint8_t att_op_code;                        /* E.g. #BT_ATT_OPCODE_ERROR_RESPONSE. */
    uint32_t gatt_op_code;                      /* E.g. #BT_GATTC_DISCOVER_PRIMARY_SERVICE. */
    uint16_t gatt_mtu;                          /* ATT MTU */
#ifdef BT_EATT_ENABLE
    uint16_t att_cid;                           /* ATT channel id, would be 0x0004 for ATT and dynamically allocated value for EATT*/
#endif
    bt_uuid_t uuid;                             /* Used when invoke #bt_gattc_discover_primary_service_by_uuid or #bt_gattc_discover_charc */
    uint16_t attribute_handle;                  /* Used when invoke #bt_gattc_read_charc or #bt_gattc_read_long_charc */
    uint16_t starting_handle;                   /* Used when #bt_gatt_rx_proc_read_by_type_rsp or #bt_gatt_rx_proc_read_rsp */
    uint16_t ending_handle;                     /* Used when #bt_gattc_discover_charc or #bt_gattc_discover_charc_descriptor */
    uint16_t find_included_srv_ending_handle;   /* Used when #bt_gattc_find_included_services */
    uint16_t offset;                            /* Used when #bt_gattc_prepare_write_charc */
    uint16_t write_attribute_value_length;      /* Used when #bt_gattc_prepare_write_charc */
    uint8_t *write_attribute_value;             /* Used when #bt_gattc_prepare_write_charc */
}) bt_att_t;

BT_PACKED(
typedef struct {
    uint8_t signaling_identifier;
    bt_att_t bt_att;
}) bt_l2cap_t;

typedef struct _bt_tx_queue_t {
    bt_linknode_t next_node;                  /* link the tx queue to hci circular queue */
    bt_linknode_t queue;                      /* tx packets to be send */
    uint16_t    unacked_nocp;                 /* un-acknoledge count */
    uint8_t     priority;                     /* future use */
} bt_tx_queue_t;

typedef struct {
    bt_hci_le_packet_t *rx_pending;
    uint16_t cmd_credit; /* Max 1 credit for commands. */
    uint16_t acl_credit;
    uint16_t acl_packet_length;
    uint16_t acl_le_credit;
    uint16_t acl_le_packet_length;
    uint16_t cmd_flow_control; /*acl credit is not enough*/
    uint16_t acl_flow_control; /*cmd credit is not enough*/
} bt_hci_t;

#define BT_GAP_ADV_TERMINATE                    (0x1 << 0)
#define BT_GAP_READ_REMOTE_FEATURE_CPMPLETE     (0x1 << 1)
typedef uint8_t bt_gap_le_status_mask;

typedef struct _bt_connection_t {
    bt_linknode_t next_node;
    bt_handle_t handle;
    bt_gap_le_bonding_info_t   *bonding_info;
    // bt_hci_le_packet_t *tx_pending;
    bt_tx_queue_t tx_con_queue;
    bt_role_t   role;
    bt_gap_le_security_mode_t  security_mode; /* Bitwise combination of BT_GAP_LE_SERCURITY_XXXX_MASK. */
    bt_gap_le_status_mask      status_mask;
    bt_addr_t   local_addr;
    bt_addr_t   peer_addr;
    bt_addr_t   local_ll_addr;  /* For SM pairing. */
    bt_addr_t   peer_ll_addr;   /* For SM pairing. */
//   uint16_t tx_pending_l2cap_size;
    bt_l2cap_t  l2cap;
    bt_hci_le_packet_t *rx_pending; /*use for assembling packet*/
    void *conn_ind_buffer;
    uint8_t support_features[8];
#ifdef __BT_HB_DUO__
    bool is_ltk_to_link_key;       /* remote device and local will generate link key */
    uint8_t key_info;                      /* remote device and local support h7*/
    bool is_allowed_rho;
#endif //__BT_HB_DUO__
    bool is_connected;
} bt_connection_t;


typedef struct {
    bt_connection_t  *le_connection;
    union {
        bt_smp_pairing_req_t    pairing_req;
        bt_smp_security_req_t   security_req;
    };
} bt_smp_wl_context_t;

#define BT_EXT_LE_ADV_STATE_STOPED      0x00
#define BT_EXT_LE_ADV_STATE_STARTED     0x01
#define BT_EXT_LE_ADV_STATE_STARTING    0x02
#define BT_EXT_LE_ADV_STATE_STOPING     0x03
typedef uint8_t bt_ext_le_adv_state_t;

typedef struct _bt_le_adv_set_t {
    bt_linknode_t   next_node;
    uint8_t         handle;
    bt_bd_addr_t    random_address;
    bt_addr_type_t  address_type;
    bt_ext_le_adv_state_t adv_enable;
    bt_ext_le_adv_state_t periodic_adv_enable;
} bt_le_adv_set_t;

#define BT_CONTROLLER_SPEC_VER_4_2 0x00
#define BT_CONTROLLER_SPEC_VER_5_0 0x01
#define BT_CONTROLLER_SEPC_VER_5_0_DISABLE_ADV      0x10
#define BT_CONTROLLER_SEPC_VER_5_0_DISABLE_PER_ADV  0x20
#define BT_CONTROLLER_SEPC_VER_5_0_DISABLE_SCAN     0x40
#define BT_CONTROLLER_SEPC_VER_5_0_DISABLE_CONN     0x80
typedef uint8_t bt_controller_spec_ver_t;

#define BT_COMPATIBLE_TYPE_NONE      0x00
#define BT_COMPATIBLE_TYPE_LEGACY    0x01
#define BT_COMPATIBLE_TYPE_MULTIPLE  0x02
#define BT_COMPATIBLE_TYPE_EXTENDED  0x03
typedef uint8_t bt_compatible_t;

#define BT_SNIFF_MASK_DISABLE_NONE       0x00
#define BT_SNIFF_MASK_DISABLE_SNIFF      0x01
#define BT_SNIFF_MASK_DISABLE_SNIFF_SUB  0x02
typedef uint8_t bt_sniff_mask_t;

BT_PACKED(
typedef struct {
    uint32_t transmit_band_with;
    uint32_t receive_band_with;
    uint16_t max_latency;
    uint16_t voice_setting;
    uint8_t  retransmission_effort;
    uint16_t packet_type;
    uint8_t       tx_coding_format_byte_0;             //for esco only
    uint32_t      tx_coding_format_byte_1_4;           //for esco only
    uint8_t       rx_coding_format_byte_0;             //for esco only
    uint32_t      rx_coding_format_byte_1_4;           //for esco only
}) bt_gap_accept_sco_params_t;

typedef struct {
    bt_gap_connection_t             *connection;
    bt_hci_le_packet_t              *bonding_packet;
    uint32_t                         confirm_value;
    bt_gap_oob_data_presented_t      oob_present;
    bt_gap_security_auth_request_t   auth_request;
    uint8_t                          timer_op;
    bt_gap_io_capability_t           local_io_capability;
    bt_gap_pin_code_information_t    pin_code;
} bt_gap_bonding_session_t;

typedef struct {
    bt_gap_connection_t     *connection;
    uint32_t                 op_data;
    bt_hci_le_packet_t      *send_buffer;
} bt_gap_connection_operation_info_t;

typedef struct {
    bt_gap_connection_t    *bt_connection;
    bt_handle_t             handle;
    bt_gap_link_type_t      sco_type;
    uint8_t                 disconn_acl;
    bt_gap_sco_status_t     active;
    uint8_t                 air_mode;
} bt_gap_sco_link_t;

typedef struct {
    bt_bd_addr_t           *address;
    bt_handle_t             handle;
    bt_gap_link_type_t      sco_type;
    bt_gap_sco_status_t     active;
    uint8_t                 air_mode;
} bt_gap_sco_info_t;

typedef struct {
    bt_bd_addr_t            address;
    bt_handle_t             handle;
} bt_gap_conn_info_t;

#ifdef BT_LE_AUDIO_ENABLE
typedef struct {
    bt_linknode_t next_node;
    bt_handle_t cis_handle;
} bt_cis_connection_t;
#endif

typedef void (*bt_gap_sco_callback_t)(bt_gap_sco_evt_t evt, const bt_gap_sco_info_t *sco_status, bt_gap_accept_sco_params_t *param);

typedef struct {
    bt_hci_t        hci;
    bt_bd_addr_t    local_public_addr;
    bt_bd_addr_t    local_random_addr;
    bt_addr_type_t  slave_addr_type;    /* Only valid if advertising is enabled. */
    bt_addr_type_t  master_addr_type;   /* Only valid if connection is creating. */
    bt_gap_le_local_key_t  *local_key;
    bt_linknode_t   le_connection;
#ifdef BT_LE_AUDIO_ENABLE
    bt_linknode_t   cis_connection;
#endif
    bt_sm_session_t sm_session;
    uint8_t         *buffer;
    uint8_t         *scan_buffer;
#ifdef BT_LE_AUDIO_ENABLE
    uint8_t         *conn_ind_buffer;
#endif
    uint16_t        gatt_max_mtu;
    uint8_t         sc_only_mode;       /* Secure Connection Only Mode */
    uint8_t         max_adv_instance;   /* The max count of multi-adv instance */
    uint8_t         *reconn_buffer;     /* Buffer to reconnect after 0x3E connection failed. */
    bool            sdps_database_state_update_flag;  /* True when database state need to be updated. */
    uint16_t        adv_le_data_length;
    bt_linknode_t   adv_sets;           /* The list of all adv set .*/
    uint8_t         adv_set_allocater[32];   /* Advertiser set allocater.*/
    bt_controller_spec_ver_t controller_spec_ver; /* Record the supported bluetooth specification version by controller. */
    bt_compatible_t scan_type;
    bt_compatible_t adv_type;
    bool            vcore_lock_1P1;
    bt_init_feature_mask_t feature_mask;
    bt_smp_wl_context_t    smp_wl;
#ifdef __BT_HB_DUO__
    bt_linknode_t                         bt_connection;
    bt_gap_sco_link_t                     bt_sco_link[2]; /* support 2 sco link */
    bt_gap_bonding_session_t              bt_bonding_info;
    const bt_gap_config_t                *bt_configuration;
    bt_gap_connection_operation_info_t    pending_op;
    bt_sniff_mask_t                       sniff_disable_mask;   /* Whether the device can enter sniff mode or Whether the host can trigger enter sniff subrating mode*/
    bool                                  wb_scan;
    uint8_t                               aws_role_mask;
    bt_gap_conn_info_t                    last_bt_conn;
#endif
    bt_linknode_t  module_free_handle_list; /*For each module hanlde something when task fress*/
} bt_hummingbird_t;

typedef bt_status_t (*bt_module_free_handle_callback_t)(void *ptr);
typedef struct {
    bt_linknode_t  free_handle_list;
    bt_module_free_handle_callback_t callback;
} bt_module_free_handle_list_t;

#endif /*__BT_TYPE_DEF_H__*/

