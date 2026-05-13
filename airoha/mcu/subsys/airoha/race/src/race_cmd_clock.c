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

#include "race_cmd_clock.h"

#ifdef RACE_CLOCK_CMD_ENABLE
#include "hal_clock_internal.h"

#if defined(HAL_DCXO_MODULE_ENABLED) && defined(CONFIG_AIR_NVKEY_ENABLE)
#include "nvkey.h"
#endif

/*****************************************************************************
 * CONSTANT DEFINITIONS
 *****************************************************************************/
/* RACE CAPID Sub Command */
enum {
    CAPID_SUB_CMD_READ_RG = 0,     /* CMD: 05 5A 03 00 C0 02 00          RSP: 05 5B 05 00 C0 02 00 XX XX */
    CAPID_SUB_CMD_WRITE_RG,        /* CMD: 05 5A 05 00 C0 02 01 XX XX    RSP: 05 5B 04 00 C0 02 01 00    */
    CAPID_SUB_CMD_READ_NVKEY,      /* CMD: 05 5A 03 00 C0 02 02          RSP: 05 5B 05 00 C0 02 02 XX XX */
    CAPID_SUB_CMD_WRITE_NVKEY_RG   /* CMD: 05 5A 05 00 C0 02 03 XX XX    RSP: 05 5B 04 00 C0 02 03 00/01 */
};

/*****************************************************************************
 * FUNCTION DECLARATIONS
 *****************************************************************************/
#ifndef FPGA_ENV
#ifdef HAL_DCXO_MODULE_ENABLED
extern void *hal_dcxo_race_handler(ptr_race_pkt_t pCmdMsg, uint8_t channel_id);
#endif
#ifdef HAL_DVFS_MODULE_ENABLED
extern void *hal_dvfs_race_handler(ptr_race_pkt_t pCmdMsg, uint8_t channel_id);
#endif
extern void *hal_clock_race_handler(ptr_race_pkt_t pCmdMsg, uint8_t channel_id);
#endif /* !FPGA_ENV */

/*****************************************************************************
 * FUNCTION CODES
 *****************************************************************************/
#ifdef HAL_DCXO_MODULE_ENABLED
static void *race_capid_handler(ptr_race_pkt_t pCmdMsg, uint8_t channel_id)
{
    uint8_t *pPayload = pCmdMsg->payload;
    uint8_t  sub_cmd = pPayload[0];
    bool     data_len_err = false, mem_alloc_fail = false;
    void    *pRtnPayload = NULL;
    uint16_t data_len = pCmdMsg->hdr.length - 2; /* not count RACE ID */
    uint16_t capid_val;

    if (data_len) {
        switch (sub_cmd) {
            case CAPID_SUB_CMD_READ_RG:
                //race_clk_log_info("CAPID_READ_RG", 0);
                pRtnPayload = RACE_ClaimPacketAppID(pCmdMsg->hdr.pktId.field.app_id,
                                                    (uint8_t)RACE_TYPE_RESPONSE,
                                                    (uint16_t)RACE_ID_CAPID,
                                                    (uint16_t)sizeof(race_clk_common_uint16_val_only_t),
                                                    channel_id);
                if (pRtnPayload) {
                    capid_val = get_capid_rg();
                    ((race_clk_common_uint16_val_only_t *)pRtnPayload)->sub_cmd = sub_cmd;
                    ((race_clk_common_uint16_val_only_t *)pRtnPayload)->val = capid_val;
                    race_clk_log_info("CAPID RG value 0x%04X", 1, capid_val);
                }
                else {
                    mem_alloc_fail = true;
                }
                break;
            case CAPID_SUB_CMD_WRITE_RG:
                if (data_len >= 3) {
                    capid_val = pPayload[2];
                    capid_val <<= 8;
                    capid_val += pPayload[1];
                    //race_clk_log_info("CAPID_WRITE_RG 0x%04X", 1, capid_val);
                    if (capid_val <= CAPID_VAL_MAX) {
                        pRtnPayload = RACE_ClaimPacketAppID(pCmdMsg->hdr.pktId.field.app_id,
                                                            (uint8_t)RACE_TYPE_RESPONSE,
                                                            (uint16_t)RACE_ID_CAPID,
                                                            (uint16_t)sizeof(race_clk_common_uint8_val_only_t),
                                                            channel_id);
                        if (pRtnPayload) {
                            set_capid_rg(capid_val);
                            ((race_clk_common_uint8_val_only_t *)pRtnPayload)->sub_cmd = sub_cmd;
                            ((race_clk_common_uint8_val_only_t *)pRtnPayload)->val = (uint8_t)RACE_ERRCODE_SUCCESS;
                            race_clk_log_info("CAPID RG value 0x%04X", 1, get_capid_rg());
                        }
                        else {
                            mem_alloc_fail = true;
                        }
                    }
                    else {
                        race_clk_log_err("Invalid CAPID value", 0);
                    }
                }
                else {
                    data_len_err = true;
                }
                break;

#ifdef CONFIG_AIR_NVKEY_ENABLE
            case CAPID_SUB_CMD_READ_NVKEY:
                //race_clk_log_info("CAPID_READ_NVKEY", 0);
                pRtnPayload = RACE_ClaimPacketAppID(pCmdMsg->hdr.pktId.field.app_id,
                                                    (uint8_t)RACE_TYPE_RESPONSE,
                                                    (uint16_t)RACE_ID_CAPID,
                                                    (uint16_t)sizeof(race_clk_common_uint16_val_only_t),
                                                    channel_id);
                if (pRtnPayload) {
                    capid_val = get_capid_nvdm();
                    ((race_clk_common_uint16_val_only_t *)pRtnPayload)->sub_cmd = sub_cmd;
                    ((race_clk_common_uint16_val_only_t *)pRtnPayload)->val = capid_val;
                    race_clk_log_info("CAPID NVKEY value 0x%04X", 1, capid_val);
                }
                else {
                    mem_alloc_fail = true;
                }
                break;
            case CAPID_SUB_CMD_WRITE_NVKEY_RG:
                if (data_len >= 3) {
                    capid_val = pPayload[2];
                    capid_val <<= 8;
                    capid_val += pPayload[1];
                    //race_clk_log_info("CAPID_WRITE_NVKEY_RG 0x%04X", 1, capid_val);
                    if (capid_val <= CAPID_VAL_MAX) {
                        pRtnPayload = RACE_ClaimPacketAppID(pCmdMsg->hdr.pktId.field.app_id,
                                                            (uint8_t)RACE_TYPE_RESPONSE,
                                                            (uint16_t)RACE_ID_CAPID,
                                                            (uint16_t)sizeof(race_clk_common_uint8_val_only_t),
                                                            channel_id);
                        if (pRtnPayload) {
                            ((race_clk_common_uint8_val_only_t *)pRtnPayload)->sub_cmd = sub_cmd;
                            nvkey_status_t status = set_capid_nvdm(capid_val);
                            if (status == NVKEY_STATUS_OK) {
                                set_capid_rg(capid_val);
                                ((race_clk_common_uint8_val_only_t *)pRtnPayload)->val = (uint8_t)RACE_ERRCODE_SUCCESS;
                                //race_clk_log_info("CAPID NVKEY value 0x%04X", 1, get_capid_nvdm());
                                //race_clk_log_info("CAPID RG value 0x%04X", 1, get_capid_rg());
                                race_clk_log_info("CAPID NVKEY value 0x%04X, RG value 0x%04X", 2, get_capid_nvdm(), get_capid_rg());
                            }
                            else {
                                race_clk_log_err("Write CAPID NVKEY fail %d", 1, status);
                                ((race_clk_common_uint8_val_only_t *)pRtnPayload)->val = (uint8_t)RACE_ERRCODE_FAIL;
                            }
                        }
                        else {
                            mem_alloc_fail = true;
                        }
                    }
                    else {
                        race_clk_log_err("Invalid CAPID value", 0);
                    }
                }
                else {
                    data_len_err = true;
                }
                break;
#endif /* CONFIG_AIR_NVKEY_ENABLE */

            default:
                race_clk_log_err("CAPID sub_cmd 0x%02X not supported", 1, sub_cmd);
                break;
        }
    }
    else {
        data_len_err = true;
    }
    if (data_len_err) {
        race_clk_log_err("CAPID data_len %d error", 1, data_len);
    }
    if (mem_alloc_fail) {
        race_clk_log_err("CAPID mem alloc fail", 0);
    }
    return pRtnPayload;
}
#endif /* HAL_DCXO_MODULE_ENABLED */

void *RACE_CmdHandler_clock(ptr_race_pkt_t pRaceHeaderCmd, uint16_t length, uint8_t channel_id)
{
    void *pRtn = NULL;

    race_clk_log_info("CmdHandler: ch 0x%02X, type 0x%02X, race id 0x%04X, data len %d", 4,
                      channel_id, pRaceHeaderCmd->hdr.type, pRaceHeaderCmd->hdr.id, length-2);

    if (pRaceHeaderCmd->hdr.type == RACE_TYPE_COMMAND) {
        switch (pRaceHeaderCmd->hdr.id) {
#ifdef HAL_DCXO_MODULE_ENABLED
            case RACE_ID_CAPID:
                pRtn = race_capid_handler(pRaceHeaderCmd, channel_id);
                break;
#endif /* HAL_DCXO_MODULE_ENABLED */

#ifndef FPGA_ENV
#ifdef HAL_DCXO_MODULE_ENABLED
            case RACE_ID_DCXO:
                pRtn = hal_dcxo_race_handler(pRaceHeaderCmd, channel_id);
                break;
#endif /* HAL_DCXO_MODULE_ENABLED */

#ifdef HAL_DVFS_MODULE_ENABLED
            case RACE_ID_DVFS:
                pRtn = hal_dvfs_race_handler(pRaceHeaderCmd, channel_id);
                break;
#endif /* HAL_DVFS_MODULE_ENABLED */

            case RACE_ID_CLOCK:
                pRtn = hal_clock_race_handler(pRaceHeaderCmd, channel_id);
                break;
#endif /* !FPGA_ENV */

            default:
                //race_clk_log_err("CmdHandler: RACE_ID 0x%04X not supported", 1, pRaceHeaderCmd->hdr.id);
                break;
        }
    }
    //else {
    //    race_clk_log_err("CmdHandler: RACE_TYPE 0x%02X not supported", 1, pRaceHeaderCmd->hdr.type);
    //}
    return pRtn;
}

#endif /* RACE_CLOCK_CMD_ENABLE */

