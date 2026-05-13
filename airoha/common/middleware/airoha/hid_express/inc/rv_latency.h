/* Copyright Statement:
 *
 * (C) 2024  Airoha Technology Corp. All rights reserved.
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
 

#ifndef _RV_LATENCY_H_
#define _RV_LATENCY_H_

#include "stdio.h"
#include "stdint.h"

#if defined(AIR_LATENCY_REPORT)
#define RV_LATENCY__CHECK_POINT_FIRST(ref_time)                     rv_latency__set_ref_time(ref_time)
#define RV_LATENCY__CHECK_POINT_SECOND()                            rv_latency__read_key_timestamp()
#define RV_LATENCY__CHECK_POINT_THIRD(submit_time, report_go)       rv_latency__submit_to_HWMAC_timestamp(submit_time, report_go)
#define RV_LATENCY__UPDATE(report_go)                               rv_latency__update(report_go)
#define RV_LATENCY__CHECK_AND_PRINT_REPORT()                        rv_latency__check_and_print_report()
#else
#define RV_LATENCY__CHECK_POINT_FIRST(ref_time)
#define RV_LATENCY__CHECK_POINT_SECOND()
#define RV_LATENCY__CHECK_POINT_THIRD(submit_time, report_go)
#define RV_LATENCY__UPDATE(report_go)
#define RV_LATENCY__CHECK_AND_PRINT_REPORT()
#endif

#if defined(AIR_LATENCY_REPORT)
void rv_latency__set_ref_time(uint32_t ref_time);
void rv_latency__read_key_timestamp();
void rv_latency__submit_to_HWMAC_timestamp(uint32_t submit_time, uint32_t report_go);
void rv_latency__update();
void rv_latency__check_and_print_report();
#endif

#endif /* _RV_LATENCY_H_ */
