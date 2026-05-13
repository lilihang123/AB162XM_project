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
/* Airoha restricted information */

#if defined(AIR_BL_DFU_ENABLE)


#include "lw_mux.h"
#include "race_parser.h"

#if defined(AIR_BL_USB_HID_DFU_ENABLE)
#include "bl_usb_hid.h"
#else
#include "hal_uart.h"
#endif

void race_bl_init(void)
{
    lw_mux_local_init();
    //lw_mux_open(LW_MUX_UART_2, race_lw_mux_event_handler);
#if defined(AIR_BL_USB_HID_DFU_ENABLE)
    lw_mux_open(LW_MUX_USB_HID_0, race_lw_mux_event_handler);
#else
    printk("race_bl_init uart2 \r\n");
    hal_uart_deinit(HAL_UART_2);
    hal_uart_config_t uart_config;
    uart_config.baudrate = HAL_UART_BAUDRATE_921600;
    uart_config.parity = HAL_UART_PARITY_NONE;
    uart_config.stop_bit = HAL_UART_STOP_BIT_1;
    uart_config.word_length = HAL_UART_WORD_LENGTH_8;
    hal_uart_init(HAL_UART_2, &uart_config);

    lw_mux_open(LW_MUX_UART_2, race_lw_mux_event_handler);
#endif
}

void race_bl_usb_plug_in_handler(void)
{
#if defined(AIR_BL_USB_HID_DFU_ENABLE)
    lw_mux_open(LW_MUX_USB_HID_0, race_lw_mux_event_handler);
#endif
}

void race_bl_usb_plug_out_handler(void)
{
#if defined(AIR_BL_USB_HID_DFU_ENABLE)
    lw_mux_close(LW_MUX_USB_HID_0);
#endif
}
#endif


