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
#ifdef RACE_FOTA_CMD_ENABLE
#include "stdio.h"
#include "fota_util.h"
#include "fota_flash.h"
#include "fota_multi_info.h"
#include "fota_multi_info_util.h"
#include "race_util.h"
#include "race_xport.h"
#include "race_cmd_fota.h"
#include "race_fota_util.h"
#include "race_noti.h"
#include "race_bt.h"
#include "race_storage_access.h"
#include "race_storage_util.h"
#include "race_timer.h"
#include "race_fota.h"
#include "fota_signature.h"
#ifdef MTK_PORT_SERVICE_BT_ENABLE
#include "ble_air_internal.h"
#endif
#include "hal_sleep_manager.h"
#include "hal_sleep_manager_platform.h"


////////////////////////////////////////////////////////////////////////////////
// Constant Definitions ////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// TYPE DEFINITIONS ////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// Global Variables ////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// FUNCTION DECLARATIONS ///////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void *RACE_CmdHandler_FOTA_commit(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint16_t length, uint8_t channel_id)
{
    UNUSED(pCmdMsg);
    UNUSED(length);

    typedef struct {
        uint8_t status;
    } PACKED RSP;

    uint8_t integrity_res = 0xFF;
    int32_t ret = RACE_ERRCODE_FAIL;
    uint8_t timer_id = race_fota_commit_timer_id_get();
    RSP *pEvt = RACE_ClaimPacketAppID(pCmdMsg->pktId.field.app_id,
                                      RACE_TYPE_RESPONSE,
                                      RACE_FOTA_COMMIT,
                                      sizeof(RSP),
                                      channel_id);

    if (pEvt) {
        ret = fota_dl_integrity_res_read(&integrity_res);
        if (FOTA_ERRCODE_SUCCESS == ret &&
            FOTA_DL_INTEGRITY_RES_VAL_PASS == integrity_res) {
            ret = fota_upgrade_flag_set();
            if (FOTA_ERRCODE_SUCCESS == ret) {
#if defined(AIR_DONGLE_FOTA_BY_SP_ENABLE) || defined(AIR_FOTA_DONGLE_HEADSET_BY_SP_ENABLE)
                uint8_t flag = 1;
                uint32_t f_length = sizeof(uint8_t);
                race_fota_write_nvkey_upgrade_complete_flag(&flag, f_length);
#endif
                /* If failed, FOTA upgrade will be triggered in the other cause of reboot.
                               * No error handle here.
                               */
                printk("commit_timer_id:%d", timer_id);
                if (RACE_TIMER_INVALID_TIMER_ID == timer_id) {
                    ret = race_timer_smart_start(&timer_id,
                                                 RACE_TIMER_FOTA_COMMIT_DELAY_IN_MS,
                                                 race_fota_commit_timer_expiration_hdl,
                                                 NULL);

                    if (RACE_ERRCODE_SUCCESS == ret) {
                        ret = race_fota_commit_timer_id_set(timer_id);
                    }
                } else {
                    ret = race_timer_smart_reset(timer_id);
                }
                if (RACE_ERRCODE_SUCCESS != ret) {
                    /* Even if ret is not SUCCESS, also reboot Agent */
                race_event_send_fota_need_reboot_event(NULL, 0);
                    ret = RACE_ERRCODE_SUCCESS;
                }

            }
        } else {
            ret = FOTA_ERRCODE_FAIL;
        }

        if (FOTA_ERRCODE_SUCCESS == ret) {
            race_fota_dl_state_set(RACE_FOTA_DOWNLOAD_STATE_COMMITING);
#ifdef RACE_FOTA_DELAY_COMMIT_ENABLE
            race_fota_set_sp_trans_method_by_channel_id(channel_id);
#endif
        }

        pEvt->status = FOTA_ERRCODE_SUCCESS == ret ? RACE_ERRCODE_SUCCESS : RACE_ERRCODE_FAIL;
    }
    return pEvt;
}


/* RACE_FOTA_STOP cmd does not interrupt on-going RHO or FOTA_reboot */
void *RACE_CmdHandler_FOTA_stop(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint16_t length, uint8_t channel_id)
{
    UNUSED(length);

    typedef struct {
        RACE_COMMON_HDR_STRU cmdhdr;
        uint8_t sender;
        uint8_t recipient;
        uint8_t reason;
    } PACKED CMD;

    typedef struct {
        uint8_t status;
    } PACKED RSP;

    CMD *pCmd = (CMD *)pCmdMsg;
    RSP *pEvt = RACE_ClaimPacketAppID(pCmdMsg->pktId.field.app_id,
                                      RACE_TYPE_RESPONSE,
                                      RACE_FOTA_STOP,
                                      sizeof(RSP),
                                      channel_id);
    race_recipient_type_enum recipient_type = race_recipient_type_convt(pCmd->recipient);
    int32_t ret = RACE_ERRCODE_SUCCESS;

    /*RACE_LOG_MSGID_I("sender:%x recipient:%x reason:%x", 3,
                     pCmd->sender,
                     pCmd->recipient,
                     pCmd->reason);*/

    if (pEvt != NULL) {
        ret = hal_sleep_manager_unlock_sleep(SLEEP_LOCK_RACE_CMD);
        if (RACE_ERRCODE_SUCCESS != ret) {
            LOG_ERR("[FOTA] hal_sleep_manager_unlock_sleep, ret:%x", ret);
            pEvt->status = ret;
        }

        if (RACE_FOTA_STOP_REASON_SP_LOST <= pCmd->reason) {
            //RACE_LOG_MSGID_W("wrong reason from SP:%x", 1, pCmd->reason);
            pCmd->reason = RACE_FOTA_STOP_REASON_CANCEL;
        }

        race_fota_stop_agent_sp_stop_req_struct sp_req = {0};

        sp_req.channel_id = channel_id;
        sp_req.recipient_type = recipient_type;
        sp_req.sender = pCmd->sender;
        sp_req.reason = pCmd->reason;
        ret = race_fota_stop_agent_sp_stop_req_process(&sp_req);

        pEvt->status = ret;
    }

    return pEvt;
}


void *RACE_CmdHandler_FOTA_query_state(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint16_t length, uint8_t channel_id)
{
    UNUSED(pCmdMsg);
    UNUSED(length);

    typedef struct {
        uint8_t status;
        uint16_t fota_state;
    } PACKED RSP;

    int32_t ret = RACE_ERRCODE_FAIL;
    uint16_t fota_state;
    RSP *pEvt = RACE_ClaimPacketAppID(pCmdMsg->pktId.field.app_id,
                                      RACE_TYPE_RESPONSE,
                                      RACE_FOTA_QUERY_STATE,
                                      sizeof(RSP),
                                      channel_id);

    if (pEvt != NULL) {
        ret = fota_state_read(&fota_state);
        if (ret == FOTA_ERRCODE_SUCCESS) {
            pEvt->status = fota_state;
        }
        ret = FOTA_ERRCODE_SUCCESS == ret ? RACE_ERRCODE_SUCCESS : RACE_ERRCODE_FAIL;
        pEvt->status = ret;
    }

    return pEvt;
}


void *RACE_CmdHandler_FOTA_write_state(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint16_t length, uint8_t channel_id)
{
    UNUSED(pCmdMsg);
    UNUSED(length);

    typedef struct {
        RACE_COMMON_HDR_STRU cmdhdr;
        uint16_t fota_state;
    } PACKED CMD;

    typedef struct {
        uint8_t status;
        uint16_t fota_state;
    } PACKED RSP;

    int32_t ret = RACE_ERRCODE_FAIL;
    CMD *pCmd = (CMD *)pCmdMsg;
    RSP *pEvt = RACE_ClaimPacketAppID(pCmdMsg->pktId.field.app_id,
                                      RACE_TYPE_RESPONSE,
                                      RACE_FOTA_WRITE_STATE,
                                      sizeof(RSP),
                                      channel_id);

    if (pEvt != NULL) {
        pEvt->fota_state = pCmd->fota_state;
        ret = fota_state_write(pEvt->fota_state);
        pEvt->status = FOTA_ERRCODE_SUCCESS == ret ? RACE_ERRCODE_SUCCESS : RACE_ERRCODE_FAIL;
        race_fota_cntx_struct *fota_cntx = race_fota_cntx_get();
        if (fota_cntx &&
            !fota_cntx->transfer_complete &&
            race_fota_is_race_fota_running() &&
            RACE_ERRCODE_SUCCESS == ret &&
            (0x0211 == pEvt->fota_state ||
            0x0311 == pEvt->fota_state)) {
            printk("FOTA transfer complete");
            fota_cntx->transfer_complete = TRUE;
            /* Send the transfer complete event. */
            race_send_event_notify_msg(RACE_EVENT_TYPE_FOTA_TRANSFER_COMPLETE, NULL);
        }
    }

    return pEvt;
}


void *RACE_CmdHandler_FOTA_query_partition_info(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint16_t length, uint8_t channel_id)
{
    UNUSED(length);

    typedef struct {
        RACE_COMMON_HDR_STRU cmdhdr;
        uint8_t partition_id;
    } PACKED CMD;

    typedef struct {
        uint8_t status;
        uint8_t partition_id;
        uint8_t storage_type;
        uint32_t partition_address;
        uint32_t partition_length;
    } PACKED RSP;

    int32_t ret = RACE_ERRCODE_FAIL;
    uint32_t partition_address, partition_length;
    CMD *pCmd = (CMD *)pCmdMsg;
    RSP *pEvt = NULL;

    pEvt = RACE_ClaimPacketAppID(pCmd->cmdhdr.pktId.field.app_id,
                                 RACE_TYPE_RESPONSE,
                                 RACE_FOTA_QUERY_PARTITION_INFO,
                                 sizeof(RSP),
                                 channel_id);
    if (pEvt != NULL) {
        pEvt->partition_id = (race_storage_partition_id_enum)pCmd->partition_id;

        switch (pEvt->partition_id) {
            case RACE_STORAGE_PARTITION_ID_FOTA: {
                ret = fota_flash_get_slot_info(&(pEvt->storage_type),
                                               &partition_address,
                                               &partition_length);
                if(ret == FOTA_ERRCODE_SUCCESS){
                    pEvt->partition_address = partition_address;
                    /* Reduce the last 4K which is used to store history states or upgrade info. */
                    pEvt->partition_length = partition_length;
                }
                pEvt->status = FOTA_ERRCODE_SUCCESS == ret ? RACE_ERRCODE_SUCCESS : RACE_ERRCODE_FAIL;
                break;
            }

            case RACE_STORAGE_PARTITION_ID_FS: {
                /* 1530 feature only which merges filesystem sector and fota sector as a new extended fota sector. */
                pEvt->status = (uint8_t)RACE_ERRCODE_NOT_SUPPORT;
                break;
            }

            default: {
                pEvt->status = (uint8_t)RACE_ERRCODE_NOT_SUPPORT;
                break;
            }
        }
    }

    return pEvt;
}


void race_fota_hash_nb_generate_callback(FOTA_ERRCODE result,
                                                  fota_hash_type_enum hash_type,
                                                  uint8_t *hash,
                                                  uint32_t hash_len,
                                                  void *user_data)
{
    race_fota_hash_nb_generate_user_data_struct *hash_user_data = user_data;
    uint8_t *signature = NULL;
    //FOTA_LOG_MSGID_I("into race_fota_hash_nb_generate_callback", 0);

    if (hash_user_data) {
        if (FOTA_ERRCODE_SUCCESS == result) {
            signature = k_malloc(FOTA_SIGNATURE_MAX_SIZE);
            if (signature) {
                result = fota_flash_read(hash_user_data->signature_address,
                                      signature,
                                      FOTA_SIGNATURE_MAX_SIZE);

                if (true == result) {
                    result = fota_signature_verify(hash_user_data->integrity_check_type,
                                                   signature,
                                                   FOTA_SIGNATURE_MAX_SIZE,
                                                   hash,
                                                   hash_len);
                }
                printk("fota_signature_verify result: %x", result);

                if (FOTA_ERRCODE_SUCCESS == result) {
                    //FOTA_LOG_MSGID_I("race_fota_hash_nb_generate_callback: integrity pass", 0);
#ifndef AIR_FOTA_UPGRADE_ENABLE
                    /* Write the integrity check result into the multiple information sector. */
                    result = fota_dl_integrity_res_write(FOTA_DL_INTEGRITY_RES_VAL_PASS);
#endif
                } else {
                    /* Do nothing. Allow to check the integrity multiple times until it passes. */
                }
            } else {
                result = FOTA_ERRCODE_NOT_ENOUGH_MEMORY;
            }
        }
    }

    if (hash_user_data) {
        //FOTA_LOG_MSGID_I("hash_user_data->noti->status: %x", 1, result);
        ((race_fota_check_integrity_noti_struct *)hash_user_data->noti)->status = FOTA_ERRCODE_SUCCESS == result ? RACE_ERRCODE_SUCCESS : RACE_ERRCODE_CHECK_INTEGRITY_FAIL;
        result = race_noti_send(hash_user_data->noti, hash_user_data->channel_id, TRUE);
        if (FOTA_ERRCODE_SUCCESS != result) {
            RACE_FreePacket(hash_user_data->noti);
        }
        race_mem_free(hash_user_data);
    }

    if (signature) {
        k_free(signature);
    }
}


void *RACE_CmdHandler_FOTA_check_integrity(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint16_t length, uint8_t channel_id)
{
    UNUSED(length);

    typedef struct {
        RACE_COMMON_HDR_STRU cmdhdr;
        uint8_t recipient_count;
        race_fota_check_integrity_recipient_param_struct recipient_param[0];
    } PACKED CMD;

    typedef struct {
        uint8_t status;
    } PACKED RSP;

    int32_t ret = RACE_ERRCODE_FAIL;
    CMD *pCmd = (CMD *)pCmdMsg;

    RSP *pEvt = RACE_ClaimPacketAppID(pCmdMsg->pktId.field.app_id,
                                      RACE_TYPE_RESPONSE,
                                      RACE_FOTA_CHECK_INTEGRITY,
                                      sizeof(RSP),
                                      channel_id);

    race_fota_check_integrity_noti_struct *noti = NULL;
    race_fota_hash_nb_generate_user_data_struct *user_data = NULL;
    //printk("Enter RACE_CmdHandler_FOTA_check_integrity");
    if (pEvt != NULL) {

        fota_integrity_check_type_enum integrity_check_type = FOTA_INTEGRITY_CHECK_TYPE_MAX;
        uint32_t signature_address = 0, data_address = 0;
        uint32_t data_length = 0;
        FotaStorageType storage_type = Invalid;

        ret = fota_slot_get_integrity_check_info(&integrity_check_type,
                                                    &signature_address,
                                                    &data_address,
                                                    &data_length,
                                                    &storage_type);
        printk("FOTA integrity, fota_slot_get_integrity_check_info ret:%d, data_address:%x, data_length:%d,storage_type:%d", ret, data_address, data_length, storage_type);
        if (FOTA_ERRCODE_SUCCESS != ret) {
            ret = RACE_ERRCODE_FAIL;
        } else {
            fota_hash_type_enum hash_type = fota_signature_get_hash_type(integrity_check_type);
            void *context = NULL;

            /* A2. Create the noti(to Smart Phone). */
            noti = RACE_ClaimPacketAppID(pCmdMsg->pktId.field.app_id,
                                            RACE_TYPE_NOTIFICATION,
                                            RACE_FOTA_CHECK_INTEGRITY,
                                            sizeof(race_fota_check_integrity_noti_struct) + sizeof(race_fota_check_integrity_recipient_param_struct),
                                            channel_id);
            if (noti) {
                /* A3. Set the noti parameters with the cmd results.  */
                noti->recipient_count = pCmd->recipient_count;
                memcpy(noti->recipient_param, pCmd->recipient_param, sizeof(race_fota_check_integrity_recipient_param_struct));
            } else {
                ret = RACE_ERRCODE_NOT_ENOUGH_MEMORY;
                goto exit;
            }

            user_data = race_mem_alloc(sizeof(race_fota_hash_nb_generate_user_data_struct));
            if (!user_data) {
                ret = RACE_ERRCODE_NOT_ENOUGH_MEMORY;
                goto exit;
            }
            /* race_fota_hash_nb_generate_callback() will send noti and free user_data. And it will be invoked when fota_hash_nb_generate()
                            * does not return FOTA_ERRCODE_WOULDBLOCK and when fota_hash_nb_generate_cancel() is called.
                            */
            user_data->integrity_check_type = integrity_check_type;
            user_data->signature_address = signature_address;
            user_data->storage_type = storage_type;
            user_data->channel_id = channel_id;
            user_data->noti = noti;
            ret = fota_hash_nb_generate(&context, hash_type, data_address, data_length,
                                        storage_type,race_fota_hash_nb_generate_callback, user_data);
            printk("fota_hash_nb_generate ret:%d", ret);
            if (FOTA_ERRCODE_WOULDBLOCK == ret) {
                /* Send message to continue hash calculation */
                ret = race_fota_hash_nb_send_message(context);
                if (RACE_ERRCODE_SUCCESS != ret) {
                    fota_hash_nb_generate_cancel(context);
                    /* race_fota_hash_nb_generate_callback() has been invoked by fota_hash_nb_generate_cancel(). */
                } /* else race_fota_hash_nb_generate_callback() will be invoked by fota_hash_nb_generate_continue(). */
            } /* else race_fota_hash_nb_generate_callback() has been invoked by fota_hash_nb_generate(). */
            /* race_fota_hash_nb_generate_callback() has been or will be invoked. Therefore, set noti and user_data to NULL to avoid being freed twice. */
            noti = NULL;
            user_data = NULL;
            ret = RACE_ERRCODE_SUCCESS; /* Send 5B of success since race_fota_hash_nb_generate_callback() will send 5D. */
        }
    }

exit:
    if (pEvt) {
        pEvt->status = ret;
    }

    if (noti) {
        RACE_FreePacket(noti);
    }

    return pEvt;
}


void *RACE_CmdHandler_FOTA_start(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint16_t length, uint8_t channel_id)
{
    UNUSED(length);

    typedef struct {
        RACE_COMMON_HDR_STRU cmdhdr;
        uint8_t recipient;
        uint8_t fota_mode; /* 0: background; 1: active; 2: adaptive */
    } PACKED CMD;

    typedef struct {
        uint8_t status;
    } PACKED RSP;

    CMD *pCmd = (CMD *)pCmdMsg;
    RSP *pEvt = RACE_ClaimPacketAppID(pCmdMsg->pktId.field.app_id,
                                      RACE_TYPE_RESPONSE,
                                      RACE_FOTA_START,
                                      sizeof(RSP),
                                      channel_id);
    if (race_fota_is_race_fota_running()) {
        printk("FOTA is running last time");
        race_fota_reset();
    }
    int32_t ret = RACE_ERRCODE_NOT_SUPPORT;
    race_recipient_type_enum recipient_type = race_recipient_type_convt(pCmd->recipient);
    race_fota_mode_enum fota_mode = RACE_FOTA_START_GET_FOTA_MODE(pCmd->fota_mode);
    race_fota_dual_device_dl_method_enum dl_method = RACE_FOTA_START_GET_DL_METHOD(pCmd->fota_mode);
    race_fota_download_state_enum fota_dl_state = race_fota_dl_state_get();
    race_fota_start_noti_struct *noti = NULL;

    race_fota_cntx_struct *fota_cntx = race_fota_cntx_get();


    if (pEvt != NULL) {
        ret = hal_sleep_manager_lock_sleep(SLEEP_LOCK_RACE_CMD);
        if (RACE_ERRCODE_SUCCESS != ret) {
            LOG_ERR("[FOTA] hal_sleep_manager_lock_sleep, ret:%x", ret);
            pEvt->status = ret;
            return pEvt;
        }

        /* Check the start cmd parameters. */
        ret = race_fota_start_check_params(recipient_type, fota_mode, dl_method);
        if (RACE_ERRCODE_SUCCESS != ret) {
            pEvt->status = ret;
            printk("Fail to start FOTA for parameter errors. ret:%d", ret);

#ifdef RACE_FOTA_ACTIVE_MODE_KEEP_HFP
            if (RACE_ERRCODE_REJECT_FOR_CALL_ONGOING == ret &&
                race_fota_is_race_fota_running() &&
                race_fota_is_active_mode()) {
                race_fota_cancel();
            }
#endif
            return pEvt;
        }

        if (fota_cntx) {
            printk("fota_dl_state:%d channel_id:%d", fota_dl_state, channel_id);

            /* 5B/5D may be lost and SP will retry. This may cause RACE_FOTA_START be sent
                        * when FOTA is started.
                        * Even after RHO is done, the state is still RACE_FOTA_DOWNLOAD_STATE_RHOING.
                        */
            if (RACE_FOTA_DOWNLOAD_STATE_NONE == fota_dl_state ||
                RACE_FOTA_DOWNLOAD_STATE_MAX == fota_dl_state
#ifdef RACE_FOTA_DELAY_COMMIT_ENABLE
                || RACE_FOTA_DOWNLOAD_STATE_WAIT_FOR_COMMIT == fota_dl_state
#endif
               ) {
                /* FOTA start for the first time or after RHO. */
                race_fota_dl_state_set(RACE_FOTA_DOWNLOAD_STATE_STARTING);
                fota_cntx->sp_online = TRUE;
                fota_cntx->transfer_complete = FALSE;
                race_fota_set_sp_trans_method_by_channel_id(channel_id);
                race_fota_set_fota_mode(fota_mode);
                fota_cntx->dl_method = dl_method;
                bt_addr_t *addr = (bt_addr_t *)race_get_bt_connection_addr(channel_id);
                if (NULL != addr) {
                    memcpy(&fota_cntx->remote_address, addr, sizeof(bt_addr_t));
                } else {
                    //RACE_LOG_MSGID_E("error fota start get address wrong!", 0);
                }

            }

            if (RACE_RECIPIENT_TYPE_AGENT_ONLY == recipient_type) {
                uint8_t timer_id = race_fota_app_id_timer_id_get();

                ret = race_storage_enable_fota_partition_accessibility();

                /* Start app_id timer */
                if (RACE_ERRCODE_SUCCESS == ret) {
                    if (RACE_TIMER_INVALID_TIMER_ID == timer_id) {
                        ret = race_timer_smart_start(&timer_id,
                                                     RACE_FOTA_APP_ID_TIMEOUT_IN_MS,
                                                     race_fota_app_id_timer_expiration_hdl,
                                                     NULL);

                        if (RACE_ERRCODE_SUCCESS == ret) {
                            race_fota_app_id_timer_id_set(timer_id);
                        }
                    }

                    if (RACE_ERRCODE_SUCCESS == ret) {
                        noti = RACE_ClaimPacketAppID(pCmdMsg->pktId.field.app_id,
                                                     RACE_TYPE_NOTIFICATION,
                                                     RACE_FOTA_START,
                                                     sizeof(race_fota_start_noti_struct),
                                                     channel_id);
                        if (noti) {
                            noti->status = RACE_ERRCODE_SUCCESS;
                            noti->recipient = pCmd->recipient;
                            noti->fota_mode = pCmd->fota_mode;

                            /* Send the noti. */
                            ret = race_noti_send(noti, channel_id, TRUE);
                            if (RACE_ERRCODE_SUCCESS != ret) {
                                /* Free the noti if needed. */
                                RACE_FreePacket(noti);
                                noti = NULL;
                            }
                        } else {
                            ret = RACE_ERRCODE_NOT_ENOUGH_MEMORY;
                        }
                    }
                }

                if (RACE_FOTA_DOWNLOAD_STATE_STARTING == race_fota_dl_state_get()) {
                    if (RACE_ERRCODE_SUCCESS == ret) {
                        printk("Start FOTA for the first time.");
                        fota_cntx->is_dual_fota = FALSE;
                        race_fota_dl_state_set(RACE_FOTA_DOWNLOAD_STATE_START);
                        race_event_send_fota_start_event(fota_cntx->is_dual_fota, race_fota_is_active_mode());
                        //race_send_event_notify_msg(RACE_EVENT_TYPE_FOTA_START, NULL);
#ifndef AIR_BTA_IC_PREMIUM_G2
#if defined (AIR_BLE_ULTRA_LOW_LATENCY_WITH_HID_ENABLE) && defined (AIR_HEADSET_ENABLE)
                        extern void EnableForcingAirCisScheduling(void);
                        EnableForcingAirCisScheduling();
#endif
#endif
                    } else {
                        race_fota_stop_agent_reset();
                    }
                }
                /* else this is the retry cmd, do nothing. Let app_id timer handle the potential errors. */
            } else if (RACE_RECIPIENT_TYPE_AGENT_PARTNER == recipient_type) {
                ret = RACE_ERRCODE_NOT_SUPPORT;
            }
        } else {
            ret = RACE_ERRCODE_NOT_INITIALIZED;
        }

        pEvt->status = ret;
    }

    return pEvt;
}


void *RACE_CmdHandler_FOTA_get_version(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint16_t length, uint8_t channel_id)
{
    typedef struct {
        RACE_COMMON_HDR_STRU cmdhdr;
        uint8_t slot_number;
    } PACKED CMD;

    typedef struct {
        uint8_t status;
    } PACKED RSP;

    int32_t ret = RACE_ERRCODE_FAIL;
    CMD *pCmd = (CMD *)pCmdMsg;
    RSP *pEvt = RACE_ClaimPacketAppID(pCmdMsg->pktId.field.app_id,
                                      RACE_TYPE_RESPONSE,
                                      RACE_FOTA_GET_VERSION,
                                      sizeof(RSP),
                                      channel_id);
    if (!pEvt) {
        return pEvt;
    }

    race_fota_get_version_noti_struct *noti = NULL;
    uint8_t version[FOTA_VERSION_MAX_SIZE] = {0};

    /* A1. Execute the cmd. */
#ifdef CONFIG_AIR_DUAL_BANK_FOTA_ENABLE
    ret = fota_slot_version_read(version, FOTA_VERSION_MAX_SIZE, pCmd->slot_number);
#else
    ret = fota_version_get(version, FOTA_VERSION_MAX_SIZE, FOTA_VERSION_TYPE_STORED);
#endif
    if (FOTA_ERRCODE_SUCCESS == ret) {
        /* A2. Create the noti. */
        size_t version_len = strlen((const char *)version);
        noti = (void *)RACE_ClaimPacketAppID(pCmdMsg->pktId.field.app_id,
                                                RACE_TYPE_NOTIFICATION,
                                                RACE_FOTA_GET_VERSION,
                                                sizeof(race_fota_get_version_noti_struct) + version_len,
                                                channel_id);

        if (noti) {
            /* A3. Set the noti parameters with the cmd results.  */
            noti->status = RACE_ERRCODE_SUCCESS;
            noti->agent_or_partner = pCmd->slot_number;
            noti->version_len = version_len;

            if (version_len > 0) {
                memcpy(noti->version, version, version_len);
            }

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

    pEvt->status = ret;
    return pEvt;
}


void *RACE_CmdHandler_FOTA_new_transaction(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint16_t length, uint8_t channel_id)
{
    UNUSED(length);

    typedef struct {
        uint8_t status;
    } PACKED RSP;

    int32_t ret = RACE_ERRCODE_FAIL;
    RSP *pEvt = RACE_ClaimPacketAppID(pCmdMsg->pktId.field.app_id,
                                      RACE_TYPE_RESPONSE,
                                      RACE_FOTA_NEW_TRANSACTION,
                                      sizeof(RSP),
                                      channel_id);
    if (pEvt != NULL) {
        ret = fota_multi_info_sector_reset();
        pEvt->status = FOTA_ERRCODE_SUCCESS == ret ? RACE_ERRCODE_SUCCESS : RACE_ERRCODE_FAIL;
    }

    return pEvt;
}


void *RACE_CmdHandler_FOTA_ping(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint16_t length, uint8_t channel_id)
{
    UNUSED(length);

    typedef struct {
        RACE_COMMON_HDR_STRU cmdhdr;
        uint8_t recipient_count;
        race_recipient_param_general_struct recipient_param[0];
    } PACKED CMD;

    typedef struct {
        uint8_t status;
    } PACKED RSP;

    int32_t ret = RACE_ERRCODE_FAIL;
    CMD *pCmd = (CMD *)pCmdMsg;

    RSP *pEvt = RACE_ClaimPacketAppID(pCmdMsg->pktId.field.app_id,
                                      RACE_TYPE_RESPONSE,
                                      RACE_FOTA_PING,
                                      sizeof(RSP),
                                      channel_id);
    race_recipient_param_general_struct *agent_recipient_param = NULL;
    race_recipient_param_general_struct *partner_recipient_param = NULL;
    race_fota_ping_noti_struct *noti = NULL;

    if (pEvt != NULL) {
        ret = race_recipient_param_parse(pCmd->recipient_count,
                                         (uint8_t *)pCmd->recipient_param,
                                         sizeof(race_recipient_param_general_struct),
                                         (uint8_t **)&agent_recipient_param,
                                         (uint8_t **)&partner_recipient_param);
        if (RACE_ERRCODE_SUCCESS != ret) {
            goto exit;
        }

        if (agent_recipient_param && !partner_recipient_param) {
            /* Agent only */
            /* A2. Create the noti(to Smart Phone). */
            noti = RACE_ClaimPacketAppID(pCmdMsg->pktId.field.app_id,
                                         RACE_TYPE_NOTIFICATION,
                                         RACE_FOTA_PING,
                                         sizeof(race_fota_ping_noti_struct) + sizeof(race_recipient_param_general_struct),
                                         channel_id);
            if (noti) {
                /* A3. Set the noti parameters with the cmd results.  */
                noti->recipient_count = pCmd->recipient_count;
                memcpy(noti->recipient_param, pCmd->recipient_param, sizeof(race_recipient_param_general_struct));
                noti->status = RACE_ERRCODE_SUCCESS;

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
        } else {
            ret = RACE_ERRCODE_NOT_SUPPORT;
        }
    }

exit:
    if (pEvt) {
        pEvt->status = ret;
    }

    return pEvt;
}


void *RACE_CmdHandler_FOTA_query_transmit_interval(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint16_t length, uint8_t channel_id)
{
    UNUSED(length);

    typedef struct {
        RACE_COMMON_HDR_STRU cmdhdr;
        uint8_t recipient_count;
        race_recipient_param_general_struct recipient_param[0];
    } PACKED CMD;

    typedef struct {
        uint8_t status;
    } PACKED RSP;

    int32_t ret = RACE_ERRCODE_FAIL;
    CMD *pCmd = (CMD *)pCmdMsg;

    RSP *pEvt = RACE_ClaimPacketAppID(pCmdMsg->pktId.field.app_id,
                                      RACE_TYPE_RESPONSE,
                                      RACE_FOTA_QUERY_TRANSMIT_INTERVAL,
                                      sizeof(RSP),
                                      channel_id);
    race_recipient_param_general_struct *agent_recipient_param = NULL;
    race_recipient_param_general_struct *partner_recipient_param = NULL;
    race_fota_query_transmit_interval_noti_struct *noti = NULL;

    if (pEvt != NULL) {
        ret = race_recipient_param_parse(pCmd->recipient_count,
                                         (uint8_t *)pCmd->recipient_param,
                                         sizeof(race_recipient_param_general_struct),
                                         (uint8_t **)&agent_recipient_param,
                                         (uint8_t **)&partner_recipient_param);
        if (RACE_ERRCODE_SUCCESS != ret) {
            goto exit;
        }

        if (agent_recipient_param && !partner_recipient_param) {
            /* Agent only */
            race_fota_sp_trans_method_enum sp_trans_method = race_fota_sp_trans_method_get();
            uint16_t spp_transmit_interval = 0, ble_transmit_interval = 0;

            ret = race_fota_get_transmit_interval(&spp_transmit_interval, &ble_transmit_interval);
            if (RACE_ERRCODE_SUCCESS == ret) {
                /* A2. Create the noti(to Smart Phone). */
                noti = RACE_ClaimPacketAppID(pCmdMsg->pktId.field.app_id,
                                             RACE_TYPE_NOTIFICATION,
                                             RACE_FOTA_QUERY_TRANSMIT_INTERVAL,
                                             sizeof(race_fota_query_transmit_interval_noti_struct) + sizeof(race_fota_query_transmit_interval_recipient_param_struct),
                                             channel_id);
                if (noti) {
                    noti->status = RACE_ERRCODE_SUCCESS;
                    noti->recipient_count = pCmd->recipient_count;
                    noti->recipient_param[0].recipient = pCmd->recipient_param[0].recipient;

                    /* A3. Set the noti parameters with the cmd results.  */
                    if (RACE_FOTA_SP_TRANS_METHOD_SPP == sp_trans_method) {
                        noti->recipient_param[0].transmit_interval = spp_transmit_interval;
                    } else if (RACE_FOTA_SP_TRANS_METHOD_BLE == sp_trans_method
                               || RACE_FOTA_SP_TRANS_METHOD_BLE_1 == sp_trans_method
                               || RACE_FOTA_SP_TRANS_METHOD_BLE_2 == sp_trans_method
                               || RACE_FOTA_SP_TRANS_METHOD_BLE_3 == sp_trans_method
#if defined(AIR_DONGLE_FOTA_BY_SP_ENABLE) || defined(AIR_FOTA_DONGLE_HEADSET_BY_SP_ENABLE)
                               || RACE_FOTA_SP_TRANS_METHOD_SP_DONGLE == sp_trans_method
#endif
#if defined(AIR_FOTA_DONGLE_HEADSET_BY_SP_ENABLE)
                               || RACE_FOTA_SP_TRANS_METHOD_SP_DONGLE_THROUGHOUT == sp_trans_method
#endif
                               ) {
                        noti->recipient_param[0].transmit_interval = ble_transmit_interval;
                    } else {
                        noti->status = RACE_ERRCODE_NOT_SUPPORT;
                    }
                } else {
                    ret = RACE_ERRCODE_NOT_ENOUGH_MEMORY;
                    goto exit;
                }

                /* A4. Send the noti. */
                ret = race_noti_send(noti, channel_id, TRUE);
                if (RACE_ERRCODE_SUCCESS != ret) {
                    /* A5. Free the noti if needed. */
                    RACE_FreePacket(noti);
                    noti = NULL;
                }
            }
        } else {
            ret = RACE_ERRCODE_NOT_SUPPORT;
        }
    }

exit:
    if (pEvt) {
        pEvt->status = ret;
    }

    return pEvt;
}
#if 0
void *RACE_CmdHandler_FOTA_adjust_ce_length(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint16_t length, uint8_t channel_id)
{
    UNUSED(pCmdMsg);
    UNUSED(length);
    UNUSED(channel_id);
    bt_addr_t *addr = (bt_addr_t *)race_get_bt_connection_addr(channel_id);
    if (addr) {
        // ble_air_link_adjust_conn_interval(addr);
    }
    return NULL;
}
#endif
void *RACE_EvtHandler_FOTA_stop_rsp_noti_hdl(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint16_t length, uint8_t channel_id)
{
    UNUSED(length);

    typedef struct {
        RACE_COMMON_HDR_STRU Hdr;
        uint8_t status;
    } PACKED RSP_NOTI;

    RSP_NOTI *rsp_noti = (RSP_NOTI *)pCmdMsg;
    race_fota_cntx_struct *fota_cntx = race_fota_cntx_get();

    if (!pCmdMsg || !fota_cntx) {
        return NULL;
    }

    if (RACE_TYPE_RESPONSE == pCmdMsg->type) {
        race_fota_stop_agent_sp_stop_rsp_struct sp_stop_rsp = {0};

        sp_stop_rsp.recipient_type = fota_cntx->is_dual_fota ? RACE_RECIPIENT_TYPE_AGENT_PARTNER : RACE_RECIPIENT_TYPE_AGENT_ONLY;
        sp_stop_rsp.status = rsp_noti->status;
        race_fota_stop_agent_sp_stop_rsp_process(&sp_stop_rsp);
    } else if (RACE_TYPE_NOTIFICATION == pCmdMsg->type) {
        race_fota_stop_agent_sp_stop_noti_struct sp_stop_noti = {0};

        sp_stop_noti.recipient_type = fota_cntx->is_dual_fota ? RACE_RECIPIENT_TYPE_AGENT_PARTNER : RACE_RECIPIENT_TYPE_AGENT_ONLY;
        sp_stop_noti.status = rsp_noti->status;
        race_fota_stop_agent_sp_stop_noti_process(&sp_stop_noti);
    }

    return NULL;
}

void *RACE_CmdHandler_FOTA_Get_Battery(PTR_RACE_COMMON_HDR_STRU pCmdMsg, uint16_t length, uint8_t channel_id)
{
    typedef struct {
        RACE_COMMON_HDR_STRU cmdhdr;
        uint8_t agent_or_partner;
    } PACKED CMD;

    typedef struct {
        uint8_t status;
    } PACKED RSP;

    int32_t ret = RACE_ERRCODE_FAIL;
    CMD *pCmd = (CMD *)pCmdMsg;
    RSP *pEvt = RACE_ClaimPacketAppID(pCmdMsg->pktId.field.app_id,
                                      RACE_TYPE_RESPONSE,
                                      RACE_FOTA_GET_BATTERY,
                                      sizeof(RSP),
                                      channel_id);
    if (pEvt) {
        if (!pCmd->agent_or_partner) {
            /* Agent */
            race_fota_get_battery_level_noti_struct *noti = NULL;
            /* A1. Execute the cmd. */
            uint8_t battery_level = (uint8_t)race_get_battery_level();

            /* A2. Create the noti. */
            noti = (void *)RACE_ClaimPacketAppID(pCmdMsg->pktId.field.app_id,
                                                 RACE_TYPE_NOTIFICATION,
                                                 RACE_FOTA_GET_BATTERY,
                                                 sizeof(race_fota_get_battery_level_noti_struct),
                                                 channel_id);
            if (noti) {
                /* A3. Set the noti parameters with the cmd results.  */
                noti->status = RACE_ERRCODE_SUCCESS;
                noti->agent_or_partner = pCmd->agent_or_partner;
                noti->battery_level = battery_level;

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
        pEvt->status = ret;
    }

    return pEvt;
}


void *RACE_CmdHandler_FOTA(ptr_race_pkt_t pCmdMsg, uint16_t length, uint8_t channel_id)
{
    //UNUSED(length);

    if (pCmdMsg->hdr.type == RACE_TYPE_COMMAND ||
        pCmdMsg->hdr.type == RACE_TYPE_COMMAND_WITHOUT_RSP) {
        switch (pCmdMsg->hdr.id) {
            case RACE_FOTA_QUERY_PARTITION_INFO:
                return RACE_CmdHandler_FOTA_query_partition_info((PTR_RACE_COMMON_HDR_STRU) & (pCmdMsg->hdr), length, channel_id);

            case RACE_FOTA_CHECK_INTEGRITY:
                return RACE_CmdHandler_FOTA_check_integrity((PTR_RACE_COMMON_HDR_STRU) & (pCmdMsg->hdr), length, channel_id);

            case RACE_FOTA_COMMIT:
                return RACE_CmdHandler_FOTA_commit((PTR_RACE_COMMON_HDR_STRU) & (pCmdMsg->hdr), length, channel_id);

            case RACE_FOTA_STOP:
                return RACE_CmdHandler_FOTA_stop((PTR_RACE_COMMON_HDR_STRU) & (pCmdMsg->hdr), length, channel_id);

            case RACE_FOTA_QUERY_STATE:
                return RACE_CmdHandler_FOTA_query_state((PTR_RACE_COMMON_HDR_STRU) & (pCmdMsg->hdr), length, channel_id);

            case RACE_FOTA_WRITE_STATE:
                return RACE_CmdHandler_FOTA_write_state((PTR_RACE_COMMON_HDR_STRU) & (pCmdMsg->hdr), length, channel_id);

            case RACE_FOTA_GET_VERSION:
                return RACE_CmdHandler_FOTA_get_version((PTR_RACE_COMMON_HDR_STRU) & (pCmdMsg->hdr), length, channel_id);

            case RACE_FOTA_NEW_TRANSACTION:
                return RACE_CmdHandler_FOTA_new_transaction((PTR_RACE_COMMON_HDR_STRU) & (pCmdMsg->hdr), length, channel_id);

            case RACE_FOTA_START:
                return RACE_CmdHandler_FOTA_start((PTR_RACE_COMMON_HDR_STRU) & (pCmdMsg->hdr), length, channel_id);

            case RACE_FOTA_PING:
                return RACE_CmdHandler_FOTA_ping((PTR_RACE_COMMON_HDR_STRU) & (pCmdMsg->hdr), length, channel_id);

            case RACE_FOTA_QUERY_TRANSMIT_INTERVAL:
                return RACE_CmdHandler_FOTA_query_transmit_interval((PTR_RACE_COMMON_HDR_STRU) & (pCmdMsg->hdr), length, channel_id);
            case RACE_FOTA_GET_BATTERY:
                return RACE_CmdHandler_FOTA_Get_Battery((PTR_RACE_COMMON_HDR_STRU) & (pCmdMsg->hdr), length, channel_id);
            default:
                break;
        }
    } else {
        switch (pCmdMsg->hdr.id) {
            case RACE_FOTA_STOP:
                return RACE_EvtHandler_FOTA_stop_rsp_noti_hdl((PTR_RACE_COMMON_HDR_STRU) & (pCmdMsg->hdr), length, channel_id);
            default:
                break;
        }
    }

    return NULL;
}

#endif /* RACE_FOTA_CMD_ENABLE */

