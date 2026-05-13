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

#include "hal_irtx.h"
#include "hal_irtx_internal.h"
#include "hal_nvic.h"
#ifdef HAL_IRTX_MODULE_ENABLED
uint64_t nec_send_data;
uint32_t rc5_send_data;
uint32_t rc6_send_data;
uint32_t sirc_send_data;
uint32_t rcmm_send_data;
uint8_t rc5_tr = 0;
uint8_t rc6_tr = 0;
uint8_t ir_tx_status =0;
#define IRTX_INIT_STATUS (1<<0)
#define IRTX_START_STATUS (1<<1)
#define IRTX_CONFIG_STATUS (1<<2)

#if 0
#define log_irtx_info(fmt, cnt, ...)     log_hal_msgid_info("[hal][rtc] " fmt, cnt, ##__VA_ARGS__)
#define log_irtx_warning(fmt, cnt, ...)  log_hal_msgid_warning("[hal][rtc] "fmt, cnt, ##__VA_ARGS__)
#define log_irtx_error(fmt, cnt, ...)    log_hal_msgid_error("[hal][rtc] "fmt, cnt, ##__VA_ARGS__)
#else
#define log_irtx_info(fmt, cnt, ...)     printk(fmt, ##__VA_ARGS__)
#define log_irtx_warning(fmt, cnt, ...)  printk(fmt, ##__VA_ARGS__)
#define log_irtx_error(fmt, cnt, ...)    printk(fmt, ##__VA_ARGS__)
#endif

IRTX_REGISTER_T *irtx_register_base = (IRTX_REGISTER_T *)IRTX_BASE;
hal_irtx_status_t hal_irtx_init(void){
    uint32_t  save_mask;
    if(ir_tx_status & IRTX_INIT_STATUS){
        log_irtx_error("[hal][irtx]:irtx already init\r\n",0);
        return HAL_IRTX_STATUS_ERROR;
    }
    irtx_power_set(true);
    irtx_nvic_set(true);
    hal_nvic_save_and_set_interrupt_mask(&save_mask);
    irtx_register_base->reg_0088_ir_tx_0.field.reg_ir_tx_en_0088 = 1;
    ir_tx_status |= IRTX_INIT_STATUS;
    hal_nvic_restore_interrupt_mask(save_mask);
    return HAL_IRTX_STATUS_OK;
}


hal_irtx_status_t hal_irtx_deinit(void){
    uint32_t  save_mask;
    if((ir_tx_status & IRTX_INIT_STATUS) == 0){
        log_irtx_error("[hal][irtx]:in deinit, irtx not init\r\n",0);
        return HAL_IRTX_STATUS_NOT_INIT;
    }
    if(ir_tx_status & IRTX_START_STATUS){
        log_irtx_error("[hal][irtx]:in deinit, irtx busy\r\n",0);
       return HAL_IRTX_STATUS_BUSY;
    }
    if(ir_tx_status & IRTX_CONFIG_STATUS){
        log_irtx_error("[hal][irtx]:in deinit, irtx config\r\n",0);
       return HAL_IRTX_STATUS_BUSY;
    }
    irtx_nvic_set(false);
    hal_nvic_save_and_set_interrupt_mask(&save_mask);
    irtx_register_base->reg_0088_ir_tx_0.field.reg_ir_tx_en_0088 = 0;
    ir_tx_status = 0;
    hal_nvic_restore_interrupt_mask(save_mask);
    irtx_power_set(false);
    return HAL_IRTX_STATUS_OK;
}

hal_irtx_status_t hal_irtx_send_nec_data(uint8_t *address,uint8_t *command,bool repeat){
    uint32_t  save_mask;
    if((ir_tx_status & IRTX_INIT_STATUS) == 0){
        log_irtx_error("[hal][irtx]:in nec send data, irtx not init\r\n",0);
        return HAL_IRTX_STATUS_NOT_INIT;
    }
    if(ir_tx_status & IRTX_START_STATUS){
        log_irtx_error("[hal][irtx]:in nec send data, irtx busy\r\n",0);
       return HAL_IRTX_STATUS_BUSY;
    }
    hal_nvic_save_and_set_interrupt_mask(&save_mask);
    if(ir_tx_status & IRTX_CONFIG_STATUS){
        log_irtx_error("[hal][irtx]:in nec send data, irtx is config\r\n",0);
        hal_nvic_restore_interrupt_mask(save_mask);
        return HAL_IRTX_STATUS_CONFIG;
    }
    if(hal_irtx_configure_pulse_data_carrier(38000,33) != HAL_IRTX_STATUS_OK){
        log_irtx_error("[hal][irtx]:send nec data clock config error\r\n",0);
        hal_nvic_restore_interrupt_mask(save_mask);
        return HAL_IRTX_STATUS_ERROR;
    }
    
    ir_tx_status |= IRTX_CONFIG_STATUS;
    hal_nvic_restore_interrupt_mask(save_mask);
    irtx_set_unit_value(5,560,50,1,0);  //set nec logic "end";
    irtx_set_unit_value(2,9000,4500,1,0);  //set nec header;
    irtx_set_unit_value(1,560,1690,1,0);  //set nec logic "1";
    irtx_set_unit_value(0,560,560,1,0);  //set nec logic "0";
    irtx_set_total_cycle(110000); //set total cycle;
    irtx_register_base->reg_0088_ir_tx_0.field.reg_ir_tx_rstz_0088 = 1;
    irtx_register_base->reg_1004_ir_tx_mem_0.field.reg_key = 0x5;
    irtx_register_base->reg_1004_ir_tx_mem_0.field.reg_addr_auto_inc = 0x1;
    irtx_register_base->reg_1108_ir_tx_mem_0.field.reg_addr = 0x0;
    uint8_t address_reverse = *address;
    uint8_t command_reverse = *command;
    nec_send_data = (*address & 0xff)|(~address_reverse << 8 & 0xFF00)|(*command << 16 & 0xFF0000)|(~command_reverse << 24  & 0xFF000000);
    nec_send_data = nec_send_data << 1; //add one bit for HEADER;
    irtx_register_base->reg_1118_ir_tx_mem_0.field.reg_sram_wd = (irtx_bit_transfer_shift((nec_send_data & 0xF),1,4) &0xFFF0)|0x2; //set header and data;
    irtx_register_base->reg_1118_ir_tx_mem_0.field.reg_sram_wd = (irtx_bit_transfer_shift(((nec_send_data>>4)&0xF),1,4));
    irtx_register_base->reg_1118_ir_tx_mem_0.field.reg_sram_wd = (irtx_bit_transfer_shift(((nec_send_data>>8)&0xF),1,4));
    irtx_register_base->reg_1118_ir_tx_mem_0.field.reg_sram_wd = (irtx_bit_transfer_shift(((nec_send_data>>12)&0xF),1,4));
    irtx_register_base->reg_1118_ir_tx_mem_0.field.reg_sram_wd = (irtx_bit_transfer_shift(((nec_send_data>>16)&0xF),1,4));
    irtx_register_base->reg_1118_ir_tx_mem_0.field.reg_sram_wd = (irtx_bit_transfer_shift(((nec_send_data>>20)&0xF),1,4));
    irtx_register_base->reg_1118_ir_tx_mem_0.field.reg_sram_wd = (irtx_bit_transfer_shift(((nec_send_data>>24)&0xF),1,4));
    irtx_register_base->reg_1118_ir_tx_mem_0.field.reg_sram_wd = (irtx_bit_transfer_shift(((nec_send_data>>28)&0xF),1,4));
    irtx_register_base->reg_0088_ir_tx_0.field.reg_ir_tx_carrier_en_0088 = 1;  //set carrier
    if(repeat == 1){
        irtx_set_unit_value(3,9000,2250,1,0);  //set nec header;
        irtx_set_unit_value(4,560,560,1,0);  //set nec header;
        irtx_register_base->reg_1118_ir_tx_mem_0.field.reg_sram_wd = ((~command_reverse>>7) & 0x1)|(0x5<<4)|(0xf<<8)|(0x3<<12);
        irtx_register_base->reg_1118_ir_tx_mem_0.field.reg_sram_wd = ((0x4)|(0xf<<4)|(0x3<<8)|(0x4<<12)); 
        irtx_register_base->reg_1118_ir_tx_mem_0.field.reg_sram_wd = ((0xf)|(0x3<<4)|(0x4<<8)|(0xf<<12));
        irtx_register_base->reg_1118_ir_tx_mem_0.field.reg_sram_wd = (0xe); 
        irtx_register_base->reg_0080_ir_tx_0.field.reg_ir_tx_wait_value_0080=0;
    }else{
        irtx_register_base->reg_1118_ir_tx_mem_0.field.reg_sram_wd = ((~command_reverse>>7) & 0x1)|(0x5<<4)|(0xe<<8); //set end
    }
    irtx_register_base->reg_008c_ir_tx_0.field.reg_ir_tx_trigger_008C =1;      //set start
    hal_nvic_save_and_set_interrupt_mask(&save_mask);
    ir_tx_status &= ~IRTX_CONFIG_STATUS;
    ir_tx_status |= IRTX_START_STATUS;
    hal_nvic_restore_interrupt_mask(save_mask);
    return HAL_IRTX_STATUS_OK;
}


hal_irtx_status_t hal_irtx_send_rc5_data(uint8_t *address,uint8_t *command){
    uint32_t  save_mask;
    if((ir_tx_status & IRTX_INIT_STATUS) == 0){
        log_irtx_error("[hal][irtx]:in rc5 send data, irtx not init\r\n",0);
        return HAL_IRTX_STATUS_NOT_INIT;
    }
    if(ir_tx_status & IRTX_START_STATUS){
        log_irtx_error("[hal][irtx]:in rc5 send data, irtx busy\r\n",0);
       return HAL_IRTX_STATUS_BUSY;
    }
    hal_nvic_save_and_set_interrupt_mask(&save_mask);
    if(ir_tx_status & IRTX_CONFIG_STATUS){
        log_irtx_error("[hal][irtx]:in rc5 send data, irtx is config\r\n",0);
        hal_nvic_restore_interrupt_mask(save_mask);
        return HAL_IRTX_STATUS_CONFIG;
    }
    if(hal_irtx_configure_pulse_data_carrier(36000,33) != HAL_IRTX_STATUS_OK){
        log_irtx_error("[hal][irtx]:rc5 send data clock config error\r\n",0);
        hal_nvic_restore_interrupt_mask(save_mask);
        return HAL_IRTX_STATUS_ERROR;
    }
    ir_tx_status |= IRTX_CONFIG_STATUS;
    hal_nvic_restore_interrupt_mask(save_mask);
    irtx_set_unit_value(1,889,889,0,1);  //set nec logic "1";
    irtx_set_unit_value(0,889,889,1,0);  //set nec logic "0";
    irtx_set_total_cycle(114000); //set total cycle;
    irtx_register_base->reg_0088_ir_tx_0.field.reg_ir_tx_rstz_0088 = 1;
    irtx_register_base->reg_1004_ir_tx_mem_0.field.reg_key = 0x5;
    irtx_register_base->reg_1004_ir_tx_mem_0.field.reg_addr_auto_inc = 0x1;
    irtx_register_base->reg_1108_ir_tx_mem_0.field.reg_addr = 0x0;
    rc5_send_data = (*address<<6 & 0x7c0) | (*command & 0x3f);
    rc5_send_data |= (0x6|rc5_tr)<< 11; //add one bit for HEADER;
    rc5_send_data = irtx_msb_transfer_lsb(rc5_send_data,14);
    irtx_register_base->reg_1118_ir_tx_mem_0.field.reg_sram_wd = (irtx_bit_transfer_shift((rc5_send_data & 0xF),1,4)); //set header and data;
    irtx_register_base->reg_1118_ir_tx_mem_0.field.reg_sram_wd = (irtx_bit_transfer_shift(((rc5_send_data>>4)&0xF),1,4));
    irtx_register_base->reg_1118_ir_tx_mem_0.field.reg_sram_wd = (irtx_bit_transfer_shift(((rc5_send_data>>8)&0xF),1,4));
    irtx_register_base->reg_1118_ir_tx_mem_0.field.reg_sram_wd = (irtx_bit_transfer_shift((rc5_send_data>>12 & 0x3),1,2) & 0xFF)|(0xe<<8);
    irtx_register_base->reg_0088_ir_tx_0.field.reg_ir_tx_carrier_en_0088 = 1;  //set carrier
    irtx_register_base->reg_008c_ir_tx_0.field.reg_ir_tx_trigger_008C =1;      //set start
    hal_nvic_save_and_set_interrupt_mask(&save_mask);
    rc5_tr++;
    if(rc5_tr == 2)rc5_tr = 0;
    ir_tx_status &= ~IRTX_CONFIG_STATUS;
    ir_tx_status |= IRTX_START_STATUS;
    hal_nvic_restore_interrupt_mask(save_mask);
    return HAL_IRTX_STATUS_OK;
}


hal_irtx_status_t hal_irtx_send_rc6_data(uint8_t * mode,uint8_t *control,uint8_t *information){
    uint32_t  save_mask;
    if((ir_tx_status & IRTX_INIT_STATUS) == 0){
        log_irtx_error("[hal][irtx]:in rc6 send data, irtx not init\r\n",0);
        return HAL_IRTX_STATUS_NOT_INIT;
    }
    if(ir_tx_status & IRTX_START_STATUS){
        log_irtx_error("[hal][irtx]:in rc6 send data, irtx busy\r\n",0);
       return HAL_IRTX_STATUS_BUSY;
    }
    hal_nvic_save_and_set_interrupt_mask(&save_mask);
    if(ir_tx_status & IRTX_CONFIG_STATUS){
        log_irtx_error("[hal][irtx]:in rc6 send data, irtx is config\r\n",0);
        hal_nvic_restore_interrupt_mask(save_mask);
        return HAL_IRTX_STATUS_CONFIG;
    }
    if(hal_irtx_configure_pulse_data_carrier(36000,33) != HAL_IRTX_STATUS_OK){
        log_irtx_error("[hal][irtx][poll]:send rc6 data clock config error\r\n",0);
        hal_nvic_restore_interrupt_mask(save_mask);
        return HAL_IRTX_STATUS_ERROR;
    }
    ir_tx_status |= IRTX_CONFIG_STATUS;
    hal_nvic_restore_interrupt_mask(save_mask);
    irtx_set_unit_value(5,1333,1333,0,0);  //set rc6 logic "signal free";
    irtx_set_unit_value(4,2666,899,1,0);   //set rc6 logic "header";
    irtx_set_unit_value(3,889,889,1,0);   //set rc6 TR logic "1";
    irtx_set_unit_value(2,889,889,0,1);   //set rc6 TR logic "0";
    irtx_set_unit_value(1,444,444,1,0);   //set rc6 logic "1";
    irtx_set_unit_value(0,444,444,0,1);   //set rc6 logic "0";
    irtx_set_total_cycle(114000); //set total cycle;
    irtx_register_base->reg_0088_ir_tx_0.field.reg_ir_tx_rstz_0088 = 1;
    irtx_register_base->reg_1004_ir_tx_mem_0.field.reg_key = 0x5;
    irtx_register_base->reg_1004_ir_tx_mem_0.field.reg_addr_auto_inc = 0x1;
    irtx_register_base->reg_1108_ir_tx_mem_0.field.reg_addr = 0x0;
    rc6_send_data = (*control<<8) | (*information);
    rc6_send_data = irtx_msb_transfer_lsb(rc6_send_data,16);
                                                                 //header start   mb2                        mb1
    irtx_register_base->reg_1118_ir_tx_mem_0.field.reg_sram_wd = 0x4 |(0x1 << 4)| ((*mode >>2 & 0x1) << 8) | ((*mode >>1 & 0x1) << 12); //set header
                                                                  //mb0          //TR
    irtx_register_base->reg_1118_ir_tx_mem_0.field.reg_sram_wd =  (*mode & 0x1) |((2+rc6_tr) << 4)|((irtx_bit_transfer_shift((rc6_send_data&0x3),1,2) & 0xFF) << 8);
    irtx_register_base->reg_1118_ir_tx_mem_0.field.reg_sram_wd = (irtx_bit_transfer_shift(((rc6_send_data>>2)&0xF),1,4));
    irtx_register_base->reg_1118_ir_tx_mem_0.field.reg_sram_wd = (irtx_bit_transfer_shift(((rc6_send_data>>6) & 0xF),1,4));
    irtx_register_base->reg_1118_ir_tx_mem_0.field.reg_sram_wd = (irtx_bit_transfer_shift(((rc6_send_data>>10) & 0xF),1,4));                                      
                                                                                                                           //signal free
    irtx_register_base->reg_1118_ir_tx_mem_0.field.reg_sram_wd = (irtx_bit_transfer_shift(((rc6_send_data>>14)&0x3),1,2) & 0xFF) | (0x5 << 8) | (0xe << 12);
    irtx_register_base->reg_0088_ir_tx_0.field.reg_ir_tx_carrier_en_0088 = 1;  //set carrier
    irtx_register_base->reg_008c_ir_tx_0.field.reg_ir_tx_trigger_008C =1;      //set start
    rc6_tr++;
    if(rc6_tr == 2)rc6_tr = 0;
    hal_nvic_save_and_set_interrupt_mask(&save_mask);
    ir_tx_status &= ~IRTX_CONFIG_STATUS;
    ir_tx_status |= IRTX_START_STATUS;
    hal_nvic_restore_interrupt_mask(save_mask);
    return HAL_IRTX_STATUS_OK;
}

hal_irtx_status_t hal_irtx_send_sirc_12bit_data(uint8_t *command,uint8_t *address){
    uint32_t  save_mask;
    if((ir_tx_status & IRTX_INIT_STATUS) == 0){
        log_irtx_error("[hal][irtx]:in sirc 12bit send data, irtx not init\r\n",0);
        return HAL_IRTX_STATUS_NOT_INIT;
    }
    if(ir_tx_status & IRTX_START_STATUS){
        log_irtx_error("[hal][irtx]:in sirc 12bit send data, irtx busy\r\n",0);
       return HAL_IRTX_STATUS_BUSY;
    }
    hal_nvic_save_and_set_interrupt_mask(&save_mask);
    if(ir_tx_status & IRTX_CONFIG_STATUS){
        log_irtx_error("[hal][irtx]:in sirc 12bit send data, irtx is config\r\n",0);
        hal_nvic_restore_interrupt_mask(save_mask);
        return HAL_IRTX_STATUS_CONFIG;
    }
    if(hal_irtx_configure_pulse_data_carrier(40000,33) != HAL_IRTX_STATUS_OK){
        log_irtx_error("[hal][irtx]:send sirc 12bit data clock config error\r\n",0);
        hal_nvic_restore_interrupt_mask(save_mask);
        return HAL_IRTX_STATUS_ERROR;
    }
    ir_tx_status |= IRTX_CONFIG_STATUS;
    hal_nvic_restore_interrupt_mask(save_mask);
    irtx_set_unit_value(2,2400,600,1,0);  //set sirc logic "header";
    irtx_set_unit_value(1,1200,600,1,0);  //set sirc logic "1";
    irtx_set_unit_value(0,600,600,1,0);  //set sirc logic "0";
    irtx_set_total_cycle(45000); //set total cycle;
    irtx_register_base->reg_0088_ir_tx_0.field.reg_ir_tx_rstz_0088 = 1;
    irtx_register_base->reg_1004_ir_tx_mem_0.field.reg_key = 0x5;
    irtx_register_base->reg_1004_ir_tx_mem_0.field.reg_addr_auto_inc = 0x1;
    irtx_register_base->reg_1108_ir_tx_mem_0.field.reg_addr = 0x0;
    sirc_send_data = (*command & 0x7f)|((*address & 0x3f)<<7);
    sirc_send_data = sirc_send_data << 1; //add one bit for HEADER;
    irtx_register_base->reg_1118_ir_tx_mem_0.field.reg_sram_wd = (irtx_bit_transfer_shift((sirc_send_data & 0xF),1,4) &0xFFF0)|0x2; //set header and data;
    irtx_register_base->reg_1118_ir_tx_mem_0.field.reg_sram_wd = (irtx_bit_transfer_shift(((sirc_send_data>>4)&0xF),1,4));
    irtx_register_base->reg_1118_ir_tx_mem_0.field.reg_sram_wd = (irtx_bit_transfer_shift(((sirc_send_data>>8)&0xF),1,4));
    irtx_register_base->reg_1118_ir_tx_mem_0.field.reg_sram_wd = (irtx_bit_transfer_shift((sirc_send_data>>12),1,1)&0xF)|(0xe<<4);
    irtx_register_base->reg_0088_ir_tx_0.field.reg_ir_tx_carrier_en_0088 = 1;  //set carrier
    irtx_register_base->reg_008c_ir_tx_0.field.reg_ir_tx_trigger_008C =1;      //set start
    hal_nvic_save_and_set_interrupt_mask(&save_mask);
    ir_tx_status &= ~IRTX_CONFIG_STATUS;
    ir_tx_status |= IRTX_START_STATUS;
    hal_nvic_restore_interrupt_mask(save_mask);
    return HAL_IRTX_STATUS_OK;
}


hal_irtx_status_t hal_irtx_send_sirc_15bit_data(uint8_t *command,uint8_t *address){
    uint32_t  save_mask;
    if((ir_tx_status & IRTX_INIT_STATUS) == 0){
        log_irtx_error("[hal][irtx]:in sirc 15bit send data, irtx not init\r\n",0);
        return HAL_IRTX_STATUS_NOT_INIT;
    }
    if(ir_tx_status & IRTX_START_STATUS){
        log_irtx_error("[hal][irtx]:in sirc 15bit send data, irtx busy\r\n",0);
       return HAL_IRTX_STATUS_BUSY;
    }
    hal_nvic_save_and_set_interrupt_mask(&save_mask);
    if(ir_tx_status & IRTX_CONFIG_STATUS){
        log_irtx_error("[hal][irtx]:in sirc 15bit send data, irtx is config\r\n",0);
        hal_nvic_restore_interrupt_mask(save_mask);
        return HAL_IRTX_STATUS_CONFIG;
    }
    if(hal_irtx_configure_pulse_data_carrier(40000,33) != HAL_IRTX_STATUS_OK){
        log_irtx_error("[hal][irtx][poll]:send sirc 15bit data clock config error\r\n",0);
        hal_nvic_restore_interrupt_mask(save_mask);
        return HAL_IRTX_STATUS_ERROR;
    }
    ir_tx_status |= IRTX_CONFIG_STATUS;
    hal_nvic_restore_interrupt_mask(save_mask);
    irtx_set_unit_value(2,2400,600,1,0);  //set sirc logic "header";
    irtx_set_unit_value(1,1200,600,1,0);  //set sirc logic "1";
    irtx_set_unit_value(0,600,600,1,0);  //set sirc logic "0";
    irtx_set_total_cycle(45000); //set total cycle;
    irtx_register_base->reg_0088_ir_tx_0.field.reg_ir_tx_rstz_0088 = 1;
    irtx_register_base->reg_1004_ir_tx_mem_0.field.reg_key = 0x5;
    irtx_register_base->reg_1004_ir_tx_mem_0.field.reg_addr_auto_inc = 0x1;
    irtx_register_base->reg_1108_ir_tx_mem_0.field.reg_addr = 0x0;
    sirc_send_data = (*command & 0x7f)|((*address & 0xff)<<7);
    sirc_send_data = sirc_send_data << 1; //add one bit for HEADER;
    irtx_register_base->reg_1118_ir_tx_mem_0.field.reg_sram_wd = (irtx_bit_transfer_shift((sirc_send_data & 0xF),1,4) &0xFFF0)|0x2; //set header and data;
    irtx_register_base->reg_1118_ir_tx_mem_0.field.reg_sram_wd = (irtx_bit_transfer_shift(((sirc_send_data>>4)&0xF),1,4));
    irtx_register_base->reg_1118_ir_tx_mem_0.field.reg_sram_wd = (irtx_bit_transfer_shift(((sirc_send_data>>8)&0xF),1,4));
    irtx_register_base->reg_1118_ir_tx_mem_0.field.reg_sram_wd = (irtx_bit_transfer_shift(((sirc_send_data>>12)&0xF),1,4));
    irtx_register_base->reg_1118_ir_tx_mem_0.field.reg_sram_wd = 0xe;
    irtx_register_base->reg_0088_ir_tx_0.field.reg_ir_tx_carrier_en_0088 = 1;  //set carrier
    irtx_register_base->reg_008c_ir_tx_0.field.reg_ir_tx_trigger_008C =1;      //set start
    hal_nvic_save_and_set_interrupt_mask(&save_mask);
    ir_tx_status &= ~IRTX_CONFIG_STATUS;
    ir_tx_status |= IRTX_START_STATUS;
    hal_nvic_restore_interrupt_mask(save_mask);
    return HAL_IRTX_STATUS_OK;
}

hal_irtx_status_t hal_irtx_send_sirc_20bit_data(uint8_t *command,uint8_t *address,uint8_t *extend){
    uint32_t  save_mask;
    if((ir_tx_status & IRTX_INIT_STATUS) == 0){
        log_irtx_error("[hal][irtx]:in sirc 20bit send data, irtx not init\r\n",0);
        return HAL_IRTX_STATUS_NOT_INIT;
    }
    if(ir_tx_status & IRTX_START_STATUS){
        log_irtx_error("[hal][irtx]:in sirc 20bit send data, irtx busy\r\n",0);
       return HAL_IRTX_STATUS_BUSY;
    }
    hal_nvic_save_and_set_interrupt_mask(&save_mask);
    if(ir_tx_status & IRTX_CONFIG_STATUS){
        log_irtx_error("[hal][irtx]:in sirc 20bit send data, irtx is config\r\n",0);
        hal_nvic_restore_interrupt_mask(save_mask);
        return HAL_IRTX_STATUS_CONFIG;
    }
    if(hal_irtx_configure_pulse_data_carrier(40000,33) != HAL_IRTX_STATUS_OK){
        log_irtx_error("[hal][irtx][poll]:send sirc 20bit data clock config error\r\n",0);
        hal_nvic_restore_interrupt_mask(save_mask);
        return HAL_IRTX_STATUS_ERROR;
    }
    ir_tx_status |= IRTX_CONFIG_STATUS;
    hal_nvic_restore_interrupt_mask(save_mask);
    irtx_set_unit_value(2,2400,600,1,0);  //set nec logic "header";
    irtx_set_unit_value(1,1200,600,1,0);  //set nec logic "1";
    irtx_set_unit_value(0,600,600,1,0);  //set nec logic "0";
    irtx_set_total_cycle(45000); //set total cycle;
    irtx_register_base->reg_0088_ir_tx_0.field.reg_ir_tx_rstz_0088 = 1;
    irtx_register_base->reg_1004_ir_tx_mem_0.field.reg_key = 0x5;
    irtx_register_base->reg_1004_ir_tx_mem_0.field.reg_addr_auto_inc = 0x1;
    irtx_register_base->reg_1108_ir_tx_mem_0.field.reg_addr = 0x0;
    sirc_send_data = (*command & 0x7f)|((*address & 0x3f)<<7)|((*extend & 0xff)<<12);
    sirc_send_data = sirc_send_data << 1; //add one bit for HEADER;
    irtx_register_base->reg_1118_ir_tx_mem_0.field.reg_sram_wd = (irtx_bit_transfer_shift((sirc_send_data & 0xF),1,4) &0xFFF0)|0x2; //set header and data;
    irtx_register_base->reg_1118_ir_tx_mem_0.field.reg_sram_wd = (irtx_bit_transfer_shift(((sirc_send_data>>4)&0xF),1,4));
    irtx_register_base->reg_1118_ir_tx_mem_0.field.reg_sram_wd = (irtx_bit_transfer_shift(((sirc_send_data>>8)&0xF),1,4));
    irtx_register_base->reg_1118_ir_tx_mem_0.field.reg_sram_wd = (irtx_bit_transfer_shift(((sirc_send_data>>12)&0xF),1,4));
    irtx_register_base->reg_1118_ir_tx_mem_0.field.reg_sram_wd = (irtx_bit_transfer_shift(((sirc_send_data>>16)&0xF),1,4));
    irtx_register_base->reg_1118_ir_tx_mem_0.field.reg_sram_wd = (irtx_bit_transfer_shift((sirc_send_data>>20),1,1)&0xF)|(0xe<<4);
    irtx_register_base->reg_0088_ir_tx_0.field.reg_ir_tx_carrier_en_0088 = 1;  //set carrier
    irtx_register_base->reg_008c_ir_tx_0.field.reg_ir_tx_trigger_008C =1;      //set start
    hal_nvic_save_and_set_interrupt_mask(&save_mask);
    ir_tx_status &= ~IRTX_CONFIG_STATUS;
    ir_tx_status |= IRTX_START_STATUS;
    hal_nvic_restore_interrupt_mask(save_mask);
    return HAL_IRTX_STATUS_OK;
}

hal_irtx_status_t hal_irtx_send_rcmm_12bit_data(uint8_t *mode,uint8_t *address,uint8_t *data){
    uint32_t  save_mask;
    if((ir_tx_status & IRTX_INIT_STATUS) == 0){
        log_irtx_error("[hal][irtx]:in rcmm 12bit send data, irtx not init\r\n",0);
        return HAL_IRTX_STATUS_NOT_INIT;
    }
    if(ir_tx_status & IRTX_START_STATUS){
        log_irtx_error("[hal][irtx]:in rcmm 12bit send data, irtx busy\r\n",0);
       return HAL_IRTX_STATUS_BUSY;
    }
    hal_nvic_save_and_set_interrupt_mask(&save_mask);
    if(ir_tx_status & IRTX_CONFIG_STATUS){
        log_irtx_error("[hal][irtx]:in rcmm 12bit send data, irtx is config\r\n",0);
        hal_nvic_restore_interrupt_mask(save_mask);
        return HAL_IRTX_STATUS_CONFIG;
    }
    if(hal_irtx_configure_pulse_data_carrier(36000,33) != HAL_IRTX_STATUS_OK){
        log_irtx_error("[hal][irtx][poll]:send rcmm 12bit data clock config error\r\n",0);
        hal_nvic_restore_interrupt_mask(save_mask);
        return HAL_IRTX_STATUS_ERROR;
    }
    ir_tx_status |= IRTX_CONFIG_STATUS;
    hal_nvic_restore_interrupt_mask(save_mask);
    irtx_set_unit_value(5,176,10,1,0);  //set rcmm logic "end";   167 real 140 
    irtx_set_unit_value(4,417,278,1,0);  //set rcmm logic "header";
    irtx_set_unit_value(3,176,778,1,0);  //set rcmm logic "3";
    irtx_set_unit_value(2,176,611,1,0);  //set rcmm logic "2";
    irtx_set_unit_value(1,176,444,1,0);  //set rcmm logic "1";
    irtx_set_unit_value(0,176,278,1,0);  //set rcmm logic "0";
    irtx_set_total_cycle(27778); //set total cycle;
    irtx_register_base->reg_0088_ir_tx_0.field.reg_ir_tx_rstz_0088 = 1;
    irtx_register_base->reg_1004_ir_tx_mem_0.field.reg_key = 0x5;
    irtx_register_base->reg_1004_ir_tx_mem_0.field.reg_addr_auto_inc = 0x1;
    irtx_register_base->reg_1108_ir_tx_mem_0.field.reg_addr = 0x0;
    rcmm_send_data = (*mode & 0x3)|((*address & 0x3)<<2)|((*data &0xFF)<<4);
    rcmm_send_data = rcmm_send_data <<2;
    irtx_register_base->reg_1118_ir_tx_mem_0.field.reg_sram_wd = (irtx_bit_transfer_shift((rcmm_send_data & 0xFF),2,8) &0xFFF0)|0x4; //set header and data;
    irtx_register_base->reg_1118_ir_tx_mem_0.field.reg_sram_wd =  (irtx_bit_transfer_shift(((rcmm_send_data>>8) & 0xFF),2,8))|(0x5<<12); //set data;
    irtx_register_base->reg_1118_ir_tx_mem_0.field.reg_sram_wd = 0xe;
    irtx_register_base->reg_0088_ir_tx_0.field.reg_ir_tx_carrier_en_0088 = 1;  //set carrier
    irtx_register_base->reg_008c_ir_tx_0.field.reg_ir_tx_trigger_008C =1;      //set start
    hal_nvic_save_and_set_interrupt_mask(&save_mask);
    ir_tx_status &= ~IRTX_CONFIG_STATUS;
    ir_tx_status |= IRTX_START_STATUS;
    hal_nvic_restore_interrupt_mask(save_mask);
    return HAL_IRTX_STATUS_OK;
}


hal_irtx_status_t hal_irtx_send_rcmm_24bit_data(uint8_t *mode,uint32_t *data){
    uint32_t  save_mask;
    if((ir_tx_status & IRTX_INIT_STATUS) == 0){
        log_irtx_error("[hal][irtx]:in rcmm 24bit send data, irtx not init\r\n",0);
        return HAL_IRTX_STATUS_NOT_INIT;
    }
    if(ir_tx_status & IRTX_START_STATUS){
        log_irtx_error("[hal][irtx]:in rcmm 24bit send data, irtx busy\r\n",0);
       return HAL_IRTX_STATUS_BUSY;
    }
    hal_nvic_save_and_set_interrupt_mask(&save_mask);
    if(ir_tx_status & IRTX_CONFIG_STATUS){
        log_irtx_error("[hal][irtx]:in rcmm 24bit send data, irtx is config\r\n",0);
        hal_nvic_restore_interrupt_mask(save_mask);
        return HAL_IRTX_STATUS_CONFIG;
    }
    if(hal_irtx_configure_pulse_data_carrier(36000,33) != HAL_IRTX_STATUS_OK){
        log_irtx_error("[hal][irtx][poll]:send rcmm 24bit data clock config error\r\n",0);
        hal_nvic_restore_interrupt_mask(save_mask);
        return HAL_IRTX_STATUS_ERROR;
    }
    ir_tx_status |= IRTX_CONFIG_STATUS;
    hal_nvic_restore_interrupt_mask(save_mask);
    irtx_set_unit_value(5,176,10,1,0);  //set rcmm logic "end";   167 real 140 
    irtx_set_unit_value(4,417,278,1,0);  //set rcmm logic "header";
    irtx_set_unit_value(3,176,778,1,0);  //set rcmm logic "3";
    irtx_set_unit_value(2,176,611,1,0);  //set rcmm logic "2";
    irtx_set_unit_value(1,176,444,1,0);  //set rcmm logic "1";
    irtx_set_unit_value(0,176,278,1,0);  //set rcmm logic "0";
    irtx_set_total_cycle(27778); //set total cycle;
    irtx_register_base->reg_0088_ir_tx_0.field.reg_ir_tx_rstz_0088 = 1;
    irtx_register_base->reg_1004_ir_tx_mem_0.field.reg_key = 0x5;
    irtx_register_base->reg_1004_ir_tx_mem_0.field.reg_addr_auto_inc = 0x1;
    irtx_register_base->reg_1108_ir_tx_mem_0.field.reg_addr = 0x0;
    rcmm_send_data = (*mode & 0xF)|((*data &0xFFFFF)<<4);
    rcmm_send_data = rcmm_send_data <<2;
    irtx_register_base->reg_1118_ir_tx_mem_0.field.reg_sram_wd = (irtx_bit_transfer_shift((rcmm_send_data & 0xFF),2,8) &0xFFF0)|0x4;  //set header and data;
    irtx_register_base->reg_1118_ir_tx_mem_0.field.reg_sram_wd = (irtx_bit_transfer_shift(((rcmm_send_data >> 8 )& 0xFF),2,8)); //set data;
    irtx_register_base->reg_1118_ir_tx_mem_0.field.reg_sram_wd = (irtx_bit_transfer_shift(((rcmm_send_data >> 16 )& 0xFF),2,8)); //set data;
    irtx_register_base->reg_1118_ir_tx_mem_0.field.reg_sram_wd = (irtx_bit_transfer_shift(((rcmm_send_data >> 24 )& 0xFF),2,8))|(0x5<<4)|(0xe<<8);; //set data;
    irtx_register_base->reg_0088_ir_tx_0.field.reg_ir_tx_carrier_en_0088 = 1;  //set carrier
    irtx_register_base->reg_008c_ir_tx_0.field.reg_ir_tx_trigger_008C =1;      //set start
    hal_nvic_save_and_set_interrupt_mask(&save_mask);
    ir_tx_status &= ~IRTX_CONFIG_STATUS;
    ir_tx_status |= IRTX_START_STATUS;
    hal_nvic_restore_interrupt_mask(save_mask);
    return HAL_IRTX_STATUS_OK;
}


hal_irtx_status_t hal_irtx_send_rcmm_oem_data(uint8_t *mode,uint8_t *custom_id,uint16_t *data){
    uint32_t  save_mask;
    if((ir_tx_status & IRTX_INIT_STATUS) == 0){
        log_irtx_error("[hal][irtx]:in rcmm oem send data, irtx not init\r\n",0);
        return HAL_IRTX_STATUS_NOT_INIT;
    }
    if(ir_tx_status & IRTX_START_STATUS){
        log_irtx_error("[hal][irtx]:in rcmm oem send data, irtx busy\r\n",0);
       return HAL_IRTX_STATUS_BUSY;
    }
    hal_nvic_save_and_set_interrupt_mask(&save_mask);
    if(ir_tx_status & IRTX_CONFIG_STATUS){
        log_irtx_error("[hal][irtx]:in rcmm oem send data, irtx is config\r\n",0);
        hal_nvic_restore_interrupt_mask(save_mask);
        return HAL_IRTX_STATUS_CONFIG;
    }
    if(hal_irtx_configure_pulse_data_carrier(36000,33) != HAL_IRTX_STATUS_OK){
        log_irtx_error("[hal][irtx][poll]:send rcmm oem data clock config error\r\n",0);
        hal_nvic_restore_interrupt_mask(save_mask);
        return HAL_IRTX_STATUS_ERROR;
    }
    ir_tx_status |= IRTX_CONFIG_STATUS;
    hal_nvic_restore_interrupt_mask(save_mask);
    irtx_set_unit_value(5,176,10,1,0);  //set rcmm logic "end";   167 real 140 
    irtx_set_unit_value(4,417,278,1,0);  //set rcmm logic "header";
    irtx_set_unit_value(3,176,778,1,0);  //set rcmm logic "3";
    irtx_set_unit_value(2,176,611,1,0);  //set rcmm logic "2";
    irtx_set_unit_value(1,176,444,1,0);  //set rcmm logic "1";
    irtx_set_unit_value(0,176,278,1,0);  //set rcmm logic "0";
    irtx_set_total_cycle(27778); //set total cycle;
    irtx_register_base->reg_0088_ir_tx_0.field.reg_ir_tx_rstz_0088 = 1;
    irtx_register_base->reg_1004_ir_tx_mem_0.field.reg_key = 0x5;
    irtx_register_base->reg_1004_ir_tx_mem_0.field.reg_addr_auto_inc = 0x1;
    irtx_register_base->reg_1108_ir_tx_mem_0.field.reg_addr = 0x0;
    rcmm_send_data = (*mode & 0x3F)|((*custom_id & 0x3F)<<6)|((*data &0xFFF)<<12);
    rcmm_send_data = rcmm_send_data <<2;
    irtx_register_base->reg_1118_ir_tx_mem_0.field.reg_sram_wd = (irtx_bit_transfer_shift((rcmm_send_data & 0xFF),2,8) &0xFFF0)|0x4;  //set header and data;
    irtx_register_base->reg_1118_ir_tx_mem_0.field.reg_sram_wd = (irtx_bit_transfer_shift(((rcmm_send_data >> 8 )& 0xFF),2,8)); //set data;
    irtx_register_base->reg_1118_ir_tx_mem_0.field.reg_sram_wd = (irtx_bit_transfer_shift(((rcmm_send_data >> 16 )& 0xFF),2,8)); //set data;
    irtx_register_base->reg_1118_ir_tx_mem_0.field.reg_sram_wd = (irtx_bit_transfer_shift(((rcmm_send_data >> 24 )& 0xFF),2,8))|(0x5<<4)|(0xe<<8);; //set data;
    irtx_register_base->reg_0088_ir_tx_0.field.reg_ir_tx_carrier_en_0088 = 1;  //set carrier
    irtx_register_base->reg_008c_ir_tx_0.field.reg_ir_tx_trigger_008C =1;      //set start
    hal_nvic_save_and_set_interrupt_mask(&save_mask);
    ir_tx_status &= ~IRTX_CONFIG_STATUS;
    ir_tx_status |= IRTX_START_STATUS;
    hal_nvic_restore_interrupt_mask(save_mask);
    return HAL_IRTX_STATUS_OK;
}

hal_irtx_status_t hal_irtx_configure_pulse_data_carrier(uint32_t frequency,
                                                        uint8_t duty_radio){
    uint16_t high_cnt,low_cnt;
    if((frequency > IRTX_CLOCK_SOURCE) && (duty_radio > 100)){
        log_irtx_error("[hal][irtx][poll]:configure pulse data carrier failed, frequency or duty_radio is invalid!\r\n",0);
        return HAL_IRTX_STATUS_ERROR;
    }
    irtx_clock_div_set(IRTX_CLOCK_SOURCE);//set 4m clocksource
    high_cnt = (IRTX_CLOCK_SOURCE*duty_radio)/(frequency*100);
    low_cnt = (IRTX_CLOCK_SOURCE/frequency)-high_cnt;
    irtx_register_base->reg_0084_ir_tx_0.field.reg_ir_tx_carrier_hcnt_0084 = (uint8_t)high_cnt;  //set high cnt
    irtx_register_base->reg_0084_ir_tx_0.field.reg_ir_tx_carrier_lcnt_0084 = (uint8_t)low_cnt;   //set low cnt
    return HAL_IRTX_STATUS_OK;
}


hal_irtx_status_t hal_irtx_register_callback(hal_irtx_callback_t callback, void *user_data){

    irtx_register_callback(callback,user_data);

    return HAL_IRTX_STATUS_OK;
}

#endif // HAL_IRTX_MODULE_ENABLED