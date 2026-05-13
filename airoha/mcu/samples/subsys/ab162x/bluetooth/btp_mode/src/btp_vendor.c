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

/* gap.c - Bluetooth GAP Tester */

/*
 * Copyright (c) 2015-2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/sys/atomic.h>
#include <zephyr/types.h>
#include <string.h>

#include <zephyr/toolchain.h>
#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/conn.h>
#include <zephyr/bluetooth/gatt.h>
#include <zephyr/bluetooth/hci.h>

#include <zephyr/sys/byteorder.h>
#include <zephyr/net/buf.h>

#include <hci_core.h>
#include "btp_vendor.h"
#include <zephyr/logging/log.h>
#include "id.h"
#include <zephyr/bluetooth/services/bas.h>
//#define LOG_MODULE_NAME bttester_gap
//LOG_MODULE_REGISTER(LOG_MODULE_NAME, CONFIG_BTTESTER_LOG_LEVEL);

#include "btp/btp.h"
#include "hal_uart.h"

#if 0
static ssize_t read_name(struct bt_conn *conn, const struct bt_gatt_attr *attr,
			 void *buf, uint16_t len, uint16_t offset)
{
    //uint8_t key[16] = {0x57,0xa9,0xda,0x12,0xd1,0x2e,0x6e,0x13,0x1e,0x20,0x61,0x2a,0xd1,0x0a,0x6a,0x19};
    uint8_t key[24] = {0x19,0x6a,0x0a,0xd1,0x2a,0x61,0x20,0x1e,0x13,0x6e,0x2e,0xd1,0x12,0xda,0xa9,0x57,0x9e,0x7a,0x00,0xef,0xb1,0x7a,0xe7,0x46};
	//const char *name = bt_get_name();

	return bt_gatt_attr_read(conn, attr, buf, len, offset, key,
				 24);
}


static ssize_t write_name(struct bt_conn *conn, const struct bt_gatt_attr *attr,
			 const void *buf, uint16_t len, uint16_t offset,
			 uint8_t flags)
{
	char value[CONFIG_BT_DEVICE_NAME_MAX] = {};

	if (offset >= sizeof(value)) {
		return BT_GATT_ERR(BT_ATT_ERR_INVALID_OFFSET);
	}

	if (offset + len >= sizeof(value)) {
		return BT_GATT_ERR(BT_ATT_ERR_INVALID_ATTRIBUTE_LEN);
	}

	memcpy(value, buf, len);

	bt_set_name(value);

	return len;
}


BT_GATT_SERVICE_DEFINE(_vendor_btp_svc,
	//BT_GATT_PRIMARY_SERVICE(BT_UUID_DECLARE_16(0x1234)),
	/* Require pairing for writes to device name */
	BT_GATT_CHARACTERISTIC(BT_UUID_GATT_EDKM,
			       BT_GATT_CHRC_READ | BT_GATT_CHRC_WRITE,
			       BT_GATT_PERM_READ |BT_GATT_PERM_WRITE,
			       read_name, write_name, bt_dev.name),
);
#if 0

BT_GATT_SERVICE_DEFINE(_vendor_btp_svc2,
	BT_GATT_PRIMARY_SERVICE(BT_UUID_DECLARE_16(0x1235)),
	/* Require pairing for writes to device name */
	BT_GATT_CHARACTERISTIC(BT_UUID_GAP_DEVICE_NAME,
			       BT_GATT_CHRC_AUTH | BT_GATT_CHRC_AUTH,
			       BT_GATT_PERM_READ |BT_GATT_PERM_WRITE,
			       read_name, write_name, bt_dev.name),
);
#endif
#endif

static uint8_t btp_vendor_read_loacl_addr(const void *cmd, uint16_t cmd_len,
                                          void *rsp, uint16_t *rsp_len)
{
    bt_addr_le_t addr = {0};
    struct btp_vendor_read_local_addr_rp *rp = rsp;
    bt_id_read_public_addr(&addr);
    LOG_ERR("[BTP_VENDOR] Read local addr is %x:%x:%x:%x:%x:%x", addr.a.val[0], addr.a.val[1], addr.a.val[2], addr.a.val[3], addr.a.val[4], addr.a.val[5]);
    memcpy(rp, &addr, 6);
    *rsp_len = sizeof(*rp);
    return BTP_STATUS_SUCCESS;
}


static uint8_t btp_vendor_enable_sc(const void *cmd,
                                 uint16_t cmd_len,
                                 void *rsp,
                                 uint16_t *rsp_len)
{
	LOG_ERR("BTP enable sc");
	extern bool g_is_sc_enable;
	g_is_sc_enable = true;
    return BTP_STATUS_SUCCESS;
}

static uint8_t btp_vendor_set_battery_level(const void *cmd,
                                 uint16_t cmd_len,
                                 void *rsp,
                                 uint16_t *rsp_len)
{
    uint8_t battery_level = ((uint8_t *)cmd)[0];
	LOG_ERR("BTP set battery level = %02x", battery_level);
	bt_bas_set_battery_level(battery_level);
    return BTP_STATUS_SUCCESS;
}


static uint8_t btp_vendor_set_rpa_timeout(const void *cmd,
                                 uint16_t cmd_len,
                                 void *rsp,
                                 uint16_t *rsp_len)
{
    
    
	struct net_buf *buf;

    struct bt_hci_cp_le_set_rpa_timeout *cp;

    buf = bt_hci_cmd_create(BT_HCI_OP_LE_SET_RPA_TIMEOUT,
                sizeof(*cp));
    cp = net_buf_add(buf, sizeof(*cp));
    cp->rpa_timeout = 4;    
	LOG_ERR("BTP PRA TIMEOUT SET");
    bt_hci_cmd_send_sync(BT_HCI_OP_LE_SET_RPA_TIMEOUT, buf,
                   NULL);
   
   return BTP_STATUS_SUCCESS;

}
#if 0
static uint8_t btp_vendor_set_encrypt_adv_1(const void *cmd,
                                 uint16_t cmd_len,
                                 void *rsp,
                                 uint16_t *rsp_len)
{
    const uint8_t adv_data[29] = {0x18,0xe1,0x57,0xca,0xde,0x74,0xE4,0xDC,0xAF,0xDC,0x51,0xC7,0x28,0x28,0x10,0xC2,0x21,0x7F,0x0E,0x4C,0xEF,0x43,0x43,0x18,0x1F,0xBA,0x00,0x69,0xCC};
    struct bt_le_adv_param param = BT_LE_ADV_PARAM_INIT(BT_LE_ADV_OPT_ONE_TIME,
							    BT_GAP_ADV_FAST_INT_MIN_2,
							    BT_GAP_ADV_FAST_INT_MAX_2,
							    NULL);
    
    static const struct bt_data ad[] = {
        BT_DATA(BT_DATA_ENCRYPTED_AD_DATA, adv_data, sizeof(adv_data))
    };
    bt_le_adv_start(&param, ad, sizeof(ad), NULL, 0);
    
    return BTP_STATUS_SUCCESS;
}
#endif
static uint8_t btp_vendor_set_encrypt_adv(const void *cmd,
                                 uint16_t cmd_len,
                                 void *rsp,
                                 uint16_t *rsp_len)
{
    uint8_t adv_id = ((uint8_t *)cmd)[0];
    if (adv_id == 1) {
    const uint8_t adv_data[22] = {0xff,0x4b,0xfd,0x86,0xd8,0x2f,0x12,0x49,0xb7,0x1f,0x33,0xf9,0x66,0x72,0x61,0x90,0x8e,0x39,0x95,0xfa,0x12,0x99};
    struct bt_le_adv_param param = BT_LE_ADV_PARAM_INIT(BT_LE_ADV_OPT_ONE_TIME | BT_LE_ADV_OPT_USE_IDENTITY,
							    BT_GAP_ADV_FAST_INT_MIN_2,
							    BT_GAP_ADV_FAST_INT_MAX_2,
							    NULL);
     const struct bt_data ad[] = {
        BT_DATA(BT_DATA_ENCRYPTED_AD_DATA, adv_data, 22),
    };
    bt_le_adv_start(&param, ad, ARRAY_SIZE(ad), NULL, 0);
    } else if (adv_id == 2) {
        const uint8_t adv_data[29] = {0x18,0xe1,0x57,0xca,0xde,0x74,0xE4,0xDC,0xAF,0xDC,0x51,0xC7,0x28,0x28,0x10,0xC2,0x21,0x7F,0x0E,0x4C,0xEF,0x43,0x43,0x18,0x1F,0xBA,0x00,0x69,0xCC};
        struct bt_le_adv_param param = BT_LE_ADV_PARAM_INIT(BT_LE_ADV_OPT_ONE_TIME | BT_LE_ADV_OPT_USE_IDENTITY,
                                    BT_GAP_ADV_FAST_INT_MIN_2,
                                    BT_GAP_ADV_FAST_INT_MAX_2,
                                    NULL);
         const struct bt_data ad[] = {
            BT_DATA(BT_DATA_ENCRYPTED_AD_DATA, adv_data, 29),
        };
        bt_le_adv_start(&param, ad, ARRAY_SIZE(ad), NULL, 0);

    } else if (adv_id == 3) {
        const uint8_t adv_data[29] = {0x8d,0x1c,0x97,0x6e,0x7a,0x35,0x44,0x40,0x76,0x12,0x57,0x88,0xc2,0x38,0xa5,0x8e,0x8b,0xd9,0xcf,0xf0,0xde,0xfe,0x25,0x1a,0x8e,0x72,0x75,0x45,0x4c};
        struct bt_le_adv_param param = BT_LE_ADV_PARAM_INIT(BT_LE_ADV_OPT_ONE_TIME | BT_LE_ADV_OPT_USE_IDENTITY,
                                    BT_GAP_ADV_FAST_INT_MIN_2,
                                    BT_GAP_ADV_FAST_INT_MAX_2,
                                    NULL);
         const struct bt_data ad[] = {
            BT_DATA(BT_DATA_ENCRYPTED_AD_DATA, adv_data, 29),
        };
        bt_le_adv_start(&param, ad, ARRAY_SIZE(ad), NULL, 0);


    }
    return BTP_STATUS_SUCCESS;

}


static const struct btp_handler vendor_handlers[] = {
    {
        .opcode = BTP_VENDOR_READ_LOCAL_ADDR,
        .expect_len = 0,
        .func = btp_vendor_read_loacl_addr,
    },
    {
        .opcode = BTP_VENDOR_ENABLE_SC,
        .expect_len = 0,
        .func = btp_vendor_enable_sc,
    },
    {
        .opcode = BTP_VENDOR_SET_BATTERY_LEVEL,
        .expect_len = 1,
        .func = btp_vendor_set_battery_level,
    },
    {
        .opcode = BTP_VENDOR_SET_RPA_TIMEOUT,
        .expect_len = 0,
        .func = btp_vendor_set_rpa_timeout,
    },
    {
        .opcode = BTP_VENDOR_START_ADV,
        .expect_len = 1,
        .func = btp_vendor_set_encrypt_adv,
    },

};
uint8_t tester_init_vendor(void)
{
    LOG_ERR("BTP int");

    tester_register_command_handlers(BTP_SERVICE_ID_VENDOR, vendor_handlers,
                                     ARRAY_SIZE(vendor_handlers));
    //hal_uart_set_software_flowcontrol(HAL_UART_2, 0x11,0x13,0x77);
    return BTP_STATUS_SUCCESS;
}

