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

#ifndef __BDM_H__
#define __BDM_H__

/*!
     @defgroup PAGE_API_LIBRARY_BDM ab_bdm.h
     @{
        @page PAGE_API_LIBRARY_BDM ab_bdm.h
        ab_bdm.h provides BDM( block data management ) format based flash access function
*/

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

#if CONFIG_AIR_BDM_ENABLE

#define BDM_END_ID                       (uint16_t)0xDEAD      /**< BDM end ID */
#define BDM_END_BLOCK_NUM                (uint16_t)0xBEEF      /**< BDM end ID */


#define BDM_FLAG_FINISH_WRITE           (1<<0)          /**< BDM write operation finished flag */


/*!@brief BDM flash API error code  */
typedef enum
{
    BDM_SUCCESS                         =  0,           /**< bdm operation success */
    BDM_NOT_INITED                      =  1,           /**< bdm library not initialized */
    BDM_INVALID_OP_PARAM                =  2,           /**< bdm operation parameter not valid */
    BDM_BUSY                            =  3,           /**< bdm library is busy */
    BDM_ID_NOT_FOUND                    =  4,           /**< bdm data with specified id not found */
} bdm_status_t;

typedef enum {
    BDM_ERASE_COUNT,                                    /**< The erase count of every bdm data item. */
    BDM_BLOCK_NUMBER,                                   /**< The number of flash block( 4KB ) a BDM data item occupies. */
    BDM_SEQUENCE_NUMBER,                                /**< The data indicates the writing sequence of bdm data item. */
    BDM_DATA_ITEM_SIZE,                                 /**< The size of a bdm data item in byte. */
} bdm_info_t;

/** @defgroup NVDM_struct Struct
  * @{
  */

/** @brief This structure defines the information of distribution of bdm_id and bdm_sector. */
typedef struct {
    uint16_t id;                /**< The ID of a BDM data item. */
    uint16_t block_num;         /**< It represents the number of flash block( 4KB ) a BDM data item occupies. */
} id_size_mapping_t;

/**
  * @}
  */

/*!
       @brief Initialize BDM based Flash storage. The region must be within bdm_sectors.
       @param start_addr Start address of BDM based Flash storage. Must be multiple of 4096.
       @param id_size_mapping_t Mapping table of id and size of data.
       @return  API error code @ref bdm_status_t
*/
bdm_status_t ab_bdm_init(uint32_t addr, const id_size_mapping_t *table);

/*!
       @brief Write BDM format based data into flash.
       @param id            id of a data item
       @param offset        offset of data in the data item
       @param src_buff      pointer of data
       @param len           length of data
       @param flags         flags for write operation
       @return  API error code @ref bdm_status_t
*/
bdm_status_t ab_bdm_write(uint16_t id, uint32_t offset, const uint8_t* src_buff, uint32_t len, int flags);

/*!
       @brief Read BDM format based data from flash
       @param id            id of data item
       @param offset        offset of data in the data item
       @param dst_buff      pointer of destination data
       @param len           length of data
       @return  API error code @ref bdm_status_t
*/
bdm_status_t ab_bdm_read(uint16_t id, uint32_t offset, uint8_t* dst_buff, uint32_t len);

/*!
       @brief Delete BDM format based data from flash
       @param id      id of data item
       @return  API error code @ref bdm_status_t
*/
bdm_status_t ab_bdm_delete(uint16_t id);


/*!
       @brief Query BDM format based data from flash
       @param id            id of data item
       @param property      property to be queried of data item
       @return  API error code @ref bdm_status_t
*/
bdm_status_t ab_bdm_query(uint16_t id, bdm_info_t type, uint32_t* property);

#endif /* CONFIG_AIR_BDM_ENABLE */

#ifdef __cplusplus
}
#endif

/*! @} */
#endif /* __BDM_H__ */
