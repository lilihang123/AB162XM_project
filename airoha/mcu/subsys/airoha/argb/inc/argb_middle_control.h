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
 * BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWRGBGES AND AGREES
 * THAT AIROHA SOFTWARE RECEIVED FROM AIROHA AND/OR ITS REPRESENTATIVES
 * ARE PROVIDED TO RECEIVER ON AN "AS-IS" BASIS ONLY. AIROHA EXPRESSLY DISCLAIMS ANY AND ALL
 * WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
 * NEITHER DOES AIROHA PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
 * SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
 * SUPPLIED WITH AIROHA SOFTWARE, AND RECEIVER AGREES TO LOOK ONLY TO SUCH
 * THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. RECEIVER EXPRESSLY ACKNOWRGBGES
 * THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES
 * CONTAINED IN AIROHA SOFTWARE. AIROHA SHALL ALSO NOT BE RESPONSIBLE FOR ANY AIROHA
 * SOFTWARE RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
 * STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND AIROHA'S ENTIRE AND
 * CUMULATIVE LIABILITY WITH RESPECT TO AIROHA SOFTWARE RELEASED HEREUNDER WILL BE,
 * AT AIROHA'S OPTION, TO REVISE OR REPLACE AIROHA SOFTWARE AT ISSUE,
 * OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY RECEIVER TO
 * AIROHA FOR SUCH AIROHA SOFTWARE AT ISSUE.
 */
#ifndef  _ARGB_MIDDLE_CONTROL_H_
#define  _ARGB_MIDDLE_CONTROL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "bsp_argb.h"
#include "argb_control_style_cfg.h"


/**
* @brief This struct for record users operate history
*/

typedef struct {
    uint8_t     *cfg;
    uint8_t     interval;   /**< Led style number for flash / real time*/
    uint16_t    index;       /**< Led style number for flash / normal*/
} argb_pattern_data_t;

typedef void (*argb_middle_callback_t)(void *user_data);

typedef struct {
    argb_middle_callback_t call_back;
    void              *user_data;
} argb_middle_info_t;

typedef struct {
    uint8_t  argb_count;
    uint8_t  argb_size;
    uint8_t  argb_size_remain;
    uint8_t  argb_interval;
    uint8_t  *argb_data;
} argb_nvkey_t;

typedef enum {
    ARGB_MIDDLE_IDLE = 0,
    ARGB_MIDDLE_RUNNING = 1,
} rgb_middle_running_status_t;
/**
 * @brief This enum for define status
 */
typedef enum {
    ARGB_MIDDLE_STATUS_ERROR = -1,
    ARGB_MIDDLE_STATUS_OK = 0,
} argb_middle_status_t;

argb_middle_status_t    argb_middle_control_enable(uint8_t effect_type, uint8_t level, uint8_t repeat, uint8_t  *data_index, bool nvkey_option);
argb_middle_status_t    argb_middle_control_realtime_enable(uint8_t interval, argb_style_config_t *cfg);
argb_middle_status_t    argb_middle_control_disable(argb_run_type_t type, uint8_t  pattern, bool force_option);
argb_middle_status_t    argb_middle_register_callback(argb_middle_callback_t callback, void  *user_data);
argb_middle_status_t    argb_middle_control_enable_for_node(argb_pattern_data_t data_config, uint8_t pattern, argb_run_type_t run_type);


#ifdef __cplusplus
}
#endif
#endif /*END _ARGB_MIDDLE_CONTROL_H_*/