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

#ifndef _RV_PERIPHERAL_SAMPLING_H_
#define _RV_PERIPHERAL_SAMPLING_H_

#include "riscv_ccni.h"
#include "rv_application.h"
//#define NO_HID_ZERO_REPORT    /** Skip sending zero report when no data available */


#if 1
/* General return values */
typedef enum {
    SUCCESS = 0,
    ERROR_INVALID_PARAMETER,
    ERROR_BUSY,    
    ERROR_INSUFFICIENT_MEMORY,    
    ERROR_QUEUE_EMPTY,    
    ERROR_QUEUE_FULL,
    ERROR_TIMEOUT,
    ERROR_NOTHING_CHANGED,
    ERROR_UNKNOWN,
    // Additional error codes can be added here


} RETURN_STATUS;
#endif





// #if defined( )

/* Includes ------------------------------------------------------------------*/
/* Public define -------------------------------------------------------------*/
/* Public typedef ------------------------------------------------------------*/
typedef enum {
    PAIRING_STATE_SEND_REPORT,
    PAIRING_STATE_CHECK_BUFFER,
    PAIRING_STATE_CCNI_SEND,
} PAIRING_STATE;

typedef enum {
    APP_CHECK_NONE,
    APP_CHECK_8K_CONNECTED,
    APP_CHECK_CONNECTED_IDLE,
    APP_CHECK_CONNECTED_ACTIVE,
    APP_CHECK_USB_MODE,

} T_APP_CHECK_STATUS_E;


typedef struct {
    uint32_t    hid_exp_features;       /** reserved*/
    uint32_t    read_key_timestamp;     /** the timestamp when the key is read. This timestamp is used for timer caculation in ir-pt and sw-debounce modules  */
    uint32_t    rr_idx_usb;                 /** report rate idx. 0=125, 1=250, 2=500, 3=1000 , 4=2000 , 5=4000 , 6=8000. Each report rate might have different process */
    uint32_t    rr_idx_2_4g;                 /** report rate idx. 0=125, 1=250, 2=500, 3=1000 , 4=2000 , 5=4000 , 6=8000. Each report rate might have different process */
    uint32_t    rr_idx;                 /** report rate idx. 0=125, 1=250, 2=500, 3=1000 , 4=2000 , 5=4000 , 6=8000. Each report rate might have different process */
    uint32_t    state;              /** app state */


}T_RISCV_APP_S; 

/* Public macro --------------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/
extern T_RISCV_APP_S riscv_app;

/* Public functions ----------------------------------------------------------*/
int peripheral_sampling_init();
hal_ccni_status_t riscv_app_ccin_send(uint8_t* payload, uint8_t len);
void riscv_app_ccni_key_remap_send(uint32_t status, uint32_t value);
void peripheral_sampling_state_change_active();
void peripheral_sampling_pairing_state_change();
void peripheral_sampling_set_inActivity_timeout();
void peripheral_sampling_debug_print();
void peripheral_sampling_parameter_init();

void peripheral_sampling_app_state_update(uint32_t new_state);
void peripheral_sampling_common_para_update();
bool peripheral_sampling__check_condiction(uint32_t check_type);

// #endif /*  */

#endif /* _RV_PERIPHERAL_SAMPLING_H_ */
