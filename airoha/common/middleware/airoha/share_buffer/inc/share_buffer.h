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

#ifndef _SHARE_BUFFER_H_
#define _SHARE_BUFFER_H_

#if defined(AIR_SHARE_BUFFER_ENABLE)

/* Includes ------------------------------------------------------------------*/
#include "stdio.h"
#include "stdint.h"
#include "stdbool.h"
#include "string.h"
#include "hal_hw_semaphore.h"

/* Public define -------------------------------------------------------------*/
/* Public typedef ------------------------------------------------------------*/
typedef enum {
    SHARE_BUFFER_STATUS_ERROR = -1,
    SHARE_BUFFER_STATUS_OK = 0,
} share_buffer_status_t;

typedef uint8_t share_buffer_type_t;
enum {
    SHARE_BUFFER_RING = 0,
    SHARE_BUFFER_RING_4B_ALIGNED,
    SHARE_BUFFER_RING_INDEX = 0xFF, // share_buffer_type_t must be 1Byte
};

typedef struct {
    uint32_t base_addr;
    uint32_t length;
    uint32_t read_ptr; /* next read start address */
    uint32_t write_ptr;  /* next write start address */
} share_buffer_ring_info_t;

typedef struct {
    uint32_t base_addr;
    uint32_t end_addr;
} share_buffer_space_t;

typedef struct {
    uint32_t total_used_size;
    uint32_t total_free_size;
} share_buffer_mem_info_t;

typedef struct {
    uint32_t block_size;
    uint32_t block_start_addr;
    uint32_t block_end_addr;
} share_buffer_block_t;

typedef struct {
    share_buffer_space_t space;
    share_buffer_mem_info_t mem_info;
    share_buffer_block_t block;
} share_buffer_ring_parameter_t;

typedef struct {
    // hal_hw_semaphore_id_t hw_sem_id;
    uint8_t hw_sem_id;
    union {
        share_buffer_ring_parameter_t ring;
    } param;
} share_buffer_parameter_t;

typedef struct {
    share_buffer_type_t type;
    bool is_full; /* for reduce code operation about check buffer is full(for example (write_offset+N)%buffer_size), we use more memory flag but get better performance and code size */
    union {
        share_buffer_ring_info_t ring;
    } info;
} share_buffer_info_t;

/* Public macro --------------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/
extern share_buffer_status_t share_buffer_init(share_buffer_type_t type, share_buffer_info_t *share_buffer_info, share_buffer_parameter_t *share_buffer_parameter);
extern share_buffer_status_t share_buffer_get_write_pointer(share_buffer_info_t *share_buffer_info, uint8_t hw_sem_id, uint32_t *write_ptr, bool *is_full);
extern share_buffer_status_t share_buffer_set_write_pointer(share_buffer_info_t *share_buffer_info, uint8_t hw_sem_id, uint32_t write_ptr, bool *is_full);
extern share_buffer_status_t share_buffer_get_read_pointer(share_buffer_info_t *share_buffer_info, uint8_t hw_sem_id, uint32_t *read_ptr, bool *is_empty);
extern share_buffer_status_t share_buffer_set_read_pointer(share_buffer_info_t *share_buffer_info, uint8_t hw_sem_id, uint32_t read_ptr, bool *is_empty);
extern share_buffer_status_t share_buffer_get_base_address(share_buffer_info_t *share_buffer_info, uint8_t hw_sem_id, uint32_t *base_addr);
extern share_buffer_status_t share_buffer_get_end_address(share_buffer_info_t *share_buffer_info, uint8_t hw_sem_id, uint32_t *end_addr);
extern share_buffer_status_t share_buffer_malloc(share_buffer_info_t *share_buffer_info, share_buffer_parameter_t *share_buffer_parameter, uint32_t init_size, uint8_t init_value);
extern share_buffer_status_t share_buffer_free(share_buffer_info_t *share_buffer_info, share_buffer_parameter_t *share_buffer_parameter);
extern share_buffer_status_t share_buffer_query_used_space(share_buffer_info_t *share_buffer_info, share_buffer_parameter_t *share_buffer_parameter);
extern share_buffer_status_t share_buffer_query_free_space(share_buffer_info_t *share_buffer_info, share_buffer_parameter_t *share_buffer_parameter);
extern share_buffer_status_t share_buffer_query_next_block(share_buffer_info_t *share_buffer_info, share_buffer_parameter_t *share_buffer_parameter);
extern share_buffer_status_t share_buffer_write(share_buffer_info_t *share_buffer_info, void *des, void *src, uint32_t size);
extern share_buffer_status_t share_buffer_read(share_buffer_info_t *share_buffer_info, void *des, void *src, uint32_t size);

#endif /* AIR_SHARE_BUFFER_ENABLE */

#endif /* _SHARE_BUFFER_H_ */
