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
 
#if defined(CONFIG_AIR_PRODUCT_TYPE_MOUSE) && defined(CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP)
#ifndef __HID_KEY_REMAP_MOUSE_H__
#define __HID_KEY_REMAP_MOUSE_H__


/******************************************************************************/
/* macro                                                                  */
/******************************************************************************/

/******************************************************************************/
/* variables                                                                  */
/******************************************************************************/




/******************************************************************************/
/* functions                                                                  */
/******************************************************************************/
uint32_t hid_key_remap_mouse_init(uint8_t profile_idx);
uint8_t hid_key_remap_mouse_set(uint8_t key_id, KEY_REMAP_TYPE_E key_type, uint8_t *buffer, uint16_t len);
uint32_t hid_key_remap_mouse_get(uint8_t key_id, KEY_REMAP_TYPE_E *key_type, uint8_t *buffer, uint16_t report_rate);
uint8_t hid_key_remap_mouse_reload(uint8_t profile_idx, bool restore);
uint8_t hid_key_remap_mouse_delete_macro(const uint8_t macro_name[], uint8_t name_len);
void hid_key_remap_mouse_remap_enable_clear(uint8_t key_idx);
uint8_t hid_key_remap_mouse_get_type(uint8_t key_idx);
bool hid_key_remap_mouse_has_remap(uint8_t key_idx);
#if defined (CONFIG_AIR_REMAP_FN_KEY)
uint32_t hid_key_remap_mouse_set_fn_key(uint8_t fn_key);
uint32_t hid_key_remap_mouse_get_fn_key();
#endif

#endif //__HID_KEY_REMAP_MOUSE_H__
#endif
