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
 

#ifndef __APP_EVT_DISPATCHER_H__
#define __APP_EVT_DISPATCHER_H__

#if defined(CONFIG_AIR_APP_FRAMEWORK)

#include <zephyr/kernel.h>
#include "app_evt_dispatcher_defines.h"
typedef enum {
    AF_TRAVERSE_NEXT, 
    AF_TRAVERSE_TERMINATED,    
}AF_TRAVERSE_ACTION_E;


#define AF_EVT_EXTERN(evt_name)                         _APP_EVT_EXTERN(evt_name)
#define AF_EVT_DECLARE(evt_name)                        _APP_EVT_DECLARE(evt_name)

#define AF_EVT_SUBSCRIBE_FUN_FIRST(mod_name, evt_name, hdl_fun )         _APP_EVT_DISPATCH_CB_DEFINE_FUN(mod_name, evt_name, hdl_fun, APP_DISPATCH_EVT_CB_DEFINE_PRIORITY_1)
#define AF_EVT_SUBSCRIBE_FUN_HIGH(mod_name, evt_name, hdl_fun )          _APP_EVT_DISPATCH_CB_DEFINE_FUN(mod_name, evt_name, hdl_fun, APP_DISPATCH_EVT_CB_DEFINE_PRIORITY_2)
#define AF_EVT_SUBSCRIBE_FUN(mod_name, evt_name, hdl_fun )               _APP_EVT_DISPATCH_CB_DEFINE_FUN(mod_name, evt_name, hdl_fun, APP_DISPATCH_EVT_CB_DEFINE_PRIORITY_5)
#define AF_EVT_SUBSCRIBE_FUN_LOW(mod_name, evt_name, hdl_fun )           _APP_EVT_DISPATCH_CB_DEFINE_FUN(mod_name, evt_name, hdl_fun, APP_DISPATCH_EVT_CB_DEFINE_PRIORITY_7)
#define AF_EVT_SUBSCRIBE_FUN_LAST(mod_name, evt_name, hdl_fun )          _APP_EVT_DISPATCH_CB_DEFINE_FUN(mod_name, evt_name, hdl_fun, APP_DISPATCH_EVT_CB_DEFINE_PRIORITY_8)


#define AF_EVT_SUBMIT(evt)                              app_evt_apply( &evt->header);
#if defined(CONFIG_AIR_APP_FRAMEWORK_DELAYABLE)
#define AF_DELAYABLE_EVT_SUBMIT(evt, delay)                 app_delayable_evt_apply( &evt->header, delay);
#define AF_DELAYABLE_EVT_CANCEL(dwork_item)                 app_delayable_evt_cancel(dwork_item);
#endif




#define APP_EVT_EXTERN(evt_name)                         _APP_EVT_EXTERN(evt_name)
#define APP_EVT_DECLARE(evt_name)                        _APP_EVT_DECLARE(evt_name)

#define APP_DISPATCH_EVT_CB_DEFINE_FIRST(mod_name, evt_name, hdl_fun )                 _APP_EVT_DISPATCH_CB_DEFINE_FUN(mod_name, evt_name, hdl_fun, APP_DISPATCH_EVT_CB_DEFINE_PRIORITY_1)
#define APP_DISPATCH_EVT_CB_DEFINE_HIGH(mod_name, evt_name, hdl_fun )                  _APP_EVT_DISPATCH_CB_DEFINE_FUN(mod_name, evt_name, hdl_fun, APP_DISPATCH_EVT_CB_DEFINE_PRIORITY_2)
#define APP_DISPATCH_EVT_CB_DEFINE_P3(mod_name, evt_name, hdl_fun )                    _APP_EVT_DISPATCH_CB_DEFINE_FUN(mod_name, evt_name, hdl_fun, APP_DISPATCH_EVT_CB_DEFINE_PRIORITY_3)
#define APP_DISPATCH_EVT_CB_DEFINE_P4(mod_name, evt_name, hdl_fun )                    _APP_EVT_DISPATCH_CB_DEFINE_FUN(mod_name, evt_name, hdl_fun, APP_DISPATCH_EVT_CB_DEFINE_PRIORITY_4)
#define APP_DISPATCH_EVT_CB_DEFINE(mod_name, evt_name, hdl_fun )                       _APP_EVT_DISPATCH_CB_DEFINE_FUN(mod_name, evt_name, hdl_fun, APP_DISPATCH_EVT_CB_DEFINE_PRIORITY_5)
#define APP_DISPATCH_EVT_CB_DEFINE_P6(mod_name, evt_name, hdl_fun )                    _APP_EVT_DISPATCH_CB_DEFINE_FUN(mod_name, evt_name, hdl_fun, APP_DISPATCH_EVT_CB_DEFINE_PRIORITY_6)
#define APP_DISPATCH_EVT_CB_DEFINE_LOW(mod_name, evt_name, hdl_fun )                   _APP_EVT_DISPATCH_CB_DEFINE_FUN(mod_name, evt_name, hdl_fun, APP_DISPATCH_EVT_CB_DEFINE_PRIORITY_7)
#define APP_DISPATCH_EVT_CB_DEFINE_LAST(mod_name, evt_name, hdl_fun )                  _APP_EVT_DISPATCH_CB_DEFINE_FUN(mod_name, evt_name, hdl_fun, APP_DISPATCH_EVT_CB_DEFINE_PRIORITY_8)

#define APP_EVT_APPLY(evt)                              app_evt_apply( &evt->header);
#if defined(CONFIG_AIR_APP_FRAMEWORK_DELAYABLE)
#define APP_DELAYABLE_EVT_APPLY(evt, delay)                 app_delayable_evt_apply( &evt->header, delay);
#define APP_DELAYABLE_EVT_CANCEL(dwork_item)                 app_delayable_evt_cancel(dwork_item);
#endif



#endif   // CONFIG_AIR_APP_FRAMEWORK
#endif  // __APP_EVT_DISPATCHER_H__