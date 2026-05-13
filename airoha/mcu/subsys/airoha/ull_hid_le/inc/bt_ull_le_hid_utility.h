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

#ifndef __BT_ULL_LE_HID_UTILITY_H__
#define __BT_ULL_LE_HID_UTILITY_H__

#include "bt_ull_le_hid_device_manager.h"
#include "bt_ull_le_hid_service.h"

#define BT_ULL_LE_HID_EVENT_USER_DATA               (0x0C)
#define BT_ULL_LE_HID_MSG_RESPONSE                  (0x30)
#define BT_ULL_LE_HID_MSG_SERVICE_CONNECT_REQ       (0x31)
#define BT_ULL_LE_HID_MSG_SYNC_CONTEXT_INFO         (0x32)
#define BT_ULL_LE_HID_MSG_BONDING_REQ               (0x33)
#define BT_ULL_LE_HID_MSG_SYNC_BONDING_INFO         (0x34)
#define BT_ULL_LE_HID_MSG_SWITCH_LINK_MODE          (0x35)
#define BT_ULL_LE_HID_MSG_INPUT_REPORT_DATA         (0x36)
#define BT_ULL_LE_HID_MSG_RACE_DATA                 (0x37)
#define BT_ULL_LE_HID_MSG_OUT_PUT_DATA              (0x38)
typedef uint8_t bt_ull_le_hid_srv_msg_t;

#define BT_ULL_LE_HID_SRV_RSP_STATUS_SUCCESS        (0x00)
#define BT_ULL_LE_HID_SRV_RSP_STATUS_FAIL           (0x01)
typedef uint8_t bt_ull_le_hid_srv_rsp_status_t;

typedef struct {
    uint8_t     uni_aa[BT_ULL_LE_HID_DM_UNI_AA_LEN];
    uint8_t     ltk[BT_ULL_LE_HID_DM_LTK_LEN];
    uint8_t     skd[BT_ULL_LE_HID_DM_SKD_LEN];
    uint8_t     iv[BT_ULL_LE_HID_DM_IV_LEN];
    bt_ull_le_hid_srv_app_scenario_t        scenario;
    bt_ull_le_hid_srv_report_rate_level_t   report_rate;
    bt_ull_le_srv_phy_t                     phy;
} __packed bt_ull_le_hid_srv_bonding_info_t;

typedef struct {
    struct bt_conn                          *conn;
    uint16_t                                acl_handle;
    uint16_t                                att_handle_rx;
    uint16_t                                att_handle_tx;
    uint16_t                                att_handle_cccd;
    bt_ull_le_hid_srv_link_mode_t           mode;
    int                                     state;
    bt_ull_le_hid_srv_device_t              device_type;
    bt_addr_le_t                            peer_addr;
} bt_ull_le_hid_srv_link_info_t;

typedef struct {

} bt_ull_le_hid_srv_mouse_contex_t;

typedef struct {

} bt_ull_le_hid_srv_keyboard_contex_t;

typedef struct {

} bt_ull_le_hid_srv_gamped_contex_t;

typedef struct {
    bool                                         initialized;
    bt_ull_role_t                                role;
    bt_ull_le_hid_srv_device_t                   device_type;
    bt_ull_le_hid_srv_app_scenario_t             scenario;
    bt_ull_le_hid_srv_idle_time_t                idle_time;
    bt_ull_le_hid_srv_keyboard_contex_t          keyboard;
    bt_ull_le_hid_srv_mouse_contex_t             mouse;
    bt_ull_le_hid_srv_gamped_contex_t            gamepad;
    bt_ull_le_hid_srv_report_rate_t              report_rate;
    bt_ull_le_hid_srv_link_info_t                link[BT_ULL_LE_HID_SRV_MAX_LINK_NUM];
} bt_ull_le_hid_srv_context_t;

typedef struct {
    uint8_t            reseved_1;
    uint8_t            reseved_2;
    uint8_t            reseved_3;
    bt_addr_le_t       local_addr;
} __packed bt_ull_le_hid_srv_keyboard_context_info_t;

typedef struct {
    uint8_t            reseved_1;
    uint8_t            reseved_2;
    uint8_t            reseved_3;
    bt_addr_le_t       local_addr;
} __packed bt_ull_le_hid_srv_mouse_context_info_t;

typedef struct {
    uint8_t            reseved_1;
    uint8_t            reseved_2;
    uint8_t            reseved_3;
    bt_addr_le_t       local_addr;
} __packed bt_ull_le_hid_srv_gamepad_context_info_t;

typedef struct {
    union {
        bt_ull_le_hid_srv_keyboard_context_info_t       keyboard_info;
        bt_ull_le_hid_srv_mouse_context_info_t          mouse_info;
        bt_ull_le_hid_srv_gamepad_context_info_t        gamepad_info;
    } info;
} __packed bt_ull_le_hid_srv_context_info_req_t;

typedef struct {
    uint8_t     device_type;
} __packed bt_ull_le_hid_srv_connect_rsp_t;

typedef struct {
    uint8_t     device_type;
} __packed bt_ull_le_hid_srv_bonding_info_rsp_t;

typedef struct {
    uint16_t           att_handle_rx;
    uint16_t           att_handle_tx;
    uint16_t           att_handle_cccd;
    bt_addr_le_t       local_addr;
} __packed bt_ull_le_hid_srv_keboard_context_info_rsp_t,
bt_ull_le_hid_srv_mouse_context_info_rsp_t,
bt_ull_le_hid_srv_gamepad_context_info_rsp_t;

typedef struct {
    uint8_t     cmd_id;
    uint8_t     status; /* success: 0,  fail: other*/
    union {
        bt_ull_le_hid_srv_connect_rsp_t                   connect_rsp;
        bt_ull_le_hid_srv_bonding_info_rsp_t              bonding_rsp;
        bt_ull_le_hid_srv_keboard_context_info_rsp_t      keboard_context_info_rsp;
        bt_ull_le_hid_srv_mouse_context_info_rsp_t        mouse_context_info_rsp;
        bt_ull_le_hid_srv_gamepad_context_info_rsp_t      gamepad_context_info_rsp;
    } param;
} bt_ull_le_hid_srv_rsp_t;

typedef struct {
    bt_ull_le_hid_srv_link_mode_t mode;
} __packed bt_ull_le_hid_srv_change_link_req_t;

void *bt_ull_le_srv_memcpy(void *dest, const void *src, uint32_t size);
void *bt_ull_le_srv_memory_alloc(uint16_t size);
void bt_ull_le_srv_memory_free(void *point);
void *bt_ull_le_srv_memset(void *buf, uint8_t value, uint32_t size);
int32_t bt_ull_le_srv_memcmp(const void *buf1, const void *buf2, uint32_t size);
int bt_ull_le_bytes_from_str(uint8_t *buf, int buf_len, const char *src);

#endif

