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

#ifndef _HID_COMMON_REPORT_RATE_H_
#define _HID_COMMON_REPORT_RATE_H_


/* Includes ------------------------------------------------------------------*/
#include "stdio.h"
#include "stdint.h"
#include "stdbool.h"
#include "string.h"

/* Public define -------------------------------------------------------------*/

/* Public typedef ------------------------------------------------------------*/
typedef enum
{
    HID_REPORT_RATE_125_HZ,
    HID_REPORT_RATE_250_HZ,
    HID_REPORT_RATE_500_HZ,
    HID_REPORT_RATE_1K_HZ,
    HID_REPORT_RATE_2K_HZ,
    HID_REPORT_RATE_4K_HZ,
    HID_REPORT_RATE_8K_HZ,
    HID_REPORT_RATE_TOTAL_NUM,
}T_HID_REPORT_RATE_E;


#define DEFAULT_REPORT_RATE    HID_REPORT_RATE_8K_HZ

typedef struct
{
    uint8_t     rr_idx_2_4g;                        /** index of report rate table for 2.4g mode  */
    uint8_t     rr_idx_usb;                         /** index of report rate table for usb mode */

}T_HID_REPORT_RATE_VAL_S;


/* Public macro --------------------------------------------------------------*/
#define INTERVAL_MIN   125
#define RR_IDX_TO_REPORT_RATE(idx)      ((0x01 << (idx)) * INTERVAL_MIN)

/** Convert Report Rate Idx to time interval
 * idx = 0:  RR = 125, Time interval = 8000us
 * idx = 1:  RR = 250, Time interval = 4000us
 * idx = 2:  RR = 500, Time interval = 2000us
 * idx = 3:  RR =  1K, Time interval = 1000us
 * idx = 4:  RR =  2K, Time interval =  500us
 * idx = 5:  RR =  4K, Time interval =  250us
 * idx = 6:  RR =  8K, Time interval =  125us
 * idx = ?:  RR =  ??, Time interval =  125us
*/
#define RR_IDX_TO_TIME_IN_MICRO_SEC(idx)      (INTERVAL_MIN << ( (idx <= HID_REPORT_RATE_8K_HZ)? HID_REPORT_RATE_8K_HZ - idx : 0 ))



/* Public variables ----------------------------------------------------------*/
/* Inline functions ----------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/


#endif /* _HID_COMMON_REPORT_RATE_H_ */
