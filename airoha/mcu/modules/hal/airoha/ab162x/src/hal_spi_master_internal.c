/* Copyright Statement:
 *
 * (C) 2017  Airoha Technology Corp. All rights reserved.
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

#include "hal_spi_master.h"

#ifdef HAL_SPI_MASTER_MODULE_ENABLED
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "hal.h"
#include "hal_platform.h"
#include "hal_log.h"
#include "hal_nvic.h"
#include "hal_spi_master_internal.h"
#include "hal_memview.h"
#include "hal_sleep_manager.h"
#include "hal_sleep_manager_internal.h"

/***********************************************************************************************
 * Preprocessor Definitions
***********************************************************************************************/
#define   SPIM_DEFAULT_TIMING       (5) /* total = (x * 9.6ns) */

/***********************************************************************************************
 * Private Variabable Declare
***********************************************************************************************/
static SPIM_REGISTER_T *const           g_spi_master_register[HAL_SPI_MASTER_MAX] = {(SPIM_REGISTER_T *)SPI_MASTER_0_BASE, (SPIM_REGISTER_T *)SPI_MASTER_1_BASE, (SPIM_REGISTER_T *)SPI_MASTER_2_BASE};
ATTR_ZIDATA_IN_TCM static hal_spi_master_transfer_info_t   g_priv_info[HAL_SPI_MASTER_MAX];


/***********************************************************************************************
 * Function Implement
***********************************************************************************************/
void spi_master_isr_handler(uint8_t master_port, hal_spi_master_callback_t user_callback, void *user_data)
{
    hal_spi_master_callback_event_t event;
    hal_spi_master_transfer_info_t *pinfo = &g_priv_info[master_port];
    uint32_t interrupt_status = 0;

    interrupt_status = g_spi_master_register[master_port]->spimst_int.word;
    if (interrupt_status & 0x1) {
        event = (pinfo->transfer_direction == SPI_MASTER_TX) ? HAL_SPI_MASTER_EVENT_SEND_FINISHED : HAL_SPI_MASTER_EVENT_RECEIVE_FINISHED;
        //if (pinfo->mode == SPI_MASTER_MODE_FIFO) {
        //    spi_master_config_fifo(master_port, SPI_MASTER_RX, pinfo->transfer_config.receive_buffer, pinfo->transfer_config->receive_length);
        //}
        /* This is just for data corruption check */
        if (NULL != user_callback) {
            user_callback(event, user_data);
        }
    }
    //printk("[hal][spim] irq triggered, status:%x!!!! ", interrupt_status);
}

#ifdef HAL_SLEEP_MANAGER_ENABLED
static hal_spi_master_back_memory_t  spim_bk_mem[HAL_SPI_MASTER_MAX] = {0};

hal_spi_master_status_t  spi_master_ao_get_backup_info(hal_spi_master_port_t master_port, ao_backup_format_table_t *backup_info)
{
    if (master_port > HAL_SPI_MASTER_1 || backup_info == NULL) {
        return HAL_SPI_MASTER_STATUS_INVALID_PARAMETER;
    }
    backup_info->module_base_addr = (uint32_t)(g_spi_master_register[master_port]);
    backup_info->module_end_addr  = (uint32_t)(g_spi_master_register[master_port]) + 0x24;
    backup_info->module_backup_enable = 1;
    return HAL_SPI_MASTER_STATUS_OK;
}

void spi_master_backup_register_callback(void *data)
{
    uint32_t i;
    hal_spi_master_port_t master_port;

    for (master_port = HAL_SPI_MASTER_2; master_port < HAL_SPI_MASTER_MAX; master_port++) {
        /* backup related spi_master register values */
        spim_bk_mem[master_port].spimst_tx_src = g_spi_master_register[master_port]->spimst_tx_src.word;
        spim_bk_mem[master_port].spimst_rx_dst = g_spi_master_register[master_port]->spimst_rx_dst.word;
        spim_bk_mem[master_port].spimst_ctrl0  = g_spi_master_register[master_port]->spimst_ctrl0.word;
        spim_bk_mem[master_port].spimst_ctrl1  = g_spi_master_register[master_port]->spimst_ctrl1.word;
        spim_bk_mem[master_port].spimst_cfg0   = g_spi_master_register[master_port]->spimst_cfg0.word;
        spim_bk_mem[master_port].spimst_cfg1   = g_spi_master_register[master_port]->spimst_cfg1.word;
        spim_bk_mem[master_port].spimst_cfg2   = g_spi_master_register[master_port]->spimst_cfg2.word;
        spim_bk_mem[master_port].spimst_cfg3   = g_spi_master_register[master_port]->spimst_cfg3.word;
        spim_bk_mem[master_port].spimst_cfg5   = g_spi_master_register[master_port]->spimst_cfg5.word;
        spim_bk_mem[master_port].spimst_ie       = g_spi_master_register[master_port]->spimst_cfg4.field.SPIM_IE;
        for (i = 0; i <= 9; i++) {
            g_spi_master_register[master_port]->spimst_cfg4.field.SPIM_SEL_ADDR = i;
            spim_bk_mem[master_port].spimst_cfg4[i] = g_spi_master_register[master_port]->spimst_cfg4.field.SPIM_SEL_RDATA;
        }
    }
}

void spi_master_restore_register_callback(void *data)
{
    uint32_t i;
    hal_spi_master_port_t master_port;

    for (master_port = HAL_SPI_MASTER_2; master_port < HAL_SPI_MASTER_MAX; master_port++) {
        /* restore related spi_master register values */
        g_spi_master_register[master_port]->spimst_tx_src.word = spim_bk_mem[master_port].spimst_tx_src;
        g_spi_master_register[master_port]->spimst_rx_dst.word = spim_bk_mem[master_port].spimst_rx_dst;
        g_spi_master_register[master_port]->spimst_ctrl0.word  = spim_bk_mem[master_port].spimst_ctrl0;
        g_spi_master_register[master_port]->spimst_ctrl1.word  = spim_bk_mem[master_port].spimst_ctrl1;
        g_spi_master_register[master_port]->spimst_cfg0.word   = spim_bk_mem[master_port].spimst_cfg0;
        g_spi_master_register[master_port]->spimst_cfg1.word   = spim_bk_mem[master_port].spimst_cfg1;
        g_spi_master_register[master_port]->spimst_cfg2.word   = spim_bk_mem[master_port].spimst_cfg2;
        g_spi_master_register[master_port]->spimst_cfg3.word   = spim_bk_mem[master_port].spimst_cfg3;
        g_spi_master_register[master_port]->spimst_cfg5.word   = spim_bk_mem[master_port].spimst_cfg5;
        for (i = 0; i <= 9; i++) {
            g_spi_master_register[master_port]->spimst_cfg4.word = ((spim_bk_mem[master_port].spimst_cfg4[i]) << 8) | i;
        }
        g_spi_master_register[master_port]->spimst_cfg4.field.SPIM_IE = spim_bk_mem[master_port].spimst_ie;
    }
}
#endif

void spi_master_hw_reset(uint8_t master_port)
{
    uint32_t i, REG_INT;

    g_spi_master_register[master_port]->spimst_cfg4.field.SPIM_IE = 0;
    g_spi_master_register[master_port]->spimst_ctrl0.word = 0;
    g_spi_master_register[master_port]->spimst_ctrl1.word = 0;
    g_spi_master_register[master_port]->spimst_tx_src.field.SPIM_TX_SRC = 0;
    g_spi_master_register[master_port]->spimst_rx_dst.field.SPIM_RX_DST = 0;
    g_spi_master_register[master_port]->spimst_cfg0.word = 0;
    g_spi_master_register[master_port]->spimst_cfg1.word = 0;
    g_spi_master_register[master_port]->spimst_cfg2.word = 0;
    g_spi_master_register[master_port]->spimst_cfg3.word = 0;
    for (i = 0; i <= 9; i++) {
        g_spi_master_register[master_port]->spimst_cfg4.field.SPIM_SEL_ADDR = i;
        g_spi_master_register[master_port]->spimst_cfg4.field.SPIM_SEL_WDATA = 0;
    }
    g_spi_master_register[master_port]->spimst_trig.field.SPIM_RST = 1;
    REG_INT = g_spi_master_register[master_port]->spimst_int.field.SPIM_INT;
    REG_INT = REG_INT;
}

void spi_master_set_frequency(uint8_t master_port, uint32_t spi_clk_hz, spi_master_clk_sel_t clk_src_sel)
{
    uint32_t sck_count;
    uint32_t source_clock_freq = SPI_MASTER_32M_CLOCK_FREQUENCY;

    switch (clk_src_sel) {
        case SPI_MASTER_CLOCK_SOURCE_26MHZ:
            source_clock_freq = SPI_MASTER_26M_CLOCK_FREQUENCY;
            break;
        case SPI_MASTER_CLOCK_SOURCE_32MHZ:
            source_clock_freq = SPI_MASTER_32M_CLOCK_FREQUENCY;
            break;
        case SPI_MASTER_CLOCK_SOURCE_78MHZ:
            source_clock_freq = SPI_MASTER_78M_CLOCK_FREQUENCY;
            break;
    }
    sck_count = source_clock_freq / (spi_clk_hz * 2) - 1;
    g_spi_master_register[master_port]->spimst_cfg1.word = ((sck_count << SPIM_CFG1_SCK_LOW_COUNT_OFFSET) | sck_count);
}

void spi_master_init_config(uint8_t master_port, const hal_spi_master_config_t *spi_config, spi_master_clk_sel_t src_clk_sel)
{
    uint32_t reg_val = 0;

    spi_master_set_frequency(master_port, spi_config->clock_frequency, src_clk_sel);

    /* config bit order */
    reg_val = g_spi_master_register[master_port]->spimst_ctrl0.word;
    reg_val &= ~(SPIM_CTRL0_TXMSBF_MASK | SPIM_CTRL0_RXMSBF_MASK);
    reg_val |= (spi_config->bit_order << SPIM_CTRL0_TXMSBF_OFFSET) | (spi_config->bit_order << SPIM_CTRL0_RXMSBF_OFFSET);

    /* config cpol and cpha */
    reg_val &= ~(SPIM_CTRL0_CPOL_MASK | SPIM_CTRL0_CPHA_MASK | SPIM_CTRL0_TYPE_MASK);
    reg_val |= (spi_config->polarity << SPIM_CTRL0_CPOL_OFFSET);
    reg_val |= (spi_config->phase << SPIM_CTRL0_CPHA_OFFSET);

    g_spi_master_register[master_port]->spimst_ctrl0.word = reg_val;
    g_spi_master_register[master_port]->spimst_cfg4.word = (9 | (spi_config->slave_port << SPIM_CFG4_SEL_WDATA_OFFSET));
}

void spi_master_config_fifo(uint8_t master_port, spi_master_direction_t dir, uint8_t *buff, uint8_t size)
{
    int i = 0, offset = 0;
    int count = 0;
    uint32_t mdata = 0;

    count = (size / 4 + 1);
    if (dir == SPI_MASTER_TX) {
        /*reset fifo and state machine*/
        g_spi_master_register[master_port]->spimst_trig.field.SPIM_RST = 1;
        /* write data to fifo*/
        for (i = 0; i < count; i++) {
            memcpy(&mdata, &buff[offset], 4);
            g_spi_master_register[master_port]->spimst_tx_data.word = mdata;
            offset += 4;
        }
    } else {
        uint32_t remain_len = size;
        for (i = 0; i < count; i++) {
            mdata = g_spi_master_register[master_port]->spimst_rx_data.word;
            if (remain_len > 4) {
                memcpy(&buff[offset], &mdata, 4);
                remain_len -= 4;
                offset += 4;
            } else {
                memcpy(&buff[offset], &mdata, remain_len);
                return;
            }
        }
    }
}

ATTR_TEXT_IN_TCM void  spi_master_start_transfer(uint8_t master_port, spi_master_mode_t mode, bool start)
{
    hal_spi_master_transfer_info_t *pinfo = &g_priv_info[master_port];
    if (mode == SPI_MASTER_MODE_DMA) {
        if (pinfo->transfer_config.send_data != NULL) {
            g_spi_master_register[master_port]->spimst_tx_src.word = (uint32_t) hal_memview_mcu_to_infrasys((uint32_t)pinfo->transfer_config.send_data);
        }
        if (pinfo->transfer_config.receive_buffer != NULL) {
            g_spi_master_register[master_port]->spimst_rx_dst.word = (uint32_t) hal_memview_mcu_to_infrasys((uint32_t)pinfo->transfer_config.receive_buffer);
        }
    }
    if (start) {
        g_spi_master_register[master_port]->spimst_cmd_act.word = SPIMST_CMD_ACT_SPIM_CMD_ACT_MASK;
    }
}

void spi_master_set_advanced_config(uint8_t master_port, const hal_spi_master_advanced_config_t *advanced_config)
{
    uint32_t reg_val = 0;

    reg_val = g_spi_master_register[master_port]->spimst_ctrl1.word;
    reg_val &= ~(SPIM_CTRL1_ENDIAN_MASK | SPIM_CTRL1_CS_POL_MASK | SPIM_CTRL1_SAMPLE_SEL_MASK);
    reg_val |= (advanced_config->byte_order << SPIM_CTRL1_ENDIAN_OFFSET);
    reg_val |= (advanced_config->chip_polarity << SPIM_CTRL1_CS_POL_OFFSET);
    reg_val |= (advanced_config->sample_select << SPIM_CTRL1_SAMPLE_SEL_OFFSET);
    g_spi_master_register[master_port]->spimst_ctrl1.word = reg_val;
    g_spi_master_register[master_port]->spimst_ctrl1.field.SPIM_GET_DLY = (uint8_t)(advanced_config->get_tick);
}

void spi_master_set_rwaddr(hal_spi_master_port_t master_port, spi_master_direction_t type, const uint8_t *addr)
{
    switch (type) {
        case SPI_MASTER_TX:
            g_spi_master_register[master_port]->spimst_tx_src.field.SPIM_TX_SRC = (uint32_t) hal_memview_mcu_to_infrasys((uint32_t)addr);
            break;
        case SPI_MASTER_RX:
            g_spi_master_register[master_port]->spimst_rx_dst.field.SPIM_RX_DST = (uint32_t) hal_memview_mcu_to_infrasys((uint32_t)addr);
            break;
    }
}

void spi_master_set_cs_timing(uint8_t master_port, hal_spi_master_chip_select_timing_t *chip_select_timing)
{
    g_spi_master_register[master_port]->spimst_cfg0.word = (chip_select_timing->chip_select_setup_count << 16) | chip_select_timing->chip_select_hold_count;
    g_spi_master_register[master_port]->spimst_cfg2.field.SPIM_CS_IDLE_CNT = chip_select_timing->chip_select_idle_count;
}

uint32_t  spi_master_ioctl(uint8_t master_port, uint32_t cmd, uint32_t arg)
{
    uint32_t  rslt = 0;
    hal_spi_master_back_memory_t *pmem = &spim_bk_mem[master_port];

    switch (cmd) {
        case SPIM_SET_BT_EN:      {
            g_spi_master_register[master_port]->spimst_cfg3.field.SPIM_BT_HW_EN = arg & 0x1;
        };
        break;
        case SPIM_GET_BUSY_STATUS: {
            rslt = (g_spi_master_register[master_port]->spimst_sta.word & SPIMST_STA_SPIM_BUSY_MASK);
        }
        break;
        case SPIM_GET_INT_STATUS: {
            rslt = g_spi_master_register[master_port]->spimst_int.word;
        }
        break;
        case SPIM_SET_RESUME:     {
            g_spi_master_register[master_port]->spimst_trig.word = SPIMST_TRIG_SPIM_RESUME_MASK;
        }
        break;
        case SPIM_SET_CMD_CNT:    {
            g_spi_master_register[master_port]->spimst_cfg3.field.SPIM_COMMAND_CNT = (arg & 0xF);
        }
        break;
        case SPIM_SET_DUMMY_CNT:  {
            g_spi_master_register[master_port]->spimst_cfg3.field.SPIM_DUMMY_CNT  = (arg & 0xF);
        }
        break;
        case SPIM_SET_IE:         {
            g_spi_master_register[master_port]->spimst_cfg4.field.SPIM_IE = (arg & 0x1);
        }
        break;
        case SPIM_SET_DEASSERT:   {
            g_spi_master_register[master_port]->spimst_ctrl0.field.SPIM_DEASSERT_EN = (arg & 0x1);
        }
        break;

        case SPIM_SET_TRANS_MODE: {
            g_spi_master_register[master_port]->spimst_ctrl0.word &= ~(SPIM_CTRL0_TYPE_MASK);
            g_spi_master_register[master_port]->spimst_ctrl0.word |= ((arg & 0x3) << SPIM_CTRL0_TYPE_OFFSET);
            g_priv_info[master_port].spim_bus_type = (arg & 0x3);
        }
        break;

        case SPIM_SET_TRANS_RW: {
            if (arg == 0) {
                g_spi_master_register[master_port]->spimst_ctrl0.word &= ~(SPIM_CTRL0_RW_MODE_MASK);
            } else {
                g_spi_master_register[master_port]->spimst_ctrl0.word |= (SPIM_CTRL0_RW_MODE_MASK);
            }
        }
        break;
        case SPIM_SET_CHIP_SEL: {
            if (pmem->spimst_cs != (arg & 0xF)) {
                g_spi_master_register[master_port]->spimst_cfg4.word = (9 | ((arg & 0x7) << SPIM_CFG4_SEL_WDATA_OFFSET));
            }
            pmem->spimst_cs = (arg & 0xF);
        }
        break;
    }
    return rslt;
}

ATTR_TEXT_IN_TCM hal_spi_master_status_t  spi_master_check_tranfer_config(uint8_t master_port, hal_spi_master_send_and_receive_config_t *tranfer_config)
{
    hal_spi_master_send_and_receive_config_t *pinfo = &g_priv_info[master_port].transfer_config;
    spi_master_mode_t mode = g_priv_info[master_port].mode;

    if (tranfer_config->receive_buffer == pinfo->receive_buffer && tranfer_config->send_data == pinfo->send_data &&
        tranfer_config->receive_length == pinfo->receive_length && tranfer_config->send_length == pinfo->send_length &&
        mode == SPI_MASTER_MODE_DMA) {
        return HAL_SPI_MASTER_STATUS_OK;
    } else {
        return HAL_SPI_MASTER_STATUS_ERROR;
    }
}

hal_spi_master_status_t spi_master_config_transfer(uint8_t master_port, hal_spi_master_send_and_receive_config_t *transfer_config, spi_master_mode_t mode)
{
    uint32_t temp = 0;
    uint32_t reg_val = 0;
    hal_spi_master_transfer_info_t *pinfo = &g_priv_info[master_port];
    int err_no = 0;

    if ((pinfo->spim_bus_type == HAL_SPI_MASTER_SINGLE_MODE) && (mode == SPI_MASTER_MODE_DMA) && (transfer_config->receive_length != 0)  && (transfer_config->send_length > transfer_config->receive_length)) {
        log_hal_msgid_error("[hal][spim%d] spi_master_config_transfer fail: snd size(%d) > recv size(%d) in single mode\r\n", 2, transfer_config->send_length, transfer_config->receive_length);
        return HAL_SPI_MASTER_STATUS_INVALID_PARAMETER;
    }

    do {
        pinfo->transfer_config = *transfer_config;
        pinfo->mode = mode;

        /*reset fifo and state machine*/
        g_spi_master_register[master_port]->spimst_trig.field.SPIM_RST = 1;

        /* config DMA/FIFO mode */
        reg_val = g_spi_master_register[master_port]->spimst_ctrl1.word;
        reg_val &= ~(SPIMST_CTRL1_SPIM_TXDMA_EN_MASK | SPIMST_CTRL1_SPIM_RXDMA_EN_MASK);

        if (mode == SPI_MASTER_MODE_DMA) {
            if (transfer_config->send_length > 0) {
#ifdef HAL_CACHE_MODULE_ENABLED
                if (true == hal_cache_is_cacheable((uint32_t)(transfer_config->send_data))) {
                    err_no = 1;
                    break;
                }
#endif
                if (((uint32_t) transfer_config->send_data % 4) != 0) {
                    err_no = 2;
                    break;
                }
                pinfo->transfer_direction = SPI_MASTER_TX;
            }
            /*
             * HW limitation: TX DNA need akways enabled, else if transfer length is bigger than 64,
             * the SPIM will stop and not work properly.
             */
            reg_val |= (SPIMST_CTRL1_SPIM_TXDMA_EN_MASK);

            if (transfer_config->receive_length > 0) {
#ifdef HAL_CACHE_MODULE_ENABLED
                if (true == hal_cache_is_cacheable((uint32_t)(transfer_config->receive_buffer))) {
                    err_no = 1;
                    break;
                }
#endif
                if (((uint32_t) transfer_config->receive_buffer % 4) != 0) {
                    err_no = 2;
                    break;
                }
                reg_val |= (SPIMST_CTRL1_SPIM_RXDMA_EN_MASK);
                pinfo->transfer_direction = SPI_MASTER_RX;
            }
        }
        g_spi_master_register[master_port]->spimst_ctrl1.word = reg_val;

        /* config packet length and packet count: Must be config length before write fifo*/
        temp = (transfer_config->receive_length > transfer_config->send_length) ? transfer_config->receive_length : transfer_config->send_length;
        temp -= 1;
        g_spi_master_register[master_port]->spimst_cfg2.field.SPIM_PACKET_LOOP_CNT = 0;
        g_spi_master_register[master_port]->spimst_cfg2.field.SPIM_PACKET_LENGTH_CNT = temp;

        /*write data to fifo if is fifo mode: */
        if (mode == SPI_MASTER_MODE_FIFO) {
            spi_master_config_fifo(master_port, SPI_MASTER_TX, transfer_config->send_data, transfer_config->send_length);
        }

        /* config read/write mode for other mode(not single mode)*/
        reg_val = g_spi_master_register[master_port]->spimst_ctrl0.word;
        if (transfer_config->receive_buffer > 0) {
            reg_val &= ~(SPIM_CTRL0_RW_MODE_MASK);
        } else {
            reg_val |= (SPIM_CTRL0_RW_MODE_MASK);
        }
        g_spi_master_register[master_port]->spimst_ctrl0.word = reg_val;

        return HAL_SPI_MASTER_STATUS_OK;
    } while (0);

    log_hal_msgid_error("[hal][spim%d] spi_master_config_transfer fail: %d(1:cache err, 2: align err)\r\n", 2, master_port, err_no);
    return HAL_SPI_MASTER_STATUS_INVALID_PARAMETER;
}

void spi_master_set_delay_cnt(uint8_t master_port, uint16_t delay_cnt, uint8_t one_location_cnt, bool is_multy)
{
    if (is_multy == false) {
        g_spi_master_register[master_port]->spimst_cfg5.field.SPIM_B2B_DELAY_EN = 0;
        g_spi_master_register[master_port]->spimst_cfg5.field.SPIM_SB2NB_CNT = one_location_cnt;
        g_spi_master_register[master_port]->spimst_cfg5.field.SPIM_B2B_DELAY_CNT = delay_cnt;
    } else {
        g_spi_master_register[master_port]->spimst_cfg5.field.SPIM_B2B_DELAY_EN = 1;
        g_spi_master_register[master_port]->spimst_cfg5.field.SPIM_B2B_DELAY_CNT = delay_cnt;
    }
}

hal_spi_master_status_t spi_master_set_clear_data(uint8_t master_port, uint8_t cmd_cnt, bool is_high, bool enable)
{
    if (enable) {
        if (cmd_cnt > 15) {
            log_hal_msgid_error("[SPIM%d]:set clear data cmd_cnt:%d more than 15.\r\n", 2, cmd_cnt, master_port);
            return HAL_SPI_MASTER_STATUS_ERROR;
        }
        g_spi_master_register[master_port]->spimst_cfg3.field.SPIM_COMMAND_CNT = cmd_cnt;
        g_spi_master_register[master_port]->spimst_cfg3.field.SPIM_TX_MOSI_CLR_EN = 1;
        g_spi_master_register[master_port]->spimst_cfg3.field.SPIM_TX_MOSI_CLR_DATA = is_high;
    } else {
        g_spi_master_register[master_port]->spimst_cfg3.field.SPIM_COMMAND_CNT = 0;
        g_spi_master_register[master_port]->spimst_cfg3.field.SPIM_TX_MOSI_CLR_EN = 0;
    }
    return HAL_SPI_MASTER_STATUS_OK;
}

void spi_master_dump(uint8_t master_port)
{
    log_hal_msgid_info("=================SPIM%d DUMP START=================", 0);
    log_hal_msgid_info("TX_SRC:%08x, RX_DST:%08x, CTRL0:%08x, CTRL1:%08x",
                       g_spi_master_register[master_port]->spimst_tx_src.word,
                       g_spi_master_register[master_port]->spimst_rx_dst.word,
                       g_spi_master_register[master_port]->spimst_ctrl0.word,
                       g_spi_master_register[master_port]->spimst_ctrl1.word
                      );
    log_hal_msgid_info("CS_TM:%08x, SCK_CFG:%08x, PKT_CFG:%08x, CFG3:%08x",
                       g_spi_master_register[master_port]->spimst_cfg0.word,
                       g_spi_master_register[master_port]->spimst_cfg1.word,
                       g_spi_master_register[master_port]->spimst_cfg2.word,
                       g_spi_master_register[master_port]->spimst_cfg3.word
                      );
    log_hal_msgid_info("TSF_DLY:%08x, START:%08x, STA:%08x, INT:%08x",
                       g_spi_master_register[master_port]->spimst_cfg5.word,
                       g_spi_master_register[master_port]->spimst_cmd_act.word,
                       g_spi_master_register[master_port]->spimst_sta.word,
                       g_spi_master_register[master_port]->spimst_int.word
                      );

}

#endif /* HAL_SPI_MASTER_MODULE_ENABLED */

