/* Copyright Statement:
 *
 * (C) 2026  Airoha Technology Corp. All rights reserved.
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
/**
 * File: memory_map.h
 *
 * Description: This file defines the struct or macro of system memory map.
 *
 */

#ifndef __MEMORY_MAP_H__
#define __MEMORY_MAP_H__

#include "partition.h"


extern uint32_t partition_get_length(partition_t id);
extern uint32_t partition_get_begin_address(partition_t id);

#define SEC_HEADER1_BASE               partition_get_begin_address(PARTITION_SECURITY_HEADER_0)
#define SEC_HEADER1_LENGTH             partition_get_length(PARTITION_SECURITY_HEADER_0)

#define SEC_HEADER2_BASE               partition_get_begin_address(PARTITION_SECURITY_HEADER_1)
#define SEC_HEADER2_LENGTH             partition_get_length(PARTITION_SECURITY_HEADER_1)

#define BL_BASE                        partition_get_begin_address(PARTITION_BL)
#define BL_LENGTH                      partition_get_length(PARTITION_BL)

#define CM4_BASE                       partition_get_begin_address(PARTITION_MCU)
#define CM4_LENGTH                     partition_get_length(PARTITION_MCU)

#define DSP0_BASE                      partition_get_begin_address(PARTITION_DSP0)
#define DSP0_LENGTH                    partition_get_length(PARTITION_DSP0)

#define FOTA_RESERVED_BASE             partition_get_begin_address(PARTITION_FOTA)
#define FOTA_RESERVED_LENGTH           partition_get_length(PARTITION_FOTA)

#define ROM_BASE 0x08000000
#define RAM_BASE 0x04000000
#define RAM_LENGTH 0x60000

#endif  /* __MEMORY_MAP_H__ */

