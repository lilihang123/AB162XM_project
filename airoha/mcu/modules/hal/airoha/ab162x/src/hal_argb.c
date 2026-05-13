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

#include "hal_argb.h"
#include "hal_nvic.h"
#include "hal_clock.h"
#include <zephyr/kernel.h>
#ifdef HAL_ARGB_MODULE_ENABLED
static argb_info_t argb_info;
static uint8_t argb_status;
static void *buf_addr;
uint32_t count_size;
#define argb_status_init    (1<<0)
#define argb_status_setting (1<<1)
#define argb_status_config  (1<<2)
#define argb_status_buf     (1<<3)
#define argb_status_start   (1<<4)
static ARGB_REGISTER_T *argb_base = (ARGB_REGISTER_T *)(ARGB_BASE);

#if 0
#define log_argb_info(fmt, cnt, ...)     log_hal_msgid_info("[hal][rtc] " fmt, cnt, ##__VA_ARGS__)
#define log_argb_warning(fmt, cnt, ...)  log_hal_msgid_warning("[hal][rtc] "fmt, cnt, ##__VA_ARGS__)
#define log_argb_error(fmt, cnt, ...)    log_hal_msgid_error("[hal][rtc] "fmt, cnt, ##__VA_ARGS__)
#else
#define log_argb_info(fmt, cnt, ...)     printk(fmt, ##__VA_ARGS__)
#define log_argb_warning(fmt, cnt, ...)  printk(fmt, ##__VA_ARGS__)
#define log_argb_error(fmt, cnt, ...)    printk(fmt, ##__VA_ARGS__)
#endif

void argb_enable_clock_source(void)
{
#ifndef FPGA_ENV
    if (hal_clock_is_enabled(HAL_CLOCK_CG_ARGB_BCLK) == false) {
        hal_clock_enable(HAL_CLOCK_CG_ARGB_BCLK);
    }
#endif
}

void argb_disable_clock_source(void)
{
#ifndef FPGA_ENV
    if (hal_clock_is_enabled(HAL_CLOCK_CG_ARGB_BCLK) == true) {
        hal_clock_disable(HAL_CLOCK_CG_ARGB_BCLK);
    }
#endif
}

uint32_t argb_convert_ns_to_count(uint32_t clock,uint32_t ns)
{
    uint32_t clock_temp = clock/1000000;
    uint32_t temp = (ns * clock_temp+500) / 1000;
    return temp;
}

hal_argb_status_t hal_argb_init(hal_argb_setting *setting){
    uint32_t save_mask;
    if((argb_status & argb_status_init) == argb_status_init){
        log_argb_error("[hal][argb]argb already init \r\n", 0);
        return HAL_ARGB_STATUS_ERROR;
    }
    hal_nvic_save_and_set_interrupt_mask(&save_mask);
    argb_base->ctrl0.field.ONE_L_VAL = argb_convert_ns_to_count(ARGB_CLOCK_FREQUENCY,setting->timing.one_l_value) - 1;
    argb_base->ctrl0.field.ONE_H_VAL = argb_convert_ns_to_count(ARGB_CLOCK_FREQUENCY,setting->timing.one_h_value) - 1;
    argb_base->ctrl0.field.ZERO_L_VAL = argb_convert_ns_to_count(ARGB_CLOCK_FREQUENCY,setting->timing.zero_l_value) - 1;
    argb_base->ctrl0.field.ZERO_H_VAL = argb_convert_ns_to_count(ARGB_CLOCK_FREQUENCY,setting->timing.zero_h_value) - 1;
    argb_base->ctrl1.field.RST_VAL = argb_convert_ns_to_count(ARGB_CLOCK_FREQUENCY,setting->timing.reset_value) - 1;

    argb_base->ctrl1.field.BIT_NONREV = setting->bit_nonrev;
    argb_base->ctrl1.field.NONALIGN = setting->nonalign;
    argb_base->ctrl1.field.ED_BIG = setting->endian_big;
    argb_base->ctrl1.field.PAT_CNT = setting->num;
    argb_status |= argb_status_init;
    hal_nvic_restore_interrupt_mask(save_mask);
    argb_enable_clock_source();
    return HAL_ARGB_STATUS_OK;
}

hal_argb_status_t hal_argb_deinit(void){
    uint32_t save_mask;
    if((argb_status & argb_status_init) != argb_status_init){
        log_argb_info("[hal][argb]argb deinit error,not init \r\n", 0);
        return HAL_ARGB_STATUS_NOT_INIT;
    }
    if((argb_status & argb_status_start) == argb_status_start){
        log_argb_error("[hal][argb]argb deinit error,argb is busy \r\n", 0);
        return HAL_ARGB_STATUS_ERROR_BUSY;
    }
    hal_nvic_save_and_set_interrupt_mask(&save_mask);
    argb_status = 0;
    hal_nvic_restore_interrupt_mask(save_mask);
    argb_disable_clock_source();
    return HAL_ARGB_STATUS_OK;
}


hal_argb_status_t hal_argb_dma_setting(hal_argb_dma_timing_setting *setting){
    uint32_t save_mask;
    if((argb_status & argb_status_init) != argb_status_init){
        log_argb_error("[hal][argb]argb setting not  init \r\n", 0);
        return HAL_ARGB_STATUS_NOT_INIT;
    }
    hal_nvic_save_and_set_interrupt_mask(&save_mask);
    argb_base->dma_glb_clk_set.field.CLK_SET_TX = 1;
    argb_base->pdma_tx_con.field.DIRECTION |= 0x1; //enable SINC
    argb_base->pdma_tx_con.field.DIRECTION &= ~((1<<3) | (1<<4)); // disable Wrap enable && set TX of DMA transfer
    argb_base->pdma_tx_con.field.SIZE = 0x2; //set data size to 4 bytes
    argb_base->pdma_tx_con.field.SETTING |= 0x1; //enable DMA Hardware handshake
    argb_base->pdma_tx_con.field.SETTING &= ~(0x3<<2);//set Burst mode to Single
    argb_base->timer.field.AUTO_TIMER_VAL = argb_convert_ns_to_count(ARGB_CLOCK_FREQUENCY,setting->auto_timer_value*1000000);
    argb_base->dmast.field.ARGB_DMA_ST_VAL = argb_convert_ns_to_count(ARGB_CLOCK_FREQUENCY,setting->dma_start_vaule*1000000);
    argb_base->prewk.field.PR_WAKE_VAL = argb_convert_ns_to_count(ARGB_CLOCK_FREQUENCY,setting->pre_wake_value*1000000);
    argb_status |= argb_status_setting;
    hal_nvic_restore_interrupt_mask(save_mask);
    return HAL_ARGB_STATUS_OK;
}

hal_argb_status_t hal_argb_config_dma_buf(uint32_t buf_total_count, uint32_t one_count_size){
    uint32_t save_mask;
    if((argb_status & argb_status_setting) != argb_status_setting){
        log_argb_error("[hal][argb]argb config dma buf error,not setting dma\r\n", 0);
        return HAL_ARGB_STATUS_ERROR;
    }
    if((argb_status & argb_status_config) == argb_status_config){
        k_free(buf_addr);
    }
    buf_addr = k_malloc(buf_total_count*one_count_size);
    if(buf_addr == NULL){
        return HAL_ARGB_STATUS_INVALID_PARAMETER;
    }
    hal_nvic_save_and_set_interrupt_mask(&save_mask);
    count_size = one_count_size;
    argb_base->pdma_tx_pgmaddr.word = (uint32_t)buf_addr;
    argb_base->pdma_tx_count.field.COUNT = (count_size+3)/4;
    argb_base->pdma_tx_count.field.PKTCNT = buf_total_count;
    argb_status |= argb_status_config;
    hal_nvic_restore_interrupt_mask(save_mask);
    return HAL_ARGB_STATUS_OK;
}


hal_argb_status_t hal_argb_config_dma_data(uint16_t buf_count_num, uint8_t *count_data){
    uint32_t save_mask;
    if((argb_status & argb_status_config) != argb_status_config){
        log_argb_error("[hal][argb]argb config dma data error, not config dma buf \r\n", 0);
        return HAL_ARGB_STATUS_ERROR;
    }
    memcpy(((uint8_t *)buf_addr+buf_count_num*count_size), count_data, count_size);
    hal_nvic_save_and_set_interrupt_mask(&save_mask);
    argb_status |= argb_status_buf;
    hal_nvic_restore_interrupt_mask(save_mask);
    return HAL_ARGB_STATUS_OK;
}


hal_argb_status_t hal_argb_dma_start(void){
    uint32_t save_mask;
    if((argb_status & argb_status_start) == argb_status_start){
        log_argb_error("[hal][argb]argb start failed, already start \r\n", 0);
       return HAL_ARGB_STATUS_ERROR_BUSY;
    }
    if((argb_status & argb_status_buf) != argb_status_buf){
        log_argb_error("[hal][argb]argb start failed, not config dma data \r\n", 0);
        return HAL_ARGB_STATUS_ERROR;
    }
    hal_nvic_save_and_set_interrupt_mask(&save_mask);
    argb_base->pdma_tx_start.field.STR = 1;//Start DMA
    argb_base->tctrl.field.AUTO_MODE = 1; // config auto mode
    argb_base->ctrl1.field.EN_ARGB = 1; //enable argb
    argb_status |= argb_status_start;
    hal_nvic_restore_interrupt_mask(save_mask);
    return HAL_ARGB_STATUS_OK;
}

hal_argb_status_t hal_argb_dma_stop(void){
    uint32_t save_mask;
    if((argb_status & argb_status_start) != argb_status_start){
        log_argb_error("[hal][argb]argb stop failed, not start \r\n", 0);
       return HAL_ARGB_STATUS_ERROR;
    }
    hal_nvic_save_and_set_interrupt_mask(&save_mask);
    argb_base->tctrl.field.AUTO_MODE = 0; // disable auto mode
    hal_nvic_restore_interrupt_mask(save_mask);
    return HAL_ARGB_STATUS_OK;

}

static void argb_stop(void){
    uint32_t save_mask;
    if(buf_addr != NULL){
        k_free(buf_addr);
        hal_nvic_save_and_set_interrupt_mask(&save_mask);
        buf_addr = NULL;
        hal_nvic_restore_interrupt_mask(save_mask);
    }
    hal_nvic_save_and_set_interrupt_mask(&save_mask);
    argb_status &= ~(0x7 << 2); // clear start,config dma buf,config dma data
    hal_nvic_restore_interrupt_mask(save_mask);

}
static void  argb_isr(hal_nvic_irq_t irq_number){

    hal_argb_callback_event_t status = HAL_ARGB_UNKOWN_EVENT;
    uint32_t irq_status = argb_base->intr_sts.word;
    argb_base->intr_sts.word = irq_status;
    irq_status &= argb_base->intr_msk.word;
    if(irq_status & ARGB_INTR_STS_ARGB_STOP_INT_STS_MASK){
        argb_stop();
        status = HAL_ARGB_STOP_EVENT;
    }else if(irq_status & ARGB_INTR_STS_RST_ST_INT_STS_MASK){
        status = HAL_ARGB_RESET_START_EVENT;
    }else if(irq_status & ARGB_INTR_STS_AUTO_RE_ST_INT_STS_MASK){
        status = HAL_ARGB_RE_START_EVENT;
    }else if(irq_status & ARGB_INTR_STS_PR_WK_INT_STS_MASK){
        status = HAL_ARGB_PRE_WAKEUP_EVENT;
    }else if(irq_status & ARGB_INTR_STS_ARGB_DMA_ST_INT_STS_MASK){
        status = HAL_ARGB_START_EVENT;
    }else if(irq_status & ARGB_INTR_STS_AUTO_OFF_INT_STS_MASK){
        status = HAL_ARGB_AUTO_OFF_EVENT;
    }else if(irq_status & ARGB_INTR_STS_ARGB_DMA_LVL_INT_STS_MASK){
        status = HAL_ARGB_DMA_LVL_EVENT;
    }
    if(argb_info.call_back){
        argb_info.call_back(status,argb_info.user_data);
    }
}

hal_argb_status_t hal_argb_register_callback(hal_argb_callback_t argb_callback, void *user_data){
    uint32_t  save_mask;
    if((argb_status & argb_status_init) != argb_status_init){
        log_argb_error("[hal][argb]argb register callback failed, not init \r\n", 0);
        return HAL_ARGB_STATUS_NOT_INIT;
    }
    hal_nvic_save_and_set_interrupt_mask(&save_mask);

    argb_info.call_back = argb_callback;
    argb_info.user_data = user_data;
    hal_nvic_restore_interrupt_mask(save_mask);
    hal_nvic_register_isr_handler(ARGB_IRQn, argb_isr);
    hal_nvic_enable_irq(ARGB_IRQn);
    return HAL_ARGB_STATUS_OK;
}

hal_argb_status_t hal_argb_irq_enable(hal_argb_irq *irq_enable){
    uint32_t  save_mask;
    if((argb_status & argb_status_init) != argb_status_init){
        log_argb_error("[hal][argb]argb enable irq failed, not init \r\n", 0);
        return HAL_ARGB_STATUS_NOT_INIT;
    }
    hal_nvic_save_and_set_interrupt_mask(&save_mask);
    argb_base->intr_msk.field.ARGB_STOP_INT_MSK = irq_enable->argb_stop;
    argb_base->intr_msk.field.RST_ST_INT_MSK = irq_enable->argb_reset_start;
    argb_base->intr_msk.field.AUTO_RE_ST_INT_MSK = irq_enable->argb_re_start;
    argb_base->intr_msk.field.PR_WK_INT_MSK = irq_enable->argb_pre_wakeup;
    argb_base->intr_msk.field.ARGB_DMA_ST_INT_MSK = irq_enable->argb_start;
    argb_base->intr_msk.field.AUTO_OFF_INT_MSK = irq_enable->argb_auto_off;
    argb_base->intr_msk.field.ARGB_DMA_LVL_INT_MSK = irq_enable->dma_lvl;
    hal_nvic_restore_interrupt_mask(save_mask);
    return HAL_ARGB_STATUS_OK;
}

#if defined(HAL_MIDDLE_ARGB_SUPPORTED)

#include "hal_argb_internal.h"
static middle_argb_info_t middle_argb_info;

hal_argb_status_t hal_argb_init_for_middle(hal_argb_setting *setting, hal_argb_dma_timing_setting *dma_setting){

    uint32_t save_mask;
    if((argb_status & argb_status_init) == argb_status_init){
        log_argb_error("[hal][argb]argb setting already  init, state:0x%x \r\n", 1, argb_status);
        return HAL_ARGB_STATUS_ERROR;
    }
    argb_enable_clock_source();
    hal_nvic_save_and_set_interrupt_mask(&save_mask);
    // normal setting
    argb_base->ctrl0.field.ONE_L_VAL = argb_convert_ns_to_count(ARGB_CLOCK_FREQUENCY,setting->timing.one_l_value) - 1;
    argb_base->ctrl0.field.ONE_H_VAL = argb_convert_ns_to_count(ARGB_CLOCK_FREQUENCY,setting->timing.one_h_value) - 1;
    argb_base->ctrl0.field.ZERO_L_VAL = argb_convert_ns_to_count(ARGB_CLOCK_FREQUENCY,setting->timing.zero_l_value) - 1;
    argb_base->ctrl0.field.ZERO_H_VAL = argb_convert_ns_to_count(ARGB_CLOCK_FREQUENCY,setting->timing.zero_h_value) - 1;
    argb_base->ctrl1.field.RST_VAL = argb_convert_ns_to_count(ARGB_CLOCK_FREQUENCY,setting->timing.reset_value) - 1;
    argb_base->ctrl1.field.BIT_NONREV = setting->bit_nonrev;
    argb_base->ctrl1.field.NONALIGN = setting->nonalign;
    argb_base->ctrl1.field.ED_BIG = setting->endian_big;
    argb_base->ctrl1.field.PAT_CNT = setting->num;
    // dma setting
    argb_base->dma_glb_clk_set.field.CLK_SET_TX = 1;
    argb_base->pdma_tx_con.field.DIRECTION |= 0x1; //enable SINC
    argb_base->pdma_tx_con.field.DIRECTION &= ~((1<<3) | (1<<4)); // disable Wrap enable && set TX of DMA transfer
    argb_base->pdma_tx_con.field.SIZE = 0x2; //set data size to 4 bytes
    argb_base->pdma_tx_con.field.SETTING |= 0x1; //enable DMA Hardware handshake
    argb_base->pdma_tx_con.field.SETTING &= ~(0x3<<2);//set Burst mode to Single
    argb_base->timer.field.AUTO_TIMER_VAL = argb_convert_ns_to_count(ARGB_CLOCK_FREQUENCY,dma_setting->auto_timer_value*1000000);
    argb_base->dmast.field.ARGB_DMA_ST_VAL = argb_convert_ns_to_count(ARGB_CLOCK_FREQUENCY,dma_setting->dma_start_vaule*1000000);
    argb_base->prewk.field.PR_WAKE_VAL = argb_convert_ns_to_count(ARGB_CLOCK_FREQUENCY,dma_setting->pre_wake_value*1000000);
    argb_status |= argb_status_init;
    argb_status |= argb_status_setting;
    hal_nvic_restore_interrupt_mask(save_mask);
    return HAL_ARGB_STATUS_OK;
}

hal_argb_status_t hal_argb_config_data_mdoe_for_middle(uint8_t index, uint32_t data_size, uint8_t *count_data, hal_middle_argb_mode_t mode){
    uint32_t save_mask;
    if((argb_status & argb_status_setting) != argb_status_setting){
        log_argb_error("[hal][argb]argb config dma buf error,not setting dma, state:0x%x\r\n", 1,argb_status);
        return HAL_ARGB_STATUS_NOT_INIT;
    }
    if(count_data == NULL){
        return HAL_ARGB_STATUS_INVALID_PARAMETER;
    }
    hal_nvic_save_and_set_interrupt_mask(&save_mask);
    argb_base->pdma_tx_pgmaddr.word = (uint32_t)count_data;
    argb_base->pdma_tx_count.field.COUNT = (data_size + 3)/4;
    if(mode != INFINITE_MODE){
        argb_base->pdma_tx_count.field.PKTCNT = (data_size/3);
    }else{
        argb_base->pdma_tx_count.field.PKTCNT = 1;
    }
    
    argb_status |= argb_status_config;
    argb_status |= argb_status_buf;
    // argb_base->pdma_tx_start.field.STR = 1;//Start DMA
    hal_nvic_restore_interrupt_mask(save_mask);
    // log_argb_error("[hal][argb]argb config dma buf dma addr:0x%x, value:%x, data_size:%d, index:%d, mode:%d, argb_base->pdma_tx_pgmaddr.word:0x%x\r\n", 6,count_data, *count_data, data_size, index, mode, argb_base->pdma_tx_pgmaddr.word);
    return HAL_ARGB_STATUS_OK;
}

static void middle_argb_stop(void){
    uint32_t save_mask;
    hal_nvic_save_and_set_interrupt_mask(&save_mask);
    argb_status &= ~(0x7 << 2); // clear start,config dma buf,config dma data
    argb_base->pdma_tx_start.field.STR = 0; //Stop DMA
    hal_nvic_restore_interrupt_mask(save_mask);
}

static void  middle_argb_isr(hal_nvic_irq_t irq_number){
    // log_argb_error("[hal][argb]middle_argb_isr \r\n", 0);

    hal_argb_callback_event_t status = HAL_ARGB_UNKOWN_EVENT;
    uint32_t irq_status = argb_base->intr_sts.word;
    argb_base->intr_sts.word = irq_status;
    irq_status &= argb_base->intr_msk.word;
    if(irq_status & ARGB_INTR_STS_ARGB_STOP_INT_STS_MASK){
        middle_argb_stop();
        status = HAL_ARGB_STOP_EVENT;
    }else if(irq_status & ARGB_INTR_STS_RST_ST_INT_STS_MASK){
        status = HAL_ARGB_RESET_START_EVENT;
    }else if(irq_status & ARGB_INTR_STS_AUTO_RE_ST_INT_STS_MASK){
        status = HAL_ARGB_RE_START_EVENT;
    }else if(irq_status & ARGB_INTR_STS_PR_WK_INT_STS_MASK){
        status = HAL_ARGB_PRE_WAKEUP_EVENT;
    }else if(irq_status & ARGB_INTR_STS_ARGB_DMA_ST_INT_STS_MASK){
        status = HAL_ARGB_START_EVENT;
    }else if(irq_status & ARGB_INTR_STS_AUTO_OFF_INT_STS_MASK){
        status = HAL_ARGB_AUTO_OFF_EVENT;
    }else if(irq_status & ARGB_INTR_STS_ARGB_DMA_LVL_INT_STS_MASK){
        status = HAL_ARGB_DMA_LVL_EVENT;
    }
    if(middle_argb_info.call_back){
        middle_argb_info.call_back(middle_argb_info.user_data);
    }
}

hal_argb_status_t hal_middle_argb_register_callback(middle_argb_callback_t argb_callback, void *user_data){
    uint32_t  save_mask;
    if((argb_status & argb_status_init) != argb_status_init){
        log_argb_error("[hal][argb]argb register callback failed, not init \r\n", 0);
        return HAL_ARGB_STATUS_NOT_INIT;
    }
    hal_nvic_save_and_set_interrupt_mask(&save_mask);
    middle_argb_info.call_back = argb_callback;
    middle_argb_info.user_data = user_data;
    hal_nvic_restore_interrupt_mask(save_mask);
    hal_nvic_register_isr_handler(ARGB_IRQn, middle_argb_isr);
    hal_nvic_enable_irq(ARGB_IRQn);
    return HAL_ARGB_STATUS_OK;
}

hal_argb_status_t hal_middle_argb_start(void){
    uint32_t save_mask;
    if((argb_status & argb_status_start) == argb_status_start){
        log_argb_error("[hal][argb]argb start failed, already start \r\n", 0);
       return HAL_ARGB_STATUS_ERROR_BUSY;
    }
    if((argb_status & argb_status_buf) != argb_status_buf){
        log_argb_error("[hal][argb]argb start failed, not config dma data \r\n", 0);
        return HAL_ARGB_STATUS_ERROR;
    }
    hal_nvic_save_and_set_interrupt_mask(&save_mask);
    argb_base->pdma_tx_start.field.STR = 1;//Start DMA
    // argb_base->tctrl.field.AUTO_MODE = 1; // config auto mode
    argb_base->intr_sts.field.ARGB_STOP_INT_STS = 1;
    argb_base->intr_msk.field.ARGB_STOP_INT_MSK = 1;
    argb_base->ctrl1.field.EN_ARGB = 1; //enable argb
    argb_status |= argb_status_start;
    hal_nvic_restore_interrupt_mask(save_mask);
    // log_argb_error("[hal][argb]argb start reg:0x%x \r\n", 1, argb_base->ctrl1.word);
    
    return HAL_ARGB_STATUS_OK;
}

hal_argb_status_t hal_middle_argb_deinit(void){
    uint32_t save_mask;
    if((argb_status & argb_status_init) != argb_status_init){
        log_argb_info("[hal][argb]argb deinit error,not init \r\n", 0);
        return HAL_ARGB_STATUS_NOT_INIT;
    }
    if((argb_status & argb_status_start) == argb_status_start){
        log_argb_error("[hal][argb]argb deinit error,argb is busy \r\n", 0);
        return HAL_ARGB_STATUS_ERROR_BUSY;
    }
    hal_nvic_save_and_set_interrupt_mask(&save_mask);
    argb_status = 0;
    hal_nvic_restore_interrupt_mask(save_mask);
    argb_disable_clock_source();
    return HAL_ARGB_STATUS_OK;
}

hal_argb_status_t hal_middle_argb_stop(void){
    uint32_t save_mask;
    if((argb_status & argb_status_start) != argb_status_start){
        log_argb_error("[hal][argb]argb stop failed, not start \r\n", 0);
       return HAL_ARGB_STATUS_ERROR;
    }
    hal_nvic_save_and_set_interrupt_mask(&save_mask);
    argb_base->tctrl.field.AUTO_MODE = 0; // disable auto mode
    hal_nvic_restore_interrupt_mask(save_mask);
    return HAL_ARGB_STATUS_OK;

}

#endif  /* HAL_MIDDLE_ARGB_SUPPORTED */

#endif  /* HAL_ARGB_H */