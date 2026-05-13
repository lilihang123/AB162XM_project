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

#ifndef _HID_COMMON_ACL_PKT_VIA_HID_
#define _HID_COMMON_ACL_PKT_VIA_HID_
#if defined(CONFIG_AIR_ACL_PACKET_VIA_HID_REPORT) || defined(AIR_ACL_PACKET_VIA_HID_REPORT)

/* Includes ------------------------------------------------------------------*/
/* Public define -------------------------------------------------------------*/
#define ACL_PKT_BUF_SIZE        4
#define ACL_PKT_BUF_SIZE_MASK   (ACL_PKT_BUF_SIZE - 1)

#define ACL_PKT_CHANNEL_INVALID  0
#define ACL_PKT_CHANNEL_DEFAULT  1

/* Public typedef ------------------------------------------------------------*/

typedef struct{
    uint32_t data;
}T_ACL_PKT_BUFFER_S;


typedef union {
    struct {
        volatile uint8_t buf_head;          /** increase buf_head if acl packet is received */
        volatile uint8_t buf_tail;          /** increase buf_tail if the "response" data is pushed into key queue */
        uint16_t  reserved;                 /** 4 bytes align*/
        T_ACL_PKT_BUFFER_S response[ACL_PKT_BUF_SIZE];
    };

    struct {
        uint32_t header;    /** used in risc-v for speeding up copy process */
    };

}T_ACL_PACKET_QUEUE_S;


typedef enum {
    ACLPKT_ERR_SUCCESS,
    ACLPKT_ERR_INVALID_PARA,
    ACLPKT_ERR_QUEUE_FULL,
    ACLPKT_ERR_QUEUE_EMPTY,
    ACLPKT_ERR_BUSY,
}T_ACLPKT_ERR_CODE_E;

/* Public macro --------------------------------------------------------------*/


inline uint8_t acl_rsp_is_queue_empty(T_ACL_PACKET_QUEUE_S *acl_pkt)
{
    return acl_pkt->buf_head == acl_pkt->buf_tail;
}

/* Public variables ----------------------------------------------------------*/
/* Inline functions ----------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/
T_ACLPKT_ERR_CODE_E acl_pkt_add_item(T_ACL_PKT_BUFFER_S *pkt);



#endif
#endif /* _HID_COMMON_ACL_PKT_VIA_HID_ */
