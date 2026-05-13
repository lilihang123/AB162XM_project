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

#ifndef __APP_DONGLE_CM_DEVICE_MGR_H__
#define __APP_DONGLE_CM_DEVICE_MGR_H__

#include "app_dongle_cm_config.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef struct {
    uint8_t         link_type;
    uint8_t         device_type;
    uint8_t         addr_type;
    uint8_t         addr[BT_ADDR_SIZE];
#ifdef APP_DONGLE_CM_DEVICE_LIST_SUPPORT_NAME
    uint8_t         name[APP_DONGLE_CM_DEVICE_LIST_NAME_MAX_LEN];
#endif
#ifdef APP_DONGLE_CM_SUPPORT_LEA_EDR_DUAL_MODE
    uint8_t         last_link_mode;
#endif
    uint32_t        reserved;
} PACKED app_dongle_cm_device_info_t;


void        app_dongle_cm_device_mgr_init(void);

bool        app_dongle_cm_device_mgr_add(uint8_t addr_type, uint8_t *addr, uint8_t link_type, uint8_t device_type);
bool        app_dongle_cm_device_mgr_remove(uint8_t addr_type, uint8_t *addr);
bool        app_dongle_cm_device_mgr_clear(void);

uint8_t     app_dongle_cm_device_mgr_get_num(void);
uint8_t     app_dongle_cm_device_mgr_get_num_by_link_type(uint8_t link_type);
uint8_t     app_dongle_cm_device_mgr_get_num_by_device_type(uint8_t device_type);
uint8_t     app_dongle_cm_device_mgr_get_num_by_link_device_type(uint8_t link_type, uint8_t device_type);

uint8_t     app_dongle_cm_device_mgr_get_info_by_link_device_type(uint8_t link_type, uint8_t device_type, app_dongle_cm_device_info_t list[APP_DONGLE_CM_DEVICE_LIST_MAX_NUM]);

bool        app_dongle_cm_device_mgr_is_exist(uint8_t addr_type, uint8_t *addr);

uint8_t     app_dongle_cm_device_mgr_get_link_type(uint8_t addr_type, uint8_t *addr);
uint8_t     app_dongle_cm_device_mgr_get_device_type(uint8_t addr_type, uint8_t *addr);



#ifdef __cplusplus
}
#endif

#endif /* __APP_DONGLE_CM_DEVICE_MGR_H__ */
