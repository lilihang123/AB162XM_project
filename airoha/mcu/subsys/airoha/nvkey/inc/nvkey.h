/* Copyright Statement:
 *
 * (C) 2023  Airoha Technology Corp. All rights reserved.
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

#ifndef __NVKEY_H__
#define __NVKEY_H__

#include <errno.h>
#include <stdint.h>

#include "nvkey_id_def.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup NVKEY_enum Enum
  * @{
  */

/** @brief This enum defines return type of NVKEY APIs. */
typedef enum {
    NVKEY_STATUS_PERMISSION_DENIED = -EACCES,     /**< The operation is not allowed. */
    NVKEY_STATUS_MALLOC_ERROR = -9,               /**< The operation failed due to a memory allocation error. */
    NVKEY_STATUS_CRYPT_ERROR = -8,                /**< The operation failed due to a cryptographic error. */
    NVKEY_STATUS_INVALID_PARAMETER = -EINVAL,     /**< The user parameter is invalid. */
    NVKEY_STATUS_ITEM_NOT_FOUND = -ENOENT,        /**< The data item wasn't found by the NVKEY. */
    NVKEY_STATUS_INSUFFICIENT_SPACE = -ENOMEM,    /**< No space is available in the flash. */
    NVKEY_STATUS_INCORRECT_CHECKSUM = -EIO,       /**< The NVKEY found a checksum error when reading the data item. */
    NVKEY_STATUS_ERROR = -1,                      /**< An unknown error occurred. */
    NVKEY_STATUS_OK = 0,                          /**< The operation was successful. */
} nvkey_status_t;


/** @brief  This defines the callback function prototype.
 *          User should register a callback function when calling #nvkey_write_data_item_non_blocking(),
 *          this function is called after the write operation is done or the error is detected during the write operation.
 *          User must check the status to see whether the write operation is successful.
 *          The callback runs in the context of the specific task with very low priority. And the user should not do the time-consuming things .
 *  @param [in] status is the status of write operation.
 *  @param [in] user_data is a user-defined parameter.
 */
typedef void (*nvkey_user_callback_t)(nvkey_status_t status, void *user_data);

/**
  * @}
  */

/**
 * @brief     This function is used to read the data item from flash.
 *            It is an encapsulation of nvs_read().
 * @param[in] id   is the indication number of the item.
 * @param[out] buffer   is a pointer to the user buffer, that stores the data item content read from the flash.
 * @param[in,out] size   is the user buffer size when used as an input and is the size of actual data item's content read out when used as an output.
 * @return
 *                #NVKEY_STATUS_OK, if the operation completed successfully. \n
 *                #NVKEY_STATUS_ERROR, if an unknown error occurred. \n
 *                #NVKEY_STATUS_INVALID_PARAMETER, if the parameter is invalid. \n
 *                #NVKEY_STATUS_ITEM_NOT_FOUND, if the data item is not found. \n
 *                #NVKEY_STATUS_INCORRECT_CHECKSUM, if the checksum of data item is invalid. \n
 * @note      Call this API in tasks or function callbacks, but not in the interrupt handlers.
 */
nvkey_status_t nvkey_read_data(uint16_t id, uint8_t *buffer, uint32_t *size);



/**
 * @brief     This function is used to read the decrypted data item from the flash.
 *            It is an encapsulation of nvkey_read_data_item().
 * @param[in] id   is the indication number of the item.
 * @param[out] buffer   is a pointer to the user buffer, which stores the data item content read from the flash.
 * @param[in,out] size   can be the user buffer size when used as an input or the size of the actual data item's content read out when used as an output.
 * @return
 *                #NVKEY_STATUS_OK, if the operation completed successfully. \n
 *                #NVKEY_STATUS_ERROR, if an unknown error occurred. \n
 *                #NVKEY_STATUS_INVALID_PARAMETER, if the parameter is invalid. \n
 *                #NVKEY_STATUS_ITEM_NOT_FOUND, if the data item is not found. \n
 *                #NVKEY_STATUS_INCORRECT_CHECKSUM, if the checksum of data item is invalid. \n
 * @note      Call this API in tasks or function callbacks, but not in the interrupt handlers.
 */
nvkey_status_t nvkey_read_data_crypt(uint16_t id, uint8_t *buffer, uint32_t *size);


/**
 * @brief     This function is used to write or update a data item to flash.
 *            It is an encapsulation of nvs_write().
 * @param[in] id    is the indication number of the item.
 * @param[in] buffer   is a pointer to the data item's content.
 * @param[in] size   is the size of the data item's content.
 * @return
 *                #NVKEY_STATUS_OK, if the operation completed successfully. \n
 *                #NVKEY_STATUS_ERROR, if an unknown error occurred. \n
 *                #NVKEY_STATUS_INVALID_PARAMETER, if the parameter is invalid. \n
 *                #NVKEY_STATUS_INSUFFICIENT_SPACE, if the storage space is not enough. \n
 * @note      Call this API in tasks or function callbacks, but not in the interrupt handlers.
 */
nvkey_status_t nvkey_write_data(uint16_t id, const uint8_t *buffer, uint32_t size);


/**
 * @brief     This function is used to write or update an encrypted data item to the flash.
 *            It is an encapsulation of nvkey_write_data_item().
 * @param[in] id    is the indication number of the item.
 * @param[in] buffer   is a pointer to the data item's content.
 * @param[in] size   is the size of the data item's content.
 * @return
 *                #NVKEY_STATUS_OK, if the operation completed successfully. \n
 *                #NVKEY_STATUS_ERROR, if an unknown error occurred. \n
 *                #NVKEY_STATUS_INVALID_PARAMETER, if the parameter is invalid. \n
 *                #NVKEY_STATUS_INSUFFICIENT_SPACE, if the storage space is not enough. \n
 * @note      Call this API in tasks or function callbacks, but not in the interrupt handlers.
 */
nvkey_status_t nvkey_write_data_crypt(uint16_t id, uint8_t *buffer, uint32_t size);


/**
 * @brief     This function is used to write or update a data item to flash with non-blocking method.
 *            It is an encapsulation of nvkey_write_data_non_blocking().
 *            User's callback is called after the write operation is done or the error is detected during the write operation.
 *            User should check both the return status of the API and the status of the callback to verify whether the data is written to flash successfully.
 *            The callback runs in the context of the specific task with very low priority. And the user should not do the time-consuming things .
 * @param[in] id    is the indication number of the item.
 * @param[in] buffer   is a pointer to the data item's content.
 * @param[in] size   is the size of the data item's content.
 * @param[in] callback   is the user's callback, it will be called after nvkey completes the write process.
 * @param[in] user_data   is the user's data to be used in the callback.
 * @return
 *                #NVKEY_STATUS_OK, if the operation completed successfully. \n
 *                #NVKEY_STATUS_ERROR, if an unknown error occurred. \n
 *                #NVKEY_STATUS_INVALID_PARAMETER, if the parameter is invalid. \n
 * @note      Call this API in tasks or function callbacks, but not in the interrupt handlers.
 */
nvkey_status_t nvkey_write_data_non_blocking(uint16_t id, const uint8_t *buffer, uint32_t size, const nvkey_user_callback_t callback, const void *user_data);

/**
 * @brief     This function is used to write or update an encrypted data item to the flash with non-blocking method.
 *            It is an encapsulation of nvkey_write_data_non_blocking().
 *            User's callback is called after the write operation is done or the error is detected during the write operation.
 *            User should check both the return status of the API and the status of the callback to verify whether the data is written to the flash successfully.
 *            The callback runs in the context of the specific task with very low priority. And the user should not do time-consuming tasks.
 * @param[in] id    is the indication number of the item.
 * @param[in] buffer   is a pointer to the data item's content.
 * @param[in] size   is the size of the data item's content.
 * @param[in] callback   is the user's callback, it will be called after nvkey completes the write process.
 * @param[in] user_data   is the user's data to be used in the callback.
 * @return
 *                #NVKEY_STATUS_OK, if the operation completed successfully. \n
 *                #NVKEY_STATUS_ERROR, if an unknown error occurred. \n
 *                #NVKEY_STATUS_INVALID_PARAMETER, if the parameter is invalid. \n
 * @note      Call this API in tasks or function callbacks, but not in the interrupt handlers.
 */
nvkey_status_t nvkey_write_data_non_blocking_crypt(uint16_t id, const uint8_t *buffer, uint32_t size, const nvkey_user_callback_t callback, const void *user_data);

/**
 * @brief     This function is used to delete a nvkey item.
 *            It is an encapsulation of nvs_delete().
 * @param[in] id    is the indication number of the item.
 * @return
 *                #NVKEY_STATUS_OK, if the operation completed successfully. \n
 *                #NVKEY_STATUS_ERROR, if an unknown error occurred. \n
 *                #NVKEY_STATUS_INVALID_PARAMETER, if the parameter is invalid. \n
 *                #NVKEY_STATUS_ITEM_NOT_FOUND, if the data item is not found. \n
 * @note      Call this API in tasks or function callbacks, but not in the interrupt handlers.
 */
nvkey_status_t nvkey_delete_data_item(uint16_t id);


/**
 * @brief     This function is used to trigger nvs garbage collection.
 * @param[in] gc_cnt      The number of garbage collection cycles to trigger.
 * @return
 *                #NVKEY_STATUS_OK, if the operation completed successfully. \n
 *                #NVKEY_STATUS_ERROR, if an unknown error occurred. \n
 *                #NVKEY_STATUS_INVALID_PARAMETER, if the parameter is invalid. \n
 *                #NVKEY_STATUS_ITEM_NOT_FOUND, if the data item is not found. \n
 * @note      Call this API in tasks or function callbacks, but not in the interrupt handlers.
 */
nvkey_status_t nvkey_trigger_gc(uint32_t gc_cnt);

/**
 * @brief      Get the number of free sectors in the NVS partition.
 * @return
 *                #int: The number of free sectors.
 */
int nvkey_get_free_sector();

#ifdef __cplusplus
}
#endif


#endif /* __NVKEY_H__ */
