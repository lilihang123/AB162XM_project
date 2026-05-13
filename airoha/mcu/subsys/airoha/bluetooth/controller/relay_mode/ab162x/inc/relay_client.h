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


#ifndef __RELAY_CLIENT_H__
#define __RELAY_CLIENT_H__
 

#include "stdint.h"






/** @brief
 * This enum defines the ATCI status types.
 */
typedef enum {
    ATCI_STATUS_REGISTRATION_FAILURE = -2,   /**< Failed to register the AT command handler table. */
    ATCI_STATUS_ERROR = -1,                  /**< An error occurred during the function call. */
    ATCI_STATUS_OK = 0                       /**< No error occurred during the function call. */
} atci_status_t;

/** @brief
 * This enum defines the input CMD mode.
 */
typedef enum {
    ATCI_CMD_MODE_READ,        /**< Read mode command, such as "AT+CMD?". */
    ATCI_CMD_MODE_ACTIVE,      /**< Active mode command, such as "AT+CMD". */
    ATCI_CMD_MODE_EXECUTION,   /**< Execute mode command, such as "AT+CMD=<op>". */
    ATCI_CMD_MODE_TESTING,     /**< Test mode command, such as "AT+CMD=?". */
    ATCI_CMD_MODE_INVALID      /**< The input command doesn't belong to any of the four types. */
} atci_cmd_mode_t;




/** @brief This structure defines AT command handler input structure. For more information, please refer to #at_cmd_hdlr_fp() function.*/
typedef struct {
    char             *string_ptr;    /**< The input data buffer. */
    uint32_t         string_len;     /**< The response data buffer. */
    uint32_t         name_len;       /**< AT command name length. For example, in "AT+EXAMPLE=1,2,3", name_len = 10 (without symbol "=") */
    uint32_t         parse_pos;      /**< The length after detecting the AT command mode. */
    atci_cmd_mode_t mode;            /**< For more information, please refer to #atci_cmd_mode_t. */

} atci_parse_cmd_param_t;



/** @brief
 * This enum defines the Serial Port Service status.
 */
typedef enum {
    SERIAL_PORT_STATUS_DEV_NOT_READY = -7,      /**< The Serial Port Service device is not ready. */
    SERIAL_PORT_STATUS_BUSY = -6,               /**< The Serial Port Service device is busy. */
    SERIAL_PORT_STATUS_UNINITIALIZED = -5,      /**< The Serial Port Service device is uninitialized. */
    SERIAL_PORT_STATUS_UNSUPPORTED = -4,        /**< The Serial Port Service function is not supported. */
    SERIAL_PORT_STATUS_INVALID_DEVICE = -3,     /**< The Serial Port Service device is invalid. */
    SERIAL_PORT_STATUS_INVALID_PARAMETER = -2,  /**< The Serial Port Service parameters are invalid. */
    SERIAL_PORT_STATUS_FAIL = -1,               /**< The Serial Port Service function has failed. */
    SERIAL_PORT_STATUS_OK = 0,                  /**< The Serial Port Service function executed successfully. */
} serial_port_status_t;
/**
  * @}
  */



void relay_client_init(uint8_t uartPort);

typedef uint8_t bt_relay_status_t;
#define bt_relay_status_enable    (0x01)
#define bt_relay_status_disable   (0x02)
    


typedef void (*bt_relay_status_notify_callback_t)(bt_relay_status_t status);


void relay_client_init(uint8_t uartPort);
void relay_status_notify_register(bt_relay_status_notify_callback_t cb);


#endif /*__RELAY_CLIENT_H__*/

