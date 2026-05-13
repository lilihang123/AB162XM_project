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

#ifndef __AIR_LAYOUT_PARTITION_H__
#define __AIR_LAYOUT_PARTITION_H__

#ifdef __cplusplus
extern "C" {
#endif

#ifdef AIR_PARTITION_ENABLE

#include <stdint.h>
#include <stdbool.h>

typedef enum {
    PARTITION_TABLE                      = 0x00000000,          /* partition table */
    PARTITION_SECURITY_HEADER_0          = 0x00000001,          /* security header 0 */
    PARTITION_SECURITY_HEADER_1          = 0x00000002,          /* security header 1 */

    PARTITION_BL                         = 0x00000008,          /* bootloader */
    PARTITION_BL_B                       = 0x00000009,          /* bootloader B */

    PARTITION_MCU                        = 0x0000000A,          /* MCU firmware */
    PARTITION_MCU_B                      = 0x0000000B,          /* MCU firmware B */
    PARTITION_SCRATCH                    = 0x0000000C,          /* partition to scratch data */
    PARTITION_FACTORY_DATA               = 0x0000000D,          /* partition related to factory data */
    PARTITION_UPGRADE_INFO               = 0x0000000E,          /* partition related to firmware upgrade info */
    PARTITION_BDM_DATA                   = 0x0000000F,          /* partition related to BDM, which can be used by RGB pattern */

    PARTITION_DSP                        = 0x00000010,          /* DSP firmware */

    PARTITION_FOTA                       = 0x00000014,          /* reserved partition for OTA */

    PARTITION_STORAGE                    = 0x00000018,          /* partition to store non-volatile data and *can not* be overwritten by OTA */
    PARTITION_STORAGE_OTA                = 0x00000019,          /* partition to store non-volatile data and *can* be overwritten by OTA */
    PARTITION_FATFS                      = 0x0000001A,          /* partition to store non-volatile data by FATFS */
    PARTITION_NVRAM                      = 0x0000001B,          /* partition to store non-volatile data by NVRAM */
    PARTITION_TAG_IMAGES                 = 0x0000001C,          /* partition to store non-volatile data of tag images */

    PARTITION_SECURE_FW                  = 0x00000020,          /* secure firmware for ARMv8M architecture */

    /* For user customization, partition enumerate please start from 0x1000. */
    PARTITION_CUSTOM_BEGIN               = 0x00001000,
#ifdef AIR_LAYOUT_PARTITION_CUSTOM_EXTEND_ENABLE
    #include "custom_partition.h"
    CUSTOM_PARTITIONS_EXTEND
#endif

    PARTITION_DUMMY_END                  = 0x4D4D5544,
    /* It is not allowed to add new data after DUMMY_END
     * and use the partition behind PARTITION_DUMMY_END.
     */
} partition_id_t;


typedef enum {
    PARTITION_OP_OK                      = 0,
    PARTITION_OP_ERROR                   = -1,
    PARTITION_OP_NOT_INIT                = -2,
    PARTITION_OP_NOT_EXIST               = -3,
    PARTITION_OP_NO_MORE_ITEM            = -4,
    PARTITION_OP_REPEAT_ID               = -5,
    PARTITION_OP_INVALID_PARAMETER       = -6,
} partition_status_t;



typedef union {
    uint32_t value;
    struct {
        /* for flash driver. If this bit is set, for this partition, erase and write operations are not allowed unless it is an upgrade firmware scenario.  */
        uint32_t read_only               :1;
        /* for cache driver. If this bit is set, the partition will be made cacheable. */
        uint32_t cacheable               :1;
        /* This bit is used to distinguish between mutable partitions and immutable partitions.
         * This is to cope with the situation where the layout may change during firmware upgrades.
         */
        uint32_t immutable               :1;
        uint32_t __RESERVED             :29;
    } bits;
} partition_attr_t;
#if defined(__STDC_VERSION__) && (__STDC_VERSION__) >= 201100
_Static_assert(sizeof(partition_attr_t) == 4, "Unexpected structure size of partition_attr_t");
#endif

typedef struct {
    uint8_t name[16];
    uint32_t id;
    partition_attr_t attribute;
    uint32_t address;
    uint32_t length;
    uint32_t customized_data[8];
} partition_item_t;



partition_status_t partition_init(void);
partition_status_t partition_get_length(partition_id_t id, uint32_t *value);
partition_status_t partition_get_begin_address(partition_id_t id, uint32_t *value);
partition_status_t partition_is_readonly(uint32_t logic_addr, uint32_t len, bool *p_ro_var);

#endif /* AIR_PARTITION_ENABLE */

#ifdef __cplusplus
}
#endif

#endif /* __AIR_LAYOUT_PARTITION_H__ */