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
#include "hal.h"
#include "hal_queue.h"
#include <string.h>

void hal_queue_init(hal_queue_t  *pQueue)
{
    memset(pQueue, 0, sizeof(hal_queue_t));
}

int hal_queue_push(hal_queue_t  *pQueue, int  data)
{
    uint8_t  temp = 0;

    if (pQueue == NULL) {
        return HAL_QUEUE_STATUS_ERROR_INVALID_PARA;
    }
    temp = (pQueue->tail + 1) % MAX_HAL_QUEUE_LEN;
    if (temp == pQueue->head) {
        return HAL_QUEUE_STATUS_ERROR_FULL;
    }
    pQueue->data[pQueue->tail] = data;
    pQueue->tail = temp;

    return temp;
}

int hal_queue_pop(hal_queue_t  *pQueue,  int *data)
{
    uint8_t temp = 0;

    if (pQueue == NULL) {
        return HAL_QUEUE_STATUS_ERROR_INVALID_PARA;
    }
    if (pQueue->head == pQueue->tail) {
        return HAL_QUEUE_STATUS_ERROR_EMPTY;
    }
    temp  = (pQueue->head + 1) % MAX_HAL_QUEUE_LEN;
    if (data != NULL) {
        *data  = pQueue->data[pQueue->head];
    }
    pQueue->head = temp;
    return temp;
}

int hal_queue_top(hal_queue_t  *pQueue,  int *data)
{
    if (pQueue == NULL) {
        return HAL_QUEUE_STATUS_ERROR_INVALID_PARA;
    }
    if (pQueue->head == pQueue->tail) {
        return HAL_QUEUE_STATUS_ERROR_EMPTY;
    }
    *data = pQueue->data[pQueue->head];
    return pQueue->head;
}