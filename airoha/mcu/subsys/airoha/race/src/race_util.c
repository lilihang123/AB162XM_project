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
#include "hal_gpt.h"
#ifdef MTK_NVDM_ENABLE
#include "nvdm.h"
#endif
#ifdef MTK_BATTERY_MANAGEMENT_ENABLE
#include "battery_management_core.h"
#endif
#ifdef RACE_FOTA_CMD_ENABLE
#include "fota_flash.h"
#endif
#include "race_util.h"
#include "race_xport.h"
#include "hal_nvic_internal.h"
#ifdef AIR_BATTERY_MANAGEMENT_ENABLE
#include "bm_cust.h"
#endif
//K_MUTEX_DEFINE(race_cmd_mutex);
//static struct k_mutex race_mutex;
struct k_msgq race_queue;

static uint8_t g_factory_test_mode = 0xff;

uint32_t race_get_curr_time_in_ms(void)
{
    uint32_t count = 0;
    uint64_t count64 = 0;

    hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_32K, &count);
    count64 = ((uint64_t)count) * 1000 / 32768;
    return (uint32_t)count64;
}


uint32_t race_get_duration_in_ms(uint32_t start_time, uint32_t end_time)
{
    uint32_t duration = 0;

    /* Normally, it is rare or impossble for race cmd case that the duration takes just a round. On the contrary, the timer check may
     * be executed just after the timer is started. And in such case, the start_timer and end_timer may be equal. Therefore, processing
     * the end_time == start_timer in the if block.
     */
    if (end_time >= start_time) {
        duration = end_time - start_time;
    } else {
        duration = end_time + ((uint64_t)0xFFFFFFFF + 1) * 1000 / 32768 - start_time;
    }

    return duration;
}

int32_t race_get_battery_level(void)
{
#ifdef AIR_BATTERY_MANAGEMENT_ENABLE
    int32_t battery_level = bm_get_info(BM_SOC);
    LOG_INF("race_get_battery_level :%d", battery_level);
    return battery_level;
#else
    return 100;
#endif
}

void *race_pointer_cnv_send_pkt_to_pkt(race_send_pkt_t *pPacket)
{
    void *pNoti = NULL;

    if (pPacket) {
        pNoti = pPacket->race_data.payload;
    }

    //RACE_LOG_MSGID_I("race_pointer_cnv_send_pkt_to_pkt, send_pkt[0x%x], noti[0x%x]", 2, pPacket, pPacket->race_data.payload);
    return pNoti;
}


race_send_pkt_t *race_pointer_cnv_pkt_to_send_pkt(void *pNoti)
{
    race_send_pkt_t *send_pkt = NULL;

    if (pNoti) {
        race_pkt_t *pkt = NULL;

        /* Convert payload pointer to the pointer points to the begining of the whole package. */
        pkt = RACE_CONTAINER_OF(pNoti, race_pkt_t, payload);
        send_pkt = RACE_CONTAINER_OF(pkt, race_send_pkt_t, race_data);
    }

    //RACE_LOG_MSGID_I("race_pointer_cnv_pkt_to_send_pkt, send_pkt[0x%x], pNoti[0x%x]", 2, send_pkt, pNoti);

    return send_pkt;
}


race_recipient_type_enum race_recipient_type_convt(uint8_t recipient)
{
    LOG_INF("race_recipient_type_convt, recipient[0x%x]", recipient);

    if ((RACE_CMD_RECIPIENT_AGENT & recipient) &&
        (RACE_CMD_RECIPIENT_PARTNER & recipient)) {
        //RACE_LOG_MSGID_I("recipient_type:%d", 1, RACE_RECIPIENT_TYPE_AGENT_PARTNER);
        return RACE_RECIPIENT_TYPE_AGENT_PARTNER;
    } else if (RACE_CMD_RECIPIENT_AGENT & recipient) {
        //RACE_LOG_MSGID_I("recipient_type:%d", 1, RACE_RECIPIENT_TYPE_AGENT_ONLY);
        return RACE_RECIPIENT_TYPE_AGENT_ONLY;
    } else if (RACE_CMD_RECIPIENT_PARTNER & recipient) {
        //RACE_LOG_MSGID_I("recipient_type:%d", 1, RACE_RECIPIENT_TYPE_PARTNER_ONLY);
        return RACE_RECIPIENT_TYPE_PARTNER_ONLY;
    }

    //RACE_LOG_MSGID_I("recipient_type:%d", 1, RACE_RECIPIENT_TYPE_NONE);
    return RACE_RECIPIENT_TYPE_NONE;
}


RACE_ERRCODE race_recipient_param_parse(uint8_t recipient_count,
                                        uint8_t *recipient_param,
                                        uint8_t recipient_param_size,
                                        uint8_t **agent_recipient_param,
                                        uint8_t **partner_recipient_param)
{
    race_recipient_param_general_struct *recipient_param_tmp = NULL;

    if (0 == recipient_count || 2 < recipient_count ||
        !recipient_param || !recipient_param_size ||
        !agent_recipient_param || *agent_recipient_param ||
        !partner_recipient_param || *partner_recipient_param) {
        return RACE_ERRCODE_PARAMETER_ERROR;
    }

    do {
        recipient_param_tmp = (race_recipient_param_general_struct *)recipient_param;
        if (RACE_RECIPIENT_PARAM_RECIPIENT_AGENT == recipient_param_tmp->recipient) {
            if (*agent_recipient_param) {
                return RACE_ERRCODE_PARAMETER_ERROR;
            }
            *agent_recipient_param = (uint8_t *)recipient_param_tmp;
        } else if (RACE_RECIPIENT_PARAM_RECIPIENT_PARTNER == recipient_param_tmp->recipient) {
            if (*partner_recipient_param) {
                return RACE_ERRCODE_PARAMETER_ERROR;
            }
            *partner_recipient_param = (uint8_t *)recipient_param_tmp;
        } else {
            return RACE_ERRCODE_NOT_SUPPORT;
        }

        recipient_param += recipient_param_size;
    } while (--recipient_count);

    if ((!(*agent_recipient_param)) && (!(*partner_recipient_param))) {
        return RACE_ERRCODE_PARAMETER_ERROR;
    }

    return RACE_ERRCODE_SUCCESS;
}


void *race_mem_alloc(uint32_t size)
{
    void *memory = NULL;
    memory = k_malloc(size);
    if (memory != NULL) {
        memset(memory, 0, size);
    }
    return memory;
}

void race_mem_free(void *buf)
{
    LOG_INF("race_mem_free, buf[0x%X]", buf);
    if (buf) {
        k_free(buf);
        buf = NULL;
    }
}

int race_queue_create(uint32_t queue_length, uint32_t item_size)
{
    int result = 0;
    result = k_msgq_alloc_init(&race_queue, item_size, queue_length);
    return result;
}

uint32_t race_queue_get_msg_num(struct k_msgq *msgq)
{
    uint32_t queue_item_num;
    queue_item_num = k_msgq_num_used_get(msgq);
    return queue_item_num;
}

bool race_queue_send(struct k_msgq *msgq, const void *data, k_timeout_t timeout)
{
    int result = 0;
    result = k_msgq_put(msgq, data, timeout);
    return (0 == result);
}

int race_queue_receive_wait(struct k_msgq *msgq, void *data, k_timeout_t delay_time)
{
    return k_msgq_get(msgq, data, delay_time);
}

void race_set_factory_mode(uint8_t mode)
{
    g_factory_test_mode = mode;
}

bool race_get_factory_mode()
{
    if (g_factory_test_mode == 0x31) {
        return true;
    } else {
        return false;
    }
    return false;
}

