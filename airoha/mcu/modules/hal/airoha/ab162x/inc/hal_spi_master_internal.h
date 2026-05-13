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

#ifndef __HAL_SPI_MASTER_INTERNAL_H__
#define __HAL_SPI_MASTER_INTERNAL_H__
#include "hal.h"
#include "hal_platform.h"
#include "hal_queue.h"
#ifdef HAL_SPI_MASTER_MODULE_ENABLED
#include "hal_sleep_manager_internal.h"

#define HAL_SPI_MASTER_PORT_NUM_3

#define  SPI_MASTER_INPUT_CLOCK_FREQUENCY (104000000)
#define SPI_MASTER_26M_CLOCK_FREQUENCY    (26000000)
#define SPI_MASTER_32M_CLOCK_FREQUENCY    (32000000)
#define SPI_MASTER_78M_CLOCK_FREQUENCY    (78000000)
#define  SPI_MASTER_FIFO_DEPTH            (16)
#define  MAX_SPI_MASTER_QUEUE_LEN         (8)

#ifdef HAL_SPI_MASTER_PORT_NUM_1
#define  SPIM_BASE_REGISTER_ARRAY   {SPI_MASTER_0_BASE}
#define  SPIM_IRQ_CODE_ARRAY        {SPI_MST0_IRQn}
#define  SPIM_IRQ_PRIO_ARRAY        {SPI_MST0_IRQ_PRIORITY}
#define  SPIM_BUS_CG_ARRAY          {HAL_CLOCK_CG_SPIMST0_BUS}
#define  SPIM_CG_ARRAY              {HAL_CLOCK_CG_SPIMST0}
#define  SPIM_CLK_MUX_ARRAY         {CLK_SPIMST0_SEL}
#define  SPIM_SLP_HANDLE_ARRAY      {SLEEP_LOCK_SPI_MST0}
#endif

#ifdef HAL_SPI_MASTER_PORT_NUM_2
#define  SPIM_BASE_REGISTER_ARRAY   {SPI_MASTER_0_BASE,         SPI_MASTER_1_BASE}
#define  SPIM_IRQ_CODE_ARRAY        {SPI_MST0_IRQn,             SPI_MST1_IRQn}
#define  SPIM_IRQ_PRIO_ARRAY        {SPI_MST0_IRQ_PRIORITY,     SPI_MST1_IRQ_PRIORITY}
#define  SPIM_BUS_CG_ARRAY          {HAL_CLOCK_CG_SPIMST0_BUS,  HAL_CLOCK_CG_SPIMST1_BUS}
#define  SPIM_CG_ARRAY              {HAL_CLOCK_CG_SPIMST0,      HAL_CLOCK_CG_SPIMST1}
#define  SPIM_CLK_MUX_ARRAY         {CLK_SPIMST0_SEL,           CLK_SPIMST1_SEL}
#define  SPIM_SLP_HANDLE_ARRAY      {SLEEP_LOCK_SPI_MST0,       SLEEP_LOCK_SPI_MST1}
#endif

#ifdef HAL_SPI_MASTER_PORT_NUM_3
#define  SPIM_BASE_REGISTER_ARRAY   {SPI_MASTER_0_BASE,         SPI_MASTER_1_BASE,          SPI_MASTER_2_BASE}
#define  SPIM_IRQ_CODE_ARRAY        {SPI_MST0_IRQn,             SPI_MST1_IRQn,              SPI_MST2_IRQn}
#define  SPIM_IRQ_PRIO_ARRAY        {SPI_MST0_IRQ_PRIORITY,     SPI_MST1_IRQ_PRIORITY,      SPI_MST2_IRQ_PRIORITY}
#define  SPIM_BUS_CG_ARRAY          {HAL_CLOCK_CG_SPIMST0_BUS,  HAL_CLOCK_CG_SPIMST1_BUS,   HAL_CLOCK_CG_SPIMST2_BUS}
#define  SPIM_CG_ARRAY              {HAL_CLOCK_CG_SPIMST0,      HAL_CLOCK_CG_SPIMST1,       HAL_CLOCK_CG_SPIMST2}
#define  SPIM_CLK_MUX_ARRAY         {CLK_SPIMST0_SEL,           CLK_SPIMST1_SEL,            CLK_SPIMST2_SEL}
#define  SPIM_SLP_HANDLE_ARRAY      {SLEEP_LOCK_SPI_MST0,       SLEEP_LOCK_SPI_MST1,        SLEEP_LOCK_SPI_MST2}
#endif

/* SPI MASTER CLOCK SOURCE */
typedef enum {
    SPI_MASTER_CLOCK_SOURCE_26MHZ = 1,
    SPI_MASTER_CLOCK_SOURCE_32MHZ = 0,
    SPI_MASTER_CLOCK_SOURCE_78MHZ = 3
} spi_master_clk_sel_t;

typedef enum {
    SPI_MASTER_STATUS_UNINITIALIZED,
    SPI_MASTER_STATUS_POLLING_MODE,
    SPI_MASTER_STATUS_DMA_MODE
} spi_master_status_t;

typedef enum {
    SPI_MASTER_TX = 0,
    SPI_MASTER_RX = 1
} spi_master_direction_t;

typedef enum {
    SPI_MASTER_MODE_FIFO = 0,
    SPI_MASTER_MODE_DMA  = 1
} spi_master_mode_t;

typedef enum {
    HAL_SPI_MASTER_TRANSFER_MODE_BLOCKING      = 0,  /**<SPI Master transfer in blocking mode.*/
    HAL_SPI_MASTER_TRANSFER_MODE_NONBLOCKING   = 1   /**<SPI Master transfer in non-blocking mode*/
} hal_spi_master_transfer_mode_t;

typedef enum {
    SPIM_GET_BUSY_STATUS = 0,
    SPIM_SET_IE,
    SPIM_SET_DISABLE_INT,
    SPIM_GET_INT_STATUS,
    SPIM_SET_DEASSERT,
    SPIM_SET_TRANS_MODE,
    SPIM_SET_TRANS_RW,
    SPIM_SET_RESUME,
    SPIM_SET_CHIP_SEL,
    SPIM_SET_CMD_CNT,
    SPIM_SET_DUMMY_CNT,
    SPIM_SET_BT_EN
} hal_spi_master_command_t;

typedef struct {
    hal_spi_master_bit_order_t bit_order;                       /**< SPI master bit order setting. */
    hal_spi_master_clock_polarity_t polarity;                   /**< SPI master clock polarity setting. */
    hal_spi_master_clock_phase_t phase;                         /**< SPI master clock phase setting. */
    hal_spi_master_chip_select_polarity_t cs_polarity;          /**< SPI master chip select polarity setting. */
} hal_spi_master_init_config_t;

typedef struct {
    bool enable_pause_mode;
    hal_spi_master_send_and_receive_config_t transfer_config;
    spi_master_direction_t transfer_direction;
    spi_master_mode_t mode;
    uint8_t spim_bus_type;
} hal_spi_master_transfer_info_t;

typedef struct {
    hal_spi_master_slave_port_t slave_port;                    /**< SPI slave device selection. */
    hal_spi_master_transfer_mode_t transfer_mode;              /**<SPI master transfer in blocking or non-blocking mode. */
    hal_spi_master_send_and_receive_config_t snd_rcv_config;   /**< SPI master send and receive configuration. */
} hal_spi_master_transfer_config_t;

#if defined(HAL_SPI_MASTER_FEATURE_NO_BUSY) && defined (HAL_SPI_MASTER_FEATURE_DMA_MODE)
typedef struct {
    hal_spi_send_and_receive_config_ex_no_busy_t tranfer_cfg[MAX_SPI_MASTER_QUEUE_LEN];
    bool used_flag[MAX_SPI_MASTER_QUEUE_LEN];
    uint8_t index;
} spi_master_transfer_queue_t;
#endif

typedef struct {
    hal_queue_t queue;
    uint8_t     op_state;
} hal_spi_master_private_t;

typedef struct {
    uint32_t spimst_tx_src;
    uint32_t spimst_rx_dst;
    uint32_t spimst_ctrl0;
    uint32_t spimst_ctrl1;
    uint32_t spimst_cfg0;
    uint32_t spimst_cfg1;
    uint32_t spimst_cfg2;
    uint32_t spimst_cfg3;
    uint32_t spimst_cfg5;
    uint8_t  spimst_cfg4[10];
    uint8_t  spimst_cs;
    uint8_t  spimst_cs_idle;
    uint8_t  spimst_ie;
} hal_spi_master_back_memory_t;

#define    SPI_MASTER_STATE_USER_MODE_NORMAL        (1)
#define    SPI_MASTER_STATE_USER_MODE_NON_BLOCK     (1 << 1)
#define    SPI_MASTER_STATE_IS_WORKING              (1 << 2)
#define    SPI_MASTER_STATE_IRQ_MODE_OFS            (3)
#define    SPI_MASTER_STATE_IRQ_MODE_MASK           (1 << 3)

void spi_master_hw_reset(uint8_t master_port);
void spi_master_init_config(uint8_t master_port, const hal_spi_master_config_t *spi_config, spi_master_clk_sel_t src_clk_sel);
void spi_master_config_fifo(uint8_t master_port, spi_master_direction_t dir, uint8_t *buff, uint8_t size);
void spi_master_set_frequency(uint8_t master_port, uint32_t spi_clk_hz, spi_master_clk_sel_t clk_src_sel);
void spi_master_start_transfer(uint8_t master_port, spi_master_mode_t mode, bool start);
void spi_master_isr_handler(uint8_t master_port, hal_spi_master_callback_t user_callback, void *user_data);
void spi_master_dump_register(uint8_t master_port, int index);
void spi_master_set_cs_timing(uint8_t master_port, hal_spi_master_chip_select_timing_t *chip_select_timing);
void spi_master_set_rwaddr(hal_spi_master_port_t master_port, spi_master_direction_t type, const uint8_t *addr);
void spi_master_set_advanced_config(uint8_t master_port, const hal_spi_master_advanced_config_t *advanced_config);
hal_spi_master_status_t  spi_master_ao_get_backup_info(hal_spi_master_port_t master_port, ao_backup_format_table_t *backup_info);

uint32_t spi_master_ioctl(uint8_t master_port, uint32_t cmd, uint32_t arg);
hal_spi_master_status_t spi_master_check_tranfer_config(uint8_t master_port, hal_spi_master_send_and_receive_config_t *tranfer_config);
hal_spi_master_status_t spi_master_config_transfer(uint8_t master_port, hal_spi_master_send_and_receive_config_t *transfer_config, spi_master_mode_t mode);
#ifdef HAL_SLEEP_MANAGER_ENABLED
void spi_master_backup_register_callback(void *user_data);
void spi_master_restore_register_callback(void *user_data);
#endif
void spi_master_set_delay_cnt(uint8_t master_port, uint16_t delay_cnt, uint8_t one_location_cnt, bool is_multy);
hal_spi_master_status_t spi_master_set_clear_data(uint8_t master_port, uint8_t cmd_cnt, bool is_high, bool enable);
void spi_master_set_bt_enable(uint8_t master_port, bool bt_enable);
void spi_master_trigger_start(uint8_t master_port, bool start);

#endif   /* HAL_SPI_MASTER_MODULE_ENABLED */
#endif   /*__HAL_SPI_MASTER_INTERNAL_H__*/


