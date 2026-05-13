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
#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/conn.h>
#include <zephyr/bluetooth/uuid.h>
#include <zephyr/bluetooth/gatt.h>
#include <errno.h>
#include <zephyr/sys/printk.h>
#include <zephyr/sys/byteorder.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

#if IS_ENABLED(CONFIG_AIR_PRODUCT_TYPE_GAME_CONTROLLER)
#include "hid_scenario_le_gamepad.h"
#include "hid_scenario_service.h"
#include "hid_scenario_service_internal.h"
#include "hal_spi_master.h"

#define thisMODULE le_gamepad
#define thisMOD "le_gamepad"

LOG_MODULE_REGISTER(thisMODULE);

#define HID_GATT_FLAG_REMOTE_WAKE 0x1
#define HID_GATT_FLAG_NORMAL_CONNECTABLE 0x2

#define HID_GAMEPAD_OUTPUT_MAX_LEN 16

typedef struct {
    uint16_t      bcd_hid;              /**< HID class specification release number. */
    uint8_t       b_country_code;       /**< Hardware target country. */
    uint8_t       flags;                /**< Bit0:RemoteWake, bit1: NormallyConnectable. */
} hid_scenario_le_gamepad_info_t;

typedef struct {
    hid_scenario_le_gamepad_info_t  info;
    uint8_t                         report_id;
    uint8_t*                        report_map;
    uint32_t                        report_map_size;
} hid_scenario_le_gamepad_ctx_t;

static hid_scenario_le_gamepad_ctx_t s_le_gamepad_ctx = {
    .info = {0x10, 0x00, 0x03},
    .report_map = NULL,
};

ATTR_ALIGN(16) uint8_t spi_dummy_write_reg1 = 0xff;

#if defined(HID_SCENARIO_LE_GAMEPAD_INTERNAL_HOGP)
static struct bt_gatt_attr s_hid_le_gamepad_attrs[] = {
    BT_GATT_PRIMARY_SERVICE(BT_UUID_HIDS),

    BT_GATT_CHARACTERISTIC(BT_UUID_HIDS_INFO,
                           BT_UUID_CHRC_READ,
                           hid_scenario_le_gamepad_info, NULL, NULL),

    BT_GATT_CHARACTERISTIC(BT_UUID_HIDS_REPORT_MAP,
                           BT_UUID_CHRC_READ,
                           BT_GATT_PERM_READ_ENCRYPT,
                           hid_scenario_le_gamepad_report_map, NULL, NULL),

    BT_GATT_CHARACTERISTIC(BT_UUID_HIDS_CTRL_POINT,
                           BT_GATT_CHRC_WRITE_WITHOUT_RESP,
                           BT_GATT_PERM_WRITE,
                           hid_scenario_le_gamepad_ctrl_point, NULL, NULL),

    BT_GATT_CHARACTERISTIC(BT_UUID_HIDS_REPORT,
                           BT_GATT_CHRC_READ | BT_GATT_CHRC_NOTIFY,
                           BT_GATT_PERM_READ,
                           hid_scenario_le_gamepad_read_empty, NULL, NULL),
    BT_GATT_CCC(hid_scenario_le_gamepad_cccd, BT_GATT_PERM_READ | BT_GATT_PERM_WRITE),

    BT_GATT_DESCRIPTOR(BT_UUID_HIDS_REPORT_REF,/* TODO */
                           BT_GATT_PERM_READ,
                           hid_scenario_le_gamepad_report_ref, NULL, NULL),
};

static struct bt_gatt_service s_hid_le_gamepad_srv = BT_GATT_SERVICE(s_hid_le_gamepad_attrs);

static ssize_t hid_scenario_le_gamepad_info(struct bt_conn *conn,
                                        const struct bt_gatt_attr *attr,
                                        void *buf,
                                        uint16_t len,
                                        uint16_t offset)
{
    return bt_gatt_attr_read(conn, attr, buf, len, offset,
                            &s_le_gamepad_ctx.info, sizeof(s_le_gamepad_ctx.info));
}

static ssize_t hid_scenario_le_gamepad_report_map(struct bt_conn *conn,
                                        const struct bt_gatt_attr *attr,
                                        void *buf,
                                        uint16_t len,
                                        uint16_t offset)
{
    return bt_gatt_attr_read(conn, attr, buf, len, offset,
                            s_le_gamepad_ctx.report_map, s_le_gamepad_ctx.hid_report_map_size);
}

static ssize_t hid_scenario_le_gamepad_ctrl_point(struct bt_conn *conn,
                                        const struct bt_gatt_attr *attr,
                                        void *buf,
                                        uint16_t len,
                                        uint16_t offset)
{
    /* TODO log */
    return 0;
}
#endif

ssize_t hid_scenario_le_gamepad_report_ref(struct bt_conn *conn,
                                        const struct bt_gatt_attr *attr,
                                        void *buf,
                                        uint16_t len,
                                        uint16_t offset)
{
    static const uint8_t input_ref[2] = {REPORT_ID_BT_GAME_CONTROLLER, 0x1};
    DBG_LOGI(thisMOD," hid_scenario_le_gamepad_report_ref, handle=0x%x", bt_gatt_attr_get_handle(attr));
    return bt_gatt_attr_read(conn, attr, buf, len, offset, input_ref, sizeof(input_ref));
}

ssize_t hid_scenario_le_gamepad_report_ref1(struct bt_conn *conn,
                                        const struct bt_gatt_attr *attr,
                                        void *buf,
                                        uint16_t len,
                                        uint16_t offset)
{
    static const uint8_t input_ref[2] = {REPORT_ID_BT_GAME_CONTROLLER_GROUP0, 0x1};
    DBG_LOGI(thisMOD," hid_scenario_le_gamepad_report_ref, handle=0x%x", bt_gatt_attr_get_handle(attr));
    return bt_gatt_attr_read(conn, attr, buf, len, offset, input_ref, sizeof(input_ref));
}

ssize_t hid_scenario_le_gamepad_report_ref2(struct bt_conn *conn,
                                        const struct bt_gatt_attr *attr,
                                        void *buf,
                                        uint16_t len,
                                        uint16_t offset)
{
    static const uint8_t input_ref[2] = {REPORT_ID_BT_GAME_CONTROLLER_GROUP1, 0x2};
    DBG_LOGI(thisMOD," hid_scenario_le_gamepad_report_ref, handle=0x%x", bt_gatt_attr_get_handle(attr));
    return bt_gatt_attr_read(conn, attr, buf, len, offset, input_ref, sizeof(input_ref));
}

ssize_t hid_scenario_le_gamepad_report_ref3(struct bt_conn *conn,
                                        const struct bt_gatt_attr *attr,
                                        void *buf,
                                        uint16_t len,
                                        uint16_t offset)
{
    static const uint8_t input_ref[2] = {REPORT_ID_BT_GAME_CONTROLLER_GROUP2, 0x2};
    DBG_LOGI(thisMOD," hid_scenario_le_gamepad_report_ref, handle=0x%x", bt_gatt_attr_get_handle(attr));
    return bt_gatt_attr_read(conn, attr, buf, len, offset, input_ref, sizeof(input_ref));
}

ssize_t hid_scenario_le_gamepad_read_empty(struct bt_conn *conn,
                                        const struct bt_gatt_attr *attr,
                                        void *buf,
                                        uint16_t len,
                                        uint16_t offset)
{
    DBG_LOGI(thisMOD," hid_scenario_le_gamepad_read_empty, handle=0x%x", bt_gatt_attr_get_handle(attr));
    uint8_t report_data[2] = {s_le_gamepad_ctx.report_id, 0x01};//0x01 input report type.
    return bt_gatt_attr_read(conn, attr, buf, len, offset, report_data, sizeof(report_data));
}

ssize_t hid_scenario_le_gamepad_write1(struct bt_conn *conn,
                                        const struct bt_gatt_attr *attr,
                                        const void *buf,
                                        uint16_t len,
                                        uint16_t offset, uint8_t flags)
{
#if defined(CONFIG_AIR_HID_OUTPUT_REPORT_NOTIFY)
#if 0
    static uint8_t notify_buf[HID_GAMEPAD_OUTPUT_MAX_LEN + 1];
    notify_buf[0] = REPORT_ID_BT_GAME_CONTROLLER_GROUP1;
    memcpy(&notify_buf[1], buf, len >= HID_GAMEPAD_OUTPUT_MAX_LEN ? HID_GAMEPAD_OUTPUT_MAX_LEN : len + 1);
    //DBG_LOGI(thisMOD," hid_scenario_le_gamepad_write, handle=0x%x, len=%d, offset=%d", bt_gatt_attr_get_handle(attr), len, offset);
    hid_scenario_send_notification(SS_EVT_HID_OUTPUT_REPORT, notify_buf, len > HID_GAMEPAD_OUTPUT_MAX_LEN ? HID_GAMEPAD_OUTPUT_MAX_LEN : len + 1);
#else
    hid_scenario_send_notification(SS_EVT_HID_OUTPUT_REPORT, (uint8_t*)buf, len);
#endif
#endif
    return len;
}

ssize_t hid_scenario_le_gamepad_write2(struct bt_conn *conn,
                                        const struct bt_gatt_attr *attr,
                                        const void *buf,
                                        uint16_t len,
                                        uint16_t offset, uint8_t flags)
{
#if defined(CONFIG_AIR_HID_OUTPUT_REPORT_NOTIFY)
#if 0
    static uint8_t notify_buf[HID_GAMEPAD_OUTPUT_MAX_LEN + 1];
    notify_buf[0] = REPORT_ID_BT_GAME_CONTROLLER_GROUP1;
    memcpy(&notify_buf[1], buf, len >= HID_GAMEPAD_OUTPUT_MAX_LEN ? HID_GAMEPAD_OUTPUT_MAX_LEN : len + 1);
    //DBG_LOGI(thisMOD," hid_scenario_le_gamepad_write, handle=0x%x, len=%d", bt_gatt_attr_get_handle(attr), len);
    hid_scenario_send_notification(SS_EVT_HID_OUTPUT_REPORT, notify_buf, len > HID_GAMEPAD_OUTPUT_MAX_LEN ? HID_GAMEPAD_OUTPUT_MAX_LEN : len + 1);
#else
    hid_scenario_send_notification(SS_EVT_HID_OUTPUT_REPORT, (uint8_t*)buf, len);
#endif
#endif
    return len;
}

void hid_scenario_le_gamepad_cccd(const struct bt_gatt_attr *attr, uint16_t value)
{
    uint8_t hid_scenario_hog_cccd_gamepad = (value == BT_GATT_CCC_NOTIFY) ? 1 : 0;
    DBG_LOGI(thisMOD," hid_scenario_le_gamepad_cccd, handle=0x%x, value=%d", bt_gatt_attr_get_handle(attr), hid_scenario_hog_cccd_gamepad);
    if (hid_scenario_hog_cccd_gamepad){
        hid_common_set_hid_exp_flag(FLAG_BIT_ATT_NOTIFY_MOUSE_ENA);
        hid_scenario_send_state_update_notification(MODE_OPEN_CONNECTED_CCCD_READY, 0);
    }
}

void game_controller_bt_mode_hw_trigger_enable(void)
{
    hal_spi_master_config_t spi_config;
    int ret = 0;

    spi_config.bit_order = HAL_SPI_MASTER_MSB_FIRST;
    spi_config.slave_port = HAL_SPI_MASTER_SLAVE_0;
    spi_config.clock_frequency = 8000000;
    spi_config.phase = HAL_SPI_MASTER_CLOCK_PHASE1;
    spi_config.polarity = HAL_SPI_MASTER_CLOCK_POLARITY1;
    ret = hal_spi_master_init(HAL_SPI_MASTER_0, &spi_config);
    if (HAL_SPI_MASTER_STATUS_OK != ret) {
        LOG_INF(thisMOD" bt_hw_trigger_enable spi init failed, ret: %d.", ret);
    }
    hal_spi_master_set_clear_data(HAL_SPI_MASTER_0,1,1,true);

    hal_spi_master_send_and_receive_config_t spi_send_and_receive_config;
    spi_send_and_receive_config.receive_length = 1;
    spi_send_and_receive_config.send_length = 1;
    spi_send_and_receive_config.send_data = &spi_dummy_write_reg1;
    spi_send_and_receive_config.receive_buffer = &spi_dummy_write_reg1;
    hal_spi_master_send_and_receive_dma_advanced(HAL_SPI_MASTER_0, &spi_send_and_receive_config,false);   //not start
    hal_spi_master_set_bt_enable(HAL_SPI_MASTER_0, true);
}

#if defined(HID_SCENARIO_LE_GAMEPAD_INTERNAL_HOGP)
void hid_scenario_le_gamepad_init(hid_scenario_le_gamepad_init_param_t* init_param)
{
    s_le_gamepad_ctx.info.bcd_hid = init_param->ver;
    s_le_gamepad_ctx.info.b_country_code = init_param->country_code;
    s_le_gamepad_ctx.info.flags = 0x0;

    if (init_param->remote_wake_up) {
        s_le_gamepad_ctx.info.flags |= HID_GATT_FLAG_REMOTE_WAKE;
    }
    if (init_param->normal_connectable) {
        s_le_gamepad_ctx.info.flag |= HID_GATT_FLAG_NORMAL_CONNECTABLE;
    }
    s_le_gamepad_ctx.info.report_map = init_param->hid_report_map;
    s_le_gamepad_ctx.report_map_size = init_param->hid_report_map_size;
    s_le_gamepad_ctx.report_id = input_param->report_id;
    /* TODO log*/
}

void hid_scenario_le_gamepad_enable(void)
{
    bt_gatt_service_register(&s_hid_le_gamepad_srv);
    /* TODO log*/
}

void hid_scenario_le_gamepad_disable(void)
{
    bt_gatt_service_unregister(&s_hid_le_gamepad_srv);
    /* TODO log*/
}
#endif


#endif