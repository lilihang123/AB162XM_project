/* Copyright Statement:
 *
 * (C) 2005-2016  MediaTek Inc. All rights reserved.
 *
 * This software/firmware and related documentation ("MediaTek Software") are
 * protected under relevant copyright laws. The information contained herein
 * is confidential and proprietary to MediaTek Inc. ("MediaTek") and/or its licensors.
 * Without the prior written permission of MediaTek and/or its licensors,
 * any reproduction, modification, use or disclosure of MediaTek Software,
 * and information contained herein, in whole or in part, shall be strictly prohibited.
 * You may only use, reproduce, modify, or distribute (as applicable) MediaTek Software
 * if you have agreed to and been bound by the applicable license agreement with
 * MediaTek ("License Agreement") and been granted explicit permission to do so within
 * the License Agreement ("Permitted User").  If you are not a Permitted User,
 * please cease any access or use of MediaTek Software immediately.
 * BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 * THAT MEDIATEK SOFTWARE RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES
 * ARE PROVIDED TO RECEIVER ON AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL
 * WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
 * NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
 * SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
 * SUPPLIED WITH MEDIATEK SOFTWARE, AND RECEIVER AGREES TO LOOK ONLY TO SUCH
 * THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. RECEIVER EXPRESSLY ACKNOWLEDGES
 * THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES
 * CONTAINED IN MEDIATEK SOFTWARE. MEDIATEK SHALL ALSO NOT BE RESPONSIBLE FOR ANY MEDIATEK
 * SOFTWARE RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
 * STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND
 * CUMULATIVE LIABILITY WITH RESPECT TO MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
 * AT MEDIATEK'S OPTION, TO REVISE OR REPLACE MEDIATEK SOFTWARE AT ISSUE,
 * OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY RECEIVER TO
 * MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
 */

#ifndef __HAL_ARGB_H__
#define __HAL_ARGB_H__
#include "hal_platform.h"
#ifdef HAL_ARGB_MODULE_ENABLED
#define argb_irq_num 25

/** @brief	This enum defines the API return type.  */
typedef enum {
    HAL_ARGB_STATUS_NOT_INIT             = -4,         /**<  The argb not init */
    HAL_ARGB_STATUS_ERROR_BUSY           = -3,         /**<  The argb bus is busy, an error occurred. */
    HAL_ARGB_STATUS_ERROR                = -2,         /**< An error occurred during the function call. */
    HAL_ARGB_STATUS_INVALID_PARAMETER    = -1,         /**< A wrong parameter is given. */
    HAL_ARGB_STATUS_OK                   =  0          /**< No error during the function call. */
} hal_argb_status_t;


typedef enum {
    HAL_ARGB_STOP_EVENT = 0,                            /**<  The ARGB STOP EVENT. */
    HAL_ARGB_RESET_START_EVENT = 1,                     /**<  The ARGB AUTO MODE Reset_START EVENT.*/
    HAL_ARGB_RE_START_EVENT = 2,                        /**<  The ARGB AUTO MODE Re_START EVENT.*/
    HAL_ARGB_PRE_WAKEUP_EVENT = 3,                      /**<  The ARGB AUTO MODE Pre_Wakeup EVENT.*/
    HAL_ARGB_START_EVENT = 4,                           /**<  The ARGB AUTO MODE START EVENT.*/
    HAL_ARGB_AUTO_OFF_EVENT =  5,                       /**<  The ARGB AUTO MODE OFF EVENT.*/
    HAL_ARGB_DMA_LVL_EVENT = 6,                         /**<  The ARGB DMA LVL EVENT.*/
    HAL_ARGB_UNKOWN_EVENT =  7,                         /**<  The ARGB AUTO MODE UNKOWN EVENT*/
} hal_argb_callback_event_t;


typedef struct {
    bool argb_stop;                               /**<  THe ARGB stop IRQ*/
    bool argb_reset_start;                        /**<  THe ARGB reset Start IRQ*/
    bool argb_re_start;                           /**<  THe ARGB Re_Start IRQ*/
    bool argb_pre_wakeup;                         /**<  THe ARGB Pre_Wakeup IRQ*/
    bool argb_start;                              /**<  THe ARGB start IRQ*/ 
    bool argb_auto_off;                           /**<  THe ARGB auto off IRQ*/
    bool dma_lvl;                                 /**<  THe ARGB dma lvl IRQ*/
}hal_argb_irq;


typedef struct {
    uint16_t one_l_value;                               /**<  THe ARGB one low value count,ns*/
    uint16_t one_h_value;                               /**<  THe ARGB one high value count,ns*/
    uint16_t zero_l_value;                              /**<  THe ARGB zero low value count,ns*/
    uint16_t zero_h_value;                              /**<  THe ARGB zero high value count,ns*/
    uint32_t reset_value;                               /**<  THe ARGB reset value count,ns*/ 
}hal_argb_timing_setting;

typedef struct {
    uint32_t auto_timer_value;                               /**<  THe ARGB play frequency,ns,0 is not set*/
    uint32_t dma_start_vaule;                               /**<  THe ARGB load dma data frequency,ns,0 is not set*/
    uint32_t pre_wake_value;                              /**<  THe ARGB set next dma data frequency,,0 is not set*/
}hal_argb_dma_timing_setting;

typedef struct {
    hal_argb_timing_setting timing;                   /**<  define THe ARGB timing*/
    bool bit_nonrev;                                         /**<  define THe ARGB play order*/
    bool nonalign;                                          /**<  define THe ARGB data non align*/
    bool endian_big;                                         /**<  define THe ARGB endian big*/
    uint8_t num;                                             /**<  define THe ARGB num*/
}hal_argb_setting;


typedef void (*hal_argb_callback_t)(hal_argb_callback_event_t event, void *user_data);


typedef struct {
    hal_argb_callback_t call_back;      
    void              *user_data;       
} argb_info_t;

/**
 * @brief    This function initializes the argb hardware.
 * @param[in]  setting is the argb init setting. For more details about the parameter, please refer to #hal_argb_setting.
 * @return    To indicate whether this function call is successful or not.
 *            If the return value is #HAL_ARGB_STATUS_OK, the operation completed successfully.
 *            If the return value is #HAL_ARGB_STATUS_ERROR, the argb already init.
 * @sa  hal_argb_deinit()
 */
hal_argb_status_t hal_argb_init(hal_argb_setting *setting);

/**
 * @brief    This function de-initializes the argb hardware.
 * @return    To indicate whether this function call is successful or not.
 *            If the return value is #HAL_ARGB_STATUS_OK, the operation completed successfully.
 *            If the return value is #HAL_ARGB_STATUS_ERROR_BUSY, the argb is running .
 *            If the return value is #HAL_ARGB_STATUS_NOT_INIT, the argb not init.
 * @sa  hal_argb_init()
 */
hal_argb_status_t hal_argb_deinit(void);

/**
 * @brief    This function setting the argb dma config.
 * @param[in]  setting is the argb dma setting. For more details about the parameter, please refer to #hal_argb_dma_timing_setting.
 * @return    To indicate whether this function call is successful or not.
 *            If the return value is #HAL_ARGB_STATUS_OK, the operation completed successfully.
 *            If the return value is #HAL_ARGB_STATUS_NOT_INIT, the argb not init.
 */
hal_argb_status_t hal_argb_dma_setting(hal_argb_dma_timing_setting *setting);

/**
 * @brief    This function config the argb dma buffer.
 * @param[in]  buf_total_count is the argb dma total buffer count num.
 * @param[in]  one_count_size is the argb dma one buffer count data size.
 * @return    To indicate whether this function call is successful or not.
 *            If the return value is #HAL_ARGB_STATUS_OK, the operation completed successfully.
 *            If the return value is #HAL_ARGB_STATUS_ERROR, the argb not setting dma.
 *            If the return value is HAL_ARGB_STATUS_INVALID_PARAMETER,the argb molloc failed.
 */
hal_argb_status_t hal_argb_config_dma_buf(uint32_t buf_total_count, uint32_t one_count_size);

/**
 * @brief    This function config the argb dma buf data.
 * @param[in]  buf_count_num is the argb dma buf count number.
 * @param[in]  count_data is the argb dma buf count number data.
 * @return    To indicate whether this function call is successful or not.
 *            If the return value is #HAL_ARGB_STATUS_OK, the operation completed successfully.
 *            If the return value is #HAL_ARGB_STATUS_ERROR, the argb not config dma buf.
 */
hal_argb_status_t hal_argb_config_dma_data(uint16_t buf_count_num, uint8_t *count_data);

/**
 * @brief    This function start the argb. 
 * @return    To indicate whether this function call is successful or not.
 *            If the return value is #HAL_ARGB_STATUS_OK, the operation completed successfully.
 *            If the return value is #HAL_ARGB_STATUS_ERROR, the argb not config dma buf.
 *            If the return value is HAL_ARGB_STATUS_ERROR_BUSY, the argb is running.
 */
hal_argb_status_t hal_argb_dma_start(void);

/**
 * @brief    This function stop the argb. 
 * @return    To indicate whether this function call is successful or not.
 *            If the return value is #HAL_ARGB_STATUS_OK, the operation completed successfully.
 *            If the return value is #HAL_ARGB_STATUS_ERROR, the argb not start.
 */
hal_argb_status_t hal_argb_dma_stop(void);

/**
 * @brief    This register the argb callback function. 
 * @param[in]  argb_callback is the argb user callback, please refer to #hal_argb_callback_t.
 * @param[in]  user_data is a user-defined input data returned during the callback function's call. 
 * @return    To indicate whether this function call is successful or not.
 *            If the return value is #HAL_ARGB_STATUS_OK, the operation completed successfully.
 *            If the return value is #HAL_ARGB_STATUS_NOT_INIT, the argb not init.
 */
hal_argb_status_t hal_argb_register_callback(hal_argb_callback_t argb_callback, void *user_data);

/**
 * @brief     The function enables the argb interrupt. 
 * @param[in]  irq_enable is the argb enable IRQ, please refer to #hal_argb_irq.
 * @return    To indicate whether this function call is successful or not.
 *            If the return value is #HAL_ARGB_STATUS_OK, the operation completed successfully.
 *            If the return value is #HAL_ARGB_STATUS_NOT_INIT, the argb not init.
 */
hal_argb_status_t hal_argb_irq_enable(hal_argb_irq *irq_enable);

#endif /* HAL_ARGB_H */

#endif