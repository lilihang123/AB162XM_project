/* Copyright Statement:
 *
 * (C) 2025  Airoha Technology Corp. All rights reserved.
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
 * THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("AIROHA SOFTWARE")
 * RECEIVED FROM AIROHA AND/OR ITS REPRESENTATIVES ARE PROVIDED
 * TO RECEIVER ON AN "AS-IS" BASIS ONLY. AIROHA EXPRESSLY DISCLAIMS ANY AND ALL
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

#ifndef __HID_SCENARIO_LE_GAMEPAD_H__
#define __HID_SCENARIO_LE_GAMEPAD_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

//#define HID_SCENARIO_LE_GAMEPAD_INTERNAL_HOGP

typedef struct {
    uint16_t    bcd_hid;
    uint8_t     b_country_code;
    bool        remote_wake_up;
    bool        normal_connect;
    uint8_t     report_id;
    uint8_t*    hid_report_map;
    uint32_t    hid_report_map_size;
} hid_scenario_le_gamepad_init_param_t;

#ifdef HID_SCENARIO_LE_GAMEPAD_INTERNAL_HOGP
ssize_t hid_scenario_le_gamepad_info(struct bt_conn *conn, const struct bt_gatt_attr *attr, void *buf, uint16_t len, uint16_t offset);
ssize_t hid_scenario_le_gamepad_report_map(struct bt_conn *conn, const struct bt_gatt_attr *attr, void *buf, uint16_t len, uint16_t offset);
ssize_t hid_scenario_le_gamepad_ctrl_point(struct bt_conn *conn, const struct bt_gatt_attr *attr, void *buf, uint16_t len, uint16_t offset);
void    hid_scenario_le_gamepad_init(hid_scenario_le_gamepad_init_param_t* init_param);
void    hid_scenario_le_gamepad_enable(void);
void    hid_scenario_le_gamepad_disable(void);
#endif
ssize_t hid_scenario_le_gamepad_read_empty(struct bt_conn *conn, const struct bt_gatt_attr *attr, void *buf, uint16_t len, uint16_t offset);
ssize_t hid_scenario_le_gamepad_report_ref(struct bt_conn *conn, const struct bt_gatt_attr *attr, void *buf, uint16_t len, uint16_t offset);
ssize_t hid_scenario_le_gamepad_report_ref1(struct bt_conn *conn, const struct bt_gatt_attr *attr, void *buf, uint16_t len, uint16_t offset);
ssize_t hid_scenario_le_gamepad_report_ref2(struct bt_conn *conn, const struct bt_gatt_attr *attr, void *buf, uint16_t len, uint16_t offset);
ssize_t hid_scenario_le_gamepad_report_ref3(struct bt_conn *conn, const struct bt_gatt_attr *attr, void *buf, uint16_t len, uint16_t offset);
void    hid_scenario_le_gamepad_cccd(const struct bt_gatt_attr *attr, uint16_t value);
ssize_t hid_scenario_le_gamepad_write1(struct bt_conn *conn, const struct bt_gatt_attr *attr, const void *buf,uint16_t len, uint16_t offset, uint8_t flags);
ssize_t hid_scenario_le_gamepad_write2(struct bt_conn *conn, const struct bt_gatt_attr *attr, const void *buf,uint16_t len, uint16_t offset, uint8_t flags);
void game_controller_bt_mode_hw_trigger_enable(void);
#ifdef __cplusplus
}
#endif
#endif /* __HID_SCENARIO_LE_GAMEPAD_H__ */