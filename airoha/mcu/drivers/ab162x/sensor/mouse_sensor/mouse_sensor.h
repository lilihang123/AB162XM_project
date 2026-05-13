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

#ifndef  __MOUSE_SENSOR_PIXART_H__
#define  __MOUSE_SENSOR_PIXART_H__

#include <zephyr/drivers/sensor.h>

#ifdef __cplusplus
extern "C" {
#endif
enum mouse_sensor_attribute {
	/** Sensor XY direction.
    Swap_XY   = 0,                                     < Swap XY directions.
    INV_Y  = 1,                                        < Invert Y direction.
    INV_X = 2                                          < Invert X direction. */

	MOUSE_SENSOR_ATTR_XY_DIRECTION = SENSOR_ATTR_PRIV_START,

	/** Sensor CPI for both X and Y axes.
    Cpi  50~26000               */
	MOUSE_SENSOR_ATTR_CPI,

	/** Sensor CPI for ONLY X.
    Cpi  50~26000               */
	MOUSE_SENSOR_ATTR_CPI_X,

	/** Sensor CPI for ONLY Y.
    Cpi  50~26000               */
	MOUSE_SENSOR_ATTR_CPI_Y,

	/** Sensor LOD.
    value 1                lift_cut_off_1mm   (default)
    value 2                lift_cut_off_2mm
                           other vaule is invalid  */
	MOUSE_SENSOR_ATTR_LOD,

	/** Sensor mode set.
    value 0                high_performance_mode  (default)
    value 1                low_power_mode
    value 2                office_mode
    value 3                corded_gaming_mode
                           other vaule is invalid  */
	MOUSE_SENSOR_ATTR_MODE_SET,

	/** Sensor rest mode set.
    value 0                disable rest mode
    value 1                enable rest mode
                           other vaule is invalid  */
	MOUSE_SENSOR_ATTR_REST_MODE,

    /** Sensor keep high fps set.
     value 0                disable keep high fps
     value 1                enable keep high fps
                             other vaule is invalid  */
    MOUSE_SENSOR_ATTR_KEEP_HIGH_FPS,
	/** Sensor motion sync set.
    value 0                disable motion sync
    value 1                enable motion sync
                           other vaule is invalid  */
    MOUSE_SENSOR_ATTR_MOTION_SYNC,

    /** Sensor ripple control set.
    value 0                disable ripple control
    value 1                enable ripple control
                           other vaule is invalid  */
    MOUSE_SENSOR_ATTR_RIPPLE_CONTROL ,

    /** Sensor angle snap set.
    value 0                disable angle snap
    value 1                enable angle snap
                           other vaule is invalid  */
    MOUSE_SENSOR_ATTR_ANGLE_SNAP ,

   /** Sensor init set.**/

    MOUSE_SENSOR_ATTR_INIT ,

   /** Sensor init set.**/

    MOUSE_SENSOR_ATTR_DEINIT ,

   /** Sensor BT trigger set.**/

    MOUSE_SENSOR_ATTR_BT_TRIGGER ,

	/** Sensor Run Downshift Register set.**/

    MOUSE_SENSOR_ATTR_RUN_DOWNSHIFT_REG,

    /** Sensor REST1 Downshift Register set.**/
    MOUSE_SENSOR_ATTR_REST1_DOWNSHIFT_REG,

    /** Sensor REST2 Downshift Register set.**/
    MOUSE_SENSOR_ATTR_REST2_DOWNSHIFT_REG,

    /** Sensor REST1 Period time set,value unit:ms**/
    MOUSE_SENSOR_ATTR_REST1_PERIOD_TIME,

    /** Sensor REST2 Period time set,value unit:ms**/
    MOUSE_SENSOR_ATTR_REST2_PERIOD_TIME,

    /** Sensor REST3 Period time set,value unit:ms**/
    MOUSE_SENSOR_ATTR_REST3_PERIOD_TIME,

    /** Sensor Run DownShift Multiplier Register set.**/
    MOUSE_SENSOR_ATTR_RUN_DOWNSHIFT_MULT_REG,

    /** Sensor REST1 DownShift Multiplier Register set.**/
    MOUSE_SENSOR_ATTR_REST1_DOWNSHIFT_MULT_REG,

    /** Sensor REST2 DownShift Multiplier Register set.**/
    MOUSE_SENSOR_ATTR_REST2_DOWNSHIFT_MULT_REG,

    /** Sensor RUN DownShift Time set,value unit:ms**/
    MOUSE_SENSOR_ATTR_RUN_DOWNSHIFT_TIME,

    /** Sensor REST1 DownShift Time set,value unit:ms**/
    MOUSE_SENSOR_ATTR_REST1_DOWNSHIFT_TIME,

    /** Sensor REST2 DownShift Time set,value unit:ms**/
    MOUSE_SENSOR_ATTR_REST2_DOWNSHIFT_TIME,

    /** Sensor clear data
    value                 clear data count**/
    MOUSE_SENSOR_ATTR_CLEAR_DATA,

   /** Sensor SPI status get .
   value 0                busy
   value 1                idle  **/
    MOUSE_SENSOR_ATTR_SPI_STATUS ,

   /** Sensor SPI NVIC IRQ .**/
    MOUSE_SENSOR_ATTR_SPI_NVIC_IRQ ,
    
    MOUSE_SENSOR_ATTR_REINIT,
};

enum mouse_sensor_channel {

   /** get data from RAM.   **/
   MOUSE_SENSOR_CHAN_RAM_DATA = SENSOR_CHAN_PRIV_START,

   /** get data from sensor.   **/
   MOUSE_SENSOR_CHAN_SENSOR_DATA ,
};


typedef enum {
   Run_DownShift   =0,
   Rest1_DownShift ,
   Rest2_DownShift ,
   Rest1_Period,
   Rest2_Period,
   Rest3_Period,
   Run_DownShift_Mult,
   Rest1_DownShift_Mult,
   Rest2_DownShift_Mult,
   frame_rate_MAX
} mouse_rest_reg;

typedef enum {
   Run_DownShift_time  =0,
   Rest1_DownShift_time,
   Rest2_DownShift_time,
} mouse_rest_time;

typedef enum {
   Rest1_Period_time  =0,
   Rest2_Period_time,
   Rest3_Period_time,
} mouse_period_time;

typedef enum {
   Motion_sync   =0,
   Ripple_control ,
   Angle_Snap ,
} mouse_function;

typedef enum {
   Swap_XY   = 0,                                     /**< Swap XY directions. */
   INV_Y  = 1,                                        /**< Invert Y direction. */
   INV_X = 2,                                         /**< Invert X direction. */
   INV_XY = 3,                                         /**< Invert XY directions. */
   INV_X_AND_Swap_XY = 4,                              /**< Invert X direction and swap XY directions. */
   INV_Y_AND_Swap_XY = 5,                              /**< Invert Y direction and swap XY directions. */
   INV_XY_AND_Swap_XY = 6,                             /**< Invert XY directions and swap XY directions. */
   NOT_INV_AND_NOT_SWAP = 7,                          /**< Not invert and not swap. */
   NO_DIRECTION_ADJUSTMENT = 8                       /**< No direction adjustment. */
} mouse_degree;

typedef enum {
   lift_cut_off_1mm   = 0,                                            /**< Switch lift_cut_off_1mm. */
   lift_cut_off_2mm   = 1,                                            /**< Switch lift_cut_off_2mm. */
   lift_cut_off_0_7mm   = 2                                           /**< Switch lift_cut_off 0.7mm. */
} lift_cut_off;


typedef enum {
   cpi_both_setting   = 0,                                          /**< set x and y cpi setting. */
   cpi_x_setting      = 1,                                          /**< set x cpi setting. */
   cpi_y_setting      = 2                                           /**< set y cpi setting. */
} cpi_setting;


typedef enum {
   high_performance_mode  = 0,                                      /**< MOUSE mode_setting high_performance_mode */
   low_power_mode         = 1,                                      /**< MOUSE mode_setting low_power_mode  */
   office_mode            = 2,                                      /**< MOUSE mode_setting office_mode */
   corded_gaming_mode     = 3                                       /**< MOUSE mode_setting corded_gaming_mode */
} mouse_mode;

#ifdef __cplusplus
}
#endif

#endif 