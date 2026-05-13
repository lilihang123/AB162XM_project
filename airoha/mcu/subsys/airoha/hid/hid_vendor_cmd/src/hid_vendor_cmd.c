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
#include <zephyr/logging/log.h>
#include <zephyr/bluetooth/hci.h>


#include "hid_vendor_cmd.h"


#define thisMODULE  hid_ven
#define thisMOD    "hid_ven"

LOG_MODULE_REGISTER(thisMODULE);


/******************************************************************************/
/*  function prototype                                                        */
/******************************************************************************/

/******************************************************************************/
/* variables                                                                  */
/******************************************************************************/


/******************************************************************************/
/* callback function                                                          */
/******************************************************************************/


/******************************************************************************/
/* event handler functions                                                    */
/******************************************************************************/


/******************************************************************************/
/* private functions                                                          */
/******************************************************************************/


/******************************************************************************/
/* public functions                                                           */
/******************************************************************************/





int hid_vendor_set_peripheral_trigger(T_BT_TRIGGER_TYPE_S *params)
{
    if (!params) {
        return 1;
    }

    T_BT_TRIGGER_TYPE_S *vendor_params;
    struct net_buf *buf, *rsp = NULL;
    int err;

    buf = bt_hci_cmd_create(BT_HCI_CMD_VENDOR_SET_PRI_ENABLE,
				sizeof(*params));
	if (!buf) {
		return 2;
	} 

	vendor_params = net_buf_add(buf, sizeof(*params));
    (void)memset(vendor_params, 0, sizeof(*params));
    memcpy(vendor_params, params, sizeof(*params));

    err = bt_hci_cmd_send_sync(BT_HCI_CMD_VENDOR_SET_PRI_ENABLE, buf, &rsp);
    
    if (err) {
		return err;
	}

    net_buf_unref(rsp);
    return err;
}

