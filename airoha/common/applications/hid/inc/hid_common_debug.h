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

#ifndef _HID_COMMON_DEBUG_H_
#define _HID_COMMON_DEBUG_H_

#if defined(AIR_HID_COMMON_SERVICE)

/* Includes ------------------------------------------------------------------*/
#include "stdio.h"
#include "stdint.h"
#include "stdbool.h"
#include "string.h"
#include "hal_gpio.h"

/* Public define -------------------------------------------------------------*/

#if 0 // m21 debug pins
#define DBG_SIGNAL_MAIN_LOOP        28
#define DBG_SIGNAL_USB_TX           35
#define DBG_SIGNAL_USB_TX_DONE      36
#define DBG_SIGNAL_USB_SOF          34
#define DBG_SIGNAL_LATCH_REPORT     44  //B
#define DBG_SIGNAL_SPI_CB           45  //G
#define DBG_SIGNAL_TX_NACK          46  //R
#define DBG_SIGNAL_DEBUG_1          1
#define DBG_SIGNAL_DEBUG_2          25
#define DBG_SIGNAL_DEBUG_3          29
#define DBG_SIGNAL_BT_RX            4
#define DBG_SIGNAL_BT_TX            5

#else   // m20 debug pins

#define DBG_SIGNAL_MAIN_LOOP        28
#define DBG_SIGNAL_USB_TX           35
#define DBG_SIGNAL_USB_TX_DONE      36
#define DBG_SIGNAL_USB_SOF          37
#define DBG_SIGNAL_LATCH_REPORT     38
#define DBG_SIGNAL_SPI_CB           39
#define DBG_SIGNAL_TX_NACK          44
#define DBG_SIGNAL_DEBUG_1          45
#define DBG_SIGNAL_DEBUG_2          46
#define DBG_SIGNAL_DEBUG_3          47
#define DBG_SIGNAL_BT_RX            23
#define DBG_SIGNAL_BT_TX            24
#endif

/* Public typedef ------------------------------------------------------------*/
typedef enum {
    DBG_PIN_SPI_CB,
    DBG_PIN_LATCH_REPORT,
    DBG_PIN_NACK,
    DBG_PIN_GENERAL_DBG_1,
    DBG_PIN_GENERAL_DBG_2,
    DBG_PIN_USB_SOF,
    DBG_PIN_USB_TX_SUCCESS,
    DBG_PIN_USB_TX,

    DBG_PIN_MAX,
}T_DEBUG_PIN_USAGE_E;


typedef struct
{
    uint16_t enable_mask;
    uint8_t pin[DBG_PIN_MAX];
}T_COMMON_LA_DBG_S;



#define DATA_SIZE                                (8)  // first section for hid report data log
#define TIMESTAMP_SIZE                           (4)  // second section for timestamp
#define REPORT_SIZE                             (DATA_SIZE + TIMESTAMP_SIZE)
#define REPORT_BUF_SIZE                         (8*REPORT_SIZE)  // 8 reports

typedef  struct
{
    uint8_t ack[REPORT_BUF_SIZE];
    // uint8_t nack[REPORT_BUF_SIZE];
}T_REPORT_BUFF_S;

typedef  struct
{
    bool pool_idx;
    bool pool_print_idx;
    uint32_t buff_w_idx;
    uint32_t counter;

    // ping pong buffer
    T_REPORT_BUFF_S pool[2];
}T_HID_REPORT_LOG_S;

typedef struct {
    uint8_t msg;
    T_HID_REPORT_LOG_S * log_ptr;
}__attribute__((__packed__)) T_LOG_REQ_S;


//#define AIR_LATENCY_ANALYSIS_TINY

/* Public macro --------------------------------------------------------------*/
#if defined(AIR_BASIC_LA_DEBUG) || defined(CONFIG_AIR_HID_DEBUG_PIN)
    #define GPIO_OUTPUT_REG     ((volatile uint8_t*)0x420B0010)  //
    #if defined(AIR_LATENCY_ANALYSIS_TINY)
        #define DBG_LATENCY_L(x)       GPIO_OUTPUT_REG[x>>3] &= ~(1<<(x & 0x07));
        #define DBG_LATENCY_H(x)       GPIO_OUTPUT_REG[x>>3] |= (1<<(x & 0x07));
        #define DBG_PING_L(x)
        #define DBG_PING_H(x)
    #else
        #define DBG_LATENCY_L(x)       GPIO_OUTPUT_REG[x>>3] &= ~(1<<(x & 0x07));
        #define DBG_LATENCY_H(x)       GPIO_OUTPUT_REG[x>>3] |= (1<<(x & 0x07));
        #define DBG_PING_L(x)           GPIO_OUTPUT_REG[x>>3] &= ~(1<<(x & 0x07));
        #define DBG_PING_H(x)           GPIO_OUTPUT_REG[x>>3] |= (1<<(x & 0x07));
    #endif
#else
    #define DBG_LATENCY_L(x)
    #define DBG_LATENCY_H(x)
    #define DBG_PING_H(x)
    #define DBG_PING_L(x)
#endif


#define DBG_IDX(x, pin_id)  \
{\
    uint8_t pulse = x; \
    while(pulse--){\
        DBG_PING_H(pin_id); \
        DBG_PING_L(pin_id); \
    };\
}\

/* Public variables ----------------------------------------------------------*/
/* Inline functions ----------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/

#endif /* AIR_HID_COMMON_SERVICE */
#endif /* _HID_COMMON_DEBUG_H_ */
