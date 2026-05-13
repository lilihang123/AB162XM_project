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

#if defined(AIR_HID_COMMON_MEMORY)

#if defined(CONFIG_AIR_ACL_PACKET_VIA_HID_REPORT)

/* Includes ------------------------------------------------------------------*/
#include "stdio.h"
#include "stdint.h"
#include "stdbool.h"
#include "string.h"
#include "hid_common.h"
#include "hid_common_acl_rsp_via_hid.h"
#include <zephyr/logging/log.h>

/* Private define ------------------------------------------------------------*/



/* Private typedef -----------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/
/* Public functions ---------------------------------------------------------*/

/** Check if the queue is full */
bool acl_pkt__is_queue_full(T_ACL_PACKET_QUEUE_S *acl_pkt_ctrl)
{
    return (((acl_pkt_ctrl->buf_head + 1) & ACL_PKT_BUF_SIZE_MASK) == acl_pkt_ctrl->buf_tail);
}

T_ACLPKT_ERR_CODE_E acl_pkt_add_item(T_ACL_PKT_BUFFER_S *pkt)
{
    T_ACL_PACKET_QUEUE_S *acl_pkt = &hid_common->hid.acl_pkt_queue;

    if (acl_pkt__is_queue_full(acl_pkt) ){
        return ACLPKT_ERR_QUEUE_FULL;
    }

    acl_pkt->response[acl_pkt->buf_head].data = pkt->data;

    acl_pkt->buf_head++;
    if (acl_pkt->buf_head >= ACL_PKT_BUF_SIZE){
        acl_pkt->buf_head = 0;
    }

    // LOG_INF("acl_pkt_add_item  %d, %d, pkt->channel = 0x%08X, pkt->data 0x%08X", acl_pkt->buf_head , acl_pkt->buf_tail, pkt->channel, pkt->data );
    return ACLPKT_ERR_SUCCESS;
}

#endif
#endif /* AIR_HID_COMMON_MEMORY */
