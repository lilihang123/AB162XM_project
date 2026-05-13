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

#include <zephyr/kernel.h>
#include "af_framework.h"



/*============================Application Framework============================*/
// General subscribable event
// Please SORT by alphabet
AF_EVT_DECLARE(evt_active_status);
AF_EVT_DECLARE(evt_app_state);
AF_EVT_DECLARE(evt_app_state_change_req);
AF_EVT_DECLARE(evt_app_battery);
AF_EVT_DECLARE(evt_app_bat_timer);
AF_EVT_DECLARE(evt_app_rgb_test);
AF_EVT_DECLARE(evt_enter_test);

AF_EVT_DECLARE(evt_bt_status);

AF_EVT_DECLARE(evt_conn_status);
AF_EVT_DECLARE(evt_conn_req);

AF_EVT_DECLARE(evt_fake_report_req);
AF_EVT_DECLARE(evt_fake_report_execute);

AF_EVT_DECLARE(evt_gatt_ch_status);

AF_EVT_DECLARE(evt_pairing_request);

AF_EVT_DECLARE(evt_link_change);

#if defined(CONFIG_AIR_HID_OUTPUT_REPORT_NOTIFY)
AF_EVT_DECLARE(evt_hid_output_report);
#endif

AF_EVT_DECLARE(evt_restore);

#if defined (CONFIG_AIR_SUPPORT_IRPT_LR_KEY)
AF_EVT_DECLARE(evt_riscv_key);
#endif

#if defined (CONFIG_AIR_SUPPORT_IR_COMP)
AF_EVT_DECLARE(evt_riscv_wheel_status);
#endif
AF_EVT_DECLARE(evt_module_init);
AF_EVT_DECLARE(evt_mouse_sensor);

AF_EVT_DECLARE(evt_rr_change_req);
AF_EVT_DECLARE(evt_rr_status);
AF_EVT_DECLARE(evt_dpi_change_req);
AF_EVT_DECLARE(evt_dpi_status);

AF_EVT_DECLARE(evt_scenario_status);
AF_EVT_DECLARE(evt_slide_switch_status);

#if defined (CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE)
AF_EVT_DECLARE(evt_usb_status);
#endif /*END _CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_USB_MODE_*/

AF_EVT_DECLARE(evt_race_cmd_req);
AF_EVT_DECLARE(evt_race_cmd_rsp);
AF_EVT_DECLARE(evt_race_cmd_rsp_for_rgb);

AF_EVT_DECLARE(evt_factory_reset);
AF_EVT_DECLARE(evt_key_event);
AF_EVT_DECLARE(evt_hogp_attr);
AF_EVT_DECLARE(evt_sw_deb_update);
AF_EVT_DECLARE(evt_job_next_process);
AF_EVT_DECLARE(evt_force_key_release_success);

#if defined(CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
AF_EVT_DECLARE(evt_key_remap_processing);
AF_EVT_DECLARE(evt_remap_backend_process);
#endif /* CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP */
/*=============================================================================*/


