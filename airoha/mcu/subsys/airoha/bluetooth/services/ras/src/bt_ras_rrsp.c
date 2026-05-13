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
#include <zephyr/bluetooth/conn.h>
#include <zephyr/bluetooth/uuid.h>
#include <zephyr/bluetooth/gatt.h>
#include <zephyr/sys/__assert.h>
#include <zephyr/net/buf.h>
#include "../inc/bt_ras_internal.h"
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(bt_ras_rrsp, CONFIG_BT_RAS_RRSP_LOG_LEVEL);

/************************************************
* Macro
*************************************************/

/**
 *  @brief Client Characteristic Configuration Declaration Macro.
 *
 *  Helper macro to declare a CCC attribute.
 *
 *  @param _changed Configuration changed callback.
 *  @param _perm CCC access permissions,
 *               a bitmap of @ref bt_gatt_perm values.
 */
#define BT_GATT_CCC_WRITE_MANAGED(_write, _perm)				\
	BT_GATT_CCC_MANAGED(((struct _bt_gatt_ccc[])			\
		{BT_GATT_CCC_INITIALIZER(NULL, _write, NULL)}), _perm)


#define BT_RAS_RRSP_WORK_QUEUE_STACK_SIZE 1024
#define BT_RAS_RRSP_RETENTION_TIMEOUT	  K_MSEC(5000)  //The max value is 10s


/************************************************
* Struct
*************************************************/
typedef struct {
	struct bt_conn *conn;

	struct k_work ranging_data_send_work;
	struct k_work ranging_data_ready_and_or_overwritten_work;// overwritten must be sent before ready
	struct k_work ras_cp_work;
	struct k_work_delayable ranging_data_retention_work;

	struct bt_gatt_indicate_params ranging_data_ind_params;
	struct bt_gatt_indicate_params ras_cp_ind_params;
	struct bt_gatt_indicate_params ranging_data_ready_params;
	struct bt_gatt_indicate_params ranging_data_overwritten_params;


    bt_ras_cs_procedure_storage_t *ranging_data;
    bt_ras_cp_res_t ras_cp_result;
    bt_ras_cp_res_t ras_cp_result_cache;
	uint16_t ranging_counter_ready;
	uint16_t ranging_counter_overwritten;
	uint16_t ranging_counter_getting;

	uint16_t segment_counter;
	uint16_t ranging_data_sent;
    uint16_t first_segment_index;// for get_lost_segment
	uint16_t last_segment_index;// for get_lost_segment

    bool rreq_is_receiving;// RX Get CMD
	bool ranging_data_ready_wait_to_send;
	bool ranging_data_overwritten_wait_to_send;
	bool ras_cp_result_cache_wait_to_send;
	bool get_lost_segment;
} bt_ras_rrsp_info_t;

/************************************************
* Variables
*************************************************/
K_THREAD_STACK_DEFINE(g_bt_ras_rrsp_work_queue_stack_area, BT_RAS_RRSP_WORK_QUEUE_STACK_SIZE);
static struct k_work_q g_bt_ras_rrsp_work_queue;
static bt_ras_features_t g_bt_ras_rrsp_features = BT_RAS_FEATURES_RETRIEVE_LOST_RANG_DATA_SEG | BT_RAS_FEATURES_ABORT_OPERATION;
static bt_ras_rrsp_info_t g_bt_ras_rrsp_info[CONFIG_BT_MAX_CONN];

NET_BUF_SIMPLE_DEFINE_STATIC(g_bt_ras_segment_buf, CONFIG_BT_L2CAP_TX_MTU);

/************************************************
* Prototype
*************************************************/
static ssize_t bt_ras_rrsp_features_read(struct bt_conn *conn,
        const struct bt_gatt_attr *attr, void *buf,
        uint16_t len, uint16_t offset);
static ssize_t bt_ras_rrsp_ondemand_ccc_write_cb(struct bt_conn *conn,
    const struct bt_gatt_attr *attr, uint16_t value);
static ssize_t bt_ras_rrsp_cp_write(struct bt_conn *conn,
    struct bt_gatt_attr const *attr, void const *buf,
    uint16_t len, uint16_t offset, uint8_t flags);
static void bt_ras_rrsp_cp_ccc_changed(struct bt_gatt_attr const *attr, uint16_t value);
static ssize_t bt_ras_rrsp_read_ranging_data_ready(struct bt_conn *conn,
    const struct bt_gatt_attr *attr, void *buf,
    uint16_t len, uint16_t offset);
static void bt_ras_rrsp_ranging_data_ready_ccc_changed(struct bt_gatt_attr const *attr, uint16_t value);
static ssize_t bt_ras_rrsp_read_ranging_data_overwritten(struct bt_conn *conn,
    const struct bt_gatt_attr *attr, void *buf,
    uint16_t len, uint16_t offset);
static void bt_ras_rrsp_ranging_data_overwritten_ccc_changed(struct bt_gatt_attr const *attr, uint16_t value);
static void bt_ras_rrsp_ranging_data_send_work_handler(struct k_work *work);
static void bt_ras_rrsp_cp_work_handler(struct k_work *work);
static void bt_ras_rrsp_ranging_data_ready_and_or_overwritten_work_handler(struct k_work *work);
static void bt_ras_rrsp_ranging_data_retention_work_handler(struct k_work *work);

/************************************************
* Static functions
*************************************************/
BT_GATT_SERVICE_DEFINE(ras_svc,
    BT_GATT_PRIMARY_SERVICE(BT_UUID_RAS),
    /* RAS Features */
    BT_GATT_CHARACTERISTIC(BT_UUID_RAS_FEATURES, BT_GATT_CHRC_READ, BT_GATT_PERM_READ_ENCRYPT,
                   bt_ras_rrsp_features_read, NULL, NULL),
    /* On-demand Ranging Data */
    BT_GATT_CHARACTERISTIC(BT_UUID_ONDEMAND_RANGING_DATA, BT_GATT_CHRC_INDICATE | BT_GATT_CHRC_NOTIFY,
                   BT_GATT_PERM_NONE, NULL, NULL, NULL),
    BT_GATT_CCC_WRITE_MANAGED(bt_ras_rrsp_ondemand_ccc_write_cb,
                   BT_GATT_PERM_READ_ENCRYPT | BT_GATT_PERM_WRITE_ENCRYPT),
    /* RAS Control Point */
    BT_GATT_CHARACTERISTIC(BT_UUID_RAS_CP,
                   BT_GATT_CHRC_WRITE_WITHOUT_RESP | BT_GATT_CHRC_INDICATE,
                   BT_GATT_PERM_WRITE_ENCRYPT, NULL, bt_ras_rrsp_cp_write, NULL),
    BT_GATT_CCC(bt_ras_rrsp_cp_ccc_changed, BT_GATT_PERM_READ_ENCRYPT | BT_GATT_PERM_WRITE_ENCRYPT),
    /* Ranging Data Ready */
    BT_GATT_CHARACTERISTIC(BT_UUID_RANGING_DATA_READY,
                   BT_GATT_CHRC_READ | BT_GATT_CHRC_INDICATE | BT_GATT_CHRC_NOTIFY,
                   BT_GATT_PERM_READ_ENCRYPT, bt_ras_rrsp_read_ranging_data_ready, NULL, NULL),
    BT_GATT_CCC(bt_ras_rrsp_ranging_data_ready_ccc_changed,
            BT_GATT_PERM_READ_ENCRYPT | BT_GATT_PERM_WRITE_ENCRYPT),
    /* Ranging Data Overwritten */
    BT_GATT_CHARACTERISTIC(BT_UUID_RANGING_DATA_OVERWRITTEN,
                   BT_GATT_CHRC_READ | BT_GATT_CHRC_INDICATE | BT_GATT_CHRC_NOTIFY,
                   BT_GATT_PERM_READ_ENCRYPT, bt_ras_rrsp_read_ranging_data_overwritten, NULL, NULL),
    BT_GATT_CCC(bt_ras_rrsp_ranging_data_overwritten_ccc_changed,
            BT_GATT_PERM_READ_ENCRYPT | BT_GATT_PERM_WRITE_ENCRYPT),
);

static bt_ras_rrsp_info_t *bt_ras_rrsp_find(struct bt_conn *conn)
{
    for (uint32_t i = 0; i < CONFIG_BT_MAX_CONN; i++) {
        if (g_bt_ras_rrsp_info[i].conn == conn) {
            return &g_bt_ras_rrsp_info[i];
        }
    }
    LOG_WRN("[RAS] rrsp info is not found");

    return NULL;
}

static void bt_ras_rrsp_connected(struct bt_conn *conn, uint8_t err)
{
	if (err) {
		return;
	}

    bt_ras_rrsp_info_t *p_rrsp_info = bt_ras_rrsp_find(NULL);
    if (p_rrsp_info) {
        memset(p_rrsp_info, 0, sizeof(bt_ras_rrsp_info_t));
        p_rrsp_info->conn = bt_conn_ref(conn);
        k_work_init(&p_rrsp_info->ranging_data_send_work, bt_ras_rrsp_ranging_data_send_work_handler);
        k_work_init(&p_rrsp_info->ranging_data_ready_and_or_overwritten_work, bt_ras_rrsp_ranging_data_ready_and_or_overwritten_work_handler);
        k_work_init(&p_rrsp_info->ras_cp_work, bt_ras_rrsp_cp_work_handler);
        k_work_init_delayable(&p_rrsp_info->ranging_data_retention_work, bt_ras_rrsp_ranging_data_retention_work_handler);
    }
    else {
        LOG_ERR("[RAS] Connection is already max %d", CONFIG_BT_MAX_CONN);
    }
}

static void bt_ras_rrsp_disconnected(struct bt_conn *conn, uint8_t reason)
{
    bt_ras_rrsp_info_t *p_rrsp_info = bt_ras_rrsp_find(conn);
	if (p_rrsp_info) {
		(void)k_work_cancel(&p_rrsp_info->ranging_data_send_work);
		(void)k_work_cancel(&p_rrsp_info->ranging_data_ready_and_or_overwritten_work);
		(void)k_work_cancel(&p_rrsp_info->ras_cp_work);
		(void)k_work_cancel_delayable(&p_rrsp_info->ranging_data_retention_work);

		k_work_queue_drain(&g_bt_ras_rrsp_work_queue, false);

		bt_conn_unref(p_rrsp_info->conn);
		p_rrsp_info->conn = NULL;
	}
}

BT_CONN_CB_DEFINE(conn_callbacks) = {
	.connected = bt_ras_rrsp_connected,
	.disconnected = bt_ras_rrsp_disconnected,
};

static ssize_t bt_ras_rrsp_features_read(struct bt_conn *conn,
    const struct bt_gatt_attr *attr, void *buf,
    uint16_t len, uint16_t offset)
{
    return bt_gatt_attr_read(conn, attr, buf, len, offset, &g_bt_ras_rrsp_features,
                 sizeof(g_bt_ras_rrsp_features));
}

static void bt_ras_rrsp_ranging_data_notify_sent_cb(struct bt_conn *conn, void *user_data)
{
    bt_ras_rrsp_info_t *p_rrsp_info = bt_ras_rrsp_find(conn);

    if (p_rrsp_info) {
        k_work_submit_to_queue(&g_bt_ras_rrsp_work_queue, &p_rrsp_info->ranging_data_send_work);
    }
}

static void bt_ras_rrsp_ranging_data_indicate_sent_cb(struct bt_conn *conn,
                      struct bt_gatt_indicate_params *params, uint8_t err)
{
    bt_ras_rrsp_info_t *p_rrsp_info = bt_ras_rrsp_find(conn);

    if (p_rrsp_info) {
        k_work_submit_to_queue(&g_bt_ras_rrsp_work_queue, &p_rrsp_info->ranging_data_send_work);
    }
}

static int bt_ras_rrsp_ranging_data_indication(struct bt_conn *conn, struct net_buf_simple *buf)
{
    struct bt_gatt_attr *attr;

    bt_ras_rrsp_info_t *p_rrsp_info = bt_ras_rrsp_find(conn);
    if (!p_rrsp_info) {
        return -EINVAL;
    }

    attr = bt_gatt_find_by_uuid(ras_svc.attrs, 0, BT_UUID_ONDEMAND_RANGING_DATA);

    if (!bt_gatt_is_subscribed(conn, attr, BT_GATT_CCC_INDICATE | BT_GATT_CCC_NOTIFY)) {
        LOG_WRN("On-demand ranging data is not subscribed.");
        return -EINVAL;
    }
    /*
        Client enabled both indications and notifications, then the RAS Server shall use notifications to
        transfer Real-time/On-demand Ranging Data in a segmented fashion.
    */
    if (bt_gatt_is_subscribed(conn, attr, BT_GATT_CCC_NOTIFY)) {
        struct bt_gatt_notify_params params = {0};
        params.attr = attr;
        params.uuid = NULL;
        params.data = buf->data;
        params.len = buf->len;
        params.func = bt_ras_rrsp_ranging_data_notify_sent_cb;

        return bt_gatt_notify_cb(conn, &params);
    } else if (bt_gatt_is_subscribed(conn, attr, BT_GATT_CCC_INDICATE)) {
        p_rrsp_info->ranging_data_ind_params.attr = attr;
        p_rrsp_info->ranging_data_ind_params.uuid = NULL;
        p_rrsp_info->ranging_data_ind_params.data = buf->data;
        p_rrsp_info->ranging_data_ind_params.len = buf->len;
        p_rrsp_info->ranging_data_ind_params.func = bt_ras_rrsp_ranging_data_indicate_sent_cb;
        p_rrsp_info->ranging_data_ind_params.destroy = NULL;

        return bt_gatt_indicate(conn, &p_rrsp_info->ranging_data_ind_params);
    }

    return -EINVAL;
}

static int bt_ras_rrsp_cp_indication(struct bt_conn *conn)
{
    bt_ras_rrsp_info_t *p_rrsp_info = bt_ras_rrsp_find(conn);
    if (!p_rrsp_info) {
        return -EINVAL;
    }

    struct bt_gatt_attr *attr = bt_gatt_find_by_uuid(ras_svc.attrs, 0, BT_UUID_RAS_CP);
    if (!bt_gatt_is_subscribed(conn, attr, BT_GATT_CCC_INDICATE)) {
        LOG_WRN("[RAS] RAS CP is not subscribed.");
        return -EINVAL;
    }
    bt_ras_cp_res_t* cp_res = &p_rrsp_info->ras_cp_result;

	NET_BUF_SIMPLE_DEFINE(indication, sizeof(bt_ras_cp_res_t));

	net_buf_simple_add_u8(&indication, cp_res->type);

    switch (cp_res->type) {
        case BT_RAS_CP_RES_COMPLETE_RANG_DATA:
            net_buf_simple_add_le16(&indication, cp_res->complete_ranging_data_params.ranging_counter);
            break;
        case BT_RAS_CP_RES_COMPLETE_LOST_RANG_DATA_SEG:
            net_buf_simple_add_le16(&indication, cp_res->complete_lost_ranging_data_params.ranging_counter);
            net_buf_simple_add_u8(&indication, cp_res->complete_lost_ranging_data_params.first_segment_index);
            net_buf_simple_add_u8(&indication, cp_res->complete_lost_ranging_data_params.last_segment_index);
            break;
        case BT_RAS_CP_RES_CODE:
            net_buf_simple_add_u8(&indication, cp_res->res_params);
            break;

        default:
            break;
    }

    p_rrsp_info->ras_cp_ind_params.attr = attr;
    p_rrsp_info->ras_cp_ind_params.uuid = NULL;
    p_rrsp_info->ras_cp_ind_params.data = indication.data;
    p_rrsp_info->ras_cp_ind_params.len = indication.len;
    p_rrsp_info->ras_cp_ind_params.func = NULL;
    p_rrsp_info->ras_cp_ind_params.destroy = NULL;
    return bt_gatt_indicate(p_rrsp_info->conn, &p_rrsp_info->ras_cp_ind_params);
}

static int bt_ras_rrsp_ranging_data_ready_indication(struct bt_conn *conn)
{
    bt_ras_rrsp_info_t *p_rrsp_info = bt_ras_rrsp_find(conn);
    struct bt_gatt_attr *ranging_data_ready_attr = bt_gatt_find_by_uuid(ras_svc.attrs, 0, BT_UUID_RANGING_DATA_READY);
    if (p_rrsp_info) {
        if (bt_gatt_is_subscribed(conn, ranging_data_ready_attr, BT_GATT_CCC_INDICATE)) {
            p_rrsp_info->ranging_data_ready_params.attr = ranging_data_ready_attr;
            p_rrsp_info->ranging_data_ready_params.uuid = NULL;
            p_rrsp_info->ranging_data_ready_params.data = &p_rrsp_info->ranging_counter_ready;
            p_rrsp_info->ranging_data_ready_params.len = sizeof(uint16_t);
            p_rrsp_info->ranging_data_ready_params.func = NULL;
            p_rrsp_info->ranging_data_ready_params.destroy = NULL;
            return bt_gatt_indicate(conn, &p_rrsp_info->ranging_data_ready_params);
        } else if (bt_gatt_is_subscribed(conn, ranging_data_ready_attr, BT_GATT_CCC_NOTIFY)) {
            return bt_gatt_notify(conn, ranging_data_ready_attr, &p_rrsp_info->ranging_counter_ready, sizeof(uint16_t));
        }
        else {
            LOG_WRN("[RAS] Rang data ready is not subscribed.");
        }
    }
    return -EINVAL;
}

static int bt_ras_rrsp_ranging_data_overwritten_indication(struct bt_conn *conn)
{
    bt_ras_rrsp_info_t *p_rrsp_info = bt_ras_rrsp_find(conn);
    struct bt_gatt_attr *ranging_data_overwritten_attr = bt_gatt_find_by_uuid(ras_svc.attrs, 0, BT_UUID_RANGING_DATA_OVERWRITTEN);
    if (p_rrsp_info) {
        if (bt_gatt_is_subscribed(conn, ranging_data_overwritten_attr, BT_GATT_CCC_INDICATE)) {
            p_rrsp_info->ranging_data_overwritten_params.attr = ranging_data_overwritten_attr;
            p_rrsp_info->ranging_data_overwritten_params.uuid = NULL;
            p_rrsp_info->ranging_data_overwritten_params.data = &p_rrsp_info->ranging_counter_overwritten;
            p_rrsp_info->ranging_data_overwritten_params.len = sizeof(uint16_t);
            p_rrsp_info->ranging_data_overwritten_params.func = NULL;
            p_rrsp_info->ranging_data_overwritten_params.destroy = NULL;
            return bt_gatt_indicate(conn, &p_rrsp_info->ranging_data_overwritten_params);
        } else if (bt_gatt_is_subscribed(conn, ranging_data_overwritten_attr, BT_GATT_CCC_NOTIFY)) {
            return bt_gatt_notify(conn, ranging_data_overwritten_attr, &p_rrsp_info->ranging_counter_overwritten, sizeof(uint16_t));
        }
        else {
            LOG_WRN("[RAS] Rang data overwritten is not subscribed.");
        }
    }
    return -EINVAL;
}

static bt_ras_cp_res_params_t bt_ras_rrsp_cp_command_decode(const uint8_t *buf, uint16_t len,
			       bt_ras_cp_proc_t *proc)
{
	struct net_buf_simple net_buf;
    bt_ras_cp_res_params_t res = BT_RAS_CP_RES_ERR_SUCCESS;

	if (len < sizeof(bt_ras_cp_proc_type_t)) {
		return BT_RAS_CP_RES_ERR_INVALID_PARAMETER;
	}

	net_buf_simple_init_with_data(&net_buf, (void *) buf, len);

	proc->type = net_buf_simple_pull_u8(&net_buf);
	switch (proc->type) {
	case BT_RAS_CP_PROC_GET_RANG_DATA:
		if (net_buf.len != sizeof(bt_ras_cp_get_ranging_data_params_t)) {
			return BT_RAS_CP_RES_ERR_INVALID_PARAMETER;
		}
		proc->get_ranging_data_params.ranging_counter = net_buf_simple_pull_le16(&net_buf);
		break;
	case BT_RAS_CP_PROC_ACK_RANG_DATA:
		if (net_buf.len != sizeof(bt_ras_cp_ack_ranging_data_params_t)) {
			return BT_RAS_CP_RES_ERR_INVALID_PARAMETER;
		}
		proc->ack_ranging_data_params.ranging_counter = net_buf_simple_pull_le16(&net_buf);
		break;
    case BT_RAS_CP_PROC_RETIEVE_LOST_RANG_DATA:
		if (net_buf.len != sizeof(bt_ras_cp_retrieve_lost_ranging_data_seg_params_t)) {
			return BT_RAS_CP_RES_ERR_INVALID_PARAMETER;
		}
		proc->retrieve_lost_ranging_data_seg_params.ranging_counter = net_buf_simple_pull_le16(&net_buf);
		proc->retrieve_lost_ranging_data_seg_params.first_segment_index = net_buf_simple_pull_u8(&net_buf);
		proc->retrieve_lost_ranging_data_seg_params.last_segment_index = net_buf_simple_pull_u8(&net_buf);
		break;
	case BT_RAS_CP_PROC_ABORT:
		if (net_buf.len != 0) {
			return BT_RAS_CP_RES_ERR_INVALID_PARAMETER;
		}
		break;
#if 0
	case BT_RAS_CP_PROC_SET_FILTER:
		if (net_buf.len != sizeof(bt_ras_cp_filter_params_t)) {
			return BT_RAS_CP_RES_ERR_INVALID_PARAMETER;
		}
		proc->set_filter_params.filter = net_buf_simple_pull_le16(&net_buf);
		break;
#endif
    default:
        res = BT_RAS_CP_RES_ERR_OPCODE_NOT_SUPPORTED;
		break;
	}

	return res;
}


static bt_ras_cp_res_params_t bt_ras_rrsp_cp_procedure(
	struct bt_conn *conn,
	bt_ras_cp_proc_t *proc)
{

    //TBD: Check Real-time Ranging Data is enabled, return BT_RAS_CP_RES_ERR_PROCEDURE_NOT_COMPLETED
    /*
        If a request with an Op Code other than Abort Operation is written to the RAS Control Point while the
        RAS Server is performing a previously triggered RAS Control Point procedure (i.e., resulting from
        invalid client behavior), then the RAS Server shall indicate the RAS Control Point with a Response
        Code Op Code and a Response Code Value in the Parameter set to Server Busy.
    */

    bt_ras_rrsp_info_t *p_rrsp_info = bt_ras_rrsp_find(conn);
    if ((p_rrsp_info->ranging_data || k_work_is_pending(&p_rrsp_info->ras_cp_work)) && (BT_RAS_CP_PROC_ABORT != proc->type)) {
        /* RAS V1.0 3.3.2.1 Get Ranging Data procedure: while an On-demand Ranging Data procedure is ongoing, ... Server Busy. */
        return BT_RAS_CP_RES_ERR_SERVER_BUSY;
    }

	switch (proc->type) {
    	case BT_RAS_CP_PROC_GET_RANG_DATA: {
            // Check On-demand Ranging Data is enabled
            struct bt_gatt_attr *attr =	bt_gatt_find_by_uuid(ras_svc.attrs, 0, BT_UUID_ONDEMAND_RANGING_DATA);
            if (!attr) {
                LOG_ERR("[RAS] On-demand Ranging Data characteristic is not found");
                return BT_RAS_CP_RES_ERR_PROCEDURE_NOT_COMPLETED;
            }
            if (!bt_gatt_is_subscribed(conn, attr, BT_GATT_CCC_INDICATE) &&
                !bt_gatt_is_subscribed(conn, attr, BT_GATT_CCC_NOTIFY)) {
                LOG_WRN("[RAS] RREQ not subscribed to On-demand Ranging Data characteristic.");
                return BT_RAS_CP_RES_ERR_PROCEDURE_NOT_COMPLETED;
            }
            p_rrsp_info->ranging_counter_getting = proc->get_ranging_data_params.ranging_counter;

            p_rrsp_info->ranging_data = bt_ras_cs_procedure_storage_take(p_rrsp_info->conn, proc->get_ranging_data_params.ranging_counter);
            if (!p_rrsp_info->ranging_data) {
                return BT_RAS_CP_RES_ERR_NO_RECORDS_FOUND;
            }

            p_rrsp_info->rreq_is_receiving = true;
            p_rrsp_info->get_lost_segment = false;
            p_rrsp_info->first_segment_index = 0;
            p_rrsp_info->last_segment_index = 0;
            p_rrsp_info->ranging_data_sent = 0;
            p_rrsp_info->segment_counter = 0;

            k_work_submit_to_queue(&g_bt_ras_rrsp_work_queue, &p_rrsp_info->ranging_data_send_work);
            break;
        }
    	case BT_RAS_CP_PROC_ACK_RANG_DATA: {
            /*
                If the RAS Server cannot locate any Ranging Data matching the Ranging Counter of the request,
                then the RAS Server shall indicate the RAS Control Point with a Response Code Op Code and
                Response Code Value in the Parameter set to No Records Found. Otherwise, the RAS Server shall
                delete all On-demand Ranging Data matching the requested Ranging Counter.
            */
            bt_ras_cs_procedure_storage_t *storage = bt_ras_cs_procedure_storage_take(p_rrsp_info->conn, proc->ack_ranging_data_params.ranging_counter);
            if (!storage) {
                return BT_RAS_CP_RES_ERR_NO_RECORDS_FOUND;
            }
            k_work_cancel_delayable(&p_rrsp_info->ranging_data_retention_work);

            bt_ras_cs_procedure_storage_free(storage);
            p_rrsp_info->ranging_data_sent = 0;
            p_rrsp_info->rreq_is_receiving = false;
            p_rrsp_info->get_lost_segment = false;
            p_rrsp_info->ranging_counter_getting = BT_RAS_RANGING_COUNTER_INVALID;
            break;
        }
    	case BT_RAS_CP_PROC_RETIEVE_LOST_RANG_DATA: {
           p_rrsp_info->ranging_data = bt_ras_cs_procedure_storage_take(p_rrsp_info->conn, proc->retrieve_lost_ranging_data_seg_params.ranging_counter);
            if ((NULL == p_rrsp_info->ranging_data) ||
                ((p_rrsp_info->segment_counter & BIT_MASK(6)) <= proc->retrieve_lost_ranging_data_seg_params.first_segment_index) ||
                (((p_rrsp_info->segment_counter & BIT_MASK(6)) <= proc->retrieve_lost_ranging_data_seg_params.last_segment_index) &&
                (BT_RAS_UNKNOWN_SEGMENT_NUM <= proc->retrieve_lost_ranging_data_seg_params.last_segment_index))) {
                return BT_RAS_CP_RES_ERR_NO_RECORDS_FOUND;
            }
            if (!k_work_delayable_is_pending(&p_rrsp_info->ranging_data_retention_work) ||
                (p_rrsp_info->ranging_counter_getting != proc->retrieve_lost_ranging_data_seg_params.ranging_counter)) {
                //Complete_Ranging_Data Response is not sent to the client
                return BT_RAS_CP_RES_ERR_INVALID_PARAMETER;
            }
            uint16_t max_ranging_data_len = bt_gatt_get_mtu(conn) - 4;//Indication opcode(1) + ATT Handle(2) + sizeof(bt_ras_segment_header_t) = 4
            p_rrsp_info->get_lost_segment = true;
            p_rrsp_info->first_segment_index = proc->retrieve_lost_ranging_data_seg_params.first_segment_index;
            p_rrsp_info->last_segment_index = proc->retrieve_lost_ranging_data_seg_params.last_segment_index;
            p_rrsp_info->ranging_data_sent = max_ranging_data_len * proc->retrieve_lost_ranging_data_seg_params.first_segment_index;
            p_rrsp_info->segment_counter = proc->retrieve_lost_ranging_data_seg_params.first_segment_index;
            k_work_cancel_delayable(&p_rrsp_info->ranging_data_retention_work);
            k_work_submit_to_queue(&g_bt_ras_rrsp_work_queue, &p_rrsp_info->ranging_data_send_work);
            break;
        }
        case BT_RAS_CP_PROC_ABORT: {
            if (p_rrsp_info->ranging_data) {
                bt_ras_cs_procedure_storage_free(p_rrsp_info->ranging_data);
                p_rrsp_info->ranging_data_sent = 0;
                p_rrsp_info->rreq_is_receiving = false;
                p_rrsp_info->get_lost_segment = false;
                p_rrsp_info->ranging_counter_getting = BT_RAS_RANGING_COUNTER_INVALID;
            }
            break;
        }
        case BT_RAS_CP_PROC_SET_FILTER://The RREQ shall not write the Set_Filter command after enabling Ranging Data notifications or indications.
        default:
            return BT_RAS_CP_RES_ERR_OPCODE_NOT_SUPPORTED;
	}

    return BT_RAS_CP_RES_ERR_SUCCESS;
};

static ssize_t bt_ras_rrsp_cp_write(struct bt_conn *conn,
    struct bt_gatt_attr const *attr, void const *buf,
    uint16_t len, uint16_t offset, uint8_t flags)
{
	bt_ras_cp_proc_t ras_cp_proc = {0};
    bt_ras_cp_res_t result;
    bt_ras_rrsp_info_t *p_rrsp_info = bt_ras_rrsp_find(conn);
    if (!p_rrsp_info) {
		return BT_GATT_ERR(BT_ATT_ERR_UNLIKELY);
    }

	if (!bt_gatt_is_subscribed(conn, attr, BT_GATT_CCC_INDICATE)) {
		LOG_ERR("[RAS] Control Point is not subscribed");
		return BT_GATT_ERR(BT_ATT_ERR_CCC_IMPROPER_CONF);
	}

	if (offset != 0) {
		LOG_ERR("[RAS] Invalid offset of Control Point Write Request");
		return BT_GATT_ERR(BT_ATT_ERR_INVALID_OFFSET);
	}
    result.type = BT_RAS_CP_RES_CODE;
	result.res_params = bt_ras_rrsp_cp_command_decode(buf, len, &ras_cp_proc);
    if (BT_RAS_CP_RES_ERR_SUCCESS == result.res_params) {
        result.res_params = bt_ras_rrsp_cp_procedure(conn, &ras_cp_proc);
    }
	if (k_work_is_pending(&p_rrsp_info->ras_cp_work)) {
        if (!p_rrsp_info->ras_cp_result_cache_wait_to_send) {
            p_rrsp_info->ras_cp_result_cache_wait_to_send = true;
            memcpy(&p_rrsp_info->ras_cp_result_cache, &result, sizeof(bt_ras_cp_res_t));
        }
        else {
            LOG_ERR("[RAS] Can not procss the new request");
            return BT_GATT_ERR(BT_ATT_ERR_PROCEDURE_IN_PROGRESS);
        }
	}
    else {
        memcpy(&p_rrsp_info->ras_cp_result, &result, sizeof(bt_ras_cp_res_t));
        k_work_submit_to_queue(&g_bt_ras_rrsp_work_queue, &p_rrsp_info->ras_cp_work);
    }

    if ((BT_RAS_CP_PROC_GET_RANG_DATA == ras_cp_proc.type) && (BT_RAS_CP_RES_ERR_SUCCESS == p_rrsp_info->ras_cp_result.res_params)) {
        k_work_submit_to_queue(&g_bt_ras_rrsp_work_queue, &p_rrsp_info->ranging_data_send_work);
    }
	return len;
}


static ssize_t bt_ras_rrsp_read_ranging_data_ready(struct bt_conn *conn,
    const struct bt_gatt_attr *attr, void *buf,
    uint16_t len, uint16_t offset)
{
    bt_ras_rrsp_info_t *p_rrsp_info = bt_ras_rrsp_find(conn);

	if (!p_rrsp_info) {
		return BT_GATT_ERR(BT_ATT_ERR_READ_NOT_PERMITTED);
	}

	return bt_gatt_attr_read(conn, attr, buf, len, offset, &p_rrsp_info->ranging_counter_ready,
				 sizeof(uint16_t));
}

static ssize_t bt_ras_rrsp_read_ranging_data_overwritten(struct bt_conn *conn,
    const struct bt_gatt_attr *attr, void *buf,
    uint16_t len, uint16_t offset)
{
    bt_ras_rrsp_info_t *p_rrsp_info = bt_ras_rrsp_find(conn);

	if (!p_rrsp_info) {
		return BT_GATT_ERR(BT_ATT_ERR_READ_NOT_PERMITTED);
	}

	return bt_gatt_attr_read(conn, attr, buf, len, offset, &p_rrsp_info->ranging_counter_overwritten,
				 sizeof(uint16_t));
}

static ssize_t bt_ras_rrsp_ondemand_ccc_write_cb(struct bt_conn *conn,
    const struct bt_gatt_attr *attr, uint16_t value)
{
    //If the RREQ does not enable Real-time Ranging Data notifications or indications,
    //then it shall enable On-demand Ranging Data notifications or indications

	if (!value) {
		LOG_DBG("[RAS] Disable On-demand Ranging Data.");
	} else {
	    // RAS 1.0 Section 2.7: The RAS Server shall operate in either Real-time or On-demand mode, but not both simultaneously. A
	    // If Real-time Ranging Data is supported and is enabled by client, must return BT_GATT_ERR(BT_ATT_ERR_CCC_IMPROPER_CONF).
		LOG_DBG("[RAS] Enable On-demand Ranging Data.");
	}

	return sizeof(value);
}

static void bt_ras_rrsp_cp_ccc_changed(struct bt_gatt_attr const *attr, uint16_t value)
{
	LOG_DBG("[RAS] RAS control point CCCD changed: 0x%04x", value);
}

static void bt_ras_rrsp_ranging_data_ready_ccc_changed(struct bt_gatt_attr const *attr, uint16_t value)
{
	LOG_DBG("[RAS] Ranging Data Ready CCCD changed: 0x%04x", value);
}

static void bt_ras_rrsp_ranging_data_overwritten_ccc_changed(struct bt_gatt_attr const *attr, uint16_t value)
{
	LOG_DBG("[RAS] Ranging Data Overwritten CCCD changed: 0x%04x", value);
}

static int bt_ras_rrsp_range_data_segment_send(bt_ras_rrsp_info_t *p_rrsp_info)
{
    int err;
    if (!p_rrsp_info->conn) {
        LOG_ERR("[RAS] conn is null");
        return -EINVAL;
    }

    /* RAS V1.0 section 3.2.2 Ranging Data segmentation
       If the total size of the received Ranging Data is greater than (ATT_MTU-4), then multiple segments
       shall be sent to transfer the entire Ranging Data Body (the data to be transported).
       Note that the number of segments that need to be sent to convey the data to be transported is
       represented by N, which shall be calculated by dividing the size of the data to be transported
       by (ATT_MTU-4), rounded up to the nearest integer.
     */
    uint16_t max_ranging_data_len = bt_gatt_get_mtu(p_rrsp_info->conn) - 4;//Indication opcode(1) + ATT Handle(2) + sizeof(bt_ras_segment_header_t) = 4

    /* g_bt_ras_segment_buf is only accessed by the RRSP WQ, so is safe to reuse. */
    net_buf_simple_reset(&g_bt_ras_segment_buf);

    bt_ras_ranging_data_segment_t *ranging_data_segment = net_buf_simple_add(&g_bt_ras_segment_buf, sizeof(bt_ras_ranging_data_segment_t) + max_ranging_data_len);
    if (!ranging_data_segment) {
        LOG_ERR("[RAS] Cannot allocate segment buffer");
        return -ENOMEM;
    }

    bool first_seg = (p_rrsp_info->ranging_data_sent == 0);
    bool last_seg;
    uint16_t actual_data_len = bt_ras_cs_procedure_storage_pull_data(p_rrsp_info->ranging_data,
                        ranging_data_segment->ranging_data, max_ranging_data_len,
                        &p_rrsp_info->ranging_data_sent, &last_seg);

    LOG_DBG("[RAS] Got ranging data %u bytes (max: %u) data sent %u last seg %d", actual_data_len, max_ranging_data_len, p_rrsp_info->ranging_data_sent, last_seg);

    if (actual_data_len) {
        ranging_data_segment->header.first_seg = first_seg;
        ranging_data_segment->header.last_seg = last_seg;
        ranging_data_segment->header.seg_counter = p_rrsp_info->segment_counter & BIT_MASK(6);
        if (max_ranging_data_len != actual_data_len) {
            (void)net_buf_simple_remove_mem(&g_bt_ras_segment_buf, (max_ranging_data_len - actual_data_len));
        }
        err = bt_ras_rrsp_ranging_data_indication(p_rrsp_info->conn, &g_bt_ras_segment_buf);
        if (err) {
            LOG_WRN("[RAS] bt_ras_rrsp_ranging_data_indication failed err %d", err);
            p_rrsp_info->ranging_data_sent -= actual_data_len;
            k_work_submit_to_queue(&g_bt_ras_rrsp_work_queue, &p_rrsp_info->ranging_data_send_work);
            return err;
        }
        /*  RAP V1.0 section 4.1 Maximum transmission unit
            If the Ranging Data is segmented to more than 64 segments, then the RREQ does not have a way to retrieve
            a lost segment with a higher index value of 63.
            If last_segment_index == 0xFF, get lost segment from first_segment_index to end. RREQ May lost the last segment.
        */
        if ((p_rrsp_info->get_lost_segment) && (p_rrsp_info->segment_counter >= p_rrsp_info->last_segment_index)) {
            last_seg = true;
        }
        p_rrsp_info->segment_counter++;// Rolling Segment Counter
        LOG_DBG("[RAS] Rolling Segment Counter %d", p_rrsp_info->segment_counter);
    }

    if (last_seg) {
        struct bt_gatt_attr *ondemand_attr = bt_gatt_find_by_uuid(ras_svc.attrs, 0, BT_UUID_ONDEMAND_RANGING_DATA);
        bt_ras_cp_res_t result;

        if (bt_gatt_is_subscribed(p_rrsp_info->conn, ondemand_attr, BT_GATT_CCC_NOTIFY | BT_GATT_CCC_INDICATE)) {
            if (!p_rrsp_info->get_lost_segment) {
                result.type = BT_RAS_CP_RES_COMPLETE_RANG_DATA;
                result.complete_ranging_data_params.ranging_counter = p_rrsp_info->ranging_data->ranging_counter;
            }
            else {
                result.type = BT_RAS_CP_RES_COMPLETE_LOST_RANG_DATA_SEG;
                result.complete_lost_ranging_data_params.ranging_counter = p_rrsp_info->ranging_data->ranging_counter;
                result.complete_lost_ranging_data_params.first_segment_index = p_rrsp_info->first_segment_index;
                result.complete_lost_ranging_data_params.last_segment_index = (p_rrsp_info->segment_counter - 1) & BIT_MASK(6);//p_rrsp_info->last_segment_index;
            }
            p_rrsp_info->ranging_data = NULL;

            if (k_work_is_pending(&p_rrsp_info->ras_cp_work)) {
                if (!p_rrsp_info->ras_cp_result_cache_wait_to_send) {
                    p_rrsp_info->ras_cp_result_cache_wait_to_send = true;
                    memcpy(&p_rrsp_info->ras_cp_result_cache, &result, sizeof(bt_ras_cp_res_t));
                }
                else {
                    LOG_ERR("[RAS] Can not indicate ranging data sent commpletely");
                    return 0;
                }
            }
            else {
                memcpy(&p_rrsp_info->ras_cp_result, &result, sizeof(bt_ras_cp_res_t));
                k_work_submit_to_queue(&g_bt_ras_rrsp_work_queue, &p_rrsp_info->ras_cp_work);
            }
            /*  RAP V1.0 section 3.2.1 Ranging Data retention requirements
                A maximum timeout of 10 seconds, or a shorter implementation configurable timeout value, has elapsed since
                the RRSP indicated a Complete Ranging Data indication and the RREQ did not respond with an ACK_Ranging_Data
                command or a Retrieve_Lost_Ranging_Data command.
            */
            k_work_schedule(&p_rrsp_info->ranging_data_retention_work, BT_RAS_RRSP_RETENTION_TIMEOUT);
        }
    }

    return 0;
}

static void bt_ras_rrsp_ranging_data_send_work_handler(struct k_work *work)
{
    bt_ras_rrsp_info_t *p_rrsp_info = CONTAINER_OF(work, bt_ras_rrsp_info_t, ranging_data_send_work);

    if (!p_rrsp_info->rreq_is_receiving || !p_rrsp_info->ranging_data) {
        return;
    }

    int err = bt_ras_rrsp_range_data_segment_send(p_rrsp_info);

    if (err) {
        LOG_WRN("[RAS] Send segment fail error: %d", err);
    }
}

static void bt_ras_rrsp_cp_work_handler(struct k_work *work)
{
    bt_ras_rrsp_info_t *p_rrsp_info = CONTAINER_OF(work, bt_ras_rrsp_info_t, ras_cp_work);

    int err = bt_ras_rrsp_cp_indication(p_rrsp_info->conn);
    if (err) {
        LOG_WRN("[RAS] Control point indication failed: %d", err);
        k_work_submit_to_queue(&g_bt_ras_rrsp_work_queue, &p_rrsp_info->ras_cp_work);
    }
    else {
        if (p_rrsp_info->ras_cp_result_cache_wait_to_send) {
            p_rrsp_info->ras_cp_result_cache_wait_to_send = false;
            memcpy(&p_rrsp_info->ras_cp_result, &p_rrsp_info->ras_cp_result_cache, sizeof(bt_ras_cp_res_t));
            k_work_submit_to_queue(&g_bt_ras_rrsp_work_queue, &p_rrsp_info->ras_cp_work);
        }
    }
}

static void bt_ras_rrsp_ranging_data_ready_and_or_overwritten_work_handler(struct k_work *work)
{
    bt_ras_rrsp_info_t *p_rrsp_info = CONTAINER_OF(work, bt_ras_rrsp_info_t, ranging_data_ready_and_or_overwritten_work);
    int err;

    if (p_rrsp_info->ranging_data_overwritten_wait_to_send) {
        err = bt_ras_rrsp_ranging_data_overwritten_indication(p_rrsp_info->conn);
        if (err) {
            LOG_WRN("[RAS] Rang data overwritten indication failed: %d", err);
            k_work_submit_to_queue(&g_bt_ras_rrsp_work_queue, &p_rrsp_info->ranging_data_ready_and_or_overwritten_work);
        }
        else {
            p_rrsp_info->ranging_data_overwritten_wait_to_send = false;
        }
    }

    if (p_rrsp_info->ranging_data_ready_wait_to_send) {
        err = bt_ras_rrsp_ranging_data_ready_indication(p_rrsp_info->conn);
        if (err) {
            LOG_WRN("[RAS] Rang data ready indication failed: %d", err);
            k_work_submit_to_queue(&g_bt_ras_rrsp_work_queue, &p_rrsp_info->ranging_data_ready_and_or_overwritten_work);
        }
        else {
            p_rrsp_info->ranging_data_ready_wait_to_send = false;
        }
    }

}

static void bt_ras_rrsp_ranging_data_retention_work_handler(struct k_work* work)
{
	struct k_work_delayable *dwork = k_work_delayable_from_work(work);

    bt_ras_rrsp_info_t *p_rrsp_info = CONTAINER_OF(dwork, bt_ras_rrsp_info_t, ranging_data_retention_work);
    /* RAS V1.0 Section 3.3.4 RAS Control Point procedure timeout and failure
       When the RAS Server transmits a Complete Ranging Data Response indication or a Complete Lost
       Ranging Data Segment Response indication of the RAS Control Point characteristic, the response
       shall be considered to have timed out if the ACK_Ranging_Data command is not received within 5 seconds.
       If a timeout occurs, then the RAS Server shall consider the RAS Control Point procedure to have failed.
     */
    bt_ras_cs_procedure_storage_t * storage = bt_ras_cs_procedure_storage_take(p_rrsp_info->conn, p_rrsp_info->ranging_counter_getting);
    (void)bt_ras_cs_procedure_storage_free(storage);
    p_rrsp_info->ranging_data_sent = 0;
    p_rrsp_info->rreq_is_receiving = false;
    p_rrsp_info->get_lost_segment = false;
    p_rrsp_info->ranging_counter_getting = BT_RAS_RANGING_COUNTER_INVALID;
}

static int bt_ras_rrsp_init(void)
{
    k_work_queue_init(&g_bt_ras_rrsp_work_queue);
    k_work_queue_start(&g_bt_ras_rrsp_work_queue, g_bt_ras_rrsp_work_queue_stack_area,
        K_THREAD_STACK_SIZEOF(g_bt_ras_rrsp_work_queue_stack_area),
        K_PRIO_PREEMPT(K_LOWEST_APPLICATION_THREAD_PRIO), NULL);

    return 0;
}

SYS_INIT(bt_ras_rrsp_init, APPLICATION, CONFIG_APPLICATION_INIT_PRIORITY);

/************************************************
* Public functions
*************************************************/

void bt_ras_rrsp_new_ranging_data_ready(struct bt_conn *conn, uint16_t ranging_counter)
{
    bt_ras_rrsp_info_t *p_rrsp_info = bt_ras_rrsp_find(conn);
    if (!p_rrsp_info) {
        return;
    }

    struct bt_gatt_attr *ondemand_attr = bt_gatt_find_by_uuid(ras_svc.attrs, 0, BT_UUID_ONDEMAND_RANGING_DATA);

    if (bt_gatt_is_subscribed(conn, ondemand_attr, BT_GATT_CCC_NOTIFY | BT_GATT_CCC_INDICATE)) {
        p_rrsp_info->ranging_data_ready_wait_to_send = true;
        p_rrsp_info->ranging_counter_ready = ranging_counter;
        k_work_submit_to_queue(&g_bt_ras_rrsp_work_queue, &p_rrsp_info->ranging_data_ready_and_or_overwritten_work);
    }
}

void bt_ras_rrsp_ranging_data_overwritten(struct bt_conn *conn, uint16_t ranging_counter)
{
    bt_ras_rrsp_info_t *p_rrsp_info = bt_ras_rrsp_find(conn);
    if (!p_rrsp_info) {
        return;
    }

    struct bt_gatt_attr *ondemand_attr = bt_gatt_find_by_uuid(ras_svc.attrs, 0, BT_UUID_ONDEMAND_RANGING_DATA);

    if (bt_gatt_is_subscribed(conn, ondemand_attr, BT_GATT_CCC_NOTIFY | BT_GATT_CCC_INDICATE)) {
        p_rrsp_info->ranging_data_overwritten_wait_to_send = true;
        p_rrsp_info->ranging_counter_overwritten = ranging_counter;
        k_work_submit_to_queue(&g_bt_ras_rrsp_work_queue, &p_rrsp_info->ranging_data_ready_and_or_overwritten_work);
    }
}

