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

#ifndef __HAL_SLEEP_MANAGER_H__
#define __HAL_SLEEP_MANAGER_H__
#include "air_chip.h"
#include "hal_platform.h"
#include <zephyr/pm/state.h>

#ifdef HAL_SLEEP_MANAGER_ENABLED
#if defined(AIR_BTD_IC_MANDATORY_G1)
#include "hal_sleep_manager_platform.h"
#endif
#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
* Enum
*****************************************************************************/
/**
 * @defgroup hal_sleep_manager_enum Enum
 * @{
 */

/** @brief This enum defines the Sleep Manager API return status*/
typedef enum {
    HAL_SLEEP_MANAGER_ERROR                           = -1,    /**< An undefined error occurred. */
    HAL_SLEEP_MANAGER_OK                              = 0,     /**< The operation completed successfully. */
} hal_sleep_manager_status_t;

#if defined(AIR_BTD_IC_MANDATORY_G1)
/** @brief This enum defines the Sleep Manager lock sleep mode*/
typedef enum {
    SLEEP_PURE_WFI_MODE = 0, /**< prue wfi. >*/
    SLEEP_TICKLESS_MODE = 1, /**< wfi tickless mode. >*/
    SLEEP_SUSPEND_MODE  = 2, /**< suspend mode. >*/
    SLEEP_ONE_MODE      = 3, /**< sleep-1 mode. >*/
    SLEEP_TWO_MODE      = 4, /**< sleep-2 mode. >*/
    SLEEP_MODE_MAX
}sleep_management_mode_t;
#endif

/*****************************************************************************
 * Functions
 *****************************************************************************/

/**
 * @brief       This function initializes the Sleep Manager.
 * @return      #HAL_SLEEP_MANAGER_OK, if this function completed successfully. */
hal_sleep_manager_status_t hal_sleep_manager_init(void);

#ifdef HAL_SLEEP_MANAGER_SUPPORT_WAKEUP_SOURCE_CONFIG
/**
 * @brief       This function enables a specific Wakeup Source.
 * @param[in]   pin is the specified Wakeup Source defined in #hal_sleep_manager_wakeup_source_t.
 * @return      #HAL_SLEEP_MANAGER_OK, if this function completed successfully.
 */
hal_sleep_manager_status_t hal_sleep_manager_enable_wakeup_pin(hal_sleep_manager_wakeup_source_t pin);

/**
 * @brief       This function disables the specific Wakeup Source.
 * @param[in]   pin is the specific Wakeup Source to be disabled.
 * @return      #HAL_SLEEP_MANAGER_OK, if this function completed successfully.
 */
hal_sleep_manager_status_t hal_sleep_manager_disable_wakeup_pin(hal_sleep_manager_wakeup_source_t pin);
#endif

/**
 * @brief       Set sleep(suspend) time length. If no other wake up event occurs, the system will sleep for a specific time.
 * @param[in]   sleep_time_ms is time duration in milliseconds.
 * @return      return HAL_SLEEP_MANAGER_OK, if supported.
 * @note        This api only use in non os environment
 */
hal_sleep_manager_status_t hal_sleep_manager_set_sleep_time(uint32_t sleep_time_ms);

/**
 * @brief       This function checks if there are any Sleep Locks in the system. Apply it before entering the sleep mode.
 * @return      True if any locks are on hold.
 */
bool hal_sleep_manager_is_sleep_locked(void);

/**
 * @brief       This function checks whether the sleep handle is still alive. If it is alive, it means that the system still can be controled by this sleep handle.
 * @param[in]   handle_index is the sleep handle index returned from #hal_sleep_manager_set_sleep_handle().
 * @return      True, if the the sleep handle is alive. False, if the sleep handle is invalid.
 */
bool hal_sleep_manager_is_sleep_handle_alive(uint8_t handle_index);

/**
 * @brief       The sleep lock status is represented by an unsigned integer (uint32_t). Each sleep handle corresponds to a bit position in this unsigned integer. If the sleep handle index is 5, for example, the value at the 5th bit position of this unsigned integer represents the status of the sleep handle of index 5. If the value of the 5th bit is 1, it indicates that the sleep handle with index 5 is currently holding the sleep lock.
 * @return      If handle_index's corresponding bit is 1, indicates this handle_index is holding a Sleep Lock.
 * @note        Call #hal_sleep_manager_set_sleep_handle() to set up the sleep handle, before calling this function.
 */
#if defined(AIR_BTD_IC_MANDATORY_G1)
uint32_t hal_sleep_manager_get_sleep_lock_status(void);
#else
uint32_t hal_sleep_manager_get_lock_status(void);
#endif /*AIR_BTD_IC_MANDATORY_G1*/
/**
 * @brief       This function releases the sleep handle if it is no longer in use. \n
 * @param[in]   handle_index is the sleep handle index returned from #hal_sleep_manager_set_sleep_handle(). \n
 * @return      #HAL_SLEEP_MANAGER_OK, if this function completed successfully.
 * @note        Call #hal_sleep_manager_set_sleep_handle() to set up the sleep handle, before calling this function.
 */
hal_sleep_manager_status_t hal_sleep_manager_release_sleep_handle(uint8_t handle_index);

/**
 * @brief       This function prevents the MCU from getting into sleep mode.
 * @param[in]   handle_index is the sleep handle index, returned from #hal_sleep_manager_set_sleep_handle().
 * @return      #HAL_SLEEP_MANAGER_OK, Sleep Lock is locked.
 * @note        Call #hal_sleep_manager_set_sleep_handle() to set up the sleep handle, before calling this function.
 */
hal_sleep_manager_status_t hal_sleep_manager_lock_sleep(uint8_t handle_index);
//
/**
 * @brief       This function unlocks the specific Sleep Lock and permits the MCU going into sleep mode when needed if all Sleep Locks are unlocked.
 * @param[in]   handle_index is the sleep handle index returned from #hal_sleep_manager_set_sleep_handle().
 * @return      #HAL_SLEEP_MANAGER_OK, sleep lock is unlocked.
 * @note        Call #hal_sleep_manager_set_sleep_handle() to set up the sleep handle, before calling this function.
 */
hal_sleep_manager_status_t hal_sleep_manager_unlock_sleep(uint8_t handle_index);

/**
 * @brief       This function sets up a sleep handle to control the sleep state of the system. \n
 *              This handle enables the Sleep Manager to identify the sleep states based on the sleep handles assigned.
 * @param[in]   handle_name is the name of the sleep handle of type string.
 * @return      The sleep handle index, if the operation is successful. If (0xFF) is returned, the operation failed.
 */
uint8_t hal_sleep_manager_set_sleep_handle(const char *handle_name);

/**
 * @brief       The idle lock status is represented by an unsigned integer (uint32_t). Each idle handle corresponds to a bit position in this unsigned integer. If the idle handle index is 5, for example, the value at the 5th bit position of this unsigned integer represents the status of the idle handle of index 5. If the value of the 5th bit is 1, it indicates that the idle handle with index 5 is currently holding the idle lock.
 * @return      If handle_index's corresponding bit is 1, indicates this handle_index is holding a Idle Lock.
 * @note        Call #hal_sleep_manager_set_idle_handle() to set up the idle handle, before calling this function.
 */
uint32_t hal_sleep_manager_get_idle_lock_status(void);

/**
 * @brief       This function checks if there are any Idle Locks in the system. Apply it before entering the idle mode.
 * @return      True if any locks are on hold.
 */
bool hal_sleep_manager_is_idle_locked(void);

/**
 * @brief       This function releases the idle handle if it is no longer in use. \n
 * @param[in]   handle_index is the idle handle index returned from #hal_sleep_manager_set_idle_handle(). \n
 * @return      #HAL_SLEEP_MANAGER_OK, if this function completed successfully.
 * @note        Call #hal_sleep_manager_set_idle_handle() to set up the idle handle, before calling this function.
 */
hal_sleep_manager_status_t hal_sleep_manager_release_idle_handle(uint8_t handle_index);

/**
 * @brief       This function prevents the MCU from getting into idle mode.
 * @param[in]   handle_index is the idle handle index, returned from #hal_sleep_manager_set_idle_handle().
 * @return      #HAL_SLEEP_MANAGER_OK, Idle Lock is locked.
 * @note        Call #hal_sleep_manager_set_idle_handle() to set up the idle handle, before calling this function.
 */
hal_sleep_manager_status_t hal_sleep_manager_lock_idle(uint8_t handle_index);
//
/**
 * @brief       This function unlocks the specific Idle Lock and permits the MCU going into idle mode when needed if all Idle Locks are unlocked.
 * @param[in]   handle_index is the idle handle index returned from #hal_sleep_manager_set_idle_handle().
 * @return      #HAL_SLEEP_MANAGER_OK, idle lock is unlocked.
 * @note        Call #hal_sleep_manager_set_idle_handle() to set up the idle handle, before calling this function.
 */
hal_sleep_manager_status_t hal_sleep_manager_unlock_idle(uint8_t handle_index);

/**
 * @brief       This function sets up a idle handle to control the idle state of the system. \n
 *              This handle enables the Sleep Manager to identify the idle states based on the idle handles assigned.
 * @param[in]   handle_name is the name of the idle handle of type string.
 * @return      The idle handle index, if the operation is successful. If (0xFF) is returned, the operation failed.
 */
uint8_t hal_sleep_manager_set_idle_handle(const char *handle_name);

#if defined(AIR_BTD_IC_MANDATORY_G1)
/**
 * @brief       The sleep suspend lock status is represented by an unsigned integer (uint32_t). Each suspend sleep handle corresponds to a bit position in this unsigned integer. If the suspend sleep handle index is 5, for example, the value at the 5th bit position of this unsigned integer represents the status of the extend sleep handle of index 5. If the value of the 5th bit is 1, it indicates that the extend sleep handle with index 5 is currently holding the extend sleep lock.
 * @return      If handle_index's corresponding bit is 1, indicates this handle_index is holding a  Sleep Lock.
 * @note        Call #hal_sleep_manager_set_extslp_handle() to set up the suspend sleep handle, before calling this function.
 */
uint32_t hal_sleep_manager_get_slp_suspend_lock_status(void);

/**
 * @brief       This function checks if there are any suspend Sleep Locks in the system. Apply it before entering the suspend sleep mode.
 * @return      True if any locks are on hold.
 */
bool hal_sleep_manager_is_slp_suspend_locked(void);

/**
 * @brief       This function releases the suspend sleep handle if it is no longer in use. \n
 * @param[in]   handle_index is the suspend sleep handle index returned from #hal_sleep_manager_set_extslp_handle(). \n
 * @return      #HAL_SLEEP_MANAGER_OK, if this function completed successfully.
 * @note        Call #hal_sleep_manager_set_slp_suspend_handle() to set up the suspend sleep handle, before calling this function.
 */
hal_sleep_manager_status_t hal_sleep_manager_release_slp_suspend_handle(uint8_t handle_index);

/**
 * @brief       This function prevents the MCU from getting into suspend sleep mode.
 * @param[in]   handle_index is the suspend sleep handle index, returned from #hal_sleep_manager_set_extslp_handle().
 * @return      #HAL_SLEEP_MANAGER_OK, suspend Sleep Lock is locked.
 * @note        Call #hal_sleep_manager_set_slp_suspend_handle() to set up the suspend sleep handle, before calling this function.
 */
hal_sleep_manager_status_t hal_sleep_manager_lock_slp_suspend(uint8_t handle_index);
//
/**
 * @brief       This function unlocks the specific suspend Sleep Lock and permits the MCU going into suspend sleep mode when needed if all suspend Sleep Locks are unlocked.
 * @param[in]   handle_index is the suspend sleep handle index returned from #hal_sleep_manager_set_extslp_handle().
 * @return      #HAL_SLEEP_MANAGER_OK, suspend sleep lock is unlocked.
 * @note        Call #hal_sleep_manager_set_slp_suspend_handle() to set up the suspend sleep handle, before calling this function.
 */
hal_sleep_manager_status_t hal_sleep_manager_unlock_slp_suspend(uint8_t handle_index);

/**
 * @brief       This function sets up a suspend sleep handle to control the suspend sleep state of the system. \n
 *              This handle enables the Sleep Manager to identify the suspend sleep states based on the suspend sleep handles assigned.
 * @param[in]   handle_name is the name of the suspend sleep handle of type string.
 * @return      The suspend sleep handle index, if the operation is successful. If (0xFF) is returned, the operation failed.
 */
uint8_t hal_sleep_manager_set_slp_suspend_handle(const char *handle_name);

/**
 * @brief       The suspend sleep lock status is represented by an unsigned integer (uint32_t). Each suspend sleep handle corresponds to a bit position in this unsigned integer. If the suspend sleep handle index is 5, for example, the value at the 5th bit position of this unsigned integer represents the status of the suspend sleep handle of index 5. If the value of the 5th bit is 1, it indicates that the suspend sleep handle with index 5 is currently holding the suspend sleep lock.
 * @return      If handle_index's corresponding bit is 1, indicates this handle_index is holding a suspend Sleep Lock.
 * @note        Call #hal_sleep_manager_set_extslp_handle() to set up the suspend sleep handle, before calling this function.
 */
uint32_t hal_sleep_manager_get_slp_1_lock_status(void);

/**
 * @brief       This function checks if there are any Sleep one Locks in the system. Apply it before entering the Sleep one mode.
 * @return      True if any locks are on hold.
 */
bool hal_sleep_manager_is_slp_1_locked(void);

/**
 * @brief       This function releases the Sleep one handle if it is no longer in use. \n
 * @param[in]   handle_index is the Sleep one handle index returned from #hal_sleep_manager_set_extslp_handle(). \n
 * @return      #HAL_SLEEP_MANAGER_OK, if this function completed successfully.
 * @note        Call #hal_sleep_manager_set_extslp_handle() to set up the Sleep one handle, before calling this function.
 */
hal_sleep_manager_status_t hal_sleep_manager_release_slp_1_handle(uint8_t handle_index);

/**
 * @brief       This function prevents the MCU from getting into Sleep one mode.
 * @param[in]   handle_index is the Sleep one handle index, returned from #hal_sleep_manager_set_extslp_handle().
 * @return      #HAL_SLEEP_MANAGER_OK, Sleep one Lock is locked.
 * @note        Call #hal_sleep_manager_set_extslp_handle() to set up the Sleep one handle, before calling this function.
 */
hal_sleep_manager_status_t hal_sleep_manager_lock_slp_mode_1(uint8_t handle_index);
//
/**
 * @brief       This function unlocks the specific Sleep one Lock and permits the MCU going into Sleep one mode when needed if all Sleep one Locks are unlocked.
 * @param[in]   handle_index is the Sleep one handle index returned from #hal_sleep_manager_set_extslp_handle().
 * @return      #HAL_SLEEP_MANAGER_OK, Sleep one lock is unlocked.
 * @note        Call #hal_sleep_manager_set_extslp_handle() to set up the Sleep one handle, before calling this function.
 */
hal_sleep_manager_status_t hal_sleep_manager_unlock_slp_mode_1(uint8_t handle_index);

/**
 * @brief       This function sets up a Sleep one handle to control the Sleep one state of the system. \n
 *              This handle enables the Sleep Manager to identify the Sleep one states based on the Sleep one handles assigned.
 * @param[in]   handle_name is the name of the Sleep one handle of type string.
 * @return      The Sleep one handle index, if the operation is successful. If (0xFF) is returned, the operation failed.
 */
uint8_t hal_sleep_manager_set_slp_1_handle(const char *handle_name);



/**
 * @brief       The Sleep one lock status is represented by an unsigned integer (uint32_t). Each Sleep one handle corresponds to a bit position in this unsigned integer. If the Sleep one handle index is 5, for example, the value at the 5th bit position of this unsigned integer represents the status of the Sleep one handle of index 5. If the value of the 5th bit is 1, it indicates that the Sleep one handle with index 5 is currently holding the Sleep one lock.
 * @return      If handle_index's corresponding bit is 1, indicates this handle_index is holding a Sleep one Lock.
 * @note        Call #hal_sleep_manager_set_extslp_handle() to set up the Sleep one handle, before calling this function.
 */
uint32_t hal_sleep_manager_get_slp_2_lock_status(void);

/**
 * @brief       This function checks if there are any Sleep two in the system. Apply it before entering the Sleep two mode.
 * @return      True if any locks are on hold.
 */
bool hal_sleep_manager_is_slp_2_locked(void);

/**
 * @brief       This function releases the Sleep two handle if it is no longer in use. \n
 * @param[in]   handle_index is the Sleep two handle index returned from #hal_sleep_manager_set_extslp_handle(). \n
 * @return      #HAL_SLEEP_MANAGER_OK, if this function completed successfully.
 * @note        Call #hal_sleep_manager_set_extslp_handle() to set up the Sleep two handle, before calling this function.
 */
hal_sleep_manager_status_t hal_sleep_manager_release_sle_2_handle(uint8_t handle_index);

/**
 * @brief       This function prevents the MCU from getting into Sleep two mode.
 * @param[in]   handle_index is the Sleep two handle index, returned from #hal_sleep_manager_set_extslp_handle().
 * @return      #HAL_SLEEP_MANAGER_OK, Sleep two Lock is locked.
 * @note        Call #hal_sleep_manager_set_extslp_handle() to set up the Sleep two handle, before calling this function.
 */
hal_sleep_manager_status_t hal_sleep_manager_lock_slp_mode_2(uint8_t handle_index);
//
/**
 * @brief       This function unlocks the specific Sleep two Lock and permits the MCU going into Sleep two mode when needed if all Sleep two Locks are unlocked.
 * @param[in]   handle_index is the Sleep two handle index returned from #hal_sleep_manager_set_extslp_handle().
 * @return      #HAL_SLEEP_MANAGER_OK, Sleep two lock is unlocked.
 * @note        Call #hal_sleep_manager_set_extslp_handle() to set up the Sleep two handle, before calling this function.
 */
hal_sleep_manager_status_t hal_sleep_manager_unlock_slp_mode_2(uint8_t handle_index);

/**
 * @brief       This function sets up a Sleep two handle to control the Sleep two state of the system. \n
 *              This handle enables the Sleep Manager to identify the Sleep two states based on the Sleep two handles assigned.
 * @param[in]   handle_name is the name of the Sleep two handle of type string.
 * @return      The Sleep two handle index, if the operation is successful. If (0xFF) is returned, the operation failed.
 */
uint8_t hal_sleep_manager_set_slp_2_handle(const char *handle_name);
/**
 * @brief       This function used for register the suspend_callback to back up the AO domain register before entry sleep . \n
 * @param[in]   module is ao domain module. \n
 */
void hal_sleep_management_register_ao_domain_suspend_callback(sleep_management_ao_domain_backup_restore_module_t module, sleep_management_suspend_callback_t callback, void *data);
/**
 * @brief       This function used for register the suspend_callback to back up the AO domain register before entry sleep . \n
 * @param[in]   module is ao domain module. \n
 */
void hal_sleep_management_register_ao_domain_resume_callback(sleep_management_ao_domain_backup_restore_module_t module, sleep_management_resume_callback_t callback, void *data);
#else
/**
 * @brief       The extend sleep lock status is represented by an unsigned integer (uint32_t). Each extend sleep handle corresponds to a bit position in this unsigned integer. If the extend sleep handle index is 5, for example, the value at the 5th bit position of this unsigned integer represents the status of the extend sleep handle of index 5. If the value of the 5th bit is 1, it indicates that the extend sleep handle with index 5 is currently holding the extend sleep lock.
 * @return      If handle_index's corresponding bit is 1, indicates this handle_index is holding a extend sleep Lock.
 * @note        Call #hal_sleep_manager_set_extslp_handle() to set up the extend sleep handle, before calling this function.
 */
uint32_t hal_sleep_manager_get_extslp_lock_status(void);

/**
 * @brief       This function checks if there are any Extend Sleep Locks in the system. Apply it before entering the extend sleep mode.
 * @return      True if any locks are on hold.
 */
bool hal_sleep_manager_is_extslp_locked(void);

/**
 * @brief       This function releases the extend sleep handle if it is no longer in use. \n
 * @param[in]   handle_index is the extend sleep handle index returned from #hal_sleep_manager_set_extslp_handle(). \n
 * @return      #HAL_SLEEP_MANAGER_OK, if this function completed successfully.
 * @note        Call #hal_sleep_manager_set_extslp_handle() to set up the extend sleep handle, before calling this function.
 */
hal_sleep_manager_status_t hal_sleep_manager_release_extslp_handle(uint8_t handle_index);

/**
 * @brief       This function prevents the MCU from getting into extend sleep mode.
 * @param[in]   handle_index is the extend sleep handle index, returned from #hal_sleep_manager_set_extslp_handle().
 * @return      #HAL_SLEEP_MANAGER_OK, Extend Sleep Lock is locked.
 * @note        Call #hal_sleep_manager_set_extslp_handle() to set up the extend sleep handle, before calling this function.
 */
hal_sleep_manager_status_t hal_sleep_manager_lock_extslp(uint8_t handle_index);
//
/**
 * @brief       This function unlocks the specific Extend Sleep Lock and permits the MCU going into extend sleep mode when needed if all Extend Sleep Locks are unlocked.
 * @param[in]   handle_index is the extend sleep handle index returned from #hal_sleep_manager_set_extslp_handle().
 * @return      #HAL_SLEEP_MANAGER_OK, extend sleep lock is unlocked.
 * @note        Call #hal_sleep_manager_set_extslp_handle() to set up the extend sleep handle, before calling this function.
 */
hal_sleep_manager_status_t hal_sleep_manager_unlock_extslp(uint8_t handle_index);

/**
 * @brief       This function sets up a extend sleep handle to control the extend sleep state of the system. \n
 *              This handle enables the Sleep Manager to identify the extend sleep states based on the extend sleep handles assigned.
 * @param[in]   handle_name is the name of the extend sleep handle of type string.
 * @return      The extend sleep handle index, if the operation is successful. If (0xFF) is returned, the operation failed.
 */
uint8_t hal_sleep_manager_set_extslp_handle(const char *handle_name);
#endif  /*AIR_BTD_IC_MANDATORY_G1*/

///**
// * @brief       This function sets the system to any of the modes defined in #hal_sleep_mode_t.
// * @param[in]   mode is the desired sleep mode.
// */
void hal_sleep_manager_enter_sleep_mode(hal_sleep_mode_t mode);

void hal_sleep_manager_sw_gpt_callback(void);
void hal_sleep_manager_sw_gpt_callback_rtc(void);
hal_sleep_manager_status_t hal_sleep_manager_set_sleep_time_rtc(uint32_t sleep_time_ms);
#ifdef CONFIG_PM
bool hal_sleep_manager_is_enter_tickless_sleep(void);
uint32_t hal_sleep_manager_get_sleep_time(void);
bool hal_sleep_manager_is_tickless_idle_locked(void);
#endif

#ifdef __cplusplus
}
#endif

#endif
#endif