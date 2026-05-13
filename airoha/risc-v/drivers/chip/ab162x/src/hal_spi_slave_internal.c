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

#include "hal_spi_slave.h"

#ifdef HAL_SPI_SLAVE_MODULE_ENABLED
#include <string.h>
#include "hal_spi_slave_internal.h"
#include "hal_clock.h"
//#include "hal_log.h"
//#include "hal_sleep_manager.h"
//#include "hal_memview.h"
//#include "hal_sleep_manager_internal.h"



static SPIS_REGISTER_T *const g_spi_slave_register[HAL_SPI_SLAVE_MAX] = {(SPIS_REGISTER_T *) SPI_SLAVE_BASE};
static SPIS_PAD_REGISTER_T *const g_spi_slave_pad_register[HAL_SPI_SLAVE_MAX] = {(SPIS_PAD_REGISTER_T *)SPI_SLAVE_PAD_BASE};
#ifdef HAL_SPI_SLAVE_FEATURE_BYPASS
static SPIS_BYPASS_REGISTER_T *const g_spi_slave_bypass_register[HAL_SPI_SLAVE_MAX] = {SPI_SLAVE_BYPASS_0};
#endif
static hal_spi_slave_fsm_status_t g_spi_slave_fsm[MAX_STATUS][MAX_OPERATION_CMD] = {
    /* POWER_OFF_CMD                             POWER_ON_CMD                         CONFIG_READ_CMD                       READ_CMD                               CONFIG_WRITE_CMD                      WRITE_CMD */
    /*PWROFF_STA*/ {HAL_SPI_SLAVE_FSM_INVALID_OPERATION,     HAL_SPI_SLAVE_FSM_SUCCESS_OPERATION, HAL_SPI_SLAVE_FSM_INVALID_OPERATION,  HAL_SPI_SLAVE_FSM_INVALID_OPERATION,   HAL_SPI_SLAVE_FSM_INVALID_OPERATION,  HAL_SPI_SLAVE_FSM_INVALID_OPERATION},
    /*PWRON_STA */ {HAL_SPI_SLAVE_FSM_SUCCESS_OPERATION,     HAL_SPI_SLAVE_FSM_INVALID_OPERATION, HAL_SPI_SLAVE_FSM_SUCCESS_OPERATION,  HAL_SPI_SLAVE_FSM_INVALID_OPERATION,   HAL_SPI_SLAVE_FSM_SUCCESS_OPERATION,  HAL_SPI_SLAVE_FSM_INVALID_OPERATION},
    /*CR_STA    */ {HAL_SPI_SLAVE_FSM_ERROR_PWROFF_AFTER_CR, HAL_SPI_SLAVE_FSM_INVALID_OPERATION, HAL_SPI_SLAVE_FSM_SUCCESS_OPERATION, HAL_SPI_SLAVE_FSM_SUCCESS_OPERATION,   HAL_SPI_SLAVE_FSM_ERROR_CW_AFTER_CR,  HAL_SPI_SLAVE_FSM_ERROR_WRITE_AFTER_CR},
    /*CW_STA    */ {HAL_SPI_SLAVE_FSM_ERROR_PWROFF_AFTER_CW, HAL_SPI_SLAVE_FSM_INVALID_OPERATION, HAL_SPI_SLAVE_FSM_ERROR_CR_AFTER_CW,  HAL_SPI_SLAVE_FSM_ERROR_READ_AFTER_CW, HAL_SPI_SLAVE_FSM_SUCCESS_OPERATION, HAL_SPI_SLAVE_FSM_SUCCESS_OPERATION}
};
#ifdef SPIS_SLEEP_MANAGER_ENABLED
static uint32_t g_spi_slave_ctrl_reg[HAL_SPI_SLAVE_MAX] = {0};
static uint32_t g_spi_slave_ie_reg[HAL_SPI_SLAVE_MAX] = {0};
static uint32_t g_spi_slave_tmout_reg[HAL_SPI_SLAVE_MAX] = {0};
//static uint32_t g_spi_slave_pad_dummy_cnt_reg[HAL_SPI_SLAVE_MAX] = {0};
static uint32_t g_spi_slave_pad_cmd_def0_reg[HAL_SPI_SLAVE_MAX] = {0};
static uint32_t g_spi_slave_pad_cmd_def1_reg[HAL_SPI_SLAVE_MAX] = {0};
static uint32_t g_spi_slave_pad_cmd_def2_reg[HAL_SPI_SLAVE_MAX] = {0};
static sleep_management_lock_request_t g_spi_slave_sleep_handle[HAL_SPI_SLAVE_MAX] = {SLEEP_LOCK_SPI_SLV};
#endif

uint8_t g_last2now_status[2] = {PWROFF_STA, PWROFF_STA};

static inline void update_fsm_status(hal_spi_slave_transaction_status_t *transaction_status, \
                                     hal_spi_slave_callback_event_t int_status, spi_slave_fsm_status_t fsm_status, spi_slave_operation_cmd_t current_command)
{
    transaction_status->interrupt_status = int_status;
    spi_slave_update_status(fsm_status);
    transaction_status->fsm_status = g_spi_slave_fsm[g_last2now_status[0]][current_command];
}

typedef void (*spi_slave_int_callback_t)(hal_spi_slave_port_t spi_port, hal_spi_slave_callback_t user_callback, void *user_data);

static void spi_slave_poweron_callback(hal_spi_slave_port_t spi_port, hal_spi_slave_callback_t user_callback, void *user_data)
{
    hal_spi_slave_transaction_status_t status;
#ifdef SPIS_SLEEP_MANAGER_ENABLED
    /* after receive POWER-ON command, lock sleep */
    hal_sleep_manager_lock_sleep(g_spi_slave_sleep_handle[spi_port]);
#endif
    update_fsm_status(&status, HAL_SPI_SLAVE_EVENT_POWER_ON, PWRON_STA, POWER_ON_CMD);
    /* set slv_on bit here */
    g_spi_slave_register[spi_port]->spislv_trig.field.SPIS_SW_ON = 0x1;
    user_callback(status, user_data);
}

static void spi_slave_poweroff_callback(hal_spi_slave_port_t spi_port, hal_spi_slave_callback_t user_callback, void *user_data)
{
    hal_spi_slave_transaction_status_t status;
    update_fsm_status(&status, HAL_SPI_SLAVE_EVENT_POWER_OFF, PWROFF_STA, POWER_OFF_CMD);
    /* clear slv_on bit here */
    g_spi_slave_register[spi_port]->spislv_trig.field.SPIS_SW_ON = 0x0;
#ifdef SPIS_SLEEP_MANAGER_ENABLED
    /* after spis de-init done, unlock sleep */
    hal_sleep_manager_unlock_sleep(g_spi_slave_sleep_handle[spi_port]);
#endif
    user_callback(status, user_data);
}

static void spi_slave_read_finish_callback(hal_spi_slave_port_t spi_port, hal_spi_slave_callback_t user_callback, void *user_data)
{
    hal_spi_slave_transaction_status_t status;
    update_fsm_status(&status, HAL_SPI_SLAVE_EVENT_RD_FINISH, PWRON_STA, READ_CMD);
    /* clear TX_DMA_SW_READY bit here */
    g_spi_slave_register[spi_port]->spislv_trig.field.SPIS_TXDMA_SW_RDY = 0;
    user_callback(status, user_data);
}

static void spi_slave_write_finish_callback(hal_spi_slave_port_t spi_port, hal_spi_slave_callback_t user_callback, void *user_data)
{
    hal_spi_slave_transaction_status_t status;
    update_fsm_status(&status, HAL_SPI_SLAVE_EVENT_WR_FINISH, PWRON_STA, WRITE_CMD);
    /* clear RX_DMA_SW_READY bit here */
    g_spi_slave_register[spi_port]->spislv_trig.field.SPIS_RXDMA_SW_RDY = 0;
    user_callback(status, user_data);
}

static void spi_slave_read_config_callback(hal_spi_slave_port_t spi_port, hal_spi_slave_callback_t user_callback, void *user_data)
{
    hal_spi_slave_transaction_status_t status;
    update_fsm_status(&status, HAL_SPI_SLAVE_EVENT_CRD_FINISH, CR_STA, CONFIG_READ_CMD);
    user_callback(status, user_data);
}

static void spi_slave_write_config_callback(hal_spi_slave_port_t spi_port, hal_spi_slave_callback_t user_callback, void *user_data)
{
    hal_spi_slave_transaction_status_t status;
    update_fsm_status(&status, HAL_SPI_SLAVE_EVENT_CWR_FINISH, CW_STA, CONFIG_WRITE_CMD);
    user_callback(status, user_data);
}

static void spi_slave_error_callback(hal_spi_slave_port_t spi_port)
{
    spi_slave_update_status(PWRON_STA);
    /* clear TX/RX_DMA_SW_READY bit here */
    g_spi_slave_register[spi_port]->spislv_trig.field.SPIS_TXDMA_SW_RDY  = 0;
    g_spi_slave_register[spi_port]->spislv_trig.field.SPIS_RXDMA_SW_RDY  = 0;
}

static void spi_slave_read_error_callback(hal_spi_slave_port_t spi_port, hal_spi_slave_callback_t user_callback, void *user_data)
{
    hal_spi_slave_transaction_status_t status;

    spi_slave_error_callback(spi_port);
    status.interrupt_status = HAL_SPI_SLAVE_EVENT_RD_ERR;
    status.fsm_status = HAL_SPI_SLAVE_FSM_SUCCESS_OPERATION;
    user_callback(status, user_data);
}

static void spi_slave_write_error_callback(hal_spi_slave_port_t spi_port, hal_spi_slave_callback_t user_callback, void *user_data)
{
    hal_spi_slave_transaction_status_t status;

    spi_slave_error_callback(spi_port);
    status.interrupt_status = HAL_SPI_SLAVE_EVENT_WR_ERR;
    status.fsm_status = HAL_SPI_SLAVE_FSM_SUCCESS_OPERATION;
    user_callback(status, user_data);
}

static void spi_slave_timeout_error_callback(hal_spi_slave_port_t spi_port, hal_spi_slave_callback_t user_callback, void *user_data)
{
    hal_spi_slave_transaction_status_t status;

    spi_slave_error_callback(spi_port);
    status.interrupt_status = HAL_SPI_SLAVE_EVENT_TIMEOUT_ERR;
    status.fsm_status = HAL_SPI_SLAVE_FSM_SUCCESS_OPERATION;
    user_callback(status, user_data);
}

static void spi_slave_direct_mode_callback(hal_spi_slave_port_t spi_port, hal_spi_slave_callback_event_t event, hal_spi_slave_callback_t user_callback, void *user_data)
{
    hal_spi_slave_transaction_status_t status = {.fsm_status = HAL_SPI_SLAVE_FSM_SUCCESS_OPERATION};
    status.interrupt_status = event;

    switch (event) {
        case HAL_SPI_SLAVE_EVENT_IDLE_TIMEOUT  :
            break;
        case HAL_SPI_SLAVE_EVENT_TX_DMA_EMPTY  :
            /* Only notify once to user, there is free space to send data. */
            g_spi_slave_register[spi_port]->spislv_ie.field.SPIS_IE &= ~SPIS_IE_TX_DMA_EMPTY_MASK;
            break;
        case HAL_SPI_SLAVE_EVENT_RX_DMA_FULL   :
            break;
        case HAL_SPI_SLAVE_EVENT_RX_OVERRUN:
            break;
        default:
            break;
    }
    if (user_callback) {
        user_callback(status, user_data);
    }
}
static spi_slave_int_callback_t spi_slave_int_callback[] = {
    spi_slave_read_finish_callback,
    spi_slave_write_finish_callback,
    spi_slave_poweroff_callback,
    spi_slave_poweron_callback,
    spi_slave_read_config_callback,
    spi_slave_write_config_callback,
    spi_slave_read_error_callback,
    spi_slave_write_error_callback,
    spi_slave_timeout_error_callback,
};

void spi_slave_lisr(hal_spi_slave_port_t spi_port, hal_spi_slave_callback_t user_callback, void *user_data)
{
    uint32_t irq_status;
    uint32_t shift_h;
    uint32_t shift_l;
    uint32_t i;
    uint32_t irq_event;

    if (g_spi_slave_register[spi_port]->spislv_ctrl.field.SPIS_DIR_MODE) {
        irq_status = g_spi_slave_register[spi_port]->spislv_int.field.SPIS_INT &g_spi_slave_register[spi_port]->spislv_ie.field.SPIS_IE & SPIS_INT_DIRECT_MODE_MASK;
        irq_status >>= SPIS_INT_DIRECT_MODE_OFFSET;

        for (i = 0; irq_status; i++) {
            if (irq_status & (1 << i)) {
                irq_event = 1 << (i + SPIS_INT_DIRECT_MODE_OFFSET);
                spi_slave_direct_mode_callback(spi_port, irq_event, user_callback, user_data);
                g_spi_slave_register[spi_port]->spislv_int.field.SPIS_INT &= irq_event;
                irq_status &= ~(1 << i);
            }
        }
    } else {
        irq_status = g_spi_slave_register[spi_port]->spislv_int.field.SPIS_INT &g_spi_slave_register[spi_port]->spislv_ie.field.SPIS_IE & SPIS_INT_MASK;
        /* regroup the priority of interrupts for subsequent processing. */
        shift_h = (irq_status & (SPIS_INT_RD_TRANS_FINISH_MASK | SPIS_INT_WR_TRANS_FINISH_MASK | SPIS_INT_POWER_ON_MASK | SPIS_INT_POWER_OFF_MASK)) >> 2;
        shift_l = (irq_status & (SPIS_INT_RD_CFG_FINISH_MASK | SPIS_INT_WR_CFG_FINISH_MASK)) << 4;
        irq_status = shift_h | shift_l | (irq_status & (SPIS_INT_RD_DATA_ERR_MASK | SPIS_INT_WR_DATA_ERR_MASK | SPIS_INT_TMOUT_ERR_MASK));

        /* because more than one interrupt may be raised at the same time, they must be processed one by one at a specify prority. */
        for (i = 0; irq_status; i++) {
            if (irq_status & (1 << i)) {
                spi_slave_int_callback[i](spi_port, user_callback, user_data);
                if (irq_status & shift_h) {
                    g_spi_slave_register[spi_port]->spislv_int.field.SPIS_INT &= (1 << (i + 2));
                } else if (irq_status & shift_l) {
                    /* As only the shift_l[5:4], shift_h[3:0] and irq_status[8:0] can be 1, when program runs here, the variable
                    i must be greater than 3 and less than 6. but, to avoid the warning from code static analysis tool, we do and
                    operation with 0x1F to make sure left shifting is not more than 31 bits. */
                    g_spi_slave_register[spi_port]->spislv_int.field.SPIS_INT &= (1 << ((i - 4) & 0x1F));
                } else {
                    g_spi_slave_register[spi_port]->spislv_int.field.SPIS_INT &= (1 << i);
                }
                irq_status &= ~(1 << i);
            }
        }
    }
}

void spi_slave_init(hal_spi_slave_port_t spi_port, const hal_spi_slave_config_t *spi_config)
{
    /* reset spi slave's status frist */
    // g_spi_slave_register[spi_port]->TRIG_UNION.TRIG_CELLS.SW_RST = 1;
    // g_spi_slave_register[spi_port]->TRIG_UNION.TRIG_CELLS.SW_RST = 0;

    /* user configure parameters */
    switch (spi_config->bit_order) {
        case HAL_SPI_SLAVE_LSB_FIRST:
            g_spi_slave_register[spi_port]->spislv_ctrl.field.SPIS_CTRL0 &= (~(SPIS_CTRL_TXMSBF_MASK | SPIS_CTRL_RXMSBF_MASK));
            break;
        case HAL_SPI_SLAVE_MSB_FIRST:
            g_spi_slave_register[spi_port]->spislv_ctrl.field.SPIS_CTRL0 |= (SPIS_CTRL_TXMSBF_MASK | SPIS_CTRL_RXMSBF_MASK);
            break;
    }

    switch (spi_config->phase) {
        case HAL_SPI_SLAVE_CLOCK_PHASE0:
            g_spi_slave_pad_register[spi_port]->spislv_pad_debug_en.field.SPIS_PAD_CTRL0 &= (~SPIS_CTRL_CPHA_MASK);
            break;
        case HAL_SPI_SLAVE_CLOCK_PHASE1:
            g_spi_slave_pad_register[spi_port]->spislv_pad_debug_en.field.SPIS_PAD_CTRL0 |= SPIS_CTRL_CPHA_MASK;
            break;
    }

    switch (spi_config->polarity) {
        case HAL_SPI_SLAVE_CLOCK_POLARITY0:
            g_spi_slave_pad_register[spi_port]->spislv_pad_debug_en.field.SPIS_PAD_CTRL0 &= (~SPIS_CTRL_CPOL_MASK);
            break;
        case HAL_SPI_SLAVE_CLOCK_POLARITY1:
            g_spi_slave_pad_register[spi_port]->spislv_pad_debug_en.field.SPIS_PAD_CTRL0|= SPIS_CTRL_CPOL_MASK;
            break;
    }

    /* timeout threshold */
    g_spi_slave_register[spi_port]->spislv_tmout_thr.word = spi_config->timeout_threshold;

    /* enable all interrupt, set four-byte address and size, set sw decode bit */
    g_spi_slave_register[spi_port]->spislv_ie.field.SPIS_IE |= SPIS_IE_MASK;
    g_spi_slave_register[spi_port]->spislv_ctrl.field.SPIS_CTRL0 |= SPIS_CTRL_SIZE_OF_ADDR_MASK;
    g_spi_slave_register[spi_port]->spislv_ctrl.field.SPIS_CTRL1 = (SPIS_CTRL_DEC_ADDR_EN_MASK | SPIS_CTRL_SW_RDY_EN_MASK);
    g_spi_slave_register[spi_port]->spislv_ctrl.field.SPIS_DIR_MODE = 0;
}

hal_spi_slave_status_t spi_slave_send(hal_spi_slave_port_t spi_port, const uint8_t *data, uint32_t size)
{
    uint32_t config_size = 0;

    /* return HAL_SPI_SLAVE_STATUS_ERROR if config_size isn't equal to size. */
    config_size = g_spi_slave_register[spi_port]->spislv_trans_length.word;
    if (config_size != size) {
        //log_hal_msgid_error("[SPIS%d][send]:size error. expected:%d request:%d\r\n", 3, spi_port, size, config_size);
        return HAL_SPI_SLAVE_STATUS_ERROR;
    } else {
        /* set src_buffer_addr, buffer_size as size and tx_fifo_ready. */
        g_spi_slave_register[spi_port]->spislv_buffer_base_addr.word = ((uint32_t)data);
        g_spi_slave_register[spi_port]->spislv_buffer_size.word= size;
        g_spi_slave_register[spi_port]->spislv_trig.field.SPIS_TXDMA_SW_RDY = 1;
    }

    return HAL_SPI_SLAVE_STATUS_OK;
}

#ifdef HAL_SPI_SLAVE_FEATURE_DIRECT_MODE
uint32_t spi_slave_send_vfifo(hal_spi_slave_port_t spi_port, const uint8_t *data, uint32_t size)
{
    uint32_t write_address;
    uint32_t write_length;
    uint32_t bytes_to_boundary;

    if (g_spi_slave_register[spi_port]->spislv_txdma_byte_avail.field.SPIS_TXDMA_BYTE_AVAIL == 0) {
        return 0;
    }
    if (g_spi_slave_register[spi_port]->spislv_txdma_ptr.field.SPIS_TXDMA_WPTR >= g_spi_slave_register[spi_port]->spislv_txdma_ptr.field.SPIS_TXDMA_RPTR) {
        bytes_to_boundary = g_spi_slave_register[spi_port]->spislv_txdma_size.field.SPIS_TXDMA_SIZE + 1 - g_spi_slave_register[spi_port]->spislv_txdma_ptr.field.SPIS_TXDMA_WPTR;
    } else {
        bytes_to_boundary = g_spi_slave_register[spi_port]->spislv_txdma_ptr.field.SPIS_TXDMA_RPTR - g_spi_slave_register[spi_port]->spislv_txdma_ptr.field.SPIS_TXDMA_WPTR;
    }

    write_address = (g_spi_slave_register[spi_port]->spislv_txdma_start_addr.word) + g_spi_slave_register[spi_port]->spislv_txdma_ptr.field.SPIS_TXDMA_WPTR;

    if (size > g_spi_slave_register[spi_port]->spislv_txdma_byte_avail.field.SPIS_TXDMA_BYTE_AVAIL) {
        write_length = g_spi_slave_register[spi_port]->spislv_txdma_byte_avail.field.SPIS_TXDMA_BYTE_AVAIL;
    } else {
        write_length = size;
    }

    if (write_length > bytes_to_boundary) {
        memcpy((void *)write_address, data, bytes_to_boundary);
        write_address = (g_spi_slave_register[spi_port]->spislv_txdma_start_addr.word);
        memcpy((void *)write_address, data + bytes_to_boundary, write_length - bytes_to_boundary);
    } else {
        memcpy((void *)write_address, data, write_length);
    }

    g_spi_slave_register[spi_port]->spislv_txdma_sw_con.field.SPIS_TXDMA_SW_MV_BYTE = write_length;
    //g_spi_slave_register[spi_port]->spislv_ie.field.SPIS_IE |= SPIS_IE_TX_DMA_EMPTY_MASK;
    g_spi_slave_register[spi_port]->spislv_dir_mode_dma_con.field.SPIS_TX_DMA_START = 1;

    return write_length;
}

uint32_t spi_slave_receive_vfifo(hal_spi_slave_port_t spi_port, uint8_t *data, uint32_t size)
{
    uint32_t read_address = 0;
    uint32_t read_length = 0;
    uint32_t bytes_to_boundary = 0;

    if (g_spi_slave_register[spi_port]->spislv_rxdma_fifo_cnt.field.SPIS_RXDMA_FIFO_CNT == 0) {
        return 0;
    }
    if (g_spi_slave_register[spi_port]->spislv_rxdma_ptr.field.SPIS_RXDMA_RPTR > g_spi_slave_register[spi_port]->spislv_rxdma_ptr.field.SPIS_RXDMA_WPTR) {
        bytes_to_boundary = g_spi_slave_register[spi_port]->spislv_rxdma_size.field.SPIS_RXDMA_SIZE + 1 - g_spi_slave_register[spi_port]->spislv_rxdma_ptr.field.SPIS_RXDMA_RPTR;
    } else {
        bytes_to_boundary = g_spi_slave_register[spi_port]->spislv_rxdma_ptr.field.SPIS_RXDMA_WPTR - g_spi_slave_register[spi_port]->spislv_rxdma_ptr.field.SPIS_RXDMA_RPTR;
    }

    read_address = (g_spi_slave_register[spi_port]->spislv_rxdma_start_addr.word) + g_spi_slave_register[spi_port]->spislv_rxdma_ptr.field.SPIS_RXDMA_RPTR;

    if (size > g_spi_slave_register[spi_port]->spislv_rxdma_fifo_cnt.field.SPIS_RXDMA_FIFO_CNT) {
        read_length = g_spi_slave_register[spi_port]->spislv_rxdma_fifo_cnt.field.SPIS_RXDMA_FIFO_CNT;
    } else {
        read_length = size;
    }

    if (read_length > bytes_to_boundary) {
        memcpy(data, (void *)read_address, bytes_to_boundary);
        read_address = (g_spi_slave_register[spi_port]->spislv_rxdma_start_addr.word);
        memcpy(data + bytes_to_boundary, (void *)read_address, read_length - bytes_to_boundary);
    } else {
        memcpy(data, (void *)read_address, read_length);
    }

    g_spi_slave_register[spi_port]->spislv_rxdma_sw_con.field.SPIS_RXDMA_SW_MV_BYTE = read_length;

    return read_length;
}

void spi_slave_set_vfifo(hal_spi_slave_port_t spi_port, hal_spi_slave_vfifo_config_t *config)
{
    g_spi_slave_register[spi_port]->spislv_ctrl.field.SPIS_DIR_MODE = 1;

    /* Disable all interrupts in commond mode. */
    g_spi_slave_register[spi_port]->spislv_ie.field.SPIS_IE &= ~SPIS_IE_MASK;

    g_spi_slave_register[spi_port]->spislv_ie.field.SPIS_IE |= SPIS_IE_IDLE_TMOUT_MASK;

    if (config->tx_buffer || config->rx_buffer) {
        if (config->tx_buffer) {
            g_spi_slave_register[spi_port]->spislv_txdma_start_addr.word = ((uint32_t)config->tx_buffer);
            g_spi_slave_register[spi_port]->spislv_txdma_size.field.SPIS_TXDMA_SIZE = config->tx_buffer_size - 1;
            g_spi_slave_register[spi_port]->spislv_txdma_size.field.SPIS_TXDMA_THRE = config->tx_threshold;
            g_spi_slave_register[spi_port]->spislv_dir_mode_dma_con.field.SPIS_TXDMA_TRANS_TYPE = config->transfer_type;
            g_spi_slave_register[spi_port]->spislv_dir_mode_dma_con.field.SPIS_TX_DMA_START  = 1;
            //g_spi_slave_register[spi_port]->spislv_ie.field.SPIS_IE |= SPIS_IE_TX_DMA_EMPTY_MASK;
        }

        if (config->rx_buffer) {
            g_spi_slave_register[spi_port]->spislv_rxdma_start_addr.word = ((uint32_t)config->rx_buffer);
            g_spi_slave_register[spi_port]->spislv_rxdma_size.field.SPIS_RXDMA_SIZE = config->rx_buffer_size - 1;
            g_spi_slave_register[spi_port]->spislv_rxdma_size.field.SPIS_RXDMA_THRE = config->rx_threshold;
            g_spi_slave_register[spi_port]->spislv_dir_mode_dma_con.field.SPIS_RXDMA_TRANS_TYPE = config->transfer_type;
            g_spi_slave_register[spi_port]->spislv_dir_mode_dma_con.field.SPIS_RX_DMA_START = 1;
            //g_spi_slave_register[spi_port]->spislv_ie.field.SPIS_IE |= (SPIS_IE_RX_OVERRUN_MASK | SPIS_IE_RX_DMA_FULL_MASK);
        }
    } else {
        g_spi_slave_register[spi_port]->spislv_dir_mode_fifo_con.field.SPIS_TX_FIFO_THRE = config->tx_threshold;
        g_spi_slave_register[spi_port]->spislv_dir_mode_fifo_con.field.SPIS_RX_FIFO_THRE = config->rx_threshold;
        //g_spi_slave_register[spi_port]->spislv_ie.field.SPIS_IE |= (SPIS_IE_TX_FIFO_EMPTY_MASK | SPIS_IE_RX_FIFO_FULL_MASK | SPIS_IE_RX_OVERRUN_MASK);
    }
}

uint32_t spi_slave_get_vfifo_available_send_space(hal_spi_slave_port_t spi_port)
{
    return g_spi_slave_register[spi_port]->spislv_txdma_byte_avail.field.SPIS_TXDMA_BYTE_AVAIL;
}

uint32_t spi_slave_get_vfifo_available_data_bytes(hal_spi_slave_port_t spi_port)
{
    return g_spi_slave_register[spi_port]->spislv_rxdma_fifo_cnt.field.SPIS_RXDMA_FIFO_CNT;
}
#endif

hal_spi_slave_status_t spi_slave_query_config_info(hal_spi_slave_port_t spi_port, uint32_t *address, uint32_t *length)
{
    if ((g_spi_slave_register[spi_port]->spislv_sta.field.SPIS_STA & 0xff) != (SPIS_STA_CFG_SUCCESS_MASK | SPIS_STA_SLV_ON_MASK)) {
        return HAL_SPI_SLAVE_STATUS_ERROR;
    }

    *address = g_spi_slave_register[spi_port]->spislv_trans_addr.field.SPIS_TRANS_ADDR;
    *length = g_spi_slave_register[spi_port]->spislv_trans_length.field.SPIS_TRANS_LENGTH;

    return HAL_SPI_SLAVE_STATUS_OK;
}

hal_spi_slave_status_t spi_slave_receive(hal_spi_slave_port_t spi_port, uint8_t *buffer, uint32_t size)
{
    uint32_t config_size = 0;

    /* return HAL_SPI_SLAVE_STATUS_ERROR if config_size isn't equal to size */
    config_size = g_spi_slave_register[spi_port]->spislv_trans_length.field.SPIS_TRANS_LENGTH;
    if (config_size != size) {
        //log_hal_msgid_error("[SPIS%d][receive]:size error. expected:%d request:%d\r\n", 3, spi_port, size, config_size);
        return HAL_SPI_SLAVE_STATUS_ERROR;
    } else {
        /* set src_buffer_addr, buffer_size as size and rx_fifo_ready. */
        g_spi_slave_register[spi_port]->spislv_buffer_base_addr.field.SPIS_BUFFER_BASE_ADDR= ((uint32_t)buffer);
        g_spi_slave_register[spi_port]->spislv_buffer_size.field.SPIS_BUFFER_SIZE = size;
        g_spi_slave_register[spi_port]->spislv_trig.field.SPIS_RXDMA_SW_RDY = 1;
    }

    return HAL_SPI_SLAVE_STATUS_OK;
}

void spi_slave_set_early_miso(hal_spi_slave_port_t spi_port, hal_spi_slave_early_miso_t early_miso)
{
    switch (early_miso) {
        case HAL_SPI_SLAVE_EARLY_MISO_DISABLE:
            g_spi_slave_register[spi_port]->spislv_ctrl.field.SPIS_MISO_EARLY_TRANS = 0;
            break;
        case HAL_SPI_SLAVE_EARLY_MISO_ENABLE:
            g_spi_slave_register[spi_port]->spislv_ctrl.field.SPIS_MISO_EARLY_TRANS = 1;
            break;
    }
}

void spi_slave_set_command(hal_spi_slave_port_t spi_port, hal_spi_slave_command_type_t command, uint8_t value)
{
    switch (command) {
        case HAL_SPI_SLAVE_CMD_WS:
            g_spi_slave_pad_register[spi_port]->spislv_pad_cmd_def1.field.SPIS_PAD_CMD_WS = value;
            break;
        case HAL_SPI_SLAVE_CMD_RS:
            g_spi_slave_pad_register[spi_port]->spislv_pad_cmd_def1.field.SPIS_PAD_CMD_RS = value;
            break;
        case HAL_SPI_SLAVE_CMD_WR:
            g_spi_slave_pad_register[spi_port]->spislv_pad_cmd_def2.field.SPIS_PAD_CMD_WR = value;
            break;
        case HAL_SPI_SLAVE_CMD_RD:
            g_spi_slave_pad_register[spi_port]->spislv_pad_cmd_def2.field.SPIS_PAD_CMD_RD = value;
            break;
        case HAL_SPI_SLAVE_CMD_POWEROFF:
            g_spi_slave_pad_register[spi_port]->spislv_pad_cmd_def1.field.SPIS_PAD_CMD_PWOFF = value;
            break;
        case HAL_SPI_SLAVE_CMD_POWERON:
            g_spi_slave_pad_register[spi_port]->spislv_pad_cmd_def1.field.SPIS_PAD_CMD_PWON = value;
            break;
        case HAL_SPI_SLAVE_CMD_CW:
            g_spi_slave_pad_register[spi_port]->spislv_pad_cmd_def2.field.SPIS_PAD_CMD_CW = value;
            break;
        case HAL_SPI_SLAVE_CMD_CR:
            g_spi_slave_pad_register[spi_port]->spislv_pad_cmd_def2.field.SPIS_PAD_CMD_CR = value;
            break;
        case HAL_SPI_SLAVE_CMD_CT:
            g_spi_slave_pad_register[spi_port]->spislv_pad_cmd_def0.field.SPIS_PAD_CMD_CT = value;
            break;
    }
}

void spi_slave_reset_default(hal_spi_slave_port_t spi_port)
{
    uint32_t int_status;

    g_spi_slave_register[spi_port]->spislv_trig.field.SPIS_SW_RST  = 1;
    
    g_spi_slave_register[spi_port]->spislv_ctrl.word = 0x00000100;
    int_status = g_spi_slave_register[spi_port]->spislv_int.word;
    g_spi_slave_register[spi_port]->spislv_int.word = int_status;
    g_spi_slave_register[spi_port]->spislv_ie.field.SPIS_IE = 0;
    g_spi_slave_register[spi_port]->spislv_tmout_thr.word = 0x000000ff;
    g_spi_slave_register[spi_port]->spislv_buffer_base_addr.field.SPIS_BUFFER_BASE_ADDR= 0;
    g_spi_slave_register[spi_port]->spislv_buffer_size.field.SPIS_BUFFER_SIZE = 0;
    g_spi_slave_pad_register[spi_port]->spislv_pad_cmd_def0.field.SPIS_PAD_DUMMY_CNT = 0;
    g_spi_slave_pad_register[spi_port]->spislv_pad_cmd_def0.field.SPIS_PAD_CMD_CT = 0x18;
    g_spi_slave_pad_register[spi_port]->spislv_pad_cmd_def1.field.SPIS_PAD_CMD_PWOFF = 0x02;
    g_spi_slave_pad_register[spi_port]->spislv_pad_cmd_def1.field.SPIS_PAD_CMD_PWON = 0x24;
    g_spi_slave_pad_register[spi_port]->spislv_pad_cmd_def1.field.SPIS_PAD_CMD_RS = 0x06;
    g_spi_slave_pad_register[spi_port]->spislv_pad_cmd_def1.field.SPIS_PAD_CMD_WS = 0x08;
    g_spi_slave_pad_register[spi_port]->spislv_pad_cmd_def2.field.SPIS_PAD_CMD_CR = 0x0a;
    g_spi_slave_pad_register[spi_port]->spislv_pad_cmd_def2.field.SPIS_PAD_CMD_CW = 0x0c;
    g_spi_slave_pad_register[spi_port]->spislv_pad_cmd_def2.field.SPIS_PAD_CMD_RD = 0x81;
    g_spi_slave_pad_register[spi_port]->spislv_pad_cmd_def2.field.SPIS_PAD_CMD_WR = 0x0e;
    g_spi_slave_pad_register[spi_port]->spislv_pad_dlysel0.word = 0;
    g_spi_slave_pad_register[spi_port]->spislv_pad_dlysel1.word = 0;
    g_spi_slave_pad_register[spi_port]->spislv_pad_dlysel2.word = 0;

    g_spi_slave_register[spi_port]->spislv_trig.field.SPIS_SW_ON = 0;
    //printf("[hal][spis] CTRL:%x", g_spi_slave_register[spi_port]->spislv_ctrl.word);
}

void hal_spi_slave_dump(uint32_t spi_port)
{
#if 0
    printk("-----------SPIS%d Register Dump-----------", spi_port);
    printk("CTRL: 0x%08x, DEF1: 0x%08x",    g_spi_slave_register[spi_port]->spislv_ctrl.word,
                                            g_spi_slave_pad_register[spi_port]->spislv_pad_cmd_def1.word
    );
#endif
}

#ifdef SPIS_SLEEP_MANAGER_ENABLED
void spi_slave_backup_register_callback(void *data)
{
    hal_spi_slave_port_t slave_port;

    for (slave_port = HAL_SPI_SLAVE_0; slave_port < HAL_SPI_SLAVE_MAX; slave_port++) {
        /* backup related spi_slave register values */
        g_spi_slave_ctrl_reg[slave_port] = g_spi_slave_register[slave_port]->spislv_ctrl.word;
        g_spi_slave_ie_reg[slave_port] = g_spi_slave_register[slave_port]->spislv_ie.word;
        g_spi_slave_tmout_reg[slave_port] = g_spi_slave_register[slave_port]->spislv_tmout_thr.word;
        g_spi_slave_pad_cmd_def0_reg[slave_port] = g_spi_slave_pad_register[slave_port]->spislv_pad_cmd_def0.word;
        g_spi_slave_pad_cmd_def1_reg[slave_port] = g_spi_slave_pad_register[slave_port]->spislv_pad_cmd_def1.word;
        g_spi_slave_pad_cmd_def2_reg[slave_port] = g_spi_slave_pad_register[slave_port]->spislv_pad_cmd_def2.word;
    }
}

void spi_slave_restore_register_callback(void *data)
{
    hal_spi_slave_port_t slave_port;

    for (slave_port = HAL_SPI_SLAVE_0; slave_port < HAL_SPI_SLAVE_MAX; slave_port++) {
        /* restore related spi_slave register values */
        g_spi_slave_register[slave_port]->spislv_ctrl.word = g_spi_slave_ctrl_reg[slave_port];
        g_spi_slave_register[slave_port]->spislv_ie.word = g_spi_slave_ie_reg[slave_port];
        g_spi_slave_register[slave_port]->spislv_tmout_thr.word = g_spi_slave_tmout_reg[slave_port];
        g_spi_slave_pad_register[slave_port]->spislv_pad_cmd_def0.word = g_spi_slave_pad_cmd_def0_reg[slave_port];
        g_spi_slave_pad_register[slave_port]->spislv_pad_cmd_def1.word = g_spi_slave_pad_cmd_def1_reg[slave_port];
        g_spi_slave_pad_register[slave_port]->spislv_pad_cmd_def2.word = g_spi_slave_pad_cmd_def2_reg[slave_port];
    }
}
#endif


#ifdef HAL_SPI_SLAVE_FEATURE_BYPASS
hal_spi_slave_status_t spi_slave_config_bypass(hal_spi_slave_port_t spi_port, const hal_spi_slave_bypass_config_t *bypass_config)
{
    uint32_t tmp;

#ifdef HAL_SPI_MASTER_MODULE_ENABLED
    if (HAL_SPI_MASTER_BUSY == spi_master_get_status(bypass_config->port)) {
        return HAL_SPI_SLAVE_STATUS_ERROR_BUSY;
    }
#endif
    tmp = g_spi_slave_bypass_register[spi_port]->BYPASS_CTRL;
    tmp &= ~SPIS_BYPASS_CS_ENABLE_MASK;
    tmp |= 1 << (SPIS_BYPASS_CS0_ENABLE_OFFSET + bypass_config->cs);

    switch (bypass_config->mode) {
        case HAL_SPI_SLAVE_BYPASS_MODE_W:
            tmp |= SPIS_BYPASS_SIO_ENABLE_MASK;
            break;
        case HAL_SPI_SLAVE_BYPASS_MODE_R:
            tmp &= ~SPIS_BYPASS_SIO_ENABLE_MASK;
            break;
        case HAL_SPI_SLAVE_BYPASS_MODE_RW:
            tmp &= ~SPIS_BYPASS_SIO_ENABLE_MASK;
            tmp |= SPIS_BYPASS_MOSI_ENABLE_MASK;
            break;
        case HAL_SPI_SLAVE_BYPASS_MODE_MAX:
            //log_hal_msgid_error("[SPIS%d]:bypass config error.\r\n", 1, spi_port);
            break;
    }

    tmp &= ~SPIS_BYPASS_MASTER_SELECT_MASK;
    tmp |= (SPIS_BYPASS_MASTER_SELECT_MASK & (bypass_config->port << SPIS_BYPASS_MASTER_SELECT_OFFSET));

    g_spi_slave_bypass_register[spi_port]->BYPASS_CTRL = tmp;
    return HAL_SPI_SLAVE_STATUS_OK;
}

void spi_slave_enable_bypass(hal_spi_slave_port_t spi_port)
{
    g_spi_slave_bypass_register[spi_port]->BYPASS_CTRL |= SPIS_BYPASS_ENABLE_MASK;
}

void spi_slave_disable_bypass(hal_spi_slave_port_t spi_port)
{
    g_spi_slave_bypass_register[spi_port]->BYPASS_CTRL &= ~SPIS_BYPASS_ENABLE_MASK;
}
#endif
#endif /*HAL_SPI_SLAVE_MODULE_ENABLED*/

