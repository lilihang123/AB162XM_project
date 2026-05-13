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
 * THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("AIROHA SOFTWARE")
 * RECEIVED FROM AIROHA AND/OR ITS REPRESENTATIVES ARE PROVIDED
 * TO RECEIVER ON AN "AS-IS" BASIS ONLY. AIROHA EXPRESSLY DISCLAIMS ANY AND ALL
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

#ifndef __HAL_DVFS_H__
#define __HAL_DVFS_H__

#include "hal_platform.h"

#ifdef HAL_DVFS_MODULE_ENABLED

/**
 * @addtogroup HAL
 * @{
 * @addtogroup DVFS
 * @{
 * This section introduces the DVFS driver APIs including terms and acronyms,
 * supported features, details on how to use this driver, DVFS function groups, enums, structures and functions.
 *
 * @section HAL_DVFS_Terms_Chapter Terms and acronyms
 *
 * The following provides descriptions of the terms commonly used in the DVFS driver and how to use its various functions.
 *
 * |Terms               |Details                                                                 |
 * |--------------------|------------------------------------------------------------------------|
 * |\b DVFS             | Dynamic Voltage and Frequency Scaling. |
 * |\b OPP              | Operating Performance Point, a tuple of frequency and voltage.|
 *
 * @section HAL_DVFS_Driver_Usage_Chapter How to use the driver
 * - The DVFS framework controls switch of voltage dependent frequencies such as CPU, DSP.
 * - DVFS OPP level reference count mechanism is implemented. DVFS framework maintains the system operating at the highest OPP level with a non-zero reference count.
 * - By default the system operates at the lowest DVFS OPP.
 * - User should request a certain DVFS OPP LOCK/UNLOCK before and after usage. (API should be used in pairs)
 *   - Step1: Call #hal_dvfs_init() to initialize the DVFS module. (will be called once during system initialization).
 *   - Step2: Request DVFS OPP lock, call #hal_dvfs_lock_control()
 *     - parameter 1: requested DVFS OPP #dvfs_frequency_t
 *     - parameter 2: HAL_DVFS_LOCK #hal_dvfs_lock_parameter_t
 *       - Reference count of the requested DVFS OPP will be incremented.
 *       - DVFS switch will occur if the requested level is higher than the current operating one.
 *   - Step3: Perform your task operation/calculation
 *       - DVFS API will make sure the system will be operating at a DVFS OPP equal/higher than the requested level
 *   - Step4: DVFS OPP unlock, call #hal_dvfs_lock_control()
 *     - parameter 1: originally requested DVFS OPP #dvfs_frequency_t
 *     - parameter 2: HAL_DVFS_UNLOCK #hal_dvfs_lock_parameter_t
 *       - Reference count of the specified DVFS OPP will be decremented.
 *       - DVFS switch will occur if the OPP level with non-zero reference count has changed.
 *   - Sample code:
 *   @code
 *
 *       dvfs_frequency_t requested_dvfs_opp = DVFS_OPP_xxxx;         // specify needed DVFS OPP
 *
 *       hal_dvfs_lock_control(requested_dvfs_opp, HAL_DVFS_LOCK);    //  request DVFS OPP lock
 *       // perform task operation
 *       hal_dvfs_lock_control(requested_dvfs_opp, HAL_DVFS_UNLOCK);  // release DVFS OPP lock (unlock)
 *   @endcode
 *
 */

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
* Enum
*****************************************************************************/
/** @defgroup hal_dvfs_enum Enum
  * @{
  */
/** @brief This enum defines return status of certain DVFS HAL APIs. User should check return value after calling these APIs. */
typedef enum {
    HAL_DVFS_STATUS_NOT_PERMITTED  = -5,      /**< The operation is not permitted. */
    HAL_DVFS_STATUS_BUSY           = -4,      /**< Device or resource is busy. */
    HAL_DVFS_STATUS_UNINITIALIZED  = -3,      /**< Non-initialized. */
    HAL_DVFS_STATUS_INVALID_PARAM  = -2,      /**< Invalid parameter value. */
    HAL_DVFS_STATUS_ERROR          = -1,      /**< The DVFS function detected a common error. */
    HAL_DVFS_STATUS_OK             =  0       /**< The DVFS function executed successfully. */
} hal_dvfs_status_t;

/** @brief This enum defines the relationship between dvfs locked level and scaling operation . */
typedef enum {
    HAL_DVFS_UNLOCK,   /**< dvfs scaling to below level is not allowed */
    HAL_DVFS_LOCK      /**< dvfs scaling to below level is allowed. */
} hal_dvfs_lock_parameter_t;
/**
  * @}
  */

/*****************************************************************************
* extern global function
*****************************************************************************/
/**
 * @brief       The function initializes the DVFS framework.
 * @return      #HAL_DVFS_STATUS_OK, if the initialization completed successfully.\n
 *              #HAL_DVFS_STATUS_ERROR, if an error occurred during the initialization.\n
 */
hal_dvfs_status_t hal_dvfs_init(void);

/**
 * @brief       This function gets the current CPU frequency.
 * @return      The current CPU frequency is in kHz.
 */
uint32_t hal_dvfs_get_cpu_frequency(void);

/**
 * @brief       This function lock dvfs level on dvfs level which indicated by first parameter  ,
                as hal_dvfs_target_cpu_frequency function called for a lower level scaling is not allowed

 * @param[out]   level            is a value to descript dvfs level.
 * @param[out]   lock_status      is a value to descript dvfs lock status.\n
 *              #HAL_DVFS_LOCK, dvfs scaling to below level is not allowed..\n
 *              #HAL_DVFS_UNLOCK, dvfs scaling to below level is allowed.\n
 * @return      #HAL_DVFS_STATUS_OK, if the operation completed successfully.\n
 *              #HAL_DVFS_STATUS_ERROR, if an error occurred during the operation..\n
 */
hal_dvfs_status_t hal_dvfs_lock_control(dvfs_frequency_t level, hal_dvfs_lock_parameter_t lock_status);

#ifdef __cplusplus
}
#endif

/**
* @}
* @}
*/


#endif /* HAL_DVFS_MODULE_ENABLED */

#endif /* __HAL_DVFS_H__ */
