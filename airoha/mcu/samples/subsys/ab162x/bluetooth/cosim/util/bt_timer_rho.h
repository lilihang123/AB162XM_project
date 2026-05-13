/* Copyright Statement:
 *
 * (C) 2018  Airoha Technology Corp. All rights reserved.
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
/* Airoha restricted information */

#ifndef __BT_TIMER_RHO_H__
#define __BT_TIMER_RHO_H__

#include <stdbool.h>
#include "bt_type.h"
#include "bt_timer.h"
#include "bt_aws_mce.h"
#include "bt_platform.h"

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @addtogroup bt_timer_rho_struct Structure
 * @{
 */

/**
 * @brief                           Timeout instance structure
 */
BT_PACKED(
typedef struct {
    uint32_t timer_id;              /**<  module id + module defined id */
    uint32_t data;                  /**<  user data */
    uint32_t time_ms;               /**<  timer timeout in ms */
    bt_timeout_callback_t cb;       /**<  timer timeout callback function */
}) bt_timer_rho_t;


/**
 * @}
 */


/**
 * @brief                   To update the data of the timer.
 * @param[in] timer_id      Timer ID
 * @param[in] data          User data saved in timer instance
 * @return                  return  BT_STATUS_SUCCESS if update success, return BT_STATUS_TIMER_NOT_FOUND if timer instance is not found
 */
bt_status_t bt_timer_rho_set_data(uint32_t timer_id, void *data);


/**
 * @brief                   To get the data length of all timers of the timer list
 * @param[in] addr    The bluetooth address.
 * @return                  return  length of the data
 */
uint32_t bt_timer_rho_get_data_length(const bt_bd_addr_t *addr);

/**
 * @brief                   To get the data of all timers of the timer list
 * @param[in] *data      data cache buffer which is allocated by user
 * @param[in] addr    The bluetooth address.
 * @return                  return  BT_STATUS_SUCCESS if get success, return BT_STATUS_FAIL if get failed
 */
bt_status_t bt_timer_rho_get_data(void *data, const bt_bd_addr_t *addr);


/**
 * @brief   To update the new timer list
 * @param[in] role      RHO agent role or partner role
 * @param[in] addr    The bluetooth address.
 * @param[in] data          the context of the new timer list to update
 * @param[in] length          the length of the context
 * @param[in] data          the status of RHO result, only be used when role is agent
 * @return  void
 */
void bt_timer_rho_update_context(bt_aws_mce_role_t role, const bt_bd_addr_t *addr, void *data, uint32_t length, bt_status_t status);


/**
 * @}
 */

#ifdef __cplusplus
}
#endif


#endif /*__BT_TIMER_RHO_H__*/
