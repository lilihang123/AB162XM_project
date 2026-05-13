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
 

#ifndef __HID_RACE_CMD_H__
#define __HID_RACE_CMD_H__

#include "hid_race_cmd_event.h"

#define ADDR_OFFSET    1
#define UNI_AA_OFFSET  8
#define LTK_OFFSET    12
#define SKD_OFFSET    28
#define IV_OFFSET     44

/******************************************************************************/
/* typedef                                                                    */
/******************************************************************************/
typedef void (* hid_race_cmd_callback)(uint16_t race_cmd_id, uint8_t *para, uint16_t len);

/******************************************************************************/
/* variables                                                                  */
/******************************************************************************/



/******************************************************************************/
/* functions                                                                  */
/******************************************************************************/
uint8_t hid_race_cmd_init(hid_race_cmd_callback cb);
void hid_race_cmd_request(uint16_t race_cmd_id, uint8_t *para, uint16_t length);
void hid_race_set_report_rate_rsp(uint8_t rsp_status);
void hid_race_get_report_rate_rsp(uint16_t report_rate);
race_errcode_enum hid_race_set_rgb_rsp(uint8_t rsp_status);
void hid_race_set_uniaa_rsp(uint8_t rsp_status);

race_errcode_enum hid_race_set_report_rate_req(uint16_t report_rate);
race_errcode_enum hid_race_get_uniaa_rsp(uint8_t *info);
void hid_race_enable_key_event_rsp(uint8_t rsp_status);
race_errcode_enum hid_race_set_dpi_value_req(uint16_t x_dpi, uint16_t y_dpi);
void hid_race_set_profile_rsp(uint8_t rsp_status);
void hid_race_get_profile_rsp(uint8_t profile_idx);
void hid_race_set_debounce_rsp(uint8_t rsp_status);
void hid_race_get_debounce_rsp(uint8_t debounce_time);
void hid_race_set_restore_rsp(uint8_t rsp_status);
void hid_race_get_battery_rsp(uint8_t charging, uint8_t battery);
race_errcode_enum hid_race_set_battery_req(uint8_t charging, uint8_t battery);

#if defined(AIR_PRODUCT_TYPE_GAME_CONTROLLER)
void hid_race_get_usb_mode_rsp(uint8_t mode);
race_errcode_enum hid_race_set_usb_mode_req(uint8_t mode);
#endif /* defined(AIR_PRODUCT_TYPE_GAME_CONTROLLER) */

#if defined(CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
void hid_race_set_key_remap_rsp(uint8_t rsp_status);
void hid_race_get_key_remap_rsp(uint8_t key_id, uint8_t key_type, uint8_t *setting, uint16_t len);
void hid_race_delete_macro_rsp(uint8_t status);
#endif
#endif //__HID_RACE_CMD_H__

