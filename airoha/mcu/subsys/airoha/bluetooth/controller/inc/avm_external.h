/* Copyright Statement:
 *
 * (C) 2019  Airoha Technology Corp. All rights reserved.
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

#ifndef _AVM_EXTERNAL_H_
#define _AVM_EXTERNAL_H_

#include <zephyr/sys/util.h>
#include "bt_type.h"
//<<<=====================================================================>>>//
//<<                            INCLUDE HEADER FILES                       >>//
//<<<=====================================================================>>>//


//<<<=====================================================================>>>//
//<<                            Constant                                  >>//
//<<<=====================================================================>>>//

#ifdef __cplusplus
extern "C" {
#endif

typedef uint32_t BT_MON_MEMORY_TYPE;


/*structure for getting BT clock*/
typedef struct bt_stru_bttime {
    uint32_t period;
    uint16_t phase;
} BT_TIME_STRU, *BT_TIME_STRU_PTR;

#define     BT_MEMORY_TYPE_TX_BUFFER          0      /**< TX packet buffer, a buffer type for the Memory Management module.*/
#define     BT_MEMORY_TYPE_RX_BUFFER          1      /**< RX packet buffer, a buffer type for the Memory Management module.*/
#define     BT_MEMORY_TYPE_CONTROLLER_BUFFER  2      /**< Controller buffer, a buffer type for the Memory Management module.*/
#define     BT_MEMORY_TYPE_RR_BUFFER          3      /**< RR buffer, a buffer type for the Memory Management module.*/
#define     BT_MEMORY_TYPE_STATIC_BUFFER0     4      /**< Static buffer for controller RX buffer0, a buffer type for the Memory Management module.*/
#define     BT_MEMORY_TYPE_STATIC_BUFFER1     5      /**< Static buffer for controller RX buffer1, a buffer type for the Memory Management module.*/
#define     BT_MEMORY_TYPE_STATIC_BUFFER2     6      /**< Static buffer for controller RX buffer2, a buffer type for the Memory Management module.*/
#define     BT_MEMORY_TYPE_TX_BUFFER_POSTPONE 7      /**< TX packet buffer, a buffer type for the Memory Management module.*/
#define     BT_MEMORY_TYPE_CONTROLLER_TCM_BUFFER    8      /**< Controller buffer, a buffer type for the Memory Management module.*/
#define     BT_MEMORY_TYPE_802154_TX_BUFFER         9      /**< 802.15.4 TX packet buffer, a buffer type for the Memory Management module.*/

#define     BT_QUEUE_RX_TYPE                  0
#define     BT_QUEUE_TX_ACL_TYPE              1
#define     BT_QUEUE_TX_CMD_TYPE              2
#define     BT_QUEUE_TX_IF_PACKET_TYPE        3
#define     BT_QUEUE_TX_ISO_TYPE              4


typedef enum {
    BT_MON_MEMORY_TYPE_TX_BUFFER         = (BT_MON_MEMORY_TYPE)BT_MEMORY_TYPE_TX_BUFFER,
    BT_MON_MEMORY_TYPE_RX_BUFFER         = (BT_MON_MEMORY_TYPE)BT_MEMORY_TYPE_RX_BUFFER,
    BT_MON_MEMORY_TYPE_CONTROLLER_BUFFER = (BT_MON_MEMORY_TYPE)BT_MEMORY_TYPE_CONTROLLER_BUFFER,
    BT_MON_MEMORY_TYPE_RR_BUFFER         = (BT_MON_MEMORY_TYPE)BT_MEMORY_TYPE_RR_BUFFER,
    BT_MON_MEMORY_TYPE_STATIC_BUFFER0    = (BT_MON_MEMORY_TYPE)BT_MEMORY_TYPE_STATIC_BUFFER0,
    BT_MON_MEMORY_TYPE_STATIC_BUFFER1    = (BT_MON_MEMORY_TYPE)BT_MEMORY_TYPE_STATIC_BUFFER1,
    BT_MON_MEMORY_TYPE_STATIC_BUFFER2    = (BT_MON_MEMORY_TYPE)BT_MEMORY_TYPE_STATIC_BUFFER2,
    BT_MON_MEMORY_TYPE_TX_BUFFER_POSTPONE = (BT_MON_MEMORY_TYPE)BT_MEMORY_TYPE_TX_BUFFER_POSTPONE,
    BT_MON_MEMORY_TYPE_802154_TX_BUFFER   = (BT_MON_MEMORY_TYPE)BT_MEMORY_TYPE_802154_TX_BUFFER,
    BT_MON_MEMORY_TYPE_NUM,
} bt_mon_memory_type_t;


typedef struct {
    uint16_t race_id;
    uint16_t tag;
    uint32_t native_clock;
    uint32_t native_phase;
    uint32_t dl_src_clock_offset;
    uint32_t dl_src_phase_offset;
    uint32_t valid;
} dchs_pka_latch_info_t;

enum dchs_role_t {
    DCHS_ROLE_NONE,
    DCHS_ROLE_MASTER,
    DCHS_ROLE_SLAVE,
};


#define BT_HCI_CMD_VENDOR_SET_LC_SLP_POLICY    0xFCC2

#define BT_AVM_UNLOCK_SLEEP             (0x00)
#define BT_AVM_LOCK_SLEEP               (0x01)
#define BT_AVM_CHANGE_SLP_POLICY        (0x02)
typedef uint8_t bt_avm_slp_policyctl_t;

#define BT_AVM_DISABLE_SLEEP             (0x00)
#define BT_AVM_ENABLE_SHORT_SLEEP        (0x01)
#define BT_AVM_ENABLE_LIGHT_SLEEP        (0x02)
#define BT_AVM_ENABLE_SOUND_SLEEP        (0x03)
#define BT_AVM_ENABLE_DEEP_SLEEP         (0x04)
typedef uint8_t bt_avm_slp_policy_t;


//<<<=====================================================================>>>//
//<<                            Data Type                                 >>//
//<<<=====================================================================>>>//
typedef struct avm_pka_callbacks {
    unsigned char *(*bt_hb_mm_allocate)(uint8_t type, unsigned int size);
    void (*bt_hb_mm_free)(uint8_t type, unsigned char *ptr);
    void (*bt_hb_rx_enqueue)(unsigned char *hb_header);
    void *(*bt_hb_tx_dequeue)(uint8_t type, unsigned char *q_header);
    unsigned short (*bt_get_hb_header_size)(void);
    void (*bt_rx_notify_hb)(void);
} avm_pka_callbacks_t;

typedef struct stru_gpt_sync_request_info {
    uint8_t  type;
    uint8_t  lens;
    uint16_t reserved;
    uint8_t  data[32];
} GPT_SYNC_REQUEST_INFO_STRU, *GPT_SYNC_REQUEST_INFO_STRU_PTR;


/* GPT sync mechanism for LED */
typedef struct stru_bt_sync_timer_info {
    uint32_t    interval;   /* the interval between each SYNC_INFO */
    uint32_t    n_clk;      /* native timer */
} BT_SYNC_TIMER_INFO_STRU, *BT_SYNC_TIMER_INFO_STRU_PTR;


typedef void (*bt_afh_notification_callback)(unsigned char *avoid_map, uint8_t length);


/* GPT sync callback function pointer
    type : BT_SYNC_TYPE_START, BT_SYNC_TYPE_INFO, BT_SYNC_TYPE_STOP
    aws_flag : gLC_LinkCtrl.AwsCtrl.isSAwsLink
*/
typedef void (*bt_sync_callback_function_t)(uint8_t type, BT_TIME_STRU syncTime, uint32_t gpt_count, uint8_t aws_flag);


BT_PACKED(
typedef struct {
    bt_avm_slp_policyctl_t slp_policyctl;
    bt_avm_slp_policy_t slp_policy;
}) bt_sleep_policy_t;

//<<<=====================================================================>>>//
//<<                           Function Declaration                        >>//
//<<<=====================================================================>>>/ uint16_t length);
void bt_avm_pka_register_callbacks(avm_pka_callbacks_t callbacks);
uint16_t bt_get_pka_header_size(uint8_t type);
void bt_tx_notify_pka(uint8_t type, unsigned char *q_header);
unsigned char bt_pka_get_bt_clock(uint16_t hci_handle, BT_TIME_STRU_PTR current_bt_clk);
unsigned char bt_pka_get_bt_clock_with_gpt(uint16_t hci_handle, \
                                           BT_TIME_STRU_PTR current_bt_clk, uint32_t *gpt);
void pka_request_sync_gpt(GPT_SYNC_REQUEST_INFO_STRU_PTR sync_req_info_ptr, \
                          uint32_t duration, uint32_t timeout);
unsigned char bt_pka_allow_poweroff(void *data);
unsigned char* bt_pka_get_leaudio_AVM_addr(uint16_t size);
unsigned char* bt_pka_get_esco_forwarder_addr(uint16_t size);
uint8_t bt_pka_get_preferred_rate(uint16_t ConnHdl);
void bt_pka_dual_ant_register_callback(bt_afh_notification_callback callback);
uint16_t bt_pka_get_acl_queue_entries(uint16_t handle);
void bt_pka_set_no_retransmission_mode(uint16_t seq_num, uint16_t length);
uint8_t bt_pka_get_no_retransmission_mode_status();
void bt_pka_enable_power_control(uint8_t enable);
char *bt_pikachu_lib_verno(void);
char *bt_pikachu_lib_lastest_commit(void);
void bt_driver_airoha_get_loacl_addr(bt_bd_addr_t *addr);
int bt_set_controller_sleep_policy(bt_sleep_policy_t *policy);
bt_status_t bt_set_controller_sleep_policy_direct(bt_sleep_policy_t *policy);

// @input : hci handle, a2dp l2cap channel, start_suspend
// @output 1 : success, 0 : fail
uint8_t bt_pka_set_a2dp_handle_channel(uint16_t handle, uint16_t a2dp_channel, uint8_t start_suspend);

// @input : N/A
// @output 1 : success, 0 : fail
uint8_t bt_pka_set_pause_sync(void);

// @input : N/A
// @output 1 : success, 0 : fail
uint8_t bt_pka_set_restart_sync(void);

uint16_t bt_pka_get_acl_queue_entries(uint16_t handle);

// @input : user, LED for 0
// @input : callback
// @input : interval, the interval between sync info callback
uint8_t bt_pka_sync_register_callback(uint8_t user, bt_sync_callback_function_t callback, uint32_t interval);

//<<<=====================================================================>>>//
//<<                           External Reference                          >>//
//<<<=====================================================================>>>//
extern avm_pka_callbacks_t avm_callbacks;

//<<<=====================================================================>>>//
//<<                          External Function Reference                 >>//
//<<<=====================================================================>>>//
extern void *pka_init_osmem_blk(void *pStart, uint32_t RealBlkSize, uint32_t MemoryType, uint32_t Caller);
extern void bt_hci_notify_pka(void *ptr, uint8_t MsgType);


//<<<=====================================================================>>>//
//<<                            MACRO                                     >>//
//<<<=====================================================================>>>//

#ifdef __cplusplus
}
#endif

#endif // _AVM_EXTERNAL_H_

