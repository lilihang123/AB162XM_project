/* Copyright Statement:
 *
 * (C) 2017  Airoha Technology Corp. All rights reserved.
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



#include "race_cmd_feature.h"
#ifdef RACE_STORAGE_CMD_ENABLE

#include "race_cmd_storage.h"
#include "race_storage_access.h"
#include "race_storage_util.h"
#include "race_noti.h"
#include "bsp_flash.h"
#include "hal_nvic.h"
#include "soc.h"
#include "race_port_bt.h"
// #define RACE_CMD_STORAGE_ENABLE_DEBUG_LOG


////////////////////////////////////////////////////////////////////////////////
// Constant Definitions ////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/* Race support maximum buffer is 1024 bytes,  support: race header + 3 * 256 byes  */
#define MAX_NUMBER_OF_READ_PAGE  (3)
/* Race cmd length   */
#define RACE_HEAD_LENGTH         (4)
/* SFC with flash*/
#define SFC_FLASH                (0)
/* SPI with flash */
#define SPI_FLASH                (1)

//////////////////////////////////////////////////////////////////////////////
// Global Variables ////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// FUNCTION DECLARATIONS /////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void *race_cmdhdl_storage_write_byte(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint16_t length, uint8_t channel_id)
{
    typedef struct {
        RACE_COMMON_HDR_STRU cmdhdr;
        uint8_t storage_type;
        uint16_t data_length;
        uint32_t storage_address;
        uint8_t data[1];
    } PACKED CMD;

    typedef struct {
        uint8_t status;
        uint8_t storage_type;
        uint16_t data_lenght;
        uint32_t storage_address;
    } PACKED RSP;

    int32_t ret = RACE_ERRCODE_FAIL;
    CMD *pCmd = (CMD *)pCmdMsg;
    if (length != (sizeof(CMD) - RACE_HEAD_LENGTH) || (pCmd->storage_type != SFC_FLASH && pCmd->storage_type != SPI_FLASH)) {
        //CMD length is wrong.
        return NULL;
    }
    RSP *pEvt = RACE_ClaimPacketAppID(pCmdMsg->pktId.field.app_id,
                                      RACE_TYPE_RESPONSE,
                                      RACE_STORAGE_WRITE_BYTE,
                                      sizeof(RSP),
                                      channel_id);
    if (pEvt) {
        ret = race_storage_is_addr_accessible(pCmd->storage_type, pCmd->storage_address, pCmd->data_length);
        if (RACE_ERRCODE_SUCCESS == ret) {
            ret = race_storage_write(pCmd->storage_address,
                                     pCmd->data,
                                     pCmd->data_length,
                                     pCmd->storage_type);
        }

        pEvt->status = ret;
    }

    return pEvt;
}

/*
    old architecture:
        command parameter number_of_page is not used, apk always set 1 to read one page, return page number always is 0.
    new architecture:
        command parameter number_of_page is used, apk can set it to read multiple pages.
*/
void *race_cmdhdl_storage_read_page(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint16_t length, uint8_t channel_id)
{
    typedef struct {
        RACE_COMMON_HDR_STRU cmdhdr;
        uint8_t storage_type;
        uint8_t number_of_page;
        uint32_t storage_address;
    } PACKED CMD;

    typedef struct {
        uint8_t status;
        uint8_t storage_type;
        uint8_t number_of_the_rest_page;
        uint8_t crc;
        uint32_t storage_address;
        uint8_t data[256 * MAX_NUMBER_OF_READ_PAGE];
    } PACKED RSP;

    int32_t ret = RACE_ERRCODE_FAIL;
    CMD *pCmd = (CMD *)pCmdMsg;
    if (length != (sizeof(CMD) - RACE_HEAD_LENGTH) || (pCmd->storage_type != SFC_FLASH && pCmd->storage_type != SPI_FLASH)) {
        //CMD length is wrong.
        return NULL;
    }
    RSP *pEvt = RACE_ClaimPacketAppID(pCmdMsg->pktId.field.app_id,
                                      RACE_TYPE_RESPONSE,
                                      RACE_STORAGE_READ_PAGE,
                                      sizeof(RSP) - 256 * (MAX_NUMBER_OF_READ_PAGE - pCmd->number_of_page),
                                      channel_id);

    if (pEvt) {
        if (pCmd->number_of_page > MAX_NUMBER_OF_READ_PAGE || pCmd->number_of_page == 0) {
            pEvt->status = RACE_ERRCODE_PARAMETER_ERROR;
        } else {
            pEvt->storage_type = pCmd->storage_type;
            pEvt->number_of_the_rest_page = 0;
            pEvt->storage_address = pCmd->storage_address;

            ret = race_storage_is_addr_accessible(pCmd->storage_type, pCmd->storage_address, (256 * pCmd->number_of_page));
            if (RACE_ERRCODE_SUCCESS == ret) {
                ret = race_storage_read(pCmd->storage_address,
                                    pEvt->data,
                                    (256 * pCmd->number_of_page),
                                    pCmd->storage_type);
            }
            pEvt->status = ret;
        }
    }

    return pEvt;
}


bool race_storage_data_check(PTR_RACE_COMMON_HDR_STRU pCmdMsg)
{
    typedef struct {
        uint8_t crc;
        uint32_t storage_addr;
        uint8_t data[256];
    } PACKED race_storage_page_info_struct;

    typedef struct {
        RACE_COMMON_HDR_STRU cmdhdr;
        uint8_t storage_type;
        uint8_t page_count;
        race_storage_page_info_struct page_info[0]; /* array size: page_count */
    } PACKED CMD;

    bool crc_pass = true;
    CMD *pCmd = (CMD *)pCmdMsg;
    uint8_t crc8 = 0;
    int32_t ret = RACE_ERRCODE_FAIL;
    int i;

    for (i = 0; i < pCmd->page_count; i++) {
        ret = race_storage_crc8_generate(&crc8,
                                         (uint32_t)pCmd->page_info[i].data,
                                         256,
                                         pCmd->storage_type);

        if ((RACE_ERRCODE_SUCCESS != ret) ||
            (crc8 != pCmd->page_info[i].crc)
           ) {
#ifdef RACE_CMD_STORAGE_ENABLE_DEBUG_LOG
            LOG_INF("race_storage_data_check: crc8( addr: 0x%08X ) not match! i:%d crc_trans:%x crc_calc:%x",
                             pCmd->page_info[i].storage_addr, i,
                             pCmd->page_info[i].crc, crc8);
#endif
            crc_pass = false;
        }
    }
    return crc_pass;
}

void *race_cmdhdl_storage_write_page(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint16_t length, uint8_t channel_id)
{

    typedef struct {
        uint8_t crc;
        uint32_t storage_addr;
        uint8_t data[256];
    } PACKED race_storage_page_info_struct;

    typedef struct {
        RACE_COMMON_HDR_STRU cmdhdr;
        uint8_t storage_type;
        uint8_t page_count;
        race_storage_page_info_struct page_info[0]; /* array size: page_count */
    } PACKED CMD;

    typedef struct {
        uint8_t status;
        uint8_t storage_type;
        uint8_t completed_page_count;
        uint32_t storage_address[0];    /* array size: completed_page_count */
    } PACKED RSP;

    int32_t ret = RACE_ERRCODE_FAIL, ret_val = RACE_ERRCODE_SUCCESS;
    CMD *pCmd = (CMD *)pCmdMsg;
    RSP *pEvt = NULL;
    uint32_t i = 0, idx = 0;
    uint8_t crc8 = 0;
    uint32_t storage_address[4] = {0};

    if (pCmd == NULL || pCmd->page_count == 0) {
        return NULL;
    }

    if (length != (sizeof(CMD) - RACE_HEAD_LENGTH + (pCmd->page_count) * sizeof(race_storage_page_info_struct))
         || (pCmd->storage_type != SFC_FLASH && pCmd->storage_type != SPI_FLASH)) {
        //CMD length is wrong.
        LOG_ERR("write_page length error length = %x, %x", length, pCmd->page_count);
        return NULL;
    }
    if (pCmd) {
        pEvt = RACE_ClaimPacketAppID(pCmdMsg->pktId.field.app_id,
                                     RACE_TYPE_RESPONSE,
                                     RACE_STORAGE_WRITE_PAGE,
                                     sizeof(RSP) + pCmd->page_count * sizeof(uint32_t),
                                     channel_id);
        if (!pEvt) {
            return NULL;
        }

        pEvt->completed_page_count = 0;

        for (i = 0; i < pCmd->page_count; i++) {
            //printk("Page %d Storage Address: %x\n", i, pCmd->page_info[i].storage_addr);
            storage_address[i] = pCmd->page_info[i].storage_addr;
            ret = race_storage_crc8_generate(&crc8,
                                             (uint32_t)pCmd->page_info[i].data,
                                             256,
                                             pCmd->storage_type);

            if (RACE_ERRCODE_SUCCESS != ret || crc8 != pCmd->page_info[i].crc) {
                ret_val = RACE_ERRCODE_CONFLICT;
                LOG_ERR("crc8( addr: 0x%08X ) not match! i:%d crc_trans:%x crc_calc:%x",
                                 pCmd->page_info[i].storage_addr, i,
                                 pCmd->page_info[i].crc, crc8);
                ret = RACE_ERRCODE_CONFLICT;
                break;
            }
        }

        memcpy(pEvt->storage_address, &storage_address, pCmd->page_count * sizeof(uint32_t));
        if (ret_val == RACE_ERRCODE_CONFLICT) {
            for (i = 0; i < pCmd->page_count; i++) {
                LOG_ERR("RACE_STORAGE_WRITE_PAGE Para[%d]: CRC8: 0x%02X, ADDR: 0x%08X",
                                 i, pCmd->page_info[i].crc, pCmd->page_info[i].storage_addr);
                for (idx = 0; idx < 256; idx += 16) {
                    LOG_ERR("RACE_STORAGE_WRITE_PAGE Data[%d]: 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X",
                                     i,
                                     pCmd->page_info[i].data[idx], pCmd->page_info[i].data[idx + 1], pCmd->page_info[i].data[idx + 2], pCmd->page_info[i].data[idx + 3],
                                     pCmd->page_info[i].data[idx + 4], pCmd->page_info[i].data[idx + 5], pCmd->page_info[i].data[idx + 6], pCmd->page_info[i].data[idx + 7],
                                     pCmd->page_info[i].data[idx + 8], pCmd->page_info[i].data[idx + 9], pCmd->page_info[i].data[idx + 10], pCmd->page_info[i].data[idx + 11],
                                     pCmd->page_info[i].data[idx + 12], pCmd->page_info[i].data[idx + 13], pCmd->page_info[i].data[idx + 14], pCmd->page_info[i].data[idx + 15]
                                    );
                }
            }
        }

        if (RACE_ERRCODE_SUCCESS == ret_val) {
            for (i = 0; i < pCmd->page_count; i++) {
                ret = race_storage_is_addr_accessible(pCmd->storage_type,
                                                      pCmd->page_info[i].storage_addr,
                                                      256);
                if (RACE_ERRCODE_SUCCESS == ret) {
                    ret = race_storage_write(pCmd->page_info[i].storage_addr,
                                             pCmd->page_info[i].data,
                                             256,
                                             pCmd->storage_type);

                    if (RACE_ERRCODE_SUCCESS == ret) {
                        pEvt->completed_page_count++;
                    } else {
                        ret_val = RACE_ERRCODE_FAIL;
                        break;
                    }
                }
            }
        }
        else {
            ret_val = ret;
        }

        pEvt->storage_type = pCmd->storage_type;
        if (0 == pCmd->page_count) {
            ret_val = RACE_ERRCODE_PARAMETER_ERROR;
        }
        pEvt->status = ret_val;
    }

    return pEvt;
}

/* Send the Noti */
RACE_ERRCODE race_storage_erase_partition_cmd_cb(uint8_t status,
                                                 uint8_t storage_type,
                                                 uint32_t partition_length,
                                                 uint32_t partition_address,
                                                 uint8_t app_id,
                                                 uint8_t channel_id,
                                                 bool noti_delay,
                                                 void *user_data)
{
    race_storage_erase_partition_noti_struct *noti = NULL;
    RACE_ERRCODE ret = RACE_ERRCODE_FAIL;

    noti = RACE_ClaimPacketAppID(app_id,
                                 RACE_TYPE_NOTIFICATION,
                                 RACE_STORAGE_ERASE_PARTITION,
                                 sizeof(race_storage_erase_partition_noti_struct),
                                 channel_id);

    if (noti) {
        noti->status = status;
        noti->storage_type = storage_type;
        noti->partition_length = partition_length;
        noti->partition_address = partition_address;

        ret = race_noti_send((void *)noti,
                             channel_id,
                             noti_delay);
        if (RACE_ERRCODE_SUCCESS != ret) {
#ifdef RACE_CMD_STORAGE_ENABLE_DEBUG_LOG
            LOG_WRN("Lost a RACE_STORAGE_ERASE_PARTITION noti, ret:%d", ret);
#endif
            RACE_FreePacket((void *)noti);
        }
    } else {
        ret = RACE_ERRCODE_NOT_ENOUGH_MEMORY;
#ifdef RACE_CMD_STORAGE_ENABLE_DEBUG_LOG
        LOG_WRN("Lost a RACE_STORAGE_ERASE_PARTITION noti, ret:%d", ret);
#endif
    }

    return ret;
}


void *race_cmdhdl_storage_erase_partition(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint16_t length, uint8_t channel_id)
{
    typedef struct {
        RACE_COMMON_HDR_STRU Hdr;
        uint8_t storage_type;
        uint32_t partition_length;
        uint32_t partition_address;
    } PACKED CMD;

    typedef struct {
        uint8_t status;
    } PACKED RSP;

    int32_t ret = RACE_ERRCODE_FAIL;
    uint32_t saved_mask;
    (void)saved_mask;
    CMD *pCmd = (CMD *)pCmdMsg;

    if (length != (sizeof(CMD) - RACE_HEAD_LENGTH) || (pCmd->storage_type != SFC_FLASH && pCmd->storage_type != SPI_FLASH)) {
        //CMD length is wrong.
        return NULL;
    }
    RSP *pEvt = RACE_ClaimPacketAppID(pCmdMsg->pktId.field.app_id,
                                      RACE_TYPE_RESPONSE,
                                      RACE_STORAGE_ERASE_PARTITION,
                                      sizeof(RSP),
                                      channel_id);
    if (pEvt) {
        ret = race_storage_is_addr_accessible(pCmd->storage_type,
                                              pCmd->partition_address,
                                              pCmd->partition_length);
        if (RACE_ERRCODE_SUCCESS == ret) {
            /* Execute the cmd */
/*only non-bt channel race cmd will execute this */
#if defined(AIR_BT_AIR_SERVICE_ENABLE)
            if (!RACE_PORT_IS_BLE(channel_id))
#endif
            {
                #if defined(CONFIG_AIR_RACE_ERASE_IRQ_DISABLE)
                hal_nvic_save_and_set_interrupt_mask(&saved_mask);
                #endif
            }
            ret = race_storage_erase_partition(pCmd->storage_type,
                                               pCmd->partition_length,
                                               pCmd->partition_address,
                                               pCmdMsg->pktId.field.app_id,
                                               channel_id,
                                               FALSE,
                                               race_storage_erase_partition_cmd_cb,
                                               NULL);
/*only non-bt channel race cmd will execute this */
#if defined(AIR_BT_AIR_SERVICE_ENABLE)
            if (!RACE_PORT_IS_BLE(channel_id))
#endif
            {
                #if defined(CONFIG_AIR_RACE_ERASE_IRQ_DISABLE)
                hal_nvic_restore_interrupt_mask(saved_mask);
                #endif
            }
            if (RACE_ERRCODE_SUCCESS == ret) {
                ret = race_storage_erase_partition_cmd_cb(ret,
                                                          pCmd->storage_type,
                                                          pCmd->partition_length,
                                                          pCmd->partition_address,
                                                          pCmdMsg->pktId.field.app_id,
                                                          channel_id,
                                                          TRUE,
                                                          NULL);
            } else if (RACE_ERRCODE_MORE_OPERATION == ret) {
                ret = RACE_ERRCODE_SUCCESS;
            }
        }

        pEvt->status = ret;
    }

    return pEvt;
}


void *race_cmdhdl_storage_lock_unlock(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint16_t length, uint8_t channel_id)
{
    typedef struct {
        RACE_COMMON_HDR_STRU cmdhdr;
        uint8_t storage_type;
        uint8_t agent_or_partner;
        uint8_t lock_or_unlock;
    } PACKED CMD;

    typedef struct {
        uint8_t status;
    } PACKED RSP;

    int32_t ret = RACE_ERRCODE_FAIL;
    CMD *pCmd = (CMD *)pCmdMsg;
    if (length != (sizeof(CMD) - RACE_HEAD_LENGTH) || (pCmd->storage_type != SFC_FLASH && pCmd->storage_type != SPI_FLASH)) {
        //CMD length is wrong.
        return NULL;
    }
    RSP *pEvt = RACE_ClaimPacketAppID(pCmdMsg->pktId.field.app_id,
                                      RACE_TYPE_RESPONSE,
                                      RACE_STORAGE_LOCK_UNLOCK,
                                      sizeof(RSP),
                                      channel_id);

    if (pEvt) {
        if (!pCmd->agent_or_partner) {
            /* Agent */
            race_storage_lock_unlock_noti_struct *noti = NULL;

            /* A1. Execute the cmd. */
            ret = RACE_ERRCODE_SUCCESS;

            if (RACE_ERRCODE_SUCCESS == ret) {
                /* A2. Create the noti. */
                noti = (void *)RACE_ClaimPacketAppID(pCmdMsg->pktId.field.app_id,
                                                     RACE_TYPE_NOTIFICATION,
                                                     RACE_STORAGE_LOCK_UNLOCK,
                                                     sizeof(race_storage_lock_unlock_noti_struct),
                                                     channel_id);
                if (noti) {
                    /* A3. Set the noti parameters with the cmd results.  */
                    noti->status = RACE_ERRCODE_SUCCESS;
                    noti->storage_type = pCmd->storage_type;
                    noti->agent_or_partner = pCmd->agent_or_partner;
                    noti->lock_or_unlock = pCmd->lock_or_unlock;

                    /* A4. Send the noti. */
                    ret = race_noti_send(noti, channel_id, TRUE);

                    if (RACE_ERRCODE_SUCCESS != ret) {
                        /* A5. Free the noti if needed. */
                        RACE_FreePacket(noti);
                        noti = NULL;
                    }
                } else {
                    ret = RACE_ERRCODE_NOT_ENOUGH_MEMORY;
                }
            }
        } else {
            /* Client */
            ret = RACE_ERRCODE_NOT_SUPPORT;
        }

        pEvt->status = ret;
    }

    return pEvt;
}


void *race_cmdhdl_storage_get_partition_sha256(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint16_t length, uint8_t channel_id)
{
    typedef struct {
        RACE_COMMON_HDR_STRU cmdhdr;
        uint8_t storage_type;
        uint8_t agent_or_partner;
        uint32_t partition_address;
        uint32_t partition_length;
    } PACKED CMD;

    typedef struct {
        uint8_t status;
    } PACKED RSP;

    int32_t ret = RACE_ERRCODE_FAIL;
    CMD *pCmd = (CMD *)pCmdMsg;
    if (length != (sizeof(CMD) - RACE_HEAD_LENGTH) || (pCmd->storage_type != SFC_FLASH && pCmd->storage_type != SPI_FLASH)) {
        //CMD length is wrong.
        return NULL;
    }
    RSP *pEvt = RACE_ClaimPacketAppID(pCmdMsg->pktId.field.app_id,
                                      RACE_TYPE_RESPONSE,
                                      RACE_STORAGE_GET_PARTITION_SHA256,
                                      sizeof(RSP),
                                      channel_id);
    if (pEvt) {
        if (!pCmd->agent_or_partner) {
            /* Agent */
            race_storage_get_partition_sha256_noti_struct *noti = NULL;
            unsigned char sha256[RACE_STORAGE_SHA256_SIZE] = {0};

            /* A1. Execute the cmd. */
            ret = race_storage_sha256_generate(sha256,
                                               pCmd->partition_address,
                                               pCmd->partition_length,
                                               pCmd->storage_type);
            if (RACE_ERRCODE_SUCCESS == ret) {
                /* A2. Create the noti(to Smart Phone). */
                noti = (void *)RACE_ClaimPacketAppID(pCmdMsg->pktId.field.app_id,
                                                     RACE_TYPE_NOTIFICATION,
                                                     RACE_STORAGE_GET_PARTITION_SHA256,
                                                     sizeof(race_storage_get_partition_sha256_noti_struct),
                                                     channel_id);
                if (noti) {
                    /* A3. Set the noti parameters with the cmd results.  */
                    noti->status = RACE_ERRCODE_SUCCESS;
                    noti->agent_or_partner = pCmd->agent_or_partner;
                    noti->storage_type = pCmd->storage_type;
                    noti->partition_address = pCmd->partition_address;
                    noti->partition_length = pCmd->partition_length;
                    memcpy(noti->sha256, sha256, RACE_STORAGE_SHA256_SIZE);

                    /* A4. Send the noti. */
                    ret = race_noti_send(noti, channel_id, TRUE);
                    if (RACE_ERRCODE_SUCCESS != ret) {
                        /* A5. Free the noti if needed. */
                        RACE_FreePacket(noti);
                        noti = NULL;
                    }
                } else {
                    ret = RACE_ERRCODE_NOT_ENOUGH_MEMORY;
                }
            }
        } else {
            /* Client */
            ret = RACE_ERRCODE_NOT_SUPPORT;
        }

        pEvt->status = ret;
    }

    return pEvt;
}


void *race_cmdhdl_storage_get_4k_erased_status(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint16_t length, uint8_t channel_id)
{
    typedef struct {
        RACE_COMMON_HDR_STRU cmdhdr;
        uint8_t storage_type;
        uint8_t agent_or_partner;
        uint32_t partition_address;
        uint32_t partition_length;
    } PACKED CMD;

    typedef struct {
        uint8_t status;
    } PACKED RSP;

    int32_t ret = RACE_ERRCODE_FAIL;
    CMD *pCmd = (CMD *)pCmdMsg;
    if (length != (sizeof(CMD) - RACE_HEAD_LENGTH) || (pCmd->storage_type != SFC_FLASH && pCmd->storage_type != SPI_FLASH)) {
        //LOG_ERR("race_cmdhdl_storage_get_4k_erased_status length error", 0);
        //CMD length is wrong.
        return NULL;
    }
    RSP *pEvt = RACE_ClaimPacketAppID(pCmdMsg->pktId.field.app_id,
                                      RACE_TYPE_RESPONSE,
                                      RACE_STORAGE_GET_4K_ERASED_STATUS,
                                      sizeof(RSP),
                                      channel_id);
    uint16_t erase_status_size = 0;


    if (pEvt) {
        if (!pCmd->agent_or_partner) {
            /* Agent */
            race_storage_get_4k_erased_status_noti_struct *noti = NULL;

            /* A1. Execute the cmd. */
            /* Get erase_status size. */
            ret = race_storage_get_partition_erase_status(NULL,
                                                          &erase_status_size,
                                                          pCmd->partition_address,
                                                          pCmd->partition_length,
                                                          pCmd->storage_type);
            if (RACE_ERRCODE_SUCCESS == ret) {
                /* A2. Create the noti. */
                noti = (void *)RACE_ClaimPacketAppID(pCmdMsg->pktId.field.app_id,
                                                     RACE_TYPE_NOTIFICATION,
                                                     RACE_STORAGE_GET_4K_ERASED_STATUS,
                                                     sizeof(race_storage_get_4k_erased_status_noti_struct) + erase_status_size,
                                                     channel_id);
                if (noti) {
                    /* A3. Set the noti parameters with the cmd results.  */
                    ret = race_storage_get_partition_erase_status(noti->erase_status,
                                                                  &erase_status_size,
                                                                  pCmd->partition_address,
                                                                  pCmd->partition_length,
                                                                  pCmd->storage_type);
                    noti->erase_status_size = erase_status_size;
                    if (RACE_ERRCODE_SUCCESS == ret) {
                        noti->status = ret;
                        noti->storage_type = pCmd->storage_type;
                        noti->agent_or_partner = pCmd->agent_or_partner;
                        noti->partition_address = pCmd->partition_address;
                        noti->partition_length = pCmd->partition_length;
                        /* A4. Send the noti. */
                        ret = race_noti_send(noti, channel_id, TRUE);
                    }

                    if (RACE_ERRCODE_SUCCESS != ret) {
                        /* A5. Free the noti if needed. */
                        RACE_FreePacket(noti);
                        noti = NULL;
                    }
                } else {
                    ret = RACE_ERRCODE_NOT_ENOUGH_MEMORY;
                }
            }
        } else {
            /* Client */
            ret = RACE_ERRCODE_NOT_SUPPORT;
        }

        pEvt->status = ret;
    }

    return pEvt;
}


void *race_cmdhdl_storage(ptr_race_pkt_t pCmdMsg, uint16_t length, uint8_t channel_id)
{
#ifdef RACE_CMD_STORAGE_ENABLE_DEBUG_LOG
    LOG_INF("race_cmdhdl_storage, pCmdMsg->hdr.id[0x%X]", (int)pCmdMsg->hdr.id);
#endif
    if (pCmdMsg->hdr.type == RACE_TYPE_COMMAND ||
        pCmdMsg->hdr.type == RACE_TYPE_COMMAND_WITHOUT_RSP) {
#ifdef AIR_BTD_IC_PREMIUM_G1
        sys_wdt_feed();
#endif
    switch (pCmdMsg->hdr.id) {
        case RACE_STORAGE_WRITE_BYTE:
            return race_cmdhdl_storage_write_byte((PTR_RACE_COMMON_HDR_STRU) & (pCmdMsg->hdr), length, channel_id);

        case RACE_STORAGE_WRITE_PAGE:
            return race_cmdhdl_storage_write_page((PTR_RACE_COMMON_HDR_STRU) & (pCmdMsg->hdr), length, channel_id);

        case RACE_STORAGE_READ_PAGE:
            return race_cmdhdl_storage_read_page((PTR_RACE_COMMON_HDR_STRU) & (pCmdMsg->hdr), length, channel_id);

        case RACE_STORAGE_ERASE_PARTITION:
            return race_cmdhdl_storage_erase_partition((PTR_RACE_COMMON_HDR_STRU) & (pCmdMsg->hdr), length, channel_id);

        case RACE_STORAGE_LOCK_UNLOCK:
            return race_cmdhdl_storage_lock_unlock((PTR_RACE_COMMON_HDR_STRU) & (pCmdMsg->hdr), length, channel_id);

        case RACE_STORAGE_GET_PARTITION_SHA256:
            return race_cmdhdl_storage_get_partition_sha256((PTR_RACE_COMMON_HDR_STRU) & (pCmdMsg->hdr), length, channel_id);

        case RACE_STORAGE_GET_4K_ERASED_STATUS:
            return race_cmdhdl_storage_get_4k_erased_status((PTR_RACE_COMMON_HDR_STRU) & (pCmdMsg->hdr), length, channel_id);

        default:
            break;
    }
    }

    return NULL;
}

#endif /* RACE_STORAGE_CMD_ENABLE */

