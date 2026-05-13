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
/*
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef  __QDEC_AIROHA_H__
#define  __QDEC_AIROHA_H__

#include <zephyr/drivers/sensor.h>

#ifdef __cplusplus
extern "C" {
#endif




enum qdec_attribute {

   /** Sensor qdec status:active/idle              */
   /** Sensor val->val1 =  qdec mode status->0x0:active mode,0x1:idle mode             */
	QDEC_MODE_STATUS= SENSOR_ATTR_PRIV_START,

	/** Sensor qdec sample period  0~511               */
   /** Sensor qdec led on period  0~16               */
   /** Sensor qdec debounce count  0~64               */
   /** Sensor val->val1 =  sample period              */
   /** Sensor val->val2 =  (led on period <<8) + debounce count      */
	QDEC_A_GROUP_CFG,

	/** Sensor qdec sample period  0~511               */
   /** Sensor qdec led on period  0~16               */
   /** Sensor qdec debounce count  0~64               */
   /** Sensor val->val1 =  sample period              */
   /** Sensor val->val2 =  (led on period <<8) + debounce count      */
	QDEC_B_GROUP_CFG,

   /** Sensor qdec data ready irq status:enable/disable              */
   /** Sensor val->val1 =  qdec mode status->0x0:disable, 0x1:enable             */
	QDEC_DATA_READY_IRQ,

   /** Sensor val->val1 = Z SUM IRQ : 0x0:disable, 0x1:enable                          */
   /** Sensor val->val2 =  z sum thr    */
	QDEC_Z_SUM_IRQ_CFG,

   /** Sensor val->val1 = hw sel : 0x0:disable, 0x1:enable                          */
   /** Sensor val->val2 =  hw sel group : 0x0 : group A, 0x1 : group B*/
	QDEC_HW_SEL_CFG,

   /** Sensor val->val1 = hw latch status : 0x0:on going, 0x1:finish                          */
   QDEC_HW_LATCH_STATUS,
};








#ifdef __cplusplus
}
#endif

#endif 