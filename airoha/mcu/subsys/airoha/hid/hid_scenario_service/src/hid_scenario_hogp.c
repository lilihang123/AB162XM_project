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
 

#include <zephyr/types.h>
#include <zephyr/drivers/gpio.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>
#include <zephyr/sys/printk.h>
#include <zephyr/sys/byteorder.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/hci.h>
#include <zephyr/bluetooth/conn.h>
#include <zephyr/bluetooth/uuid.h>
#include <zephyr/bluetooth/gatt.h>

#include "hid_scenario_hogp.h"
#include "hid_scenario_service.h"
#include "hid_scenario_service_internal.h"

#include "hid_common.h"

#if defined(CONFIG_AIR_PRODUCT_TYPE_GAME_CONTROLLER) && defined(CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_BT_MODE)
#include "hid_scenario_le_gamepad.h"
#endif

#define thisMODULE hogs
#define thisMOD "hogs"

LOG_MODULE_REGISTER(thisMODULE);


#if defined (CONFIG_AIR_SAMPLE_BT_USE_AUTHENTICATION)
/* Require encryption using authenticated link-key. */
#define SAMPLE_BT_PERM_READ BT_GATT_PERM_READ_AUTHEN
#define SAMPLE_BT_PERM_WRITE BT_GATT_PERM_WRITE_AUTHEN
#else
/* Require encryption. */
#define SAMPLE_BT_PERM_READ BT_GATT_PERM_READ
#define SAMPLE_BT_PERM_WRITE BT_GATT_PERM_WRITE
#endif



enum {
	HIDS_REMOTE_WAKE = BIT(0),
	HIDS_NORMALLY_CONNECTABLE = BIT(1),
};

struct hids_info {
	uint16_t version; /* version number of base USB HID Specification */
	uint8_t code; /* country HID Device hardware is localized for. */
	uint8_t flags;
} __packed;

struct hids_report {
	uint8_t id; /* report id */
	uint8_t type; /* report type */
} __packed;

static struct hids_info hid_scenario_hog_info = {
	.version = 0x0000,
	.code = 0x00,
	.flags = HIDS_NORMALLY_CONNECTABLE,
};

enum {
	HIDS_INPUT = 0x01,
	HIDS_OUTPUT = 0x02,
	HIDS_FEATURE = 0x03,
};


#if defined(CONFIG_AIR_PRODUCT_TYPE_GAME_CONTROLLER)
static struct hids_report hid_scenario_hog_input_game_controller = {
	.id = REPORT_ID_BT_GAME_CONTROLLER,
	.type = HIDS_INPUT,
};

static struct hids_report hid_scenario_hog_input_game_controller1 = {
	.id = REPORT_ID_BT_GAME_CONTROLLER_GROUP0,
	.type = HIDS_INPUT,
};

static struct hids_report hid_scenario_hog_output_game_controller = {
	.id = REPORT_ID_BT_GAME_CONTROLLER_GROUP1,
	.type = HIDS_OUTPUT,
};
static struct hids_report hid_scenario_hog_output_game_controller1 = {
	.id = REPORT_ID_BT_GAME_CONTROLLER_GROUP2,
	.type = HIDS_OUTPUT,
};
#else
static uint8_t hid_scenario_hog_cccd_kb_std;
static uint8_t hid_scenario_hog_cccd_kb_consumer;
static uint8_t hid_scenario_hog_cccd_mouse;

static struct hids_report hid_scenario_hog_input_kb_consumer = {
	.id = REPORT_ID_KB_CONSUMER,
	.type = HIDS_INPUT,
};


static struct hids_report hid_scenario_hog_input_kb_std = {
	.id = REPORT_ID_KB_STD,
	.type = HIDS_INPUT,
};


static struct hids_report hid_scenario_hog_input_mouse = {
	.id = REPORT_ID_MOUSE,
	.type = HIDS_INPUT,
};
#endif

#if defined(CONFIG_AIR_PRODUCT_TYPE_KEYBOARD)
#if defined(BT_MODE_NKEY_SPLIT_GROUP)
static struct hids_report hid_scenario_hog_input_kb_bit_rep_1 = {
	.id = REPORT_ID_KEYBOARD_BIT_REP_1,
	.type = HIDS_INPUT,
};

static struct hids_report hid_scenario_hog_input_kb_bit_rep_2 = {
	.id = REPORT_ID_KEYBOARD_BIT_REP_2,
	.type = HIDS_INPUT,
};

static struct hids_report hid_scenario_hog_input_kb_bit_rep_3 = {
	.id = REPORT_ID_KEYBOARD_BIT_REP_3,
	.type = HIDS_INPUT,
};
#else
static struct hids_report hid_scenario_hog_input_kb_nkey = {
	.id = REPORT_ID_KEYBOARD_NKEY,
	.type = HIDS_INPUT,
};
#endif
#endif


hid_scenario_hogp_attr_cb hid_scenario_hogp_attr_handle_cb = NULL;

#if defined(CONFIG_AIR_PRODUCT_TYPE_KEYBOARD)
#if defined(BT_MODE_NKEY_SPLIT_GROUP)
static uint8_t hid_scenario_hog_cccd_kb_bit_rep_1;
static uint8_t hid_scenario_hog_cccd_kb_bit_rep_2;
static uint8_t hid_scenario_hog_cccd_kb_bit_rep_3;
#else
static uint8_t hid_scenario_hog_cccd_kb_nkey;
#endif
#endif
static uint8_t hid_scenario_hog_ctrl_point;

struct bt_conn * hogs_conn_hdl = NULL;


static uint8_t hid_scenario_hog_report_map[] = {
	/* Can't change order */
	#if defined(CONFIG_AIR_PRODUCT_TYPE_GAME_CONTROLLER) && defined(CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_BT_MODE)
	#include "hid_descriptor_le_gamepad_1.h"
	#else
	#include "hid_descriptor_keyboard_consumer.h"
	#include "hid_descriptor_keyboard_std.h"
	#include "hid_descriptor_mouse.h"
	#if defined(CONFIG_AIR_PRODUCT_TYPE_KEYBOARD)
	#include "hid_descriptor_keyboard_Nkey.h"
	#endif /* CONFIG_AIR_PRODUCT_TYPE_KEYBOARD */
	#endif /* CONFIG_AIR_PRODUCT_TYPE_GAME_CONTROLLER*/
};


static ssize_t hid_scenario_hog_read_info(struct bt_conn *conn,
			  const struct bt_gatt_attr *attr, void *buf,
			  uint16_t len, uint16_t offset)
{
    DBG_LOGI(thisMOD," hid_scenario_hog_read_info ");
	return bt_gatt_attr_read(conn, attr, buf, len, offset, attr->user_data,
				 sizeof(struct hids_info));
}

static ssize_t hid_scenario_hog_read_report_map(struct bt_conn *conn,
			       const struct bt_gatt_attr *attr, void *buf,
			       uint16_t len, uint16_t offset)
{
    DBG_LOGI(thisMOD," hid_scenario_hog_read_report_map ");
	return bt_gatt_attr_read(conn, attr, buf, len, offset, hid_scenario_hog_report_map,
				 sizeof(hid_scenario_hog_report_map));
}







#if !defined(CONFIG_AIR_PRODUCT_TYPE_GAME_CONTROLLER)
/// Mouse callback functions
static ssize_t hid_scenario_hog_read_report_kb_consumer(struct bt_conn *conn,
			   const struct bt_gatt_attr *attr, void *buf,
			   uint16_t len, uint16_t offset)
{
    DBG_LOGI(thisMOD," hid_scenario_hog_read_report_kb_consumer ");
	return bt_gatt_attr_read(conn, attr, buf, len, offset, attr->user_data,
				 sizeof(struct hids_report));
}

static void hid_scenario_hog_input_ccc_changed_kb_consumer(const struct bt_gatt_attr *attr, uint16_t value)
{
    DBG_LOGI(thisMOD," hid_scenario_hog_input_ccc_changed_kb_consumer ");
	hid_scenario_hog_cccd_kb_consumer = (value == BT_GATT_CCC_NOTIFY) ? 1 : 0;
}

static ssize_t hid_scenario_hog_read_input_report_kb_consumer(struct bt_conn *conn,
				 const struct bt_gatt_attr *attr, void *buf,
				 uint16_t len, uint16_t offset)
{
    DBG_LOGI(thisMOD," hid_scenario_hog_read_input_report_kb_consumer ");
	return bt_gatt_attr_read(conn, attr, buf, len, offset, NULL, 0);
}
/// End of mouse call back functions



/// Mouse callback functions
static ssize_t hid_scenario_hog_read_report_kb_std(struct bt_conn *conn,
			   const struct bt_gatt_attr *attr, void *buf,
			   uint16_t len, uint16_t offset)
{
    DBG_LOGI(thisMOD," hid_scenario_hog_read_report_kb_std ");
	return bt_gatt_attr_read(conn, attr, buf, len, offset, attr->user_data,
				 sizeof(struct hids_report));
}

static void hid_scenario_hog_input_ccc_changed_kb_std(const struct bt_gatt_attr *attr, uint16_t value)
{
    DBG_LOGI(thisMOD," hid_scenario_hog_input_ccc_changed_kb_std ");
	hid_scenario_hog_cccd_kb_std = (value == BT_GATT_CCC_NOTIFY) ? 1 : 0;
}

static ssize_t hid_scenario_hog_read_input_report_kb_std(struct bt_conn *conn,
				 const struct bt_gatt_attr *attr, void *buf,
				 uint16_t len, uint16_t offset)
{
    DBG_LOGI(thisMOD," hid_scenario_hog_read_input_report_kb_std ");
	return bt_gatt_attr_read(conn, attr, buf, len, offset, NULL, 0);
}
/// End of mouse call back functions






/// Mouse callback functions
static ssize_t hid_scenario_hog_read_report_mouse(struct bt_conn *conn,
			   const struct bt_gatt_attr *attr, void *buf,
			   uint16_t len, uint16_t offset)
{
    DBG_LOGI(thisMOD," hid_scenario_hog_read_report_mouse handle = %d", attr->handle);
	return bt_gatt_attr_read(conn, attr, buf, len, offset, attr->user_data,
				 sizeof(struct hids_report));
}

static void hid_scenario_hog_input_ccc_changed_mouse(const struct bt_gatt_attr *attr, uint16_t value)
{
	hid_scenario_hog_cccd_mouse = (value == BT_GATT_CCC_NOTIFY) ? 1 : 0;

    DBG_LOGI(thisMOD," hid_scenario_hog_input_ccc_changed_mouse = %d ", hid_scenario_hog_cccd_mouse);
	DBG_LOGI(thisMOD," hid_scenario_hog_input_ccc_changed_mouse handle = %d", attr->handle);

    if (hid_scenario_hog_cccd_mouse){
		hid_common_set_hid_exp_flag(FLAG_BIT_ATT_NOTIFY_MOUSE_ENA);
        hid_scenario_send_state_update_notification(MODE_OPEN_CONNECTED_CCCD_READY, 0);
    }
}

static ssize_t hid_scenario_hog_read_input_report_mouse(struct bt_conn *conn,
				 const struct bt_gatt_attr *attr, void *buf,
				 uint16_t len, uint16_t offset)
{
    DBG_LOGI(thisMOD," hid_scenario_hog_read_input_report_mouse ");
	return bt_gatt_attr_read(conn, attr, buf, len, offset, NULL, 0);
}
/// End of mouse call back functions
#endif /* ! CONFIG_AIR_PRODUCT_TYPE_GAME_CONTROLLER */

#if defined(CONFIG_AIR_PRODUCT_TYPE_KEYBOARD)
#if defined(BT_MODE_NKEY_SPLIT_GROUP)
/// kb_bit_rep_1 callback functions
static ssize_t hid_scenario_hog_read_report_kb_bit_rep_1(struct bt_conn *conn,
			   const struct bt_gatt_attr *attr, void *buf,
			   uint16_t len, uint16_t offset)
{
    DBG_LOGI(thisMOD," hid_scenario_hog_read_report_kb_bit_rep_1 ");
	return bt_gatt_attr_read(conn, attr, buf, len, offset, attr->user_data,
				 sizeof(struct hids_report));
}

static void hid_scenario_hog_input_ccc_changed_kb_bit_rep_1(const struct bt_gatt_attr *attr, uint16_t value)
{
    DBG_LOGI(thisMOD," hid_scenario_hog_input_ccc_changed_kb_bit_rep_1 ");
	hid_scenario_hog_cccd_kb_bit_rep_1 = (value == BT_GATT_CCC_NOTIFY) ? 1 : 0;
}

static ssize_t hid_scenario_hog_read_input_report_kb_bit_rep_1(struct bt_conn *conn,
				 const struct bt_gatt_attr *attr, void *buf,
				 uint16_t len, uint16_t offset)
{
    DBG_LOGI(thisMOD," hid_scenario_hog_read_input_report_kb_bit_rep_1 ");
	return bt_gatt_attr_read(conn, attr, buf, len, offset, NULL, 0);
}
/// End of kb_bit_rep_1 call back functions

/// kb_bit_rep_2 callback functions
static ssize_t hid_scenario_hog_read_report_kb_bit_rep_2(struct bt_conn *conn,
			   const struct bt_gatt_attr *attr, void *buf,
			   uint16_t len, uint16_t offset)
{
    DBG_LOGI(thisMOD," hid_scenario_hog_read_report_kb_bit_rep_2 ");
	return bt_gatt_attr_read(conn, attr, buf, len, offset, attr->user_data,
				 sizeof(struct hids_report));
}

static void hid_scenario_hog_input_ccc_changed_kb_bit_rep_2(const struct bt_gatt_attr *attr, uint16_t value)
{
    DBG_LOGI(thisMOD," hid_scenario_hog_input_ccc_changed_kb_bit_rep_2 ");
	hid_scenario_hog_cccd_kb_bit_rep_2 = (value == BT_GATT_CCC_NOTIFY) ? 1 : 0;
}

static ssize_t hid_scenario_hog_read_input_report_kb_bit_rep_2(struct bt_conn *conn,
				 const struct bt_gatt_attr *attr, void *buf,
				 uint16_t len, uint16_t offset)
{
    DBG_LOGI(thisMOD," hid_scenario_hog_read_input_report_kb_bit_rep_2 ");
	return bt_gatt_attr_read(conn, attr, buf, len, offset, NULL, 0);
}
/// End of kb_bit_rep_2 call back functions

/// kb_bit_rep_3 callback functions
static ssize_t hid_scenario_hog_read_report_kb_bit_rep_3(struct bt_conn *conn,
			   const struct bt_gatt_attr *attr, void *buf,
			   uint16_t len, uint16_t offset)
{
    DBG_LOGI(thisMOD," hid_scenario_hog_read_report_kb_bit_rep_3 ");
	return bt_gatt_attr_read(conn, attr, buf, len, offset, attr->user_data,
				 sizeof(struct hids_report));
}

static void hid_scenario_hog_input_ccc_changed_kb_bit_rep_3(const struct bt_gatt_attr *attr, uint16_t value)
{
    DBG_LOGI(thisMOD," hid_scenario_hog_input_ccc_changed_kb_bit_rep_3 ");
	hid_scenario_hog_cccd_kb_bit_rep_3 = (value == BT_GATT_CCC_NOTIFY) ? 1 : 0;
}

static ssize_t hid_scenario_hog_read_input_report_kb_bit_rep_3(struct bt_conn *conn,
				 const struct bt_gatt_attr *attr, void *buf,
				 uint16_t len, uint16_t offset)
{
    DBG_LOGI(thisMOD," hid_scenario_hog_read_input_report_kb_bit_rep_3 ");
	return bt_gatt_attr_read(conn, attr, buf, len, offset, NULL, 0);
}
/// End of kb_bit_rep_3 call back functions
#else
/// kb_nkey callback functions
static ssize_t hid_scenario_hog_read_report_kb_nkey(struct bt_conn *conn,
			   const struct bt_gatt_attr *attr, void *buf,
			   uint16_t len, uint16_t offset)
{
    DBG_LOGI(thisMOD," hid_scenario_hog_read_report_kb_nkey ");
	return bt_gatt_attr_read(conn, attr, buf, len, offset, attr->user_data,
				 sizeof(struct hids_report));
}

static void hid_scenario_hog_input_ccc_changed_kb_nkey(const struct bt_gatt_attr *attr, uint16_t value)
{
    DBG_LOGI(thisMOD," hid_scenario_hog_input_ccc_changed_kb_nkey ");
	hid_scenario_hog_cccd_kb_nkey = (value == BT_GATT_CCC_NOTIFY) ? 1 : 0;
}

static ssize_t hid_scenario_hog_read_input_report_kb_nkey(struct bt_conn *conn,
				 const struct bt_gatt_attr *attr, void *buf,
				 uint16_t len, uint16_t offset)
{
    DBG_LOGI(thisMOD," hid_scenario_hog_read_input_report_kb_nkey ");
	return bt_gatt_attr_read(conn, attr, buf, len, offset, NULL, 0);
}
/// End of kb_nkey call back functions
#endif
#endif



static ssize_t hid_scenario_hog_write_ctrl_point(struct bt_conn *conn,
				const struct bt_gatt_attr *attr,
				const void *buf, uint16_t len, uint16_t offset,
				uint8_t flags)
{
    DBG_LOGI(thisMOD," hid_scenario_hog_write_ctrl_point ");
	uint8_t *value = attr->user_data;

	if (offset + len > sizeof(hid_scenario_hog_ctrl_point)) {
		return BT_GATT_ERR(BT_ATT_ERR_INVALID_OFFSET);
	}

	memcpy(value + offset, buf, len);

	return len;
}

/* HID Service Declaration */
BT_GATT_SERVICE_DEFINE(hog_svc,
	BT_GATT_PRIMARY_SERVICE(BT_UUID_HIDS),  //0
	
	BT_GATT_CHARACTERISTIC(BT_UUID_HIDS_INFO, BT_GATT_CHRC_READ,               //1,2
			       BT_GATT_PERM_READ, hid_scenario_hog_read_info, NULL, &hid_scenario_hog_info),
	BT_GATT_CHARACTERISTIC(BT_UUID_HIDS_REPORT_MAP, BT_GATT_CHRC_READ,          //3,4
			       BT_GATT_PERM_READ_ENCRYPT, hid_scenario_hog_read_report_map, NULL, NULL),


	#if !defined(CONFIG_AIR_PRODUCT_TYPE_GAME_CONTROLLER)
	BT_GATT_CHARACTERISTIC(BT_UUID_HIDS_REPORT,                                 //5,6
			       BT_GATT_CHRC_READ | BT_GATT_CHRC_NOTIFY,
			       SAMPLE_BT_PERM_READ,
			       hid_scenario_hog_read_input_report_kb_consumer, NULL, NULL),
	BT_GATT_CCC(hid_scenario_hog_input_ccc_changed_kb_consumer,                          //7
		    SAMPLE_BT_PERM_READ | SAMPLE_BT_PERM_WRITE),
	BT_GATT_DESCRIPTOR(BT_UUID_HIDS_REPORT_REF, BT_GATT_PERM_READ,              //8
			   hid_scenario_hog_read_report_kb_consumer, NULL, &hid_scenario_hog_input_kb_consumer),


	BT_GATT_CHARACTERISTIC(BT_UUID_HIDS_REPORT,                                 //9, 10
			       BT_GATT_CHRC_READ | BT_GATT_CHRC_NOTIFY,
			       SAMPLE_BT_PERM_READ,
			       hid_scenario_hog_read_input_report_kb_std, NULL, NULL),
	BT_GATT_CCC(hid_scenario_hog_input_ccc_changed_kb_std,                               //11,
		    SAMPLE_BT_PERM_READ | SAMPLE_BT_PERM_WRITE),
	BT_GATT_DESCRIPTOR(BT_UUID_HIDS_REPORT_REF, BT_GATT_PERM_READ,              //12
			   hid_scenario_hog_read_report_kb_std, NULL, &hid_scenario_hog_input_kb_std),


	BT_GATT_CHARACTERISTIC(BT_UUID_HIDS_REPORT,                                 //13.14
			       BT_GATT_CHRC_READ | BT_GATT_CHRC_NOTIFY,
			       SAMPLE_BT_PERM_READ,
			       hid_scenario_hog_read_input_report_mouse, NULL, NULL),
	BT_GATT_CCC(hid_scenario_hog_input_ccc_changed_mouse,                       //15
		    SAMPLE_BT_PERM_READ | SAMPLE_BT_PERM_WRITE),
	BT_GATT_DESCRIPTOR(BT_UUID_HIDS_REPORT_REF, BT_GATT_PERM_READ,              //16
			   hid_scenario_hog_read_report_mouse, NULL, &hid_scenario_hog_input_mouse),

	#if defined(CONFIG_AIR_PRODUCT_TYPE_KEYBOARD)
	#if defined(BT_MODE_NKEY_SPLIT_GROUP)
	BT_GATT_CHARACTERISTIC(BT_UUID_HIDS_REPORT,                                 //17.18
			       BT_GATT_CHRC_READ | BT_GATT_CHRC_NOTIFY,
			       SAMPLE_BT_PERM_READ,
			       hid_scenario_hog_read_input_report_kb_bit_rep_1, NULL, NULL),
	BT_GATT_CCC(hid_scenario_hog_input_ccc_changed_kb_bit_rep_1,                //19
		    SAMPLE_BT_PERM_READ | SAMPLE_BT_PERM_WRITE),
	BT_GATT_DESCRIPTOR(BT_UUID_HIDS_REPORT_REF, BT_GATT_PERM_READ,              //20
			   hid_scenario_hog_read_report_kb_bit_rep_1, NULL, &hid_scenario_hog_input_kb_bit_rep_1),

	
	BT_GATT_CHARACTERISTIC(BT_UUID_HIDS_REPORT,                               //21.22  
			       BT_GATT_CHRC_READ | BT_GATT_CHRC_NOTIFY,
			       SAMPLE_BT_PERM_READ,
			       hid_scenario_hog_read_input_report_kb_bit_rep_2, NULL, NULL),
	BT_GATT_CCC(hid_scenario_hog_input_ccc_changed_kb_bit_rep_2,               //23
		    SAMPLE_BT_PERM_READ | SAMPLE_BT_PERM_WRITE),
	BT_GATT_DESCRIPTOR(BT_UUID_HIDS_REPORT_REF, BT_GATT_PERM_READ,             //24
			   hid_scenario_hog_read_report_kb_bit_rep_2, NULL, &hid_scenario_hog_input_kb_bit_rep_2),

	
	BT_GATT_CHARACTERISTIC(BT_UUID_HIDS_REPORT,                                //25.26
			       BT_GATT_CHRC_READ | BT_GATT_CHRC_NOTIFY,
			       SAMPLE_BT_PERM_READ,
			       hid_scenario_hog_read_input_report_kb_bit_rep_3, NULL, NULL),
	BT_GATT_CCC(hid_scenario_hog_input_ccc_changed_kb_bit_rep_3,               //27
		    SAMPLE_BT_PERM_READ | SAMPLE_BT_PERM_WRITE),
	BT_GATT_DESCRIPTOR(BT_UUID_HIDS_REPORT_REF, BT_GATT_PERM_READ,             //28
			   hid_scenario_hog_read_report_kb_bit_rep_3, NULL, &hid_scenario_hog_input_kb_bit_rep_3), 

	#else
	BT_GATT_CHARACTERISTIC(BT_UUID_HIDS_REPORT,                                //17.18
			       BT_GATT_CHRC_READ | BT_GATT_CHRC_NOTIFY,
			       SAMPLE_BT_PERM_READ,
			       hid_scenario_hog_read_input_report_kb_nkey, NULL, NULL),
	BT_GATT_CCC(hid_scenario_hog_input_ccc_changed_kb_nkey,               //19
		    SAMPLE_BT_PERM_READ | SAMPLE_BT_PERM_WRITE),
	BT_GATT_DESCRIPTOR(BT_UUID_HIDS_REPORT_REF, BT_GATT_PERM_READ,             //20
			   hid_scenario_hog_read_report_kb_nkey, NULL, &hid_scenario_hog_input_kb_nkey), 
	#endif
	#endif /* CONFIG_AIR_PRODUCT_TYPE_KEYBOARD */
	#endif /* !CONFIG_AIR_PRODUCT_TYPE_GAME_CONTROLLER */

#if !defined(HID_SCENARIO_LE_GAMEPAD_INTERNAL_HOGP) && defined(CONFIG_AIR_PRODUCT_TYPE_GAME_CONTROLLER) && defined(CONFIG_AIR_HID_DEVICE_SCENARIO_SERVICE_BT_MODE)
    BT_GATT_CHARACTERISTIC(BT_UUID_HIDS_REPORT,
                           BT_GATT_CHRC_READ | BT_GATT_CHRC_NOTIFY,
                           BT_GATT_PERM_READ,
                           hid_scenario_le_gamepad_read_empty, NULL, NULL),
    BT_GATT_CCC(hid_scenario_le_gamepad_cccd, BT_GATT_PERM_READ | BT_GATT_PERM_WRITE),
	BT_GATT_DESCRIPTOR(BT_UUID_HIDS_REPORT_REF,
                           BT_GATT_PERM_READ,
                           hid_scenario_le_gamepad_report_ref, NULL, &hid_scenario_hog_input_game_controller),

	BT_GATT_CHARACTERISTIC(BT_UUID_HIDS_REPORT,
                           BT_GATT_CHRC_READ | BT_GATT_CHRC_NOTIFY,
                           BT_GATT_PERM_READ,
                           hid_scenario_le_gamepad_read_empty, NULL, NULL),
    BT_GATT_CCC(hid_scenario_le_gamepad_cccd, BT_GATT_PERM_READ | BT_GATT_PERM_WRITE),
	BT_GATT_DESCRIPTOR(BT_UUID_HIDS_REPORT_REF,
                           BT_GATT_PERM_READ,
                           hid_scenario_le_gamepad_report_ref1, NULL, &hid_scenario_hog_input_game_controller1),

	BT_GATT_CHARACTERISTIC(BT_UUID_HIDS_REPORT,
                           BT_GATT_CHRC_READ | BT_GATT_CHRC_WRITE | BT_GATT_CHRC_WRITE_WITHOUT_RESP,
                           BT_GATT_PERM_READ | BT_GATT_PERM_WRITE,
                           NULL, hid_scenario_le_gamepad_write1, NULL),
    BT_GATT_CCC(hid_scenario_le_gamepad_cccd, BT_GATT_PERM_READ | BT_GATT_PERM_WRITE),
	BT_GATT_DESCRIPTOR(BT_UUID_HIDS_REPORT_REF,
                           BT_GATT_PERM_READ,
                           hid_scenario_le_gamepad_report_ref2, NULL, &hid_scenario_hog_output_game_controller),

	BT_GATT_CHARACTERISTIC(BT_UUID_HIDS_REPORT,
                           BT_GATT_CHRC_READ | BT_GATT_CHRC_WRITE | BT_GATT_CHRC_WRITE_WITHOUT_RESP,
                           BT_GATT_PERM_READ | BT_GATT_PERM_WRITE,
                           NULL, hid_scenario_le_gamepad_write2, NULL),
    BT_GATT_CCC(hid_scenario_le_gamepad_cccd, BT_GATT_PERM_READ | BT_GATT_PERM_WRITE),
	BT_GATT_DESCRIPTOR(BT_UUID_HIDS_REPORT_REF,
                           BT_GATT_PERM_READ,
                           hid_scenario_le_gamepad_report_ref3, NULL, &hid_scenario_hog_output_game_controller1),

#endif

	BT_GATT_CHARACTERISTIC(BT_UUID_HIDS_CTRL_POINT,
			       BT_GATT_CHRC_WRITE_WITHOUT_RESP,
			       BT_GATT_PERM_WRITE,
			       NULL, hid_scenario_hog_write_ctrl_point, &hid_scenario_hog_ctrl_point),
);












void hid_scenario_hog_init(hid_scenario_hogp_attr_cb cb)
{
	hid_scenario_hogp_attr_handle_cb = cb;
}

int hog_notify(uint8_t attr_idx, uint8_t * payload_data, uint8_t payload_data_len)
{
    DBG_LOGI(thisMOD," attr_idx = %u, payload = 0x%08X,  payload_data_len = %d  ",  attr_idx,  *(uint32_t*)payload_data, payload_data_len);
    int ret = bt_gatt_notify(NULL, &hog_svc.attrs[attr_idx], payload_data, payload_data_len);

	//uint16_t handle = bt_gatt_attr_get_handle(hog_svc.attrs[attr_idx].attr);


    DBG_LOGI(thisMOD," payload_data_len = %u \n ",  payload_data_len );
    return ret; 
}



static void hogs_connected(struct bt_conn *conn, uint8_t err)
{
    DBG_LOGI(thisMOD," hogs_connected  conn = 0x%X, err = %d \n ",  conn, err );
    hogs_conn_hdl = conn;
	#if defined(CONFIG_AIR_PRODUCT_TYPE_MOUSE)
    hid_scenario_hogp_attr_handle_cb(bt_gatt_attr_get_handle(&hog_svc.attrs[ATTRIBUTE_ID_MOUSE]), 
									bt_gatt_attr_get_handle(&hog_svc.attrs[ATTRIBUTE_ID_KEYBOARD]), 
									bt_gatt_attr_get_handle(&hog_svc.attrs[ATTRIBUTE_ID_KEYBOARD_CONSUMER]));
	#elif defined(CONFIG_AIR_PRODUCT_TYPE_KEYBOARD)
	hid_scenario_hogp_attr_handle_cb(bt_gatt_attr_get_handle(&hog_svc.attrs[ATTRIBUTE_ID_MOUSE]), 
									bt_gatt_attr_get_handle(&hog_svc.attrs[ATTRIBUTE_ID_KEYBOARD]), 
									bt_gatt_attr_get_handle(&hog_svc.attrs[ATTRIBUTE_ID_KEYBOARD_CONSUMER]),
									bt_gatt_attr_get_handle(&hog_svc.attrs[ATTRIBUTE_ID_KB_NKEY]));
	#elif defined(CONFIG_AIR_PRODUCT_TYPE_GAME_CONTROLLER)
    hid_scenario_hogp_attr_handle_cb(bt_gatt_attr_get_handle(&hog_svc.attrs[ATTRIBUTE_ID_GAME_CONTROLLER]));
	#endif
}

static void hogs_disconnected(struct bt_conn *conn, uint8_t reason)
{
    DBG_LOGI(thisMOD," hogs_disconnected  conn = 0x%X, reason = %d \n ",  conn, reason );
    hogs_conn_hdl = NULL;
}

BT_CONN_CB_DEFINE(conn_cbs_hogs) = {
	.connected = hogs_connected,
	.disconnected = hogs_disconnected,
};


















