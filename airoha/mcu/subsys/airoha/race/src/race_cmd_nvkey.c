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
#ifdef AIR_BTD_IC_PREMIUM_G1


#include "race_cmd_feature.h"

#ifdef RACE_NVKEY_CMD_ENABLE

#include "nvkey.h"
#include "air_chip.h"

#include <zephyr/fs/nvs.h>
#include <settings/settings_nvs.h>
#include <zephyr/settings/settings.h>
#include <zephyr/drivers/flash.h>
#include <zephyr/storage/flash_map.h>

#include "race_xport.h"
#include "race_cmd_nvkey.h"
#include "race_event_internal.h"
#include "race_util.h"

#define RACE_CMD_NVKEY_ENABLE_DEBUG_LOG
#define RACE_CMD_NVKEY_CHECK_PERMISSION
// #define RACE_CMD_NVKEY_WHITE_LIST

#define NVKEY_MAX_DATA_ITEM_SIZE 1024

typedef struct {
    RACE_COMMON_HDR_STRU hdr;
    uint16_t nvkey_id;
    uint16_t length_of_read_bytes;
} PACKED race_nvkey_read_cmd_t;

typedef struct {
    uint16_t length_of_read_bytes;
    uint8_t read_data[0];
} PACKED race_nvkey_read_resp_t;

typedef struct {
    RACE_COMMON_HDR_STRU hdr;
    uint16_t nvkey_id;
    uint16_t length_of_read_bytes;
} PACKED race_nvkey_read_more_info_cmd_t;

typedef struct {
    int8_t return_code;
    uint16_t nvkey_id;
    uint16_t length_of_read_bytes;
    uint8_t read_data[0];
} PACKED race_nvkey_read_more_info_resp_t;


typedef struct {
    RACE_COMMON_HDR_STRU hdr;
    uint16_t nvkey_id;
    uint8_t write_data[0];
} PACKED race_nvkey_write_cmd_t;

typedef struct {
    uint8_t return_code;
} PACKED race_nvkey_write_resp_t;

typedef struct {
    RACE_COMMON_HDR_STRU hdr;
    uint16_t nvkey_id;
    uint8_t write_data[0];
} PACKED race_nvkey_write_more_info_cmd_t;

typedef struct {
    uint8_t return_code;
    uint16_t nvkey_id;
} PACKED race_nvkey_write_more_info_resp_t;


typedef struct {
    RACE_COMMON_HDR_STRU hdr;
    uint16_t minimum_space;
} PACKED race_nvkey_space_cmd_t;

typedef struct {
    uint8_t status;
} PACKED race_nvkey_space_resp_t;


typedef struct {
    uint8_t status;
    uint16_t nvs_num;
    uint16_t nvs_data[0];
} PACKED race_nvkey_resp_t;

typedef struct {
    uint16_t start_id;
    uint16_t end_id;
} PACKED race_cmd_nvkey_range_t;

#if RACE_CMD_NVKEY_WHITE_LIST
    const race_cmd_nvkey_range_t s_race_writable_ranges[] = {
        /* start_id, end_id */
    };

    const uint16_t s_race_writable_ids[] = {
        /* nvkey id */
    };

    const race_cmd_nvkey_range_t s_race_readable_ranges[] = {
        /* start_id, end_id */
    };

    const uint16_t s_race_readable_ids[] = {
        /* nvkey id */
    };

    #define NVKEY_WRITE_PERMISSION_RANGE_LIST_LEN               (sizeof(s_race_writable_ranges) / sizeof(s_race_writable_ranges[0]))
    #define NVKEY_WRITE_PERMISSION_LIST_LEN                     (sizeof(s_race_writable_ids) / sizeof(s_race_writable_ids[0]))
    #define NVKEY_READ_PERMISSION_RANGE_LIST_LEN                (sizeof(s_race_readable_ranges) / sizeof(s_race_readable_ranges[0]))
    #define NVKEY_READ_PERMISSION_LIST_LEN                      (sizeof(s_race_readable_ids) / sizeof(s_race_readable_ids[0]))
#else
    const race_cmd_nvkey_range_t s_race_not_writable_ranges[] = {
        /* start_id, end_id */
        { NVID_LOCAL_DEVICES_ADDR_ID_0, NVID_LOCAL_DEVICES_ADDR_ID_7},
        { NVID_GAMING_MODE_PEER_DEVICE_INFO_0, NVID_GAMING_MODE_PEER_DEVICE_INFO_3},
    };

    const uint16_t s_race_not_writable_ids[] = {
        /* nvkey id */
        NVID_BT_HOST_LOCAL_ADDR,

    };

    const race_cmd_nvkey_range_t s_race_not_readable_ranges[] = {
        /* start_id, end_id */
        { NVID_LOCAL_DEVICES_ADDR_ID_0, NVID_LOCAL_DEVICES_ADDR_ID_7},
        { NVID_GAMING_MODE_PEER_DEVICE_INFO_0, NVID_GAMING_MODE_PEER_DEVICE_INFO_3},
    };

    const uint16_t s_race_not_readable_ids[] = {
        /* nvkey id */
        NVID_BT_HOST_LOCAL_ADDR,
    };
    #define NVKEY_WRITE_PERMISSION_RANGE_LIST_LEN               (sizeof(s_race_not_writable_ranges) / sizeof(s_race_not_writable_ranges[0]))
    #define NVKEY_WRITE_PERMISSION_LIST_LEN                     (sizeof(s_race_not_writable_ids) / sizeof(s_race_not_writable_ids[0]))
    #define NVKEY_READ_PERMISSION_RANGE_LIST_LEN                (sizeof(s_race_not_readable_ranges) / sizeof(s_race_not_readable_ranges[0]))
    #define NVKEY_READ_PERMISSION_LIST_LEN                      (sizeof(s_race_not_readable_ids) / sizeof(s_race_not_readable_ids[0]))
#endif /* RACE_CMD_NVKEY_WHITE_LIST */



ATTR_WEAK_SYMBOL bool race_cmd_nvkey_check_writable(uint16_t nvkey_id)
{
#ifdef RACE_CMD_NVKEY_CHECK_PERMISSION
#ifdef AIR_RACE_SET_FACTORY_MODE
    if (race_get_factory_mode() == true) {
        return true;
    }
#endif
    size_t idx;
#if RACE_CMD_NVKEY_WHITE_LIST
    for (idx = 0; idx < NVKEY_WRITE_PERMISSION_RANGE_LIST_LEN; idx++) {
        if ((nvkey_id >= s_race_writable_ranges[idx].start_id) && \
            (nvkey_id <= s_race_writable_ranges[idx].end_id)
        ) {
            return true;
        }
    }
    for (idx = 0; idx < NVKEY_WRITE_PERMISSION_LIST_LEN; idx++) {
        if (nvkey_id == s_race_writable_ids[idx]) {
            return true;
        }
    }
    return false;
#else
    for (idx = 0; idx < NVKEY_WRITE_PERMISSION_RANGE_LIST_LEN; idx++) {
        if ((nvkey_id >= s_race_not_writable_ranges[idx].start_id) && \
            (nvkey_id <= s_race_not_writable_ranges[idx].end_id)
        ) {
            return false;
        }
    }
    for (idx = 0; idx < NVKEY_WRITE_PERMISSION_LIST_LEN; idx++) {
        if (nvkey_id == s_race_not_writable_ids[idx]) {
            return false;
        }
    }
    return true;
#endif /* RACE_CMD_NVKEY_WHITE_LIST */

#else /* RACE_CMD_NVKEY_CHECK_PERMISSION */
    ARG_UNUSED(nvkey_id);
    return true;
#endif
}


ATTR_WEAK_SYMBOL bool race_cmd_nvkey_check_readable(uint16_t nvkey_id)
{
#ifdef RACE_CMD_NVKEY_CHECK_PERMISSION
#ifdef AIR_RACE_SET_FACTORY_MODE
    if (race_get_factory_mode() == true) {
        return true;
    }
#endif
    size_t idx;
#if RACE_CMD_NVKEY_WHITE_LIST
    for (idx = 0; idx < NVKEY_READ_PERMISSION_RANGE_LIST_LEN; idx++) {
        if ((nvkey_id >= s_race_readable_ranges[idx].start_id) && \
            (nvkey_id <= s_race_readable_ranges[idx].end_id)
        ) {
            return true;
        }
    }
    for (idx = 0; idx < NVKEY_READ_PERMISSION_LIST_LEN; idx++) {
        if (nvkey_id == s_race_readable_ids[idx]) {
            return true;
        }
    }
    return false;
#else
    for (idx = 0; idx < NVKEY_READ_PERMISSION_RANGE_LIST_LEN; idx++) {
        if ((nvkey_id >= s_race_not_readable_ranges[idx].start_id) && \
            (nvkey_id <= s_race_not_readable_ranges[idx].end_id)
        ) {
            return false;
        }
    }
    for (idx = 0; idx < NVKEY_READ_PERMISSION_LIST_LEN; idx++) {
        if (nvkey_id == s_race_not_readable_ids[idx]) {
            return false;
        }
    }
    return true;
#endif /* RACE_CMD_NVKEY_WHITE_LIST */

#else /* RACE_CMD_NVKEY_CHECK_PERMISSION */
    ARG_UNUSED(nvkey_id);
    return true;
#endif
}

#if AIR_BTD_IC_PREMIUM_G1
/* To solve the issue of the response of nvkey read command containing extra 0x00,
 * it is necessary to first read the nvkey data into the temporary buffer,
 * then allocate the buffer by race api after knowing the exact length,
 * copy the data to the allocated buffer, and reply it to the tool through race protocol.
 * In Addition, for low power considerations, the buffer needs to be configured
 * with the none retention attribute.
 */
ATTR_ZIDATA_IN_TCM_NONE_RETENTION
#endif
static uint8_t s_nvkey_buffer[NVKEY_MAX_DATA_ITEM_SIZE];


extern struct nvs_fs* nvkey_judge_paratition(uint16_t id);

void *RACE_NVKEY_READFULLKEY_HDR(ptr_race_pkt_t pCmdMsg, uint8_t channel_id)
{
#ifdef RACE_CMD_NVKEY_ENABLE_DEBUG_LOG
    LOG_INF("RACE_NVKEY_READFULLKEY_HDR, channel_id[%d]", channel_id);
#endif

    race_nvkey_read_cmd_t *pCmd = (race_nvkey_read_cmd_t *)pCmdMsg;
    race_nvkey_read_resp_t *pEvt = NULL;
    uint32_t size = NVKEY_MAX_DATA_ITEM_SIZE;
    nvkey_status_t status = NVKEY_STATUS_ERROR;
    bool permission_allowed = false;

    permission_allowed = race_cmd_nvkey_check_readable(pCmd->nvkey_id);
    if(permission_allowed){
        status = nvkey_read_data(pCmd->nvkey_id, (uint8_t *)s_nvkey_buffer, &size);
    } else {
        status = NVKEY_STATUS_PERMISSION_DENIED;
    }

    if (status != NVKEY_STATUS_OK) {
#ifdef RACE_CMD_NVKEY_ENABLE_DEBUG_LOG
        LOG_ERR("nvkey_read_data fail(%d), nvkey_id[0x%x]", status, pCmd->nvkey_id);
#endif
        pEvt = RACE_ClaimPacket((uint8_t)RACE_TYPE_RESPONSE, (uint16_t)RACE_NVKEY_READFULLKEY,
                    (uint16_t)(sizeof(race_nvkey_read_resp_t) + 0), channel_id);
        if (pEvt) {
            pEvt->length_of_read_bytes = 0;
        } else {
#ifdef RACE_CMD_NVKEY_ENABLE_DEBUG_LOG
            LOG_ERR("RACE_ClaimPacket fail, nvkey_id[0x%x]", pCmd->nvkey_id);
#endif
        }
    } else {
        /* when the status is NVKEY_STATUS_OK, we got the right size of the nvkey item */
        LOG_INF("nvkey_read_data pass with size %d, length of read bytes: %d", (int)size, (int)(pCmd->length_of_read_bytes));
        size = (size <= pCmd->length_of_read_bytes) ? size : pCmd->length_of_read_bytes;
        pEvt = RACE_ClaimPacket((uint8_t)RACE_TYPE_RESPONSE, (uint16_t)RACE_NVKEY_READFULLKEY,
                    (uint16_t)(sizeof(race_nvkey_read_resp_t) + size), channel_id);

        if (pEvt) {
            memcpy((void *)pEvt->read_data, (void *)s_nvkey_buffer, size);
            pEvt->length_of_read_bytes = size;
        } else {
#ifdef RACE_CMD_NVKEY_ENABLE_DEBUG_LOG
            LOG_ERR("RACE_ClaimPacket fail, nvkey_id[0x%x]", pCmd->nvkey_id);
#endif
        }
    }
    return pEvt;
}

void *RACE_NVKEY_READFULLKEY_RESP_NVID_HDR(ptr_race_pkt_t pCmdMsg, uint8_t channel_id)
{
#ifdef RACE_CMD_NVKEY_ENABLE_DEBUG_LOG
    LOG_INF("RACE_NVKEY_READFULLKEY_RESP_NVID_HDR, channel_id[%d]", channel_id);
#endif

    race_nvkey_read_more_info_cmd_t *pCmd = (race_nvkey_read_more_info_cmd_t *)pCmdMsg;
    race_nvkey_read_more_info_resp_t *pEvt = NULL;
    uint32_t size = NVKEY_MAX_DATA_ITEM_SIZE;
    nvkey_status_t status = NVKEY_STATUS_ERROR;
    bool permission_allowed = false;

    permission_allowed = race_cmd_nvkey_check_readable(pCmd->nvkey_id);
    if(permission_allowed){
        status = nvkey_read_data(pCmd->nvkey_id, (uint8_t *)s_nvkey_buffer, &size);
    } else {
        status = NVKEY_STATUS_PERMISSION_DENIED;
    }

    if (status != NVKEY_STATUS_OK) {
#ifdef RACE_CMD_NVKEY_ENABLE_DEBUG_LOG
        LOG_ERR("nvkey_read_data fail(%d), nvkey_id[0x%x]", status, pCmd->nvkey_id);
#endif
        pEvt = RACE_ClaimPacket((uint8_t)RACE_TYPE_RESPONSE, (uint16_t)RACE_NVKEY_READFULLKEY_RESP_NVID,
                        (uint16_t)(sizeof(race_nvkey_read_more_info_resp_t) + 0), channel_id);
        if (pEvt) {
            pEvt->return_code = (int8_t)status;
            pEvt->nvkey_id = pCmd->nvkey_id;
            pEvt->length_of_read_bytes = 0;
        } else {
#ifdef RACE_CMD_NVKEY_ENABLE_DEBUG_LOG
            LOG_ERR("RACE_ClaimPacket fail, nvkey_id[0x%x]", pCmd->nvkey_id);
#endif
        }
    } else {
        /* when the status is NVKEY_STATUS_OK, we got the right size of the nvkey item */
        LOG_INF("nvkey_read_data pass with size %d, length of read bytes: %d", (int)size, (int)(pCmd->length_of_read_bytes));
        size = (size <= pCmd->length_of_read_bytes) ? size : pCmd->length_of_read_bytes;
        pEvt = RACE_ClaimPacket((uint8_t)RACE_TYPE_RESPONSE, (uint16_t)RACE_NVKEY_READFULLKEY_RESP_NVID,
                    (uint16_t)(sizeof(race_nvkey_read_more_info_resp_t) + size), channel_id);

        if (pEvt) {
            memcpy((void *)pEvt->read_data, (void *)s_nvkey_buffer, size);
            pEvt->return_code = (int8_t)status;
            pEvt->nvkey_id = pCmd->nvkey_id;
            pEvt->length_of_read_bytes = size;
        } else {
#ifdef RACE_CMD_NVKEY_ENABLE_DEBUG_LOG
            LOG_ERR("RACE_ClaimPacket fail, nvkey_id[0x%x]", pCmd->nvkey_id);
#endif
        }
    }

    return pEvt;
}

void *RACE_NVKEY_WRITEFULLKEY_HDR(ptr_race_pkt_t pCmdMsg, uint8_t channel_id)
{
#ifdef RACE_CMD_NVKEY_ENABLE_DEBUG_LOG
    LOG_INF("RACE_NVKEY_WRITEFULLKEY_HDR, channel_id[%d]", channel_id);
#endif

    uint32_t nvkey_length = 0, size = 0, i;
    nvkey_status_t status = NVKEY_STATUS_ERROR;
    bool permission_allowed = false;

    race_nvkey_write_cmd_t *pCmd = (race_nvkey_write_cmd_t *)pCmdMsg;

    race_nvkey_write_resp_t *pEvt = (race_nvkey_write_resp_t *)RACE_ClaimPacket((uint8_t)RACE_TYPE_RESPONSE,
                                        (uint16_t)RACE_NVKEY_WRITEFULLKEY, (uint16_t)(sizeof(race_nvkey_write_resp_t)), channel_id);

    if (pEvt != NULL) {
        permission_allowed = race_cmd_nvkey_check_writable(pCmd->nvkey_id);
        if(permission_allowed){
            nvkey_length = pCmd->hdr.length - sizeof(pCmd->hdr.id) - sizeof(pCmd->nvkey_id);
            status = nvkey_write_data(pCmd->nvkey_id, pCmd->write_data, nvkey_length);
        } else {
            status = NVKEY_STATUS_PERMISSION_DENIED;
        }

        if (status == NVKEY_STATUS_OK) {
            uint8_t *pData = NULL;

            size = nvkey_length;
            pData = (uint8_t *)race_mem_alloc(nvkey_length);
            if (pData == NULL) {
#ifdef RACE_CMD_NVKEY_ENABLE_DEBUG_LOG
                LOG_ERR("race_mem_alloc fail");
#endif
                pEvt->return_code = NVKEY_STATUS_ERROR;
                return pEvt;
            }
            status = nvkey_read_data(pCmd->nvkey_id, (uint8_t *)pData, &size);

            if (status == NVKEY_STATUS_OK) {
                for (i = 0; i < size; i++) {
                    if (pData[i] != pCmd->write_data[i]) {
                        LOG_ERR("nvkey compare fail, nvkey_id[0x%X], write_data[0x%X], read_data[0x%X]",
                                    pCmd->nvkey_id, pCmd->write_data[i], pData[i]);
                        status = RACE_STATUS_ERROR;
                    }
                }
                pEvt->return_code = (int8_t)status;
            } else {
#ifdef RACE_CMD_NVKEY_ENABLE_DEBUG_LOG
                LOG_ERR("read nvkey fail, nvkey_status[%d]", status);
#endif
                pEvt->return_code = (int8_t)status;
            }
            race_mem_free(pData);
        } else {
#ifdef RACE_CMD_NVKEY_ENABLE_DEBUG_LOG
            LOG_ERR("write nvkey fail, nvkey_status[%d]", status);
#endif
            pEvt->return_code = (int8_t)status;
        }
    }

    return pEvt;
}

void *RACE_NVKEY_WRITEFULLKEY_RESP_NVID_HDR(ptr_race_pkt_t pCmdMsg, uint8_t channel_id)
{
#ifdef RACE_CMD_NVKEY_ENABLE_DEBUG_LOG
    LOG_INF("RACE_NVKEY_WRITEFULLKEY_RESP_NVID_HDR, channel_id[%d]", channel_id);
#endif

    uint32_t nvkey_length;
    nvkey_status_t status;
    uint32_t size;
    uint8_t *pData;
    uint32_t i;
    bool permission_allowed = false;

    race_nvkey_write_more_info_cmd_t *pCmd = (race_nvkey_write_more_info_cmd_t *)pCmdMsg;

    race_nvkey_write_more_info_resp_t *pEvt = (race_nvkey_write_more_info_resp_t *)RACE_ClaimPacket((uint8_t)RACE_TYPE_RESPONSE,
                                                (uint16_t)RACE_NVKEY_WRITEFULLKEY_RESP_NVID,
                                                (uint16_t)(sizeof(race_nvkey_write_more_info_resp_t)),
                                                channel_id);

    if (pEvt != NULL) {
        pEvt->nvkey_id = pCmd->nvkey_id;
        pEvt->return_code = RACE_ERRCODE_FAIL;
        permission_allowed = race_cmd_nvkey_check_writable(pCmd->nvkey_id);
        if(permission_allowed){
            nvkey_length = pCmd->hdr.length - sizeof(pCmd->hdr.id) - sizeof(pCmd->nvkey_id);
            status = nvkey_write_data(pCmd->nvkey_id, pCmd->write_data, nvkey_length);
        } else {
            status = NVKEY_STATUS_PERMISSION_DENIED;
        }

        if (status == NVKEY_STATUS_OK) {
#ifdef RACE_CMD_NVKEY_ENABLE_DEBUG_LOG
            LOG_INF("NVKEY Write Done, Read NVKEY and compare Data");
#endif

            size = nvkey_length;
            pData = (uint8_t *)race_mem_alloc(size);
            /* check whether memory was allocated successfully */
            if (pData == NULL){
                pEvt->return_code = RACE_ERRCODE_NOT_ENOUGH_MEMORY;
            } else {
                status = nvkey_read_data(pCmd->nvkey_id, (uint8_t *)pData, &size);

                if (status == NVKEY_STATUS_OK) {
                    for (i = 0; i < size; i++) {
                        if (pData[i] != pCmd->write_data[i]) {
                            LOG_ERR("nvkey data different, nvkey[0x%X], [0x%X] != [0x%X]", pCmd->nvkey_id, pData[i], pCmd->write_data[i]);
                            status = NVKEY_STATUS_ERROR;
                            break;
                        }
                    }
                    if (status == NVKEY_STATUS_ERROR) {
                        pEvt->return_code = RACE_ERRCODE_FAIL;
                    } else {
                        pEvt->return_code = RACE_ERRCODE_SUCCESS;
                    }
                }
                race_mem_free(pData);
            }
        } else {
#ifdef RACE_CMD_NVKEY_ENABLE_DEBUG_LOG
            LOG_ERR("write nvkey with id response fail, nvkey_status[%d]", status);
#endif
            /* fix Overflowed constant (INTEGER_OVERFLOW) issue */
            pEvt->return_code = (uint8_t)status;
        }
    }

    return pEvt;
}

/**
 * RACE_NVKEY_RECLAIM_HDR
 *
 * RACE NVKEY RECLAIM Handler
 *
 *
 * @pCmdMsg : pointer of ptr_race_pkt_t
 *
 */
void *RACE_NVKEY_RECLAIM_HDR(ptr_race_pkt_t pCmdMsg, uint8_t channel_id)
{
#ifdef RACE_CMD_NVKEY_ENABLE_DEBUG_LOG
    LOG_INF("RACE_NVKEY_RECLAIM_HDR, channel_id[%d]", channel_id);
#endif

    race_nvkey_space_cmd_t *pCmd = (race_nvkey_space_cmd_t *)pCmdMsg;
    race_nvkey_space_resp_t *pEvt = NULL;
    struct nvs_fs* fs;
    ssize_t free_bytes;

    pEvt = RACE_ClaimPacket((uint8_t)RACE_TYPE_RESPONSE, (uint16_t)RACE_NVKEY_RECLAIM,
                            (uint16_t)(sizeof(race_nvkey_space_resp_t)), channel_id);
    if (pEvt != NULL) {
#if CONFIG_NVS_OTA_PARTITION_SECTOR_COUNT > 0
        fs = nvkey_judge_paratition(NVID_CAN_BE_OTA_BEGIN);
        free_bytes = nvs_calc_free_space(fs);
        if(free_bytes > (ssize_t)(pCmd->minimum_space)){
            fs = nvkey_judge_paratition(NVID_CAN_BE_OTA_END + 1);
            if(free_bytes > (ssize_t)(pCmd->minimum_space)){
                pEvt->status = 1; //follow old proj, return 1 when success.
            }
        }
#else
        settings_storage_get((void **)(&fs));
        free_bytes = nvs_calc_free_space(fs);
        if(free_bytes > (ssize_t)(pCmd->minimum_space)){
            pEvt->status = 1; //follow old proj, return 1 when success.
        }
#endif
        pEvt->status = 0;
    }

    return pEvt;
}


void *RACE_NVKEY_GETALL_HDR(ptr_race_pkt_t pCmdMsg, uint8_t channel_id)
{
    race_nvkey_resp_t *pEvt = NULL;
    int32_t data_item_count = 0;
    size_t size;
    uint32_t length_nvkey_id;
    uint16_t id_idx = 0;
    race_status_t status = RACE_STATUS_OK;

#ifdef RACE_CMD_NVKEY_ENABLE_DEBUG_LOG
    LOG_INF("RACE_NVKEY_GETALL_HDR, channel_id[%d]", channel_id);
#endif

    uint8_t *pData = s_nvkey_buffer;
    while(1){
        size = NVKEY_MAX_DATA_ITEM_SIZE;
        if(nvkey_read_data(id_idx, pData, &size) == NVKEY_STATUS_OK){
            data_item_count++;
        }
        if(id_idx == 0xFFFF){
            break;
        }
        id_idx++;
    }

    length_nvkey_id = data_item_count * sizeof(uint16_t);
    pEvt = RACE_ClaimPacket((uint8_t)RACE_TYPE_RESPONSE, (uint16_t)RACE_NVKEY_GETALL,
                            (uint16_t)(sizeof(race_nvkey_resp_t) + length_nvkey_id), channel_id);
    if (pEvt != NULL) {
        pEvt->nvs_num = (uint16_t)data_item_count;

#ifdef RACE_CMD_NVKEY_ENABLE_DEBUG_LOG
        LOG_INF("data_item_count[%d], length_nvkey_id[%d]", data_item_count, length_nvkey_id);
#endif

        id_idx = 0;
        while(1){
            size = NVKEY_MAX_DATA_ITEM_SIZE;
            if(nvkey_read_data(id_idx, pData, &size) == NVKEY_STATUS_OK){
                --data_item_count;
                if(data_item_count < 0){
                    /* during query all nvkey, some new nvkey was added. */
                    break;
                }
                pEvt->nvs_data[data_item_count] = id_idx;
            }
            id_idx++;
        }

        pEvt->status = status;
        return pEvt;
    } else {
        pEvt = RACE_ClaimPacket((uint8_t)RACE_TYPE_RESPONSE, (uint16_t)RACE_NVKEY_GETALL,
                            (uint16_t)(sizeof(race_nvkey_resp_t) + 1), channel_id);

        if (pEvt != NULL) {
            pEvt->status = RACE_ERRCODE_FAIL;
            pEvt->nvs_num = 0;
            *((uint8_t *)pEvt->nvs_data) = 0;
        } else {
            pEvt = NULL;
        }
        return pEvt;
    }
}

/**
 * RACE_RELOAD_NVKEY_TO_RAM_HDR
 *
 * Notify module to reload data from NVKEY to RAM
 *
 * @p_cmd_msg : pointer of ptr_race_pkt_t
 *
 */
static void *RACE_RELOAD_NVKEY_TO_RAM_HDR(ptr_race_pkt_t p_cmd_msg, uint8_t channel_id)
{
    typedef struct {
        uint8_t status;
    } PACKED race_response_t;

    typedef struct {
        RACE_COMMON_HDR_STRU hdr;
        uint16_t nvkey_id;
    } PACKED race_cmd_t;

    race_response_t *p_response = RACE_ClaimPacket(RACE_TYPE_RESPONSE, RACE_RELOAD_NVKEY_TO_RAM, sizeof(race_response_t), channel_id);
    if (p_response == NULL) {
#ifdef RACE_CMD_NVKEY_ENABLE_DEBUG_LOG
        LOG_ERR("response alloc fail");
#endif
        return NULL;
    }

    race_cmd_t *cmd = (race_cmd_t *)p_cmd_msg;

    uint16_t *p_nvkey_id = (uint16_t *)race_mem_alloc(sizeof(uint16_t));
    if (p_nvkey_id) {
        *p_nvkey_id = cmd->nvkey_id;
        p_response->status = race_send_event_notify_msg(RACE_EVENT_RELOAD_NVKEY_TO_RAM, (void *)p_nvkey_id);
    } else {
#ifdef RACE_CMD_NVKEY_ENABLE_DEBUG_LOG
        LOG_ERR("Cannot malloc p_nvkey_id");
#endif
        p_response->status = RACE_ERRCODE_NOT_ENOUGH_MEMORY;
    }

    return p_response;
}

void *RACE_CmdHandler_NVKEY(ptr_race_pkt_t pRaceHeaderCmd, uint16_t length, uint8_t channel_id)
{
    void *ptr = NULL;

#ifdef RACE_CMD_NVKEY_ENABLE_DEBUG_LOG
    LOG_INF("RACE_CmdHandler_NVKEY, type[0x%X], race_id[0x%X], channel_id[%d]",
                     pRaceHeaderCmd->hdr.type, pRaceHeaderCmd->hdr.id, channel_id);
#endif

    switch (pRaceHeaderCmd->hdr.id) {
        case RACE_NVKEY_READFULLKEY: {
            ptr = RACE_NVKEY_READFULLKEY_HDR(pRaceHeaderCmd, channel_id);
        }
        break;

        case RACE_NVKEY_WRITEFULLKEY: {
            ptr = RACE_NVKEY_WRITEFULLKEY_HDR(pRaceHeaderCmd, channel_id);
        }
        break;

        case RACE_NVKEY_READFULLKEY_RESP_NVID: {
            ptr = RACE_NVKEY_READFULLKEY_RESP_NVID_HDR(pRaceHeaderCmd, channel_id);
        }
        break;

        case RACE_NVKEY_WRITEFULLKEY_RESP_NVID: {
            ptr = RACE_NVKEY_WRITEFULLKEY_RESP_NVID_HDR(pRaceHeaderCmd, channel_id);
        }
        break;

        case RACE_NVKEY_RECLAIM: {
            ptr = RACE_NVKEY_RECLAIM_HDR(pRaceHeaderCmd, channel_id);
        }
        break;

        case RACE_NVKEY_GETALL: {
            ptr = RACE_NVKEY_GETALL_HDR(pRaceHeaderCmd, channel_id);
        }
        break;

        case RACE_RELOAD_NVKEY_TO_RAM: {
            ptr = RACE_RELOAD_NVKEY_TO_RAM_HDR(pRaceHeaderCmd, channel_id);
        }
        break;

        default: {
        }
        break;
    }

    return ptr;
}


#endif /* RACE_NVKEY_CMD_ENABLE */

#elif defined (AIR_BTD_IC_MANDATORY_G1)

#include "race_cmd_feature.h"

#ifdef RACE_NVKEY_CMD_ENABLE

#include "nvkey.h"
#include "air_chip.h"

#include <zephyr/fs/nvs.h>
#include <settings/settings_nvs.h>
#include <zephyr/settings/settings.h>
#include <zephyr/drivers/flash.h>
#include <zephyr/storage/flash_map.h>

#include "race_xport.h"
#include "race_cmd_nvkey.h"
#include "race_event_internal.h"
#include "race_util.h"

#define RACE_CMD_NVKEY_ENABLE_DEBUG_LOG
#define RACE_CMD_NVKEY_CHECK_PERMISSION
// #define RACE_CMD_NVKEY_WHITE_LIST

#define NVKEY_MAX_DATA_ITEM_SIZE 1024

typedef struct {
    RACE_COMMON_HDR_STRU hdr;
    uint16_t nvkey_id;
    uint16_t length_of_read_bytes;
} PACKED race_nvkey_read_cmd_t;

typedef struct {
    uint16_t length_of_read_bytes;
    uint8_t read_data[0];
} PACKED race_nvkey_read_resp_t;

typedef struct {
    RACE_COMMON_HDR_STRU hdr;
    uint16_t nvkey_id;
    uint16_t length_of_read_bytes;
} PACKED race_nvkey_read_more_info_cmd_t;

typedef struct {
    int8_t return_code;
    uint16_t nvkey_id;
    uint16_t length_of_read_bytes;
    uint8_t read_data[0];
} PACKED race_nvkey_read_more_info_resp_t;


typedef struct {
    RACE_COMMON_HDR_STRU hdr;
    uint16_t nvkey_id;
    uint8_t write_data[0];
} PACKED race_nvkey_write_cmd_t;

typedef struct {
    uint8_t return_code;
} PACKED race_nvkey_write_resp_t;

typedef struct {
    RACE_COMMON_HDR_STRU hdr;
    uint16_t nvkey_id;
    uint8_t write_data[0];
} PACKED race_nvkey_write_more_info_cmd_t;

typedef struct {
    uint8_t return_code;
    uint16_t nvkey_id;
} PACKED race_nvkey_write_more_info_resp_t;


typedef struct {
    RACE_COMMON_HDR_STRU hdr;
    uint16_t minimum_space;
} PACKED race_nvkey_space_cmd_t;

typedef struct {
    uint8_t status;
} PACKED race_nvkey_space_resp_t;


typedef struct {
    uint8_t status;
    uint16_t nvs_num;
    uint16_t nvs_data[0];
} PACKED race_nvkey_resp_t;

typedef struct {
    uint16_t start_id;
    uint16_t end_id;
} PACKED race_cmd_nvkey_range_t;

#if RACE_CMD_NVKEY_WHITE_LIST
    const race_cmd_nvkey_range_t s_race_writable_ranges[] = {
        /* start_id, end_id */
    };

    const uint16_t s_race_writable_ids[] = {
        /* nvkey id */
    };

    const race_cmd_nvkey_range_t s_race_readable_ranges[] = {
        /* start_id, end_id */
    };

    const uint16_t s_race_readable_ids[] = {
        /* nvkey id */
    };

    #define NVKEY_WRITE_PERMISSION_RANGE_LIST_LEN               (sizeof(s_race_writable_ranges) / sizeof(s_race_writable_ranges[0]))
    #define NVKEY_WRITE_PERMISSION_LIST_LEN                     (sizeof(s_race_writable_ids) / sizeof(s_race_writable_ids[0]))
    #define NVKEY_READ_PERMISSION_RANGE_LIST_LEN                (sizeof(s_race_readable_ranges) / sizeof(s_race_readable_ranges[0]))
    #define NVKEY_READ_PERMISSION_LIST_LEN                      (sizeof(s_race_readable_ids) / sizeof(s_race_readable_ids[0]))
#else
    const race_cmd_nvkey_range_t s_race_not_writable_ranges[] = {
        /* start_id, end_id */
        { NVID_LOCAL_DEVICES_ADDR_ID_0, NVID_LOCAL_DEVICES_ADDR_ID_7},
        { NVID_GAMING_MODE_PEER_DEVICE_INFO_0, NVID_GAMING_MODE_PEER_DEVICE_INFO_3},
    };

    const uint16_t s_race_not_writable_ids[] = {
        /* nvkey id */
        NVID_BT_HOST_LOCAL_ADDR,

    };

    const race_cmd_nvkey_range_t s_race_not_readable_ranges[] = {
        /* start_id, end_id */
        { NVID_LOCAL_DEVICES_ADDR_ID_0, NVID_LOCAL_DEVICES_ADDR_ID_7},
        { NVID_GAMING_MODE_PEER_DEVICE_INFO_0, NVID_GAMING_MODE_PEER_DEVICE_INFO_3},
    };

    const uint16_t s_race_not_readable_ids[] = {
        /* nvkey id */
        NVID_BT_HOST_LOCAL_ADDR,
    };
    #define NVKEY_WRITE_PERMISSION_RANGE_LIST_LEN               (sizeof(s_race_not_writable_ranges) / sizeof(s_race_not_writable_ranges[0]))
    #define NVKEY_WRITE_PERMISSION_LIST_LEN                     (sizeof(s_race_not_writable_ids) / sizeof(s_race_not_writable_ids[0]))
    #define NVKEY_READ_PERMISSION_RANGE_LIST_LEN                (sizeof(s_race_not_readable_ranges) / sizeof(s_race_not_readable_ranges[0]))
    #define NVKEY_READ_PERMISSION_LIST_LEN                      (sizeof(s_race_not_readable_ids) / sizeof(s_race_not_readable_ids[0]))
#endif /* RACE_CMD_NVKEY_WHITE_LIST */



ATTR_WEAK_SYMBOL bool race_cmd_nvkey_check_writable(uint16_t nvkey_id)
{
#ifdef RACE_CMD_NVKEY_CHECK_PERMISSION
#ifdef AIR_RACE_SET_FACTORY_MODE
    if (race_get_factory_mode() == true) {
        return true;
    }
#endif
    size_t idx;
#if RACE_CMD_NVKEY_WHITE_LIST
    for (idx = 0; idx < NVKEY_WRITE_PERMISSION_RANGE_LIST_LEN; idx++) {
        if ((nvkey_id >= s_race_writable_ranges[idx].start_id) && \
            (nvkey_id <= s_race_writable_ranges[idx].end_id)
        ) {
            return true;
        }
    }
    for (idx = 0; idx < NVKEY_WRITE_PERMISSION_LIST_LEN; idx++) {
        if (nvkey_id == s_race_writable_ids[idx]) {
            return true;
        }
    }
    return false;
#else
    for (idx = 0; idx < NVKEY_WRITE_PERMISSION_RANGE_LIST_LEN; idx++) {
        if ((nvkey_id >= s_race_not_writable_ranges[idx].start_id) && \
            (nvkey_id <= s_race_not_writable_ranges[idx].end_id)
        ) {
            return false;
        }
    }
    for (idx = 0; idx < NVKEY_WRITE_PERMISSION_LIST_LEN; idx++) {
        if (nvkey_id == s_race_not_writable_ids[idx]) {
            return false;
        }
    }
    return true;
#endif /* RACE_CMD_NVKEY_WHITE_LIST */

#else /* RACE_CMD_NVKEY_CHECK_PERMISSION */
    ARG_UNUSED(nvkey_id);
    return true;
#endif
}


ATTR_WEAK_SYMBOL bool race_cmd_nvkey_check_readable(uint16_t nvkey_id)
{
#ifdef RACE_CMD_NVKEY_CHECK_PERMISSION
#ifdef AIR_RACE_SET_FACTORY_MODE
    if (race_get_factory_mode() == true) {
        return true;
    }
#endif
    size_t idx;
#if RACE_CMD_NVKEY_WHITE_LIST
    for (idx = 0; idx < NVKEY_READ_PERMISSION_RANGE_LIST_LEN; idx++) {
        if ((nvkey_id >= s_race_readable_ranges[idx].start_id) && \
            (nvkey_id <= s_race_readable_ranges[idx].end_id)
        ) {
            return true;
        }
    }
    for (idx = 0; idx < NVKEY_READ_PERMISSION_LIST_LEN; idx++) {
        if (nvkey_id == s_race_readable_ids[idx]) {
            return true;
        }
    }
    return false;
#else
    for (idx = 0; idx < NVKEY_READ_PERMISSION_RANGE_LIST_LEN; idx++) {
        if ((nvkey_id >= s_race_not_readable_ranges[idx].start_id) && \
            (nvkey_id <= s_race_not_readable_ranges[idx].end_id)
        ) {
            return false;
        }
    }
    for (idx = 0; idx < NVKEY_READ_PERMISSION_LIST_LEN; idx++) {
        if (nvkey_id == s_race_not_readable_ids[idx]) {
            return false;
        }
    }
    return true;
#endif /* RACE_CMD_NVKEY_WHITE_LIST */

#else /* RACE_CMD_NVKEY_CHECK_PERMISSION */
    ARG_UNUSED(nvkey_id);
    return true;
#endif
}

#if AIR_BTD_IC_PREMIUM_G1
/* To solve the issue of the response of nvkey read command containing extra 0x00,
 * it is necessary to first read the nvkey data into the temporary buffer,
 * then allocate the buffer by race api after knowing the exact length,
 * copy the data to the allocated buffer, and reply it to the tool through race protocol.
 * In Addition, for low power considerations, the buffer needs to be configured
 * with the none retention attribute.
 */
ATTR_ZIDATA_IN_TCM_NONE_RETENTION
#endif
//static uint8_t s_nvkey_buffer[NVKEY_MAX_DATA_ITEM_SIZE];


extern struct nvs_fs* nvkey_judge_paratition(uint16_t id);

void *RACE_NVKEY_READFULLKEY_HDR(ptr_race_pkt_t pCmdMsg, uint8_t channel_id)
{
#ifdef RACE_CMD_NVKEY_ENABLE_DEBUG_LOG
    LOG_INF("RACE_NVKEY_READFULLKEY_HDR, channel_id[%d]", channel_id);
#endif

    race_nvkey_read_cmd_t *pCmd = (race_nvkey_read_cmd_t *)pCmdMsg;
    race_nvkey_read_resp_t *pEvt = NULL;
    uint32_t size = NVKEY_MAX_DATA_ITEM_SIZE;
    nvkey_status_t status = NVKEY_STATUS_ERROR;
    bool permission_allowed = false;
    uint8_t *pmem_nvkey = NULL;

    permission_allowed = race_cmd_nvkey_check_readable(pCmd->nvkey_id);
    if (permission_allowed) {
        pmem_nvkey = race_mem_alloc(NVKEY_MAX_DATA_ITEM_SIZE);
        if (pmem_nvkey != NULL) {
            status = nvkey_read_data(pCmd->nvkey_id, (uint8_t *)pmem_nvkey, &size);
        } else {
            #ifdef RACE_CMD_NVKEY_ENABLE_DEBUG_LOG
            LOG_INF("RACE_NVKEY_READFULLKEY_HDR: race malloc 1KB mem fail");
            #endif
            status = NVKEY_STATUS_MALLOC_ERROR;
        }
    } else {
        status = NVKEY_STATUS_PERMISSION_DENIED;
    }

    if (status != NVKEY_STATUS_OK) {
#ifdef RACE_CMD_NVKEY_ENABLE_DEBUG_LOG
        LOG_ERR("nvkey_read_data fail(%d), nvkey_id[0x%x]", status, pCmd->nvkey_id);
#endif
        pEvt = RACE_ClaimPacket((uint8_t)RACE_TYPE_RESPONSE, (uint16_t)RACE_NVKEY_READFULLKEY,
                    (uint16_t)(sizeof(race_nvkey_read_resp_t) + 0), channel_id);
        if (pEvt) {
            pEvt->length_of_read_bytes = 0;
        } else {
#ifdef RACE_CMD_NVKEY_ENABLE_DEBUG_LOG
            LOG_ERR("RACE_ClaimPacket fail, nvkey_id[0x%x]", pCmd->nvkey_id);
#endif
        }
    } else {
        /* when the status is NVKEY_STATUS_OK, we got the right size of the nvkey item */
        LOG_INF("nvkey_read_data pass with size %d, length of read bytes: %d", (int)size, (int)(pCmd->length_of_read_bytes));
        size = (size <= pCmd->length_of_read_bytes) ? size : pCmd->length_of_read_bytes;
        pEvt = RACE_ClaimPacket((uint8_t)RACE_TYPE_RESPONSE, (uint16_t)RACE_NVKEY_READFULLKEY,
                    (uint16_t)(sizeof(race_nvkey_read_resp_t) + size), channel_id);

        if (pEvt) {
            memcpy((void *)pEvt->read_data, (void *)pmem_nvkey, size);
            pEvt->length_of_read_bytes = size;
        } else {
#ifdef RACE_CMD_NVKEY_ENABLE_DEBUG_LOG
            LOG_ERR("RACE_ClaimPacket fail, nvkey_id[0x%x]", pCmd->nvkey_id);
#endif
        }
        if (pmem_nvkey) {
            race_mem_free(pmem_nvkey);
            pmem_nvkey = NULL;
        }
    }
    return pEvt;
}

void *RACE_NVKEY_READFULLKEY_RESP_NVID_HDR(ptr_race_pkt_t pCmdMsg, uint8_t channel_id)
{
#ifdef RACE_CMD_NVKEY_ENABLE_DEBUG_LOG
    LOG_INF("RACE_NVKEY_READFULLKEY_RESP_NVID_HDR, channel_id[%d]", channel_id);
#endif

    race_nvkey_read_more_info_cmd_t *pCmd = (race_nvkey_read_more_info_cmd_t *)pCmdMsg;
    race_nvkey_read_more_info_resp_t *pEvt = NULL;
    uint32_t size = NVKEY_MAX_DATA_ITEM_SIZE;
    nvkey_status_t status = NVKEY_STATUS_ERROR;
    bool permission_allowed = false;
    uint8_t *pmem_nvkey = NULL;

    permission_allowed = race_cmd_nvkey_check_readable(pCmd->nvkey_id);
    if(permission_allowed){
        pmem_nvkey = race_mem_alloc(NVKEY_MAX_DATA_ITEM_SIZE);
        if (pmem_nvkey != NULL) {
            status = nvkey_read_data(pCmd->nvkey_id, (uint8_t *)pmem_nvkey, &size);
        } else {
            #ifdef RACE_CMD_NVKEY_ENABLE_DEBUG_LOG
            LOG_INF("RACE_NVKEY_READFULLKEY_HDR: race malloc 1KB mem fail");
            #endif
            status = NVKEY_STATUS_MALLOC_ERROR;
        }
    } else {
        status = NVKEY_STATUS_PERMISSION_DENIED;
    }

    if (status != NVKEY_STATUS_OK) {
#ifdef RACE_CMD_NVKEY_ENABLE_DEBUG_LOG
        LOG_ERR("nvkey_read_data fail(%d), nvkey_id[0x%x]", status, pCmd->nvkey_id);
#endif
        pEvt = RACE_ClaimPacket((uint8_t)RACE_TYPE_RESPONSE, (uint16_t)RACE_NVKEY_READFULLKEY_RESP_NVID,
                        (uint16_t)(sizeof(race_nvkey_read_more_info_resp_t) + 0), channel_id);
        if (pEvt) {
            pEvt->return_code = (int8_t)status;
            pEvt->nvkey_id = pCmd->nvkey_id;
            pEvt->length_of_read_bytes = 0;
        } else {
#ifdef RACE_CMD_NVKEY_ENABLE_DEBUG_LOG
            LOG_ERR("RACE_ClaimPacket fail, nvkey_id[0x%x]", pCmd->nvkey_id);
#endif
        }
    } else {
        /* when the status is NVKEY_STATUS_OK, we got the right size of the nvkey item */
        LOG_INF("nvkey_read_data pass with size %d, length of read bytes: %d", (int)size, (int)(pCmd->length_of_read_bytes));
        size = (size <= pCmd->length_of_read_bytes) ? size : pCmd->length_of_read_bytes;
        pEvt = RACE_ClaimPacket((uint8_t)RACE_TYPE_RESPONSE, (uint16_t)RACE_NVKEY_READFULLKEY_RESP_NVID,
                    (uint16_t)(sizeof(race_nvkey_read_more_info_resp_t) + size), channel_id);

        if (pEvt) {
            memcpy((void *)pEvt->read_data, (void *)pmem_nvkey, size);
            pEvt->return_code = (int8_t)status;
            pEvt->nvkey_id = pCmd->nvkey_id;
            pEvt->length_of_read_bytes = size;
        } else {
#ifdef RACE_CMD_NVKEY_ENABLE_DEBUG_LOG
            LOG_ERR("RACE_ClaimPacket fail, nvkey_id[0x%x]", pCmd->nvkey_id);
#endif
        }
        if (pmem_nvkey) {
            race_mem_free(pmem_nvkey);
            pmem_nvkey = NULL;
        }
    }
    return pEvt;
}

void *RACE_NVKEY_WRITEFULLKEY_HDR(ptr_race_pkt_t pCmdMsg, uint8_t channel_id)
{
#ifdef RACE_CMD_NVKEY_ENABLE_DEBUG_LOG
    LOG_INF("RACE_NVKEY_WRITEFULLKEY_HDR, channel_id[%d]", channel_id);
#endif

    uint32_t nvkey_length = 0, size = 0, i;
    nvkey_status_t status = NVKEY_STATUS_ERROR;
    bool permission_allowed = false;

    race_nvkey_write_cmd_t *pCmd = (race_nvkey_write_cmd_t *)pCmdMsg;

    race_nvkey_write_resp_t *pEvt = (race_nvkey_write_resp_t *)RACE_ClaimPacket((uint8_t)RACE_TYPE_RESPONSE,
                                        (uint16_t)RACE_NVKEY_WRITEFULLKEY, (uint16_t)(sizeof(race_nvkey_write_resp_t)), channel_id);

    if (pEvt != NULL) {
        permission_allowed = race_cmd_nvkey_check_writable(pCmd->nvkey_id);
        if(permission_allowed){
            nvkey_length = pCmd->hdr.length - sizeof(pCmd->hdr.id) - sizeof(pCmd->nvkey_id);
            status = nvkey_write_data(pCmd->nvkey_id, pCmd->write_data, nvkey_length);
        } else {
            status = NVKEY_STATUS_PERMISSION_DENIED;
        }

        if (status == NVKEY_STATUS_OK) {
            uint8_t *pData = NULL;

            size = nvkey_length;
            pData = (uint8_t *)race_mem_alloc(nvkey_length);
            if (pData == NULL) {
#ifdef RACE_CMD_NVKEY_ENABLE_DEBUG_LOG
                LOG_ERR("race_mem_alloc fail");
#endif
                pEvt->return_code = NVKEY_STATUS_ERROR;
                return pEvt;
            }
            status = nvkey_read_data(pCmd->nvkey_id, (uint8_t *)pData, &size);

            if (status == NVKEY_STATUS_OK) {
                for (i = 0; i < size; i++) {
                    if (pData[i] != pCmd->write_data[i]) {
                        LOG_ERR("nvkey compare fail, nvkey_id[0x%X], write_data[0x%X], read_data[0x%X]",
                                    pCmd->nvkey_id, pCmd->write_data[i], pData[i]);
                        status = RACE_STATUS_ERROR;
                    }
                }
                pEvt->return_code = (int8_t)status;
            } else {
#ifdef RACE_CMD_NVKEY_ENABLE_DEBUG_LOG
                LOG_ERR("read nvkey fail, nvkey_status[%d]", status);
#endif
                pEvt->return_code = (int8_t)status;
            }
            race_mem_free(pData);
        } else {
#ifdef RACE_CMD_NVKEY_ENABLE_DEBUG_LOG
            LOG_ERR("write nvkey fail, nvkey_status[%d]", status);
#endif
            pEvt->return_code = (int8_t)status;
        }
    }

    return pEvt;
}

void *RACE_NVKEY_WRITEFULLKEY_RESP_NVID_HDR(ptr_race_pkt_t pCmdMsg, uint8_t channel_id)
{
#ifdef RACE_CMD_NVKEY_ENABLE_DEBUG_LOG
    LOG_INF("RACE_NVKEY_WRITEFULLKEY_RESP_NVID_HDR, channel_id[%d]", channel_id);
#endif

    uint32_t nvkey_length;
    nvkey_status_t status;
    uint32_t size;
    uint8_t *pData;
    uint32_t i;
    bool permission_allowed = false;

    race_nvkey_write_more_info_cmd_t *pCmd = (race_nvkey_write_more_info_cmd_t *)pCmdMsg;

    race_nvkey_write_more_info_resp_t *pEvt = (race_nvkey_write_more_info_resp_t *)RACE_ClaimPacket((uint8_t)RACE_TYPE_RESPONSE,
                                                (uint16_t)RACE_NVKEY_WRITEFULLKEY_RESP_NVID,
                                                (uint16_t)(sizeof(race_nvkey_write_more_info_resp_t)),
                                                channel_id);

    if (pEvt != NULL) {
        pEvt->nvkey_id = pCmd->nvkey_id;
        pEvt->return_code = RACE_ERRCODE_FAIL;
        permission_allowed = race_cmd_nvkey_check_writable(pCmd->nvkey_id);
        if(permission_allowed){
            nvkey_length = pCmd->hdr.length - sizeof(pCmd->hdr.id) - sizeof(pCmd->nvkey_id);
            status = nvkey_write_data(pCmd->nvkey_id, pCmd->write_data, nvkey_length);
        } else {
            status = NVKEY_STATUS_PERMISSION_DENIED;
        }

        if (status == NVKEY_STATUS_OK) {
#ifdef RACE_CMD_NVKEY_ENABLE_DEBUG_LOG
            LOG_INF("NVKEY Write Done, Read NVKEY and compare Data");
#endif

            size = nvkey_length;
            pData = (uint8_t *)race_mem_alloc(size);
            /* check whether memory was allocated successfully */
            if (pData == NULL){
                pEvt->return_code = RACE_ERRCODE_NOT_ENOUGH_MEMORY;
            } else {
                status = nvkey_read_data(pCmd->nvkey_id, (uint8_t *)pData, &size);

                if (status == NVKEY_STATUS_OK) {
                    for (i = 0; i < size; i++) {
                        if (pData[i] != pCmd->write_data[i]) {
                            LOG_ERR("nvkey data different, nvkey[0x%X], [0x%X] != [0x%X]", pCmd->nvkey_id, pData[i], pCmd->write_data[i]);
                            status = NVKEY_STATUS_ERROR;
                            break;
                        }
                    }
                    if (status == NVKEY_STATUS_ERROR) {
                        pEvt->return_code = RACE_ERRCODE_FAIL;
                    } else {
                        pEvt->return_code = RACE_ERRCODE_SUCCESS;
                    }
                }
                race_mem_free(pData);
            }
        } else {
#ifdef RACE_CMD_NVKEY_ENABLE_DEBUG_LOG
            LOG_ERR("write nvkey with id response fail, nvkey_status[%d]", status);
#endif
            /* fix Overflowed constant (INTEGER_OVERFLOW) issue */
            pEvt->return_code = (uint8_t)status;
        }
    }

    return pEvt;
}

/**
 * RACE_NVKEY_RECLAIM_HDR
 *
 * RACE NVKEY RECLAIM Handler
 *
 *
 * @pCmdMsg : pointer of ptr_race_pkt_t
 *
 */
void *RACE_NVKEY_RECLAIM_HDR(ptr_race_pkt_t pCmdMsg, uint8_t channel_id)
{
#ifdef RACE_CMD_NVKEY_ENABLE_DEBUG_LOG
    LOG_INF("RACE_NVKEY_RECLAIM_HDR, channel_id[%d]", channel_id);
#endif

    race_nvkey_space_cmd_t *pCmd = (race_nvkey_space_cmd_t *)pCmdMsg;
    race_nvkey_space_resp_t *pEvt = NULL;
    struct nvs_fs* fs;
    ssize_t free_bytes;

    pEvt = RACE_ClaimPacket((uint8_t)RACE_TYPE_RESPONSE, (uint16_t)RACE_NVKEY_RECLAIM,
                            (uint16_t)(sizeof(race_nvkey_space_resp_t)), channel_id);
    if (pEvt != NULL) {
#if CONFIG_NVS_OTA_PARTITION_SECTOR_COUNT > 0
        fs = nvkey_judge_paratition(NVID_CAN_BE_OTA_BEGIN);
        free_bytes = nvs_calc_free_space(fs);
        if(free_bytes > (ssize_t)(pCmd->minimum_space)){
            fs = nvkey_judge_paratition(NVID_CAN_BE_OTA_END + 1);
            if(free_bytes > (ssize_t)(pCmd->minimum_space)){
                pEvt->status = 1; //follow old proj, return 1 when success.
            }
        }
#else
        settings_storage_get((void **)(&fs));
        free_bytes = nvs_calc_free_space(fs);
        if(free_bytes > (ssize_t)(pCmd->minimum_space)){
            pEvt->status = 1; //follow old proj, return 1 when success.
        }
#endif
        pEvt->status = 0;
    }
    return pEvt;
}


void *RACE_NVKEY_GETALL_HDR(ptr_race_pkt_t pCmdMsg, uint8_t channel_id)
{
    race_nvkey_resp_t *pEvt = NULL;
    int32_t data_item_count = 0;
    size_t size;
    uint32_t length_nvkey_id;
    uint16_t id_idx = 0;
    race_status_t status = RACE_STATUS_OK;
    uint8_t *pmem_nvkey = NULL;

#ifdef RACE_CMD_NVKEY_ENABLE_DEBUG_LOG
    LOG_INF("RACE_NVKEY_GETALL_HDR, channel_id[%d]", channel_id);
#endif

    pmem_nvkey = race_mem_alloc(NVKEY_MAX_DATA_ITEM_SIZE);
    if (pmem_nvkey ==NULL) {
#ifdef RACE_CMD_NVKEY_ENABLE_DEBUG_LOG
        LOG_INF("RACE_NVKEY_GETALL_HDR: malloc 1k mem fail");
#endif
        return NULL;
    }

    while(1){
        size = NVKEY_MAX_DATA_ITEM_SIZE;
        if(nvkey_read_data(id_idx, pmem_nvkey, &size) == NVKEY_STATUS_OK){
            data_item_count++;
        }
        if(id_idx == 0xFFFF){
            break;
        }
        id_idx++;
    }

    length_nvkey_id = data_item_count * sizeof(uint16_t);
    pEvt = RACE_ClaimPacket((uint8_t)RACE_TYPE_RESPONSE, (uint16_t)RACE_NVKEY_GETALL,
                            (uint16_t)(sizeof(race_nvkey_resp_t) + length_nvkey_id), channel_id);
    if (pEvt != NULL) {
        pEvt->nvs_num = (uint16_t)data_item_count;

#ifdef RACE_CMD_NVKEY_ENABLE_DEBUG_LOG
        LOG_INF("data_item_count[%d], length_nvkey_id[%d]", data_item_count, length_nvkey_id);
#endif

        id_idx = 0;
        while(1){
            size = NVKEY_MAX_DATA_ITEM_SIZE;
            if(nvkey_read_data(id_idx, pmem_nvkey, &size) == NVKEY_STATUS_OK){
                --data_item_count;
                if(data_item_count < 0){
                    /* during query all nvkey, some new nvkey was added. */
                    break;
                }
                pEvt->nvs_data[data_item_count] = id_idx;
            }
            id_idx++;
        }

        pEvt->status = status;
    } else {
        pEvt = RACE_ClaimPacket((uint8_t)RACE_TYPE_RESPONSE, (uint16_t)RACE_NVKEY_GETALL,
                            (uint16_t)(sizeof(race_nvkey_resp_t) + 1), channel_id);

        if (pEvt != NULL) {
            pEvt->status = RACE_ERRCODE_FAIL;
            pEvt->nvs_num = 0;
            *((uint8_t *)pEvt->nvs_data) = 0;
        } else {
            pEvt = NULL;
        }
    }
    if (pmem_nvkey != NULL) {
        race_mem_free(pmem_nvkey);
        pmem_nvkey = NULL;
    }
    return pEvt;
}

/**
 * RACE_RELOAD_NVKEY_TO_RAM_HDR
 *
 * Notify module to reload data from NVKEY to RAM
 *
 * @p_cmd_msg : pointer of ptr_race_pkt_t
 *
 */
static void *RACE_RELOAD_NVKEY_TO_RAM_HDR(ptr_race_pkt_t p_cmd_msg, uint8_t channel_id)
{
    typedef struct {
        uint8_t status;
    } PACKED race_response_t;

    typedef struct {
        RACE_COMMON_HDR_STRU hdr;
        uint16_t nvkey_id;
    } PACKED race_cmd_t;

    race_response_t *p_response = RACE_ClaimPacket(RACE_TYPE_RESPONSE, RACE_RELOAD_NVKEY_TO_RAM, sizeof(race_response_t), channel_id);
    if (p_response == NULL) {
#ifdef RACE_CMD_NVKEY_ENABLE_DEBUG_LOG
        LOG_ERR("response alloc fail");
#endif
        return NULL;
    }

    race_cmd_t *cmd = (race_cmd_t *)p_cmd_msg;

    uint16_t *p_nvkey_id = (uint16_t *)race_mem_alloc(sizeof(uint16_t));
    if (p_nvkey_id) {
        *p_nvkey_id = cmd->nvkey_id;
        p_response->status = race_send_event_notify_msg(RACE_EVENT_RELOAD_NVKEY_TO_RAM, (void *)p_nvkey_id);
    } else {
#ifdef RACE_CMD_NVKEY_ENABLE_DEBUG_LOG
        LOG_ERR("Cannot malloc p_nvkey_id");
#endif
        p_response->status = RACE_ERRCODE_NOT_ENOUGH_MEMORY;
    }

    return p_response;
}

void *RACE_CmdHandler_NVKEY(ptr_race_pkt_t pRaceHeaderCmd, uint16_t length, uint8_t channel_id)
{
    void *ptr = NULL;

#ifdef RACE_CMD_NVKEY_ENABLE_DEBUG_LOG
    LOG_INF("RACE_CmdHandler_NVKEY, type[0x%X], race_id[0x%X], channel_id[%d]",
                     pRaceHeaderCmd->hdr.type, pRaceHeaderCmd->hdr.id, channel_id);
#endif

    switch (pRaceHeaderCmd->hdr.id) {
        case RACE_NVKEY_READFULLKEY: {
            ptr = RACE_NVKEY_READFULLKEY_HDR(pRaceHeaderCmd, channel_id);
        }
        break;

        case RACE_NVKEY_WRITEFULLKEY: {
            ptr = RACE_NVKEY_WRITEFULLKEY_HDR(pRaceHeaderCmd, channel_id);
        }
        break;

        case RACE_NVKEY_READFULLKEY_RESP_NVID: {
            ptr = RACE_NVKEY_READFULLKEY_RESP_NVID_HDR(pRaceHeaderCmd, channel_id);
        }
        break;

        case RACE_NVKEY_WRITEFULLKEY_RESP_NVID: {
            ptr = RACE_NVKEY_WRITEFULLKEY_RESP_NVID_HDR(pRaceHeaderCmd, channel_id);
        }
        break;

        case RACE_NVKEY_RECLAIM: {
            ptr = RACE_NVKEY_RECLAIM_HDR(pRaceHeaderCmd, channel_id);
        }
        break;

        case RACE_NVKEY_GETALL: {
            ptr = RACE_NVKEY_GETALL_HDR(pRaceHeaderCmd, channel_id);
        }
        break;

        case RACE_RELOAD_NVKEY_TO_RAM: {
            ptr = RACE_RELOAD_NVKEY_TO_RAM_HDR(pRaceHeaderCmd, channel_id);
        }
        break;

        default: {
        }
        break;
    }

    return ptr;
}


#endif /* RACE_NVKEY_CMD_ENABLE */

#endif
