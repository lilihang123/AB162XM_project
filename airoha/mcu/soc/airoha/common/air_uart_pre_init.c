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

#include <zephyr/kernel.h>
#include <zephyr/init.h>
#include <zephyr/logging/log.h>
#include <zephyr/devicetree.h>

#include "air_chip.h"
#include "memory_attribute.h"

#if defined(AIR_BTD_IC_PREMIUM_G1)
    void uart_reset_default_value_pre_init(UART_REGISTER_T *uartx)
    {
        uartx->LCR_UNION.LCR = 0x00;
        uartx->XON_XOFF_UNION.XON_XOFF = 0x00;
        uartx->DLM_DLL = 0x00;
        uartx->IER_UNION.IER = 0x00;
        uartx->FCR_UNION.FCR = 0x00;
        uartx->EFR_UNION.EFR = 0x00;
        uartx->MCR_UNION.MCR = 0x00;
        //uartx->MCR_UNION.MCR_CELLS.RTS = 0x00;
        //uartx->MCR_UNION.MCR_CELLS.LOOP = 0x00;
        uartx->SCR = 0x00;
        //uartx->AUTOBAUD_REG_UNION.AUTOBAUD_REG = 0x00;
        // uartx->HIGHSPEED = 0x00;
        uartx->SAMPLE_REG_UNION.SAMPLE_REG = 0x00;
        uartx->RATEFIX_UNION.RATEFIX = 0x00;
        uartx->AUTOBAUD_CON_UNION.AUTOBAUD_CON = 0x00;
        // uartx->GUARD = 0x00;
        uartx->ESCAPE_REG_UNION.ESCAPE_REG = 0x00;
        // uartx->SLEEP_REG = 0x00;
        uartx->DMA_CON_UNION.DMA_CON = 0x00;
        uartx->RXTRIG = 0x00;
        uartx->FRACDIV = 0x00;
        uartx->RX_TOC_DEST = 0x00;
        uartx->RX_TO_CON_UNION.RX_TO_CON = 0x00;
    }

    void uart_set_baudrate_pre_init(UART_REGISTER_T *uartx, uint32_t actual_baudrate)
    {
        uint32_t uart_clock, integer, remainder, fraction;
        uint32_t dll_dlm, sample_count, sample_point;
        uint32_t fraction_mapping[] = {0x00, 0x80, 0x110, 0x248, 0x2a8, 0x354, 0x36c, 0x3ba, 0x3f6, 0x3fe};
        uart_clock = 32000000;
        uartx->RATEFIX_UNION.RATEFIX = 0x0;
        uartx->FRACDIV = (~UART_FRACDIV_MASK);

        integer = uart_clock / (actual_baudrate * 256);
        remainder = ((uart_clock * 10) / (actual_baudrate * 256)) % 10;
        if ((remainder != 0) || (integer == 0)) {
            integer += 1;
        }
        dll_dlm = integer;
        sample_count = uart_clock / (actual_baudrate * dll_dlm);

        while (sample_count > 256) {
            dll_dlm++;
            sample_count = uart_clock / (actual_baudrate * dll_dlm);
        }

        fraction = ((uart_clock * 10) / (actual_baudrate * dll_dlm)) % 10;

        sample_count -= 1;
        sample_point = (sample_count - 1) >> 1;

        // uartx->HIGHSPEED = UART_HIGHSPEED_SPEED_MODE3;

        uartx->DLM_DLL = dll_dlm & 0x0000ffff;

        uartx->SAMPLE_REG_UNION.SAMPLE_REG = (sample_point << UART_SAMPLE_REG_SAMPLE_POINT_OFFSET) | (sample_count<<UART_SAMPLE_REG_SAMPLE_COUNT_OFFSET)|UART_HIGHSPEED_SPEED_MODE3;

        uartx->FRACDIV = fraction_mapping[fraction];

        if ((actual_baudrate >= 3000000) && (actual_baudrate != 8666000)) {
            uartx->LCR_UNION.LCR_CELLS.GUARD = 0x12;    /* delay 2 bits per byte. */
        }

        if (actual_baudrate == 8666000) {
            uartx->LCR_UNION.LCR_CELLS.GUARD = 0x11;    /* delay 1 bits per byte. */
        }
    }
    #ifndef HAL_UART_MODULE_ENABLED
    #define HAL_UART_MODULE_ENABLED
    #endif/*HAL_UART_MODULE_ENABLED*/
    #include "hal_uart.h"

    void uart_set_format_pre_init(UART_REGISTER_T *uartx,
                        hal_uart_word_length_t word_length,
                        hal_uart_stop_bit_t stop_bit,
                        hal_uart_parity_t parity)
    {
        uint8_t byte = 0;

        /* Setup wordlength */
        switch (word_length) {
            case HAL_UART_WORD_LENGTH_5:
                byte |= UART_LCR_WORD_5BITS;
                break;
            case HAL_UART_WORD_LENGTH_6:
                byte |= UART_LCR_WORD_6BITS;
                break;
            case HAL_UART_WORD_LENGTH_7:
                byte |= UART_LCR_WORD_7BITS;
                break;
            case HAL_UART_WORD_LENGTH_8:
                byte |= UART_LCR_WORD_8BITS;
                break;
            default:
                byte |= UART_LCR_WORD_8BITS;
                break;
        }

        /* setup stop bit */
        switch (stop_bit) {
            case HAL_UART_STOP_BIT_1:
                byte |= UART_LCR_STB_1;
                break;
            case HAL_UART_STOP_BIT_2:
                byte |= UART_LCR_STB_2;
                break;
            default:
                byte |= UART_LCR_STB_1;
                break;
        }

        /* setup parity bit */
        switch (parity) {
            case HAL_UART_PARITY_NONE:
                byte |= UART_LCR_PAR_NONE;
                break;
            case HAL_UART_PARITY_ODD:
                byte |= UART_LCR_PAR_ODD;
                break;
            case HAL_UART_PARITY_EVEN:
                byte |= UART_LCR_PAR_EVEN;
                break;
            default:
                byte |= UART_LCR_PAR_NONE;
                break;
        }

        /* DLAB End */
        uartx->LCR_UNION.LCR_CELLS.PAR_STB_WLS = byte;
    }

    void uart_set_fifo_pre_init(UART_REGISTER_T *uartx)
    {
        uartx->FCR_UNION.FCR = UART_FCR_TXTRIG_1 |
                            UART_FCR_RXTRIG_12 |
                            UART_FCR_CLRT_MASK |
                            UART_FCR_CLRR_MASK |
                            UART_FCR_FIFOE_MASK;
    }

    uint8_t uart_get_char_block_pre_init(UART_REGISTER_T *uartx)
    {
        uint32_t LSR;
        uint8_t byte;

        while (1) {
            LSR = uartx->LSR;
            if (LSR & UART_LSR_DR_MASK) {
                byte = (uint8_t)uartx->RBR;
                break;
            }
        }

        return byte;
    }

    uint32_t uart_early_init_done = 0;
    #if KERNELVERSION == 0x3030000
    static int uart_early_init(const struct device *dev)
    {
        ARG_UNUSED(dev);
    #elif KERNELVERSION >= 0x3070000
    static int uart_early_init(void)
    {
    #else
    #error "Unkown supported kernel version"
    #endif
        UART_REGISTER_T *uartx = (UART_REGISTER_T*)(UART0_BASE);
        hal_uart_config_t uart_config = {
            .baudrate = HAL_UART_BAUDRATE_921600,
            .word_length = HAL_UART_WORD_LENGTH_8,
            .stop_bit = HAL_UART_STOP_BIT_1,
            .parity = HAL_UART_PARITY_NONE,
        };
        uart_reset_default_value_pre_init(uartx);
        uart_set_baudrate_pre_init(uartx, 921600);
        uart_set_format_pre_init(uartx, uart_config.word_length, uart_config.stop_bit, uart_config.parity);
        uart_set_fifo_pre_init(uartx);
        uart_early_init_done = 1;
        return 0;
    }

    SYS_INIT(uart_early_init, CONFIG_UART_EARLY_INIT_LEVEL, CONFIG_UART_EARLY_INIT_PRIORITY);

#elif defined(AIR_BTD_IC_MANDATORY_G1)
    /* wait to be ready */
    uint32_t uart_early_init_done = 1;
#else
    #error "Unkown hardware"
#endif

