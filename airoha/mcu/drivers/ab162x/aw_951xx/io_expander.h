/* Copyright Statement:
 *
 * (C) 2025  Airoha Technology Corp. All rights reserved.
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

 #ifndef __IO_EXPANDER_SENSOR_H__
 #define __IO_EXPANDER_SENSOR_H__


#include <zephyr/drivers/sensor.h>
#include "aw95124_io_expander.h"

#ifdef __cplusplus
extern "C" {
#endif

enum io_expander_sensor_attribute {

	IO_EXPANDER_ATTR_INIT = SENSOR_ATTR_PRIV_START,

   IO_EXPANDER_ATTR_PIN_CONFIG,

   IO_EXPANDER_ATTR_PIN_IRQ_TYPE_CONFIG,

   IO_EXPANDER_ATTR_PIN_IRQ_ENABLE,

   IO_EXPANDER_ATTR_ALL_INPUT,

   IO_EXPANDER_ATTR_PIN_PULL_SET,

   IO_EXPANDER_ATTR_PIN_DIR_INPUT,

   IO_EXPANDER_ATTR_PIN_DIR_OUTPUT,

   IO_EXPANDER_ATTR_PIN_VALUE_SET,

   IO_EXPANDER_ATTR_ALL_INTS,

   IO_EXPANDER_ATTR_ENTER_LOW_POWER,

   IO_EXPANDER_ATTR_EXIT_LOW_POWER,

   IO_EXPANDER_ATTR_DEINIT,
};

enum io_expander_sensor_channel {

   /** get data from RAM.   **/
   IO_EXPANDER_CHAN_RAM_DATA = SENSOR_CHAN_PRIV_START,

   /** get data from sensor.   **/
   IO_EXPANDER_CHAN_DEVICE_DATA ,
};

typedef struct io_expander_pin_config 
{
   uint32_t pin_dir:4;
   uint32_t pin_driver:4;
   uint32_t pin_pull:4;
   uint32_t pin_irq_en:4;
   uint32_t pin_irq_type:4;
   uint32_t reserved:12;
}io_expander_pin_config_t;

#ifdef __cplusplus
}
#endif
#endif /* __IO_EXPANDER_SENSOR_H__ */
