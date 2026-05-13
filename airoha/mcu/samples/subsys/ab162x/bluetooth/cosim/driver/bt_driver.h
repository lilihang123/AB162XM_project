/* Copyright Statement:
 *
 * (C) 2005-2016  MediaTek Inc. All rights reserved.
 *
 * This software/firmware and related documentation ("MediaTek Software") are
 * protected under relevant copyright laws. The information contained herein
 * is confidential and proprietary to MediaTek Inc. ("MediaTek") and/or its licensors.
 * Without the prior written permission of MediaTek and/or its licensors,
 * any reproduction, modification, use or disclosure of MediaTek Software,
 * and information contained herein, in whole or in part, shall be strictly prohibited.
 * You may only use, reproduce, modify, or distribute (as applicable) MediaTek Software
 * if you have agreed to and been bound by the applicable license agreement with
 * MediaTek ("License Agreement") and been granted explicit permission to do so within
 * the License Agreement ("Permitted User").  If you are not a Permitted User,
 * please cease any access or use of MediaTek Software immediately.
 * BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 * THAT MEDIATEK SOFTWARE RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES
 * ARE PROVIDED TO RECEIVER ON AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL
 * WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
 * NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
 * SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
 * SUPPLIED WITH MEDIATEK SOFTWARE, AND RECEIVER AGREES TO LOOK ONLY TO SUCH
 * THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. RECEIVER EXPRESSLY ACKNOWLEDGES
 * THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES
 * CONTAINED IN MEDIATEK SOFTWARE. MEDIATEK SHALL ALSO NOT BE RESPONSIBLE FOR ANY MEDIATEK
 * SOFTWARE RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
 * STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND
 * CUMULATIVE LIABILITY WITH RESPECT TO MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
 * AT MEDIATEK'S OPTION, TO REVISE OR REPLACE MEDIATEK SOFTWARE AT ISSUE,
 * OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY RECEIVER TO
 * MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
 */
/* MediaTek restricted information */

#ifndef __BT_DRIVER_H__
#define __BT_DRIVER_H__

//#include "bt_type_def.h"

/**
 * @brief The bit ordering type within the packet from controller.
 */
#define BT_CONTROLLER_ENDIAN_ORDER_LITTLE     0x00    /**< The data follows the Little Endian format. */
#define BT_CONTROLLER_ENDIAN_ORDER_BIG        0x01    /**< The data follows the Big Endian format. */
typedef uint8_t bt_controller_endian_order_t;

/**
 * @brief The Public Key type.
 */
#define BT_PUBLIC_KEY_192   0x00      /**< Public key derived from P192. */
#define BT_PUBLIC_KEY_256   0x01      /**< Public key derived from P256. */
typedef uint8_t bt_public_key_t;

#if 0
BT_EXTERN_C_BEGIN

bt_status_t bt_driver_tx(bt_hci_le_packet_t *packet, uint32_t length);

/**
 * @brief       This function is to validate P256 or P192 public key.
 * @param[in]   key is the pointer of public key.
 * @param[in]   key_type is to indicate whether the public key type is P256 or P192.
 * @return      bool. True means that the public key is valid.
 */
bool bt_driver_validate_public_key(const uint8_t *key, bt_public_key_t key_type);

/**
 * @brief       This function is to get the bit ordering of the keys that are generated from controller.
 * @param[in]   None.
 * @return      bt_controller_endian_order_t. Big Endian or Little Endian fromat.
 */
bt_controller_endian_order_t bt_driver_get_controller_endian_order(void);

BT_EXTERN_C_END
#endif 

#endif /* __BT_DRIVER_H__ */

