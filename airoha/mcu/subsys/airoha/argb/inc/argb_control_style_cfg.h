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

#ifndef  _ARGB_CONTROL_STYLE_CFG_H_
#define  _ARGB_CONTROL_STYLE_CFG_H_

#ifdef __cplusplus
extern "C" {
#endif
/**
 * File: rgb_control_style_cfg.h
 * Description: This file is to read rgb configure infomation from NVDM.
 * Note: None
 */
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hal_platform.h"
#include "hal.h"


/**
 * @brief This enum for define argb data config
 */
#pragma  pack(1)
typedef struct {
    uint8_t      argb_num;      /**< argb number */
    uint8_t      repeat;        /**< argb repeat */
    uint8_t      mode;          /**< argb mode */
    uint8_t      onoff;         /**< argb on off(1:on,0:off) */
    uint8_t      *argb_data;    /**< argb data */
} argb_style_t;
#pragma  pack()


typedef enum {
    argb_occupy_none = 0,       /**< The argb is not running */
    argb_occupy_normal,         /**< The argb is breath / flash*/
    argb_occupy_realtime,       /**<  The argb is realtime */
} argb_run_type_t;

/**
 * @brief This struct for rgb style config setting which stored in NVDM.
 */
typedef struct {
    uint8_t      type;          /**< argb number */
    uint8_t      argb_num;      /**< argb number */
    uint8_t      pattern;       /**< argb pattern */
    uint8_t      repeat;        /**< argb repeat */
    uint8_t      *argb_data;    /**< argb data */
} argb_style_config_t;



/**
 * @brief This function get rgb style configure infomation.
 * @param[in] type is the type that RGB want to read.
 * @param[in] pattern is the pattern type that RGB want to read.
 * @param[in] style_no is the style number that rgb want to read.
 * @return #Not NULL  means success.
 *         #NULL  means fail.
 */
argb_style_config_t    *argb_style_config_read(uint8_t type, uint8_t pattern, uint8_t  repeat);


#ifdef __cplusplus
}
#endif
#endif /*END _ARGB_CONTROL_STYLE_CFG_H_*/