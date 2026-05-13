/* Copyright Statement:
*
* (C) 2024 Airoha Technology Corp. All rights reserved.
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
* the License Agreement ("Permitted User"). If you are not a Permitted User,
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
/* Airoha restricted information */


#include "bt_ull_le.h"
#include "bt_ull_le_internal.h"

#if defined(CONFIG_BT_HCI_VENDOR_EVENT_DISPATCH)
#include "bt_hci_vendor_event_dispatch.h"
#endif

#include "zephyr/logging/log.h"
#include <zephyr/bluetooth/conn.h>
#include "host/conn_internal.h"
#include "assert.h"

LOG_MODULE_REGISTER(ULL_HID);

#define BT_ULL_LOG     "[ULL][LE] "

/*               |front|                                 |back|
 *                  /                                      /
 * [Link_HEAD]-->[node1]-->[node2]-->[node3]-->[node4]-->[node5]-->NULL
 *    [des]
 * Insert [src] to [des] linked list.
 * #BT_NODE_FRONT : Insert [src] to front of [des] linked list.
 * #BT_NODE_BACK  : Insert [src] to back of [des linked list.
 */
void bt_ull_le_linknode_insert_node(bt_ull_le_linknode_t *des, bt_ull_le_linknode_t *src, bt_ull_le_linknode_position pos)
{
    bt_ull_le_linknode_t *tmp = des;
    if (pos == BT_NODE_BACK) {
        while (tmp->front != NULL) {
            tmp = tmp->front;
        }
    }
    src->front = tmp->front;
    tmp->front = src;
}

/*               |front|                                 |back|
 *                  /                                      /
 * [Link_HEAD]-->[node1]-->[node2]-->[node3]-->[node4]-->[node5]-->NULL
 *    [src]
 * #BT_NODE_FRONT : Remove [node1] from [src] linked list.
 * #BT_NODE_BACK  : Remove [node5] from [src] linked list.
 * [f_node]-->[ff_node]
 */
bt_ull_le_linknode_t *bt_ull_le_linknode_remove_node(bt_ull_le_linknode_t *src, bt_ull_le_linknode_position pos)
{
    bt_ull_le_linknode_t *f_node = src;
    bt_ull_le_linknode_t *ff_node = src->front; /* #ff_node is removing node. */
    if (ff_node != NULL) {
        if (pos == BT_NODE_BACK) {
            while (ff_node->front != NULL) {
                f_node = ff_node;
                ff_node = ff_node->front;
            }
        }
        f_node->front = ff_node->front;
        ff_node->front = NULL;
    }
    return ff_node;
}

static bt_ull_le_control_t bt_ull_le_ctrl;
bt_ull_le_air_cis_connection_t *bt_ull_le_air_cis_connection_malloc()
{
    bt_ull_le_air_cis_connection_t *air_cis_conn = k_malloc(4*8);
    if (!air_cis_conn) {
        return NULL;
    }
    BT_QUEUE_PUSH_FRONT(&bt_ull_le_ctrl.air_cis_connection, &air_cis_conn->next_node);
    return air_cis_conn;
}

void bt_ull_le_air_cis_connection_free(bt_ull_le_air_cis_connection_t *air_cis_conn)
{
    if (!air_cis_conn) {
        return;
    }
   k_free(air_cis_conn);
}

bt_ull_le_air_cis_connection_t *bt_ull_le_find_air_cis_conn_by_handle(uint32_t handle, bool remove)
{
    bt_ull_le_linknode_t *p = &bt_ull_le_ctrl.air_cis_connection, *p_temp;
    do {
        p_temp = p;
        p = p->front;
    } while (p && BT_ULL_LE_GET_AIR_CIS_CONN_FROM_NODE(p)->cis_handle != handle);

    if (p && remove) {
        bt_ull_le_linknode_remove_node(p_temp, BT_NODE_FRONT);
    }

    return p ? BT_ULL_LE_GET_AIR_CIS_CONN_FROM_NODE(p) : NULL;
}

/**********************************************************************************************************************************************************************
*
*AIR HID CIS
*
**********************************************************************************************************************************************************************/
static bt_ull_le_event_cb bt_ull_le_cb;

void bt_ull_le_register_cb(bt_ull_le_event_cb cb)
{
	bt_ull_le_cb = cb;
}

int bt_ull_le_set_air_hid_cig_parameters(bt_ull_le_set_air_hid_cig_t *params)
{
    if (!params) {
        return -EPERM;
    }
    bt_ull_le_set_air_hid_cig_t *sahc_params;
    uint32_t common_len = sizeof(bt_ull_le_set_air_hid_cig_t) - sizeof(params->cis_list);
    uint32_t cis_list_len = (params->cis_count) * sizeof(bt_ull_le_air_hid_cis_params_t);
    uint32_t total_len = common_len + cis_list_len;
    struct net_buf *buf, *rsp = NULL;
    int err;

	buf = bt_hci_cmd_create(BT_HCI_CMD_VENDOR_SET_AIR_HID_CIG_PARAMS,
				total_len);
	if (!buf) {
		LOG_ERR(BT_ULL_LOG"Unable to allocate buffer");
		return -ENOBUFS;
	}

	sahc_params = net_buf_add(buf, total_len);
    (void)memset(sahc_params, 0, total_len);
    memcpy(sahc_params, params, common_len);
    memcpy((uint8_t *)sahc_params + common_len, params->cis_list, cis_list_len);
    err = bt_hci_cmd_send_sync(BT_HCI_CMD_VENDOR_SET_AIR_HID_CIG_PARAMS, buf, &rsp);
	if (err) {
		uint8_t reason = rsp ?
			((bt_ull_le_set_air_hid_cig_cnf_t *)
			  rsp->data)->status : 0;
		LOG_ERR(BT_ULL_LOG"Set Air Hid Cig err: %d reason 0x%02x\n", err, reason);
		return err;
	}

    err = bt_ull_le_air_hid_cis_conn_proc(BT_HCI_CMD_VENDOR_SET_AIR_HID_CIG_PARAMS, (void *)rsp->data);
    net_buf_unref(rsp);
    return err;
}

int bt_ull_le_remove_air_hid_cig_parameters(bt_ull_le_remove_air_hid_cig_t *params)
{
    if (!params) {
        return -EPERM;
    }
    bt_ull_le_remove_air_hid_cig_t *rahc_params;
    struct net_buf *buf, *rsp = NULL;
    int err;
    buf = bt_hci_cmd_create(BT_HCI_CMD_VENDOR_REMOVE_AIR_HID_CIG,
				sizeof(*params));
	if (!buf) {
		LOG_ERR(BT_ULL_LOG"Unable to allocate buffer");
		return -ENOBUFS;
	}

	rahc_params = net_buf_add(buf, sizeof(*params));
    (void)memset(rahc_params, 0, sizeof(*params));
    memcpy(rahc_params, params, sizeof(*params));

    err = bt_hci_cmd_send_sync(BT_HCI_CMD_VENDOR_REMOVE_AIR_HID_CIG, buf, &rsp);
    if (err) {
		uint8_t reason = rsp ?
			((bt_ull_le_set_air_hid_cig_cnf_t *)
			rsp->data)->status : 0;
		LOG_ERR(BT_ULL_LOG"Remove Air Hid Cig err: %d reason 0x%02x\n", err, reason);
		return err;
	}

    err = bt_ull_le_air_hid_cis_conn_proc(BT_HCI_CMD_VENDOR_REMOVE_AIR_HID_CIG, (void *)rsp->data);
    net_buf_unref(rsp);
    return err;
}

struct bt_conn *creat_conn = NULL;
int bt_ull_le_create_air_hid_cis(bt_ull_le_create_air_hid_cis_t *params)
{
    if (!params) {
        return -EPERM;
    }
    
    creat_conn = bt_conn_add_le(0, BT_ADDR_LE_NONE);
    assert(creat_conn != NULL);
    bt_conn_set_state(creat_conn, BT_CONN_ADV_CONNECTABLE);
    uint32_t i;
    uint32_t common_length = sizeof(bt_ull_le_create_air_hid_cis_t) - sizeof(params->cis_list);
    uint32_t list_cm_len = 0x0;
    uint32_t list_length = 0x0;
    uint32_t dev_info_len = 0x0;
    uint32_t offset = 0x0;
    bt_ull_le_create_air_hid_cis_params_t *hid_cis = NULL;
    for (i = 0; i < params->cis_count; i ++) {
        hid_cis = (bt_ull_le_create_air_hid_cis_params_t *)(params->cis_list + offset);
        list_cm_len = sizeof(bt_ull_le_create_air_hid_cis_params_t) - sizeof(hid_cis->dev_list);
        dev_info_len = hid_cis->dev_count * sizeof(bt_ull_le_air_hid_cis_dev_info_t);
        list_length += (list_cm_len + dev_info_len);
        offset = list_length;
    }
    uint32_t total_len = common_length + list_length;
    bt_ull_le_create_air_hid_cis_t *cahc_params;
    struct net_buf *buf, *rsp = NULL;
    int err;
    buf = bt_hci_cmd_create(BT_HCI_CMD_VENDOR_CREATE_AIR_HID_CIS,
				total_len);
	if (!buf) {
		LOG_ERR(BT_ULL_LOG"Unable to allocate buffer");
        bt_conn_unref(creat_conn);
		return -ENOBUFS;
	}

	cahc_params = net_buf_add(buf, total_len);
    (void)memset(cahc_params, 0, sizeof(*params));
    memcpy(cahc_params, params, common_length);
    memcpy((uint8_t *)cahc_params + common_length, params->cis_list, list_length);

    err = bt_hci_cmd_send_sync(BT_HCI_CMD_VENDOR_CREATE_AIR_HID_CIS, buf, &rsp);
    if (err) {
		uint8_t reason = rsp ?
			((bt_ull_le_set_air_hid_cig_cnf_t *)
			rsp->data)->status : 0;
		LOG_ERR(BT_ULL_LOG"Create Air Hid Cis err: %d reason 0x%02x\n", err, reason);
        bt_conn_unref(creat_conn);
		return err;
	}
    bt_conn_unref(creat_conn);
    err = bt_ull_le_air_hid_cis_conn_proc(BT_HCI_CMD_VENDOR_CREATE_AIR_HID_CIS, (void *)rsp->data);
    net_buf_unref(rsp);
    return err;
}

#if defined (CONFIG_ULL_HID_LE_PERIPHERAL)
struct bt_conn *sync_cis_conn;
int bt_ull_le_sync_air_hid_cis(bt_ull_le_sync_air_hid_cis_t *params)
{
    if (!params) {
        return -EPERM;
    }

    sync_cis_conn = bt_conn_add_le(0, BT_ADDR_LE_NONE);
    assert(sync_cis_conn != NULL);
    bt_conn_set_state(sync_cis_conn, BT_CONN_ADV_CONNECTABLE);
    bt_ull_le_sync_air_hid_cis_t *sahc_params;
    struct net_buf *buf, *rsp = NULL;
    int err;
    uint32_t common_length = sizeof(*params);
#ifdef CONFIG_AIR_HID_SUSPEND_RESUME_DEVICE
    uint16_t len = common_length + params->adv_data_len;
    LOG_ERR(BT_ULL_LOG"Sync Air Hid Cis, len: %d, common_length: %d, adv_data_len: %d, params: 0x%x", 
            len, common_length, params->adv_data_len, params);
#else
    uint32_t len = common_length;
#endif
    buf = bt_hci_cmd_create(BT_HCI_CMD_VENDOR_SYNC_AIR_HID_CIS, len);
	if (!buf) {
		LOG_ERR(BT_ULL_LOG"Unable to allocate buffer");
        bt_conn_unref(sync_cis_conn);
		return -ENOBUFS;
	}
	sahc_params = net_buf_add(buf, len);
    (void)memset(sahc_params, 0, len);
    memcpy(sahc_params, params, common_length);
#ifdef CONFIG_AIR_HID_SUSPEND_RESUME_DEVICE
    memcpy((uint8_t *)sahc_params + common_length, params->adv_data, params->adv_data_len);
#endif

    err = bt_hci_cmd_send_sync(BT_HCI_CMD_VENDOR_SYNC_AIR_HID_CIS, buf, &rsp);
    if (err) {
		uint8_t reason = rsp ?
			((bt_ull_le_set_air_hid_cig_cnf_t *)
			rsp->data)->status : 0;
		LOG_ERR(BT_ULL_LOG"Sync Air Hid Cis err: %d reason 0x%02x\n", err, reason);
        bt_conn_unref(sync_cis_conn);
		return err;
	}
    bt_conn_unref(sync_cis_conn);
    err = bt_ull_le_air_hid_cis_conn_proc(BT_HCI_CMD_VENDOR_SYNC_AIR_HID_CIS, (void *)rsp->data);
    net_buf_unref(rsp);
    return err;
}

int bt_ull_le_cancel_sync_air_hid_cis(void)
{
    struct net_buf *buf, *rsp = NULL;
    int err;
    buf = bt_hci_cmd_create(BT_HCI_CMD_VENDOR_CANCEL_SYNC_AIR_HID_CIS,
				0);
	if (!buf) {
		LOG_ERR(BT_ULL_LOG"Unable to allocate buffer");
		return -ENOBUFS;
	}

    err = bt_hci_cmd_send_sync(BT_HCI_CMD_VENDOR_CANCEL_SYNC_AIR_HID_CIS, buf, &rsp);
    if(sync_cis_conn){
        bt_conn_unref(sync_cis_conn); 
    } else {
        LOG_ERR(BT_ULL_LOG"sync_cis_conn is null");
    }
    if (err) {
		uint8_t reason = rsp ?
			((bt_ull_le_set_air_hid_cig_cnf_t *)
			rsp->data)->status : 0;
		LOG_ERR(BT_ULL_LOG"Cancel Sync Air Hid Cis err: %d reason 0x%02x\n", err, reason);
		return err;
	}

    err = bt_ull_le_air_hid_cis_conn_proc(BT_HCI_CMD_VENDOR_CANCEL_SYNC_AIR_HID_CIS, (void *)rsp->data);
    net_buf_unref(rsp);
    return err;
}
#endif

int bt_ull_le_disconnect_air_hid_cis(bt_ull_le_air_hid_cis_disconnect_t *params)
{
    if (!params) {
        return -EPERM;
    }
    bt_ull_le_air_cis_connection_t *conn = bt_ull_le_find_air_cis_conn_by_handle(params->connection_handle, false);
    if (conn == NULL && \
        (0x00 == params->connection_handle || 0xFFFF == params->connection_handle)) {
        return -EPERM;
    }

    bt_ull_le_air_hid_cis_disconnect_t *ahcd_params;
    struct net_buf *buf, *rsp = NULL;
    int err;
    buf = bt_hci_cmd_create(BT_HCI_CMD_VENDOR_DISCONNECT_AIR_HID_CIS,
				sizeof(*params));
	if (!buf) {
		LOG_ERR(BT_ULL_LOG"Unable to allocate buffer");
		return -ENOBUFS;
	}

	ahcd_params = net_buf_add(buf, sizeof(*params));
    (void)memset(ahcd_params, 0, sizeof(*params));
    memcpy(ahcd_params, params, sizeof(*params));

    err = bt_hci_cmd_send_sync(BT_HCI_CMD_VENDOR_DISCONNECT_AIR_HID_CIS, buf, &rsp);
    if (err) {
		uint8_t reason = rsp ?
			((bt_ull_le_set_air_hid_cig_cnf_t *)
			rsp->data)->status : 0;
		LOG_ERR(BT_ULL_LOG"Disconnect Air Hid Cis err: %d reason 0x%02x\n", err, reason);
		return err;
	}

    err = bt_ull_le_air_hid_cis_conn_proc(BT_HCI_CMD_VENDOR_DISCONNECT_AIR_HID_CIS, (void *)rsp->data);
    net_buf_unref(rsp);
    return err;
}

int bt_ull_le_cancel_creating_air_hid_cis(bt_ull_le_cancel_create_air_hid_cis_params_t *params)
{
    if (!params) {
        return -EPERM;
    }
    bt_ull_le_cancel_create_air_hid_cis_params_t *ccahc_params;
    struct net_buf *buf, *rsp = NULL;
    int err;
    buf = bt_hci_cmd_create(BT_HCI_CMD_VENDOR_CANCEL_CREATE_AIR_HID_CIS,
				sizeof(*params));
	if (!buf) {
		LOG_ERR(BT_ULL_LOG"Unable to allocate buffer");
		return -ENOBUFS;
	}

	ccahc_params = net_buf_add(buf, sizeof(*params));
    (void)memset(ccahc_params, 0, sizeof(*params));
    memcpy(ccahc_params, params, sizeof(*params));

    err = bt_hci_cmd_send_sync(BT_HCI_CMD_VENDOR_CANCEL_CREATE_AIR_HID_CIS, buf, &rsp);
    if(creat_conn){
        bt_conn_unref(creat_conn); 
    } else {
        LOG_ERR(BT_ULL_LOG"creat_conn is null");
    }
    if (err) {
		uint8_t reason = rsp ?
			((bt_ull_le_set_air_hid_cig_cnf_t *)
			rsp->data)->status : 0;
		LOG_ERR(BT_ULL_LOG"Cancel Create Air Hid Cis err: %d reason 0x%02x\n", err, reason);
		return err;
	}
    err = bt_ull_le_air_hid_cis_conn_proc(BT_HCI_CMD_VENDOR_CANCEL_CREATE_AIR_HID_CIS, (void *)rsp->data);
    net_buf_unref(rsp);
    return err;    
}

int bt_ull_le_set_report_rate(bt_ull_le_change_air_hid_cis_report_rate_t *params)
{
    if (!params) {
        return -EPERM;
    }
    bt_ull_le_change_air_hid_cis_report_rate_t *srr_params;
    struct net_buf *buf, *rsp = NULL;
    int err;
    LOG_INF(BT_ULL_LOG"bt_ull_le_set_report_rate");
    buf = bt_hci_cmd_create(BT_HCI_CMD_VENDOR_SET_REPORT_RATE,
				sizeof(*params));
	if (!buf) {
		LOG_ERR(BT_ULL_LOG"Unable to allocate buffer");
		return -ENOBUFS;
	}

	srr_params = net_buf_add(buf, sizeof(*params));
    (void)memset(srr_params, 0, sizeof(*params));
    memcpy(srr_params, params, sizeof(*params));

    err = bt_hci_cmd_send_sync(BT_HCI_CMD_VENDOR_SET_REPORT_RATE, buf, &rsp);
    if (err) {
		uint8_t reason = rsp ?
			((bt_ull_le_set_air_hid_cig_cnf_t *)
			rsp->data)->status : 0;
		LOG_ERR(BT_ULL_LOG"Set report rate err: %d reason 0x%02x\n", err, reason);
		return err;
	}

    err = bt_ull_le_air_hid_cis_conn_proc(BT_HCI_CMD_VENDOR_SET_REPORT_RATE, (void *)rsp->data);
    net_buf_unref(rsp);
    return err;    
}

int bt_ull_le_set_peripheral(bt_ull_le_set_peripheral_t *params)
{
    if (!params) {
        LOG_ERR(BT_ULL_LOG"bt_ull_le_set_peripheral, params is NULL");
        return -EPERM;
    }
    bt_ull_le_set_peripheral_t *sp_params;
    struct net_buf *buf, *rsp = NULL;
    int err;
    LOG_INF(BT_ULL_LOG"bt_ull_le_set_peripheral, handle: 0x%02x, enable: %d", params->connection_handle, params->enable);
    buf = bt_hci_cmd_create(BT_HCI_CMD_VENDOR_SET_PRI_ENABLE,
				sizeof(*params));
	if (!buf) {
		LOG_ERR(BT_ULL_LOG"Unable to allocate buffer");
		return -ENOBUFS;
	}

	sp_params = net_buf_add(buf, sizeof(*params));
    (void)memset(sp_params, 0, sizeof(*params));
    memcpy(sp_params, params, sizeof(*params));

    err = bt_hci_cmd_send_sync(BT_HCI_CMD_VENDOR_SET_PRI_ENABLE, buf, &rsp);
    if (err) {
		LOG_ERR(BT_ULL_LOG"Set peripheral err: %d\n", err);
		return err;
	}

    err = bt_ull_le_air_hid_cis_conn_proc(BT_HCI_CMD_VENDOR_SET_PRI_ENABLE, (void *)rsp->data);
    net_buf_unref(rsp);
    return err;
}

#if defined(CONFIG_ULL_HID_LE_CENTRAL)
int bt_ull_le_get_connection_info(bt_ull_le_get_air_hid_cis_conn_info_t *params)
{
    if (!params) {
        LOG_ERR(BT_ULL_LOG"bt_ull_le_get_connection_info, params is NULL");
        return -EPERM;
    }
    bt_ull_le_get_air_hid_cis_conn_info_t *conn_info;
    struct net_buf *buf, *rsp = NULL;
    int err;
    LOG_INF(BT_ULL_LOG"bt_ull_le_get_connection_info, handle: 0x%02x, period: %d", params->handle, params->update_period);
    buf = bt_hci_cmd_create(BT_HCI_CMD_VENDOR_GET_AIR_HID_CONN_INFO,
                sizeof(*params));
    if (!buf) {
        LOG_ERR(BT_ULL_LOG"Unable to allocate buffer");
        return -ENOBUFS;
    }

    conn_info = net_buf_add(buf, sizeof(*params));
    (void)memset(conn_info, 0, sizeof(*params));
    memcpy(conn_info, params, sizeof(*params));

    err = bt_hci_cmd_send_sync(BT_HCI_CMD_VENDOR_GET_AIR_HID_CONN_INFO, buf, &rsp);
    if (err) {
        LOG_ERR(BT_ULL_LOG"Get Conn info err: %d\n", err);
        return err;
    }

    err = bt_ull_le_air_hid_cis_conn_proc(BT_HCI_CMD_VENDOR_GET_AIR_HID_CONN_INFO, (void *)rsp->data);
    net_buf_unref(rsp);
    return err;
}

int bt_ull_le_set_tx_power(bt_ull_le_set_air_hid_cis_tx_power_t *params)
{
    if (!params) {
        LOG_ERR(BT_ULL_LOG"bt_ull_le_set_tx_power, params is NULL");
        return -EPERM;
    }
    bt_ull_le_set_air_hid_cis_tx_power_t *tx_power_params = (bt_ull_le_set_air_hid_cis_tx_power_t *)params;
    struct net_buf *buf;
    int err;
    LOG_INF(BT_ULL_LOG"bt_ull_le_set_tx_power, handle: 0x%02x, remote_tx_power_control: %d", params->handle, params->remote_tx_power_control);
    buf = bt_hci_cmd_create(BT_HCI_CMD_VENDOR_SET_AIR_HID_TX_POWER,
                sizeof(*params));
    if (!buf) {
        LOG_ERR(BT_ULL_LOG"Unable to allocate buffer");
        return -ENOBUFS;
    }

    tx_power_params = net_buf_add(buf, sizeof(*params));
    (void)memset(tx_power_params, 0, sizeof(*params));
    memcpy(tx_power_params, params, sizeof(*params));

    err = bt_hci_cmd_send(BT_HCI_CMD_VENDOR_SET_AIR_HID_TX_POWER, buf);
    if (err) {
        LOG_ERR(BT_ULL_LOG"Set Tx power err: %d\n", err);
        return err;
    }

    //err = bt_ull_le_air_hid_cis_conn_proc(BT_HCI_CMD_VENDOR_SET_AIR_HID_TX_POWER, (void *)rsp->data);
    //net_buf_unref(rsp);
    return err;
}

int bt_ull_le_set_tx_local_tx_gc(bt_ull_le_set_air_hid_cis_local_tx_gc_t *params)
{
    if (!params) {
        LOG_ERR(BT_ULL_LOG"bt_ull_le_set_tx_local_tx_gc, params is NULL");
        return -EPERM;
    }
    bt_ull_le_set_air_hid_cis_local_tx_gc_t *tx_gc_params = (bt_ull_le_set_air_hid_cis_local_tx_gc_t *)params;
    struct net_buf *buf, *rsp = NULL;
    int err;
    LOG_INF(BT_ULL_LOG"bt_ull_le_set_tx_power, tx_gc: %d",params->local_tx_gc);
    buf = bt_hci_cmd_create(BT_HCI_CMD_VENDOR_SET_AIR_HID_LOCAL_TX_GC,
                sizeof(*params));
    if (!buf) {
        LOG_ERR(BT_ULL_LOG"Unable to allocate buffer");
        return -ENOBUFS;
    }

    tx_gc_params = net_buf_add(buf, sizeof(*params));
    (void)memset(tx_gc_params, 0, sizeof(*params));
    memcpy(tx_gc_params, params, sizeof(*params));

    err = bt_hci_cmd_send_sync(BT_HCI_CMD_VENDOR_SET_AIR_HID_LOCAL_TX_GC, buf, &rsp);
    if (err) {
        LOG_ERR(BT_ULL_LOG"Set Tx GC err: %d\n", err);
        return err;
    }

    err = bt_ull_le_air_hid_cis_conn_proc(BT_HCI_CMD_VENDOR_SET_AIR_HID_LOCAL_TX_GC, (void *)rsp->data);
    net_buf_unref(rsp);
    return err;
}

int bt_ull_le_set_remote_tx_power(bt_ull_le_set_air_hid_cis_remote_tx_power_t *params)
{
    if (!params) {
        LOG_ERR(BT_ULL_LOG"bt_ull_le_set_remote_tx_power, params is NULL");
        return -EPERM;
    }
    bt_ull_le_set_air_hid_cis_remote_tx_power_t *remote_tx_power_params = (bt_ull_le_set_air_hid_cis_remote_tx_power_t *)params;
    struct net_buf *buf = NULL;
    int err;
    LOG_INF(BT_ULL_LOG"bt_ull_le_set_remote_tx_power, handle: 0x%02x, tx_gc: %d, pa_vol: %d", params->handle, params->tx_gc, params->pa_vol);
    buf = bt_hci_cmd_create(BT_HCI_CMD_VENDOR_TX_POWER_REMOTE_CONTROL,
                sizeof(*params));
    if (!buf) {
        LOG_ERR(BT_ULL_LOG"Unable to allocate buffer");
        return -ENOBUFS;
    }

    remote_tx_power_params = net_buf_add(buf, sizeof(*params));
    (void)memset(remote_tx_power_params, 0, sizeof(*params));
    memcpy(remote_tx_power_params, params, sizeof(*params));

    err = bt_hci_cmd_send(BT_HCI_CMD_VENDOR_TX_POWER_REMOTE_CONTROL, buf);
    if (err) {
        LOG_ERR(BT_ULL_LOG"Set Remote Tx power err: %d\n", err);
        return err;
    }

    // err = bt_ull_le_air_hid_cis_conn_proc(BT_HCI_CMD_VENDOR_TX_POWER_REMOTE_CONTROL, (void *)rsp->data);
    // net_buf_unref(rsp);
    return err; 
}

int bt_ull_le_enbale_cis_scan(bt_ull_le_enable_air_hid_cis_scan_t *params)
{
    if (!params) {
        LOG_ERR(BT_ULL_LOG"bt_ull_le_enbale_cis_scan, params is NULL");
        return -EPERM;
    }
    bt_ull_le_enable_air_hid_cis_scan_t *scan_params = (bt_ull_le_enable_air_hid_cis_scan_t *)params;
    struct net_buf *buf, *rsp = NULL;
    int err;
    LOG_INF(BT_ULL_LOG"bt_ull_le_enbale_cis_scan, enable: %d, scan_interval: %d, scan_window: %d, uni_aa: %08X", 
            params->enable, params->scan_interval, params->scan_window, params->uni_aa[0]);
    buf = bt_hci_cmd_create(BT_HCI_CMD_VENDOR_ENABLE_AIR_HID_SCAN,
                sizeof(*params));
    if (!buf) {
        LOG_ERR(BT_ULL_LOG"Unable to allocate buffer");
        return -ENOBUFS;
    }

    scan_params = net_buf_add(buf, sizeof(*params));
    (void)memset(scan_params, 0, sizeof(*params));
    memcpy(scan_params, params, sizeof(*params));

    err = bt_hci_cmd_send_sync(BT_HCI_CMD_VENDOR_ENABLE_AIR_HID_SCAN, buf, &rsp);
    if (err) {
        LOG_ERR(BT_ULL_LOG"Enable Air HID Scan err: %d\n", err);
        return err;
    }

    err = bt_ull_le_air_hid_cis_conn_proc(BT_HCI_CMD_VENDOR_ENABLE_AIR_HID_SCAN, (void *)rsp->data);
    net_buf_unref(rsp);
    return err;
}
#endif

int bt_ull_le_air_hid_cis_conn_proc(uint16_t cmd_code, const void *param)
{
    int err = 0;
    switch (cmd_code) {
    case (BT_HCI_CMD_VENDOR_SET_AIR_HID_CIG_PARAMS): {
            struct bt_ull_le_set_air_hid_cig_cnf_t *set_ahc = (struct bt_ull_le_set_air_hid_cig_cnf_t *) param;
            return bt_ull_le_cb(BT_ULL_LE_SET_AIR_HID_CIG_PARAMS_CNF, err, set_ahc);
            break;
        }
    case (BT_HCI_CMD_VENDOR_REMOVE_AIR_HID_CIG): {
            struct bt_ull_le_remove_air_hid_cig_cnf_t *rm_ahc = (struct bt_ull_le_remove_air_hid_cig_cnf_t *) param;
            return bt_ull_le_cb(BT_ULL_LE_REMOVE_AIR_HID_CIG_CNF, err, rm_ahc);
            break;
        }

    case (BT_HCI_CMD_VENDOR_CREATE_AIR_HID_CIS): {
            return bt_ull_le_cb(BT_ULL_LE_CREATE_AIR_HID_CIS_CNF, err, 0);
            break;
        }
    case (BT_HCI_CMD_VENDOR_SYNC_AIR_HID_CIS): {
            return bt_ull_le_cb(BT_ULL_LE_SYNC_AIR_HID_CIS_CNF, err, 0);
            break;
        }
    case (BT_HCI_CMD_VENDOR_DISCONNECT_AIR_HID_CIS): {
            return bt_ull_le_cb(BT_ULL_LE_DISCONNECT_AIR_HID_CIS_CNF, err, 0);
            break;
        }
    case (BT_HCI_CMD_VENDOR_CANCEL_CREATE_AIR_HID_CIS): {
            return bt_ull_le_cb(BT_ULL_LE_CANCEL_CREATE_AIR_HID_CIS_CNF, err, 0);
            break;
        }
    case (BT_HCI_CMD_VENDOR_CANCEL_SYNC_AIR_HID_CIS): {
            return bt_ull_le_cb(BT_ULL_LE_CANCEL_SYNC_AIR_HID_CIS_CNF, err, 0);
            break;
        }
    default:
        break;
    }
    return err;
}

#if defined(CONFIG_BT_HCI_VENDOR_EVENT_DISPATCH)
static int bt_ull_hid_hci_event_cb(int err, uint8_t event_code, void *event_data)
{
    LOG_INF(BT_ULL_LOG"bt_ull_hid_hci_event_cb, error: 0x%x, event_code: 0x%x", err, event_code);
    if(err){
        LOG_ERR(BT_ULL_LOG"bt_ull_hid_hci_event_cb err:%x", err);
        return err;
    }
    switch (event_code) {
        case BT_HCI_SUBEVT_LE_VENDOR_AIR_HID_CIS_ESTABLISHED: {
            bt_ull_le_air_hid_cis_established_ind_t *ahc_established = (bt_ull_le_air_hid_cis_established_ind_t *) (event_data);
            LOG_INF(BT_ULL_LOG"bt_ull_hid_hci_event_cb, ahc_established:%x, status: %d, cishandle:0x%x", ahc_established, ahc_established->status, ahc_established->cis_connection_handle);
            if (!ahc_established->status) {
                bt_ull_le_air_cis_connection_t *ahc_conn  = bt_ull_le_air_cis_connection_malloc();
                if (ahc_conn) {
                    ahc_conn->cis_handle = ahc_established->cis_connection_handle;
                } else {
                    bt_ull_le_air_hid_cis_disconnect_t *ahcd_params;
                    struct net_buf *buf;

                    buf = bt_hci_cmd_create(BT_HCI_CMD_VENDOR_DISCONNECT_AIR_HID_CIS,
                                sizeof(bt_ull_le_air_hid_cis_disconnect_t));
                    if (!buf) {
                        LOG_ERR(BT_ULL_LOG"Unable to allocate buffer");
                        return -ENOMEM;
                    }

                    ahcd_params = net_buf_add(buf, sizeof(bt_ull_le_air_hid_cis_disconnect_t));
                    ahcd_params->connection_handle = ahc_established->cis_connection_handle;
                    ahcd_params->reason = BT_HCI_ERR_REMOTE_LOW_RESOURCES;
                    bt_hci_cmd_send(BT_HCI_CMD_VENDOR_DISCONNECT_AIR_HID_CIS, buf);
                    return 0;
                }
            }
            bt_ull_le_cb(BT_ULL_LE_AIR_HID_CIS_ESTABLISHED_IND, ahc_established->status, ahc_established);
            break;
        }

        case BT_HCI_SUBEVT_LE_VENDOR_AIR_HID_CIS_DISCONNECT_COMPLETE: {
            bt_ull_le_air_hid_cis_disconnect_complete_ind_t *ahc_dis_complete = (bt_ull_le_air_hid_cis_disconnect_complete_ind_t *) event_data;
            if (!ahc_dis_complete->status) {
                bt_ull_le_air_cis_connection_t *ahc_conn = bt_ull_le_find_air_cis_conn_by_handle(ahc_dis_complete->cis_connection_handle, true);
                if (ahc_conn) {
                    bt_ull_le_air_cis_connection_free(ahc_conn);
                } else {
                    LOG_ERR(BT_ULL_LOG"Disconnect Complete, Connection Handle %x", ahc_dis_complete->cis_connection_handle);
                }
            }
            bt_ull_le_cb(BT_ULL_LE_AIR_HID_CIS_DISCONNECT_COMPLETE_IND, ahc_dis_complete->status, ahc_dis_complete);
            break;
        }
        case BT_HCI_SUBEVT_LE_VENDOR_AIR_HID_CIS_RR_CHANGE: {
            bt_ull_le_air_hid_report_rate_change_ind *ahc_rr_change = (bt_ull_le_air_hid_report_rate_change_ind *) event_data;
            bt_ull_le_cb(BT_ULL_LE_SET_AIR_HID_REPORT_RATE_CHANGE_IND, ahc_rr_change->status, ahc_rr_change);
            break;
        }
        case BT_HCI_SUBEVT_LE_VENDOR_AIR_HID_CIS_ADV_REPORT: {
            bt_ull_le_air_hid_cis_adv_report_ind *adv_report = (bt_ull_le_air_hid_cis_adv_report_ind *) event_data;
            bt_ull_le_cb(BT_ULL_LE_SET_AIR_HID_CIS_ADV_REPORT_IND, 0, adv_report);
            break;
        }
        case BT_HCI_SUBEVT_LE_VENDOR_AIR_HID_CIS_CONN_INFO: {
            bt_ull_le_air_hid_conn_info_ind_t *conn_info_ind = (bt_ull_le_air_hid_conn_info_ind_t *) event_data;
            bt_ull_le_cb(BT_ULL_LE_SET_AIR_HID_CIS_CONN_INFO_IND, conn_info_ind->status, conn_info_ind);
            break;
        }
        default: {
            LOG_ERR(BT_ULL_LOG"bt_ull_hid_hci_event_cb, unexcepted event %x", event_code);
            break;
        }
    }

	return 0;
}
#endif

void bt_ull_le_free_air_hid_cis_conn(bt_ull_role_t role)
{
    if (role == BT_ULL_ROLE_CLIENT) {
        // Free the CIS connection for the client role
    } else if (role == BT_ULL_ROLE_SERVER) {
        if(creat_conn){
            bt_conn_unref(creat_conn); 
        } else {
            LOG_ERR(BT_ULL_LOG"bt_ull_le_free_air_hid_cis_conn, creat_conn is null");
        }
    }
}

void bt_ull_le_init(void)
{
    memset(&bt_ull_le_ctrl, 0, sizeof(bt_ull_le_control_t));
#if defined(CONFIG_BT_HCI_VENDOR_EVENT_DISPATCH)
    bt_hci_vendor_event_dispatch_init();
    bt_hci_vendor_event_dispatch_register(BT_HCI_VENDOR_EVENT_MODULE_ULL_HID_SRV, bt_ull_hid_hci_event_cb);
#endif
    return;
}

void bt_ull_le_deinit(void)
{
    memset(&bt_ull_le_ctrl, 0, sizeof(bt_ull_le_control_t));
    return;
}
