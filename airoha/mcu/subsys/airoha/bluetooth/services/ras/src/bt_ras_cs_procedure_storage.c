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

#include <errno.h>
#include <zephyr/types.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/sys/atomic.h>
#include <zephyr/sys/slist.h>
#include <zephyr/sys/iterable_sections.h>
#include <zephyr/bluetooth/conn.h>
#include <zephyr/bluetooth/cs.h>
#include "../inc/bt_ras.h"

#include "../inc/bt_ras_internal.h"

LOG_MODULE_DECLARE(bt_ras_rrsp, CONFIG_BT_RAS_RRSP_LOG_LEVEL);
/************************************************
* Macro
*************************************************/
#define BT_RAS_RRSP_CS_PROCEDURS_STORED (CONFIG_BT_MAX_CONN * CONFIG_BT_RAS_RRSP_CS_PROCEDURS_STORED_PER_CONN)


/************************************************
* Struct
*************************************************/
typedef struct {
    int8_t selected_tx_power;
    uint32_t cs_procedure_counter_discarded;
} bt_ras_cs_procedure_info_t;
/************************************************
* Variables
*************************************************/

/************************************************
* Prototype
*************************************************/
static bt_ras_cs_procedure_info_t g_bt_ras_cs_procedure_info[CONFIG_BT_MAX_CONN];
static bt_ras_cs_procedure_storage_t g_bt_ras_cs_procedure_storage_pool[BT_RAS_RRSP_CS_PROCEDURS_STORED];
/************************************************
* Static functions
*************************************************/
static bt_ras_cs_procedure_storage_t *bt_ras_cs_procedure_storage_find(struct bt_conn *conn, uint16_t ranging_counter)
{
	for (uint32_t i = 0; i < ARRAY_SIZE(g_bt_ras_cs_procedure_storage_pool); i++) {
		if (g_bt_ras_cs_procedure_storage_pool[i].conn == conn &&
		    g_bt_ras_cs_procedure_storage_pool[i].ranging_counter == ranging_counter) {
			return &g_bt_ras_cs_procedure_storage_pool[i];
		}
	}

	return NULL;
}

static void bt_ras_cs_procedure_storage_init(struct bt_conn *conn,
    bt_ras_cs_procedure_storage_t *storage, uint16_t procedure_counter)
{
    if (!storage) {
        return;
    }
	storage->conn = bt_conn_ref(conn);
	storage->procedure_counter = procedure_counter;
	storage->ranging_counter = BT_RAS_GET_RANGING_COUNTER(procedure_counter);
	storage->subevent_cursor = 0;
    storage->oom_occur = false;
	//storage->taken = false;
	storage->ready = false;
}

static bt_ras_cs_procedure_storage_t *bt_ras_cs_procedure_storage_allocate(struct bt_conn *conn, uint16_t procedure_counter)
{
	uint16_t storage_used_counter = 0;//The storages has been used by this connection
	uint16_t procedure_counter_age_max = 0;
	uint16_t procedure_counter_age = 0;
	bt_ras_cs_procedure_storage_t *storage_idle = NULL;
	bt_ras_cs_procedure_storage_t *storage_oldest = NULL;
    bt_ras_cs_procedure_storage_t *p_storage = NULL;

	for (uint32_t i = 0; i < ARRAY_SIZE(g_bt_ras_cs_procedure_storage_pool); i++) {
        p_storage = &g_bt_ras_cs_procedure_storage_pool[i];

		if (p_storage->conn == conn) {
			storage_used_counter++;

            if (procedure_counter >= p_storage->procedure_counter) {
                procedure_counter_age = procedure_counter - p_storage->procedure_counter;
            }
            else {
                procedure_counter_age = procedure_counter + BT_RAS_CS_PROCEDURE_COUNTER_INVALID - p_storage->procedure_counter;
            }
			/*
			    RAS V1.0 section 3.3.2.1 Get Ranging Data procedure
                The RAS Server shall have memory to record at least one complete Ranging Data for one CS Procedure.
                If a RAS Server only has enough memory for one CS Procedure, then the Ranging Data Overwritten characteristic
                or a new Ranging Data Ready indication shall be sent once the CS Procedure result is received from local Core
                Controller. If the RAS Server has enough memory to record Ranging Data of additional CS Procedures, then the
                RAS Server may wait until the end of the ongoing Ranging Data transfer and then send a new Ranging Data Ready
                indication (see Section 3.4) to the client.
			*/
			if (procedure_counter_age > procedure_counter_age_max) {
				procedure_counter_age_max = procedure_counter_age;
				storage_oldest = p_storage;
			}
		}
        // Findout the storage that have no ranging data stored.
		if (storage_idle == NULL && p_storage->conn == NULL) {
			storage_idle = p_storage;
		}
	}

	// There is enough storage to store new one.
	if (storage_used_counter < CONFIG_BT_RAS_RRSP_CS_PROCEDURS_STORED_PER_CONN) {
		bt_ras_cs_procedure_storage_init(conn, storage_idle, procedure_counter);
		return storage_idle;
	}

	// There is not enough storage to store new one, so must reuse thed oldest one.
	if (storage_oldest != NULL) {
		bt_ras_rrsp_ranging_data_overwritten(conn, storage_oldest->ranging_counter);
		bt_ras_cs_procedure_storage_free(storage_oldest);
		bt_ras_cs_procedure_storage_init(conn, storage_oldest, procedure_counter);
		return storage_oldest;
	}

	return NULL;
}

static void bt_ras_cs_procedure_enable_complete(struct bt_conn *conn, uint8_t status,
				 struct bt_conn_le_cs_procedure_enable_complete *params)
{
	uint8_t conn_index = bt_conn_index(conn);

	if ((status == BT_HCI_ERR_SUCCESS) && (conn_index < ARRAY_SIZE(g_bt_ras_cs_procedure_info))) {
		g_bt_ras_cs_procedure_info[conn_index].selected_tx_power = params->selected_tx_power;
		g_bt_ras_cs_procedure_info[conn_index].cs_procedure_counter_discarded = BT_RAS_CS_PROCEDURE_COUNTER_INVALID;
	}
}

static bool bt_ras_process_step_data(struct bt_le_cs_subevent_step *step, void *user_data)
{
	bt_ras_cs_procedure_storage_t *storage = (bt_ras_cs_procedure_storage_t *)user_data;

	uint16_t offset = storage->subevent_cursor + BT_RAS_STEP_MODE_LEN + step->data_len;

	if (offset > BT_RAS_PROCEDURE_SUBEVENTS_MEM) {
        storage->oom_occur = true;
		LOG_ERR("[RAS][OOM] There is no memory for step data of subevent: procedure_counter 0x%x offset %u ,subevents_storage_size: %u",
            storage->procedure_counter, offset, BT_RAS_PROCEDURE_SUBEVENTS_MEM);
		return false;
	}
    /*
    Bit 0-1: Mode type; range: 0x00-0x03
    Bit 2-6: RFU
    Bit 7: 1 means Aborted, 0 means Success
    If the Step is aborted and bit 7 is set to 1, then bits 0-6 do not contain any valid data and the length of Step_Data [i] is 0.
    */
	storage->procedure.subevents[storage->subevent_cursor] = step->mode;
	storage->subevent_cursor += BT_RAS_STEP_MODE_LEN;

	memcpy(&storage->procedure.subevents[storage->subevent_cursor], step->data, step->data_len);
	storage->subevent_cursor += step->data_len;

	return true;
}

static void bt_ras_cs_subevent_data_available(struct bt_conn *conn,
				    struct bt_conn_le_cs_subevent_result *result)
{
    uint16_t procedure_counter = result->header.procedure_counter;
	uint16_t ranging_counter = BT_RAS_GET_RANGING_COUNTER(procedure_counter);

	LOG_DBG("[RAS] Procedure counter 0x%x ranging_counter:0x%x", procedure_counter, ranging_counter);
	bt_ras_cs_procedure_storage_t *ranging_data_storage = bt_ras_cs_procedure_storage_find(conn, ranging_counter);

	uint8_t conn_index = bt_conn_index(conn);

	if(conn_index >= ARRAY_SIZE(g_bt_ras_cs_procedure_info)) {
		LOG_ERR("[RAS] subevent_data_available conn_index %d > ARRAY SIZE", conn_index);
        return;
    }

	if (g_bt_ras_cs_procedure_info[conn_index].cs_procedure_counter_discarded == procedure_counter) {
		/* This procedure will not be sent to the peer, so ignore all data. */
		LOG_WRN("[RAS] discard subevent data for procedure %u", procedure_counter);
		return;
	}

	if (!ranging_data_storage) {
		/* The first subevent of the procedure, allocate a storage */
		ranging_data_storage = bt_ras_cs_procedure_storage_allocate(conn, procedure_counter);

		if (!ranging_data_storage) {
			LOG_ERR("[RAS] Failed to allocate storage for procedure %u", procedure_counter);
			g_bt_ras_cs_procedure_info[conn_index].cs_procedure_counter_discarded = procedure_counter;
			return;
		}
        g_bt_ras_cs_procedure_info[conn_index].cs_procedure_counter_discarded = BT_RAS_CS_PROCEDURE_COUNTER_INVALID;
		ranging_data_storage->procedure.ranging_header.ranging_counter = ranging_counter;
		ranging_data_storage->procedure.ranging_header.config_id = result->header.config_id;
		ranging_data_storage->procedure.ranging_header.selected_tx_power = g_bt_ras_cs_procedure_info[conn_index].selected_tx_power;
		ranging_data_storage->procedure.ranging_header.antenna_paths_mask = BIT_MASK(result->header.num_antenna_paths);
	}
    else {
        if (ranging_data_storage->ready) {
            LOG_WRN("[RAS] The procedure %u is aborted or complete", procedure_counter);
            return;
        }
    }
	bt_ras_subevent_header_t *subevent_header = (bt_ras_subevent_header_t *)&ranging_data_storage->procedure.subevents[ranging_data_storage->subevent_cursor];

	ranging_data_storage->subevent_cursor += sizeof(bt_ras_subevent_header_t);

	if (ranging_data_storage->subevent_cursor > BT_RAS_PROCEDURE_SUBEVENTS_MEM) {
        ranging_data_storage->oom_occur = true;
		LOG_ERR("[RAS][OOM] There is no memory for subevent: procedure_counter %u offset %u ,subevents_storage_size: %u",
            procedure_counter, ranging_data_storage->subevent_cursor, BT_RAS_PROCEDURE_SUBEVENTS_MEM);
	}
    else {
    	subevent_header->start_acl_conn_event = result->header.start_acl_conn_event;
    	subevent_header->freq_compensation = result->header.frequency_compensation;
    	subevent_header->ranging_done_status = result->header.procedure_done_status;
    	subevent_header->subevent_done_status = result->header.subevent_done_status;
    	subevent_header->ranging_abort_reason = result->header.procedure_abort_reason;
    	subevent_header->subevent_abort_reason = result->header.subevent_abort_reason;
    	subevent_header->reference_power_level = result->header.reference_power_level;

    	if (result->header.subevent_done_status == BT_CONN_LE_CS_SUBEVENT_ABORTED) {
            /* Core 6.1 Part E Section 7.7.65.44 LE CS Subevent Result event
               Num_Steps_Reported: A Controller may return a value 0 when a subevent is aborted.
           */
    		subevent_header->num_steps_reported = 0;
    		LOG_DBG("[RAS] Discarding %u steps in aborted subevent", result->header.num_steps_reported);
    	} else {
    		subevent_header->num_steps_reported = result->header.num_steps_reported;

    		if (result->step_data_buf) {
    			struct net_buf_simple_state buf_state;

    			net_buf_simple_save(result->step_data_buf, &buf_state);
    			bt_le_cs_step_data_parse(result->step_data_buf, bt_ras_process_step_data, ranging_data_storage);
    			net_buf_simple_restore(result->step_data_buf, &buf_state);
    		}
    	}
    }

	if (subevent_header->ranging_done_status == BT_CONN_LE_CS_PROCEDURE_COMPLETE ||
	    subevent_header->ranging_done_status == BT_CONN_LE_CS_PROCEDURE_ABORTED) {
	    //3.4.2 Ranging Data Ready behavior
	    //When the CS Procedure is completed or multiple CS Subevent Results are received from the local Core Controller
	    if (ranging_data_storage->oom_occur) {
			g_bt_ras_cs_procedure_info[conn_index].cs_procedure_counter_discarded = procedure_counter;
		    bt_ras_cs_procedure_storage_free(ranging_data_storage);
            return;
        }
		ranging_data_storage->ready = true;
		bt_ras_rrsp_new_ranging_data_ready(conn, ranging_counter);
	}
}

static void bt_ras_disconnected(struct bt_conn *conn, uint8_t reason)
{
	for (uint32_t i = 0; i < ARRAY_SIZE(g_bt_ras_cs_procedure_storage_pool); i++) {
		if (g_bt_ras_cs_procedure_storage_pool[i].conn == conn) {
			bt_ras_cs_procedure_storage_free(&g_bt_ras_cs_procedure_storage_pool[i]);
		}
	}
}

BT_CONN_CB_DEFINE(conn_callbacks) = {
	.le_cs_procedure_enable_complete = bt_ras_cs_procedure_enable_complete,
	.le_cs_subevent_data_available = bt_ras_cs_subevent_data_available,
	.disconnected = bt_ras_disconnected,
};

/************************************************
* Public functions
*************************************************/
bt_ras_cs_procedure_storage_t *bt_ras_cs_procedure_storage_take(struct bt_conn *conn, uint16_t ranging_counter)
{
	bt_ras_cs_procedure_storage_t *storage = bt_ras_cs_procedure_storage_find(conn, ranging_counter);

	//if (storage) {
	//	storage->taken = true;
	//	return storage;
	//}

	return storage;
}

uint16_t bt_ras_cs_procedure_storage_pull_data(bt_ras_cs_procedure_storage_t *storage,
    uint8_t *out, uint16_t out_len,
	uint16_t *offset, bool *empty)
{
	if (!storage || !storage->ready || !out || !offset || !empty) {
		return 0;
	}

	uint16_t total = sizeof(bt_ras_ranging_header_t) + storage->subevent_cursor;
	uint16_t remaining = total - (*offset);
	uint16_t copy_len = MIN(out_len, remaining);
    if (*offset > total) {
		LOG_ERR("[RAS][ERR] Get ranging data offset %u > total %u", offset, total);
        return 0;
    }
	memcpy(out, &storage->procedure.buf[*offset], copy_len);
	*offset += copy_len;
	*empty = (remaining == copy_len);

	return copy_len;
}

void bt_ras_cs_procedure_storage_free(bt_ras_cs_procedure_storage_t *storage)
{
    if (!storage) {
        return;
    }
	if (storage->conn) {
		bt_conn_unref(storage->conn);
	}

	storage->conn = NULL;
}

