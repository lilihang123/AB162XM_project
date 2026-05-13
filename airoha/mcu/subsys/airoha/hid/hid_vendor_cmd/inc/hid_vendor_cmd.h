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
 
 
#ifndef __HID_VENDOR_COMMAND_H__
#define __HID_VENDOR_COMMAND_H__

#define BT_HCI_CMD_VENDOR_SET_PRI_ENABLE                     0xFE3C

typedef enum{
    TRIGGER_TYPE_KEY_SCAN,   /** BT trigger key scan hardware */
    TRIGGER_TYPE_I2C,        /** BT trigger I2C hardware */
    TRIGGER_TYPE_SPI,        /** BT trigger SPI hardware */
}T_HID_BT_TRIGGER_TYPE_E;

typedef enum{
    ACTION_MODE_AUTO,        /** Trigger Action depended on BT status (default on) */
    ACTION_MODE_PAUSE,       /** Trigger Action paused (no trigger) */
    ACTION_MODE_RESUME,      /** Trigger Action resume (trigger on) */
}T_HID_BT_TRIGGER_ACTION_MODE_E;

typedef struct {
    uint16_t    connection_handle;                        /**< The ACL handle*/
    uint8_t     TriggerType;                              /**< trigger HW type, see  T_HID_BT_TRIGGER_TYPE_E */
    uint8_t     ActionMode;                               /**< action mode, see T_HID_BT_TRIGGER_ACTION_MODE_E */
}__packed T_BT_TRIGGER_TYPE_S;









/******************************************************************************/
/* variables                                                                  */
/******************************************************************************/



/******************************************************************************/
/* functions                                                                  */
/******************************************************************************/

int hid_vendor_set_peripheral_trigger(T_BT_TRIGGER_TYPE_S *params);


#endif

