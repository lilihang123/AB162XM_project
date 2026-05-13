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
 

#ifndef __HID_RACE_CMD_MOUSE_H__
#define __HID_RACE_CMD_MOUSE_H__

#include "hid_race_cmd_event.h"

/******************************************************************************/
/* variables                                                                  */
/******************************************************************************/


/******************************************************************************/
/* functions                                                                  */
/******************************************************************************/
void *hid_race_cmd_mouse_handler(ptr_race_pkt_t pCmdMsg, uint16_t length, uint8_t channel_id);
#if defined(CONFIG_AIR_SW_KEY_DEBOUNCE)
void hid_race_ms_set_sw_debounce_rsp(uint8_t status);
void hid_race_ms_get_sw_debounce_rsp(uint8_t* deb_setting);
#endif

void hid_race_ms_set_sensor_LOD_rsp(uint8_t rsp_status);
void hid_race_ms_get_sensor_LOD_rsp(uint8_t LOD);
void hid_race_ms_set_sensor_motion_sync_rsp(uint8_t rsp_status);
void hid_race_ms_get_sensor_motion_sync_rsp(uint8_t motion_sync);
void hid_race_ms_set_sensor_angle_snap_rsp(uint8_t rsp_status);
void hid_race_ms_get_sensor_angle_snap_rsp(uint8_t angle_snap);
void hid_race_ms_set_sensor_ripple_control_rsp(uint8_t rsp_status);
void hid_race_ms_get_sensor_ripple_control_rsp(uint8_t ripple_control);
void hid_race_ms_set_dpi_rsp(uint8_t rsp_status);

#if defined(CONFIG_AIR_XY_DPI_OUT_OF_SYNC)
void hid_race_ms_get_dpi_rsp(uint8_t dpi_loop_stage_range, uint8_t dpi_curr_idx, uint16_t* x_dpi_settings, uint16_t* y_dpi_settings);
#else
void hid_race_ms_get_dpi_rsp(uint8_t dpi_loop_stage_range, uint8_t dpi_curr_idx, uint16_t* dpi_settings);
#endif

void hid_race_ms_set_dpi_loop_stage_range_rsp(uint8_t rsp_status);
void hid_race_ms_set_dpi_current_rsp(uint8_t rsp_status);

#if defined(CONFIG_AIR_REMAP_FN_KEY)
void hid_race_ms_set_remap_fn_key_rsp(uint8_t status);
void hid_race_ms_get_remap_fn_key_rsp(uint8_t fn_key);
#endif
#endif //__HID_RACE_CMD_MOUSE_H__

