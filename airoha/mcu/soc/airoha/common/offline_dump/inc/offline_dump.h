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

#ifndef __OFFLINE_DUMP_H__
#define __OFFLINE_DUMP_H__

#include <stdint.h>
#include <stdbool.h>

#include <time.h>


/*if use custom region, set this marco = 0 !!! */
#define OFFLINE_DUMP_SHARE_WITH_FOTA_REGION  1

/* porting define */
#if OFFLINE_DUMP_SHARE_WITH_FOTA_REGION == 1
    /* default config, offline dump share with FOTA region */
    uint32_t offline_dump_query_region_address(void);
    uint32_t offline_dump_query_region_reserve(void);
    #define OFFLINE_DUMP_ADDRESS             (offline_dump_query_region_address())
    #define OFFLINE_DUMP_RESERVE             (offline_dump_query_region_reserve())
#else
    /* customer define region address and region size, does not overlap with FOTA */
    #define OFFLINE_DUMP_ADDRESS             (0x0)      // replace user define, do not overlap with other flash intervals in use.
    #define OFFLINE_DUMP_RESERVE             (0x0)      // replace user define, do not overlap with other flash intervals in use.
#endif

#define SERIAL_FLASH_BLOCK_SIZE             4096

#define OFFLINE_BUILD_TIME_COUNT            1
#define OFFLINE_BUILD_INFO_SIZE             48
#define OFFLINE_DUMP_CUST_SDK_VERSION_LEN   64

/* offline dump cell header struct */
typedef struct {
    uint8_t status;
    uint8_t rtc_status;
    uint8_t reserved[2];
    uint16_t header_checksum;
    uint16_t header_size;
    uint8_t dump_version;
    uint8_t payload_type;
    uint8_t sdk_ver_cnt;
    uint8_t build_time_cnt;
    uint8_t magic_name[32];
    uint32_t payload_size;
    uint32_t payload_real_size;
    uint32_t seq_number;
    uint8_t rtc_time[8];
    uint8_t sdk_version[OFFLINE_BUILD_INFO_SIZE];
    uint8_t build_time[OFFLINE_BUILD_INFO_SIZE];
    uint8_t customized_sdk_version[OFFLINE_DUMP_CUST_SDK_VERSION_LEN];
    uint32_t timestamp;
} offline_dump_header_t;

typedef struct {
    uint16_t milli_sec;             /**< millisecond               - [0,999] */
    uint8_t sec;                    /**< Seconds after minutes     - [0,59]  */
    uint8_t min;                    /**< Minutes after the hour    - [0,59]  */
    uint8_t hour;                   /**< Hours after midnight      - [0,23]  */
    uint8_t day;                    /**< Day of the month          - [1,31]  */
    uint8_t mon;                    /**< Months                    - [1,12]  */
    uint8_t week;                   /**< Days in a week            - [0,6]   */
    uint8_t year;                   /**< Years                     - [0,127] */
} offline_dump_rtc_t;

/* Offline dump version */
#define OFFLINE_REGION_VERSION                    0x01

/* exception log information */
#define OFFLINE_REGION_EXCEPTION_LOG_BASE_ADDR      (OFFLINE_DUMP_ADDRESS)
#define OFFLINE_REGION_EXCEPTION_LOG_CELL_COUNT     1
#define OFFLINE_REGION_EXCEPTION_LOG_CELL_SIZE      (8 * SERIAL_FLASH_BLOCK_SIZE)
#define OFFLINE_REGION_EXCEPTION_LOG_REGION_SIZE    (OFFLINE_REGION_EXCEPTION_LOG_CELL_COUNT * OFFLINE_REGION_EXCEPTION_LOG_CELL_SIZE)

/* mini dump information */
#define OFFLINE_REGION_MINI_DUMP_BASE_ADDR          (OFFLINE_REGION_EXCEPTION_LOG_BASE_ADDR + OFFLINE_REGION_EXCEPTION_LOG_REGION_SIZE)
#define OFFLINE_REGION_MINI_DUMP_CELL_COUNT         1
#define OFFLINE_REGION_MINI_DUMP_CELL_SIZE          (128 * SERIAL_FLASH_BLOCK_SIZE)
#define OFFLINE_REGION_MINI_DUMP_REGION_SIZE        (OFFLINE_REGION_MINI_DUMP_CELL_COUNT * OFFLINE_REGION_MINI_DUMP_CELL_SIZE)


typedef void (*offline_callback_t)(void);

/* offline dump region enum */
typedef enum {
    OFFLINE_REGION_EXCEPTION_LOG = 0,
    OFFLINE_REGION_MINI_DUMP,
    OFFLINE_REGION_MAX,
} offline_dump_region_type_t;

/* offline dump status */
typedef enum {
    OFFLINE_STATUS_OK,                          /**<  status ok*/
    OFFLINE_STATUS_ERROR,                       /**<  status error*/
    OFFLINE_STATUS_ERROR_PARAMETER,             /**<  status error parameter*/
    OFFLINE_STATUS_ERROR_NOT_INIT,              /**<  status uninitialized*/
    OFFLINE_STATUS_ERROR_NOT_ALLOW,             /**<  status of flash access error*/
    OFFLINE_STATUS_ERROR_BUSY,                  /**<  status of busy*/
} offline_dump_status_t;

offline_dump_status_t offline_dump_region_init(void);

offline_dump_status_t offline_dump_region_alloc(offline_dump_region_type_t region_type, uint32_t *p_start_addr);

offline_dump_status_t offline_dump_region_write(offline_dump_region_type_t region_type, uint32_t curr_addr, uint8_t *data, uint32_t length);

offline_dump_status_t offline_dump_region_write_end(offline_dump_region_type_t region_type, uint32_t total_length);

offline_dump_status_t offline_dump_region_read(offline_dump_region_type_t region_type, uint32_t curr_addr, uint8_t *buf, uint32_t length);

offline_dump_status_t offline_dump_region_query_seq_range(offline_dump_region_type_t region_type, uint32_t *p_min_seq, uint32_t *p_max_seq);

offline_dump_status_t offline_dump_region_query_by_seq(offline_dump_region_type_t region_type, uint32_t seq, uint32_t *p_start_addr, uint32_t *p_total_length);

offline_dump_status_t offline_dump_region_query_cell_size(offline_dump_region_type_t region_type, uint32_t *p_cell_size);

offline_dump_status_t offline_dump_region_query_cell_valid_size(offline_dump_region_type_t region_type, uint32_t *p_valid_size);

// offline_dump_status_t offline_dump_region_write_with_race_header(exception_log_type_t log_type, uint32_t *curr_addr, uint8_t *data, uint32_t length);

/* config RTC */
bool offline_dump_set_rtc_time_unix(time_t timestamp);
bool offline_dump_query_unix_time(time_t *timestamp);

#endif /* __OFFLINE_DUMP_H__ */

