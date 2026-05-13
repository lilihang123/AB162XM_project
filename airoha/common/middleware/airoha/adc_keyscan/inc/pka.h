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

#ifndef _PKA_H_
#define _PKA_H_

/* Includes ------------------------------------------------------------------*/
#include "pka_share.h"

/* Public define ------------------------------------------------------------*/
/* Public typedef -----------------------------------------------------------*/
typedef void (*riscv_pka_tx_prepare_callback_t)(pka_share_callback_type_t type, uint8_t tx_cnt);
typedef void (*riscv_pka_tx_post_prepare_callback_t)(uint8_t tx_cnt);

typedef struct stru_bttime {
    uint32_t period;
    uint16_t phase;
} bttime_stru, *bttime_stru_ptr;

typedef struct {
    // callback
    // riscv_pka_tx_prepare_callback_t tx_prepare_handler;
    riscv_pka_tx_post_prepare_callback_t tx_post_prepare_handler[PKA_SHARE_TX_PREPARE_CB_TYPE_MAX];
    bttime_stru pico_offset;
} riscv_pka_info_t;


/* Public macro -------------------------------------------------------------*/


//#define RISCV_PKA_LOG_ENA
#ifdef RISCV_PKA_LOG_ENA
#define PKA_LOG(module, message, arg_cnt, ...)        LOG_MSGID_I(module, message, arg_cnt, ##__VA_ARGS__)
#else
#define PKA_LOG(module, message, arg_cnt, ...)
#endif


/* Private variables ---------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/
uint8_t pka_share_get_tx_status(void);
void pka_share_tx_buf_set_pkt_len(uint16_t *ptr, uint16_t pkt_len);

//callback
void riscv_pka_init();
void pka_share_tx_buf_send(uint8_t *ptr);
uint8_t *pka_share_tx_buf_get_from_q();

uint32_t pka_spi_callback_pre_process(pka_share_callback_type_t *type, uint32_t *tx_cn);
void pka_spi_callback_post_process();

void pka_share_get_sync_clk(bttime_stru *sync_time);
void pka_share_get_cur_pico_clk(bttime_stru_ptr time_ptr);

#endif /* _PKA_H_ */
