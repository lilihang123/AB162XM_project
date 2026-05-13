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
 

#ifndef __HID_SCENARIO_REPORT_RATE_H__
#define __HID_SCENARIO_REPORT_RATE_H__

/* Public define -------------------------------------------------------------*/
#define MODE_TYPE_USB      0
#define MODE_TYPE_GAMING   1
#define MODE_TYPE_BT       2

#define REPORT_RATE_NUM  7 


#define ULL_REPORT_RATE_IDX_TO_VALUE(idx)           ((0x01 << (idx-1)) * 125)


/******************************************************************************/
/* variables                                                                  */
/******************************************************************************/


/******************************************************************************/
/* functions                                                                  */
/******************************************************************************/
void hid_scenario_rr_init(uint8_t profile_idx);
uint8_t hid_scenario_report_rate_change(uint8_t category_id, uint8_t type, uint16_t para, uint8_t restore_or_chg_profile);
uint16_t hid_scenario_read_now_report_rate(uint8_t category_id);
uint16_t hid_scenario_read_new_report_rate(uint8_t category_id);
uint8_t hid_scenario_read_report_rate_idx(uint8_t category_id);

void hid_scenario_report_rate_change_profile(uint8_t profile_idx);
void hid_scenario_report_rate_restore();

void hid_scenario_report_rate_2_4G_change_start();
void hid_scenario_update_comm_report_rate_para(uint8_t category_id);
void hid_scenario_report_rate_validation_check(uint8_t category_id,  uint16_t para );

/** This function is used to set the report rate to default when a new 2.4G connection is established */
void hid_scenario_report_rate__new_connection(uint8_t category_id,  uint16_t report_rate );
#endif //__HID_SCENARIO_REPORT_RATE_H__

