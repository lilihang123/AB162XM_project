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

#include "zephyr/bluetooth/conn.h"
#include "zephyr/bluetooth/hci_types.h"
#if defined(AIR_PURE_GAMING_DONGLE_ENABLE)

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/hci.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/flash.h>
#include <zephyr/logging/log.h>
#include <zephyr/kernel.h>
#include <zephyr/devicetree.h>
#include <zephyr/device.h>
#include "app_acl_conn.h"
#include "app_bt_conn_manager.h"
#include "assert.h"
#include "af_events_declaration.h"
#include "app_events.h"
#include "hal_gpt.h"
#include "assert.h"
#include "nvkey.h"
#include "hal_trng.h"

/* Private define ------------------------------------------------------------*/
#define thisMODULE app_bt_acl
#define thisMOD    "app_bt_acl"
LOG_MODULE_REGISTER(thisMODULE);

#define SCAN_INTERVAL 0x0640 /* uint:0.625ms, 1000 ms */
#define SCAN_WINDOW   0x0600 /* uint:0.625ms, 960 ms */
#define INIT_INTERVAL 0x0010 /* uint:0.625ms, 10 ms */
#define INIT_WINDOW   0x0010 /* uint:0.625ms, 10 ms */
#define CONN_INTERVAL 0x0010 /* uint:0.625ms, 10 ms */
#define CONN_LATENCY  0
#define CONN_TIMEOUT  500 /* uint:10ms, 5000 ms */

#define BT_GAP_LE_AD_TYPE_APPEARANCE                                0x19
#define APPEARANCE_SERVICE_HID_MOUSE                                0x0030
#define APPEARANCE_SERVICE_HID_KEYBOARD                             0x0031
#define APPEARANCE_SERVICE_HID_GAMEPAD                              0x0032
#define BT_GAP_LE_AD_TYPE_NAME                                      0x09
#define BT_GAP_LE_AD_SHORT_NAME                                     0x08

/* Private typedef -----------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static void app_bt_acl_connected_cb(struct bt_conn *conn, uint8_t reason);
static void app_bt_acl_disconnected_cb(struct bt_conn *conn, uint8_t reason);
static void app_bt_acl_security_changed_cb(struct bt_conn *conn, bt_security_t level, enum bt_security_err err);
static struct bt_conn_cb app_acl_conn_callbacks = {
    .connected = app_bt_acl_connected_cb,
    .disconnected = app_bt_acl_disconnected_cb,
#if defined(CONFIG_BT_SMP)
    .security_changed = app_bt_acl_security_changed_cb,
#endif
};

const struct bt_le_scan_param app_acl_scan_param = {
    .type       = BT_HCI_LE_SCAN_PASSIVE,
    .options    = BT_LE_SCAN_OPT_NONE,
    .interval   = SCAN_INTERVAL,
    .window     = SCAN_WINDOW,
};

const struct bt_conn_le_create_param app_acl_create_param = {
    .options = BT_CONN_LE_OPT_NONE,
    .interval = INIT_INTERVAL,
    .window = INIT_WINDOW,
    .interval_coded = 0,
    .window_coded = 0,
    .timeout = 0,
};

const struct bt_le_conn_param app_acl_conn_param = {
    .interval_min = CONN_INTERVAL,
    .interval_max = CONN_INTERVAL,
    .latency = CONN_LATENCY,
    .timeout = CONN_TIMEOUT,
};

static uint32_t app_acl_scan_timer;
static bool app_acl_scan_timer_is_enable;
static bool app_acl_scan_running;

/* Public variables ----------------------------------------------------------*/
struct k_fifo app_bt_acl_dev_fifo;

/* Private functions ---------------------------------------------------------*/
static void app_bt_acl_connected_cb(struct bt_conn *conn, uint8_t reason)
{
    bt_addr_le_t *target_addr = (bt_addr_le_t *)bt_conn_get_dst(conn);
    app_bt_conn_handle_t *link_handle;
    struct bt_conn_info info;

    bt_conn_get_info(conn, &info);
    if (info.role == 0x80 || info.role == 0x81)
    {
        /* pseduo link connected */
        LOG_INF("[app_hid_dongle] ACL Connection handle pseduo Connected (reason 0x%x)", reason);
        return;
    }

    /* find out link */
    link_handle = app_bt_conn_manager_query_handle_by_conn(APP_BT_CONN_TYPE_ACL, conn);
    assert(link_handle != NULL);
    LOG_INF("[app_hid_dongle] ACL Connection handle 0x%x Connected (reason 0x%x), address = 0x%x:0x%x:0x%x:0x%x:0x%x:0x%x",
            link_handle,
            reason,
            target_addr->a.val[5],
            target_addr->a.val[4],
            target_addr->a.val[3],
            target_addr->a.val[2],
            target_addr->a.val[1],
            target_addr->a.val[0]);

    if (reason)
    {
        link_handle->acl_status = APP_BT_CONN_STATUS_DISCONNECTED;
        bt_conn_unref(link_handle->acl_conn);
        link_handle->acl_conn = NULL;
        /* send event to do next step */
        app_events_send(EVT_CMD_ACL_CONN_FAIL, link_handle->scenario_handle);
    }
    else
    {
        link_handle->acl_status = APP_BT_CONN_STATUS_CONNECTTED;
        // bt_conn_ref(link_handle->acl_conn);
        /* send event to do next step */
        app_events_send(EVT_CMD_ACL_CONN_SUCCESS, link_handle->scenario_handle);
    }
}

static void app_bt_acl_disconnected_cb(struct bt_conn *conn, uint8_t reason)
{
    bt_addr_le_t *target_addr = (bt_addr_le_t *)bt_conn_get_dst(conn);
    app_bt_conn_handle_t *link_handle;
    struct bt_conn_info info;

    bt_conn_get_info(conn, &info);
    if (info.role == 0x80 || info.role == 0x81)
    {
        /* pseduo link disconnected */
        LOG_INF("[app_hid_dongle] ACL Connection handle pseduo Disconnected (reason 0x%x)", reason);
        return;
    }

    /* find out link */
    link_handle = app_bt_conn_manager_query_handle_by_conn(APP_BT_CONN_TYPE_ACL, conn);
    LOG_INF("[app_hid_dongle] ACL Connection handle 0x%x Disconnected (reason 0x%x), address = 0x%x:0x%x:0x%x:0x%x:0x%x:0x%x",
            link_handle,
            reason,
            target_addr->a.val[5],
            target_addr->a.val[4],
            target_addr->a.val[3],
            target_addr->a.val[2],
            target_addr->a.val[1],
            target_addr->a.val[0]);
    if (link_handle == NULL)
    {
        return;
    }

    link_handle->acl_status = APP_BT_CONN_STATUS_DISCONNECTED;
    bt_conn_unref(link_handle->acl_conn);
    link_handle->acl_conn = NULL;

    /* send event to do next step */
    if (reason == BT_HCI_ERR_LOCALHOST_TERM_CONN)
    {
        app_events_send(EVT_CMD_ACL_DISC_SUCCESS, link_handle->scenario_handle);
    }
    else
    {
        app_events_send(EVT_CMD_ACL_DISC_ERR, link_handle->scenario_handle);
    }
}

#if defined(CONFIG_BT_SMP)
static void app_bt_acl_security_changed_cb(struct bt_conn *conn, bt_security_t level, enum bt_security_err err)
{
    bt_addr_le_t *target_addr = (bt_addr_le_t *)bt_conn_get_dst(conn);
    app_bt_conn_handle_t *link_handle;

    /* find out link */
    link_handle = app_bt_conn_manager_query_handle_by_conn(APP_BT_CONN_TYPE_ACL, conn);
    assert(link_handle != NULL);
    LOG_INF("[app_hid_dongle] ACL Connection handle 0x%x Security changed (level %u, err %d), address = 0x%x:0x%x:0x%x:0x%x:0x%x:0x%x",
            link_handle,
            level,
            err,
            target_addr->a.val[5],
            target_addr->a.val[4],
            target_addr->a.val[3],
            target_addr->a.val[2],
            target_addr->a.val[1],
            target_addr->a.val[0]);

    if (err == BT_SECURITY_ERR_SUCCESS)
    {
        link_handle->acl_status = APP_BT_CONN_STATUS_SECURITY_UPDATE;
        /* send event to do next step */
        app_events_send(EVT_CMD_ACL_SEC_UPDATE_SUCCESS, link_handle->scenario_handle);
    }
    else
    {
        /* send event to do next step */
        app_events_send(EVT_CMD_ACL_SEC_UPDATE_FAIL, link_handle->scenario_handle);
    }
}
#endif

static int app_bt_acl_device_check_adv_element(uint8_t type, struct net_buf_simple *buf, uint8_t *element, uint16_t element_size)
{
    int err = -1;
    uint8_t *data = buf->data;
    uint16_t len = buf->len;
    uint16_t offset;

    offset = 0;
    while (offset < len)
    {
        if (type == data[offset + 1])
        {
            if(memcmp(&data[offset + 2], element, element_size) == 0){
                err = 0;
                break;
            }

        }
        offset += (data[offset]+1);
    }

    return err;
}

static int app_bt_acl_device_get_adv_element(uint8_t type, struct net_buf_simple *buf, uint8_t **element)
{
    uint16_t offset;
    uint8_t *data = buf->data;
    uint16_t len = buf->len;

    offset = 0;
    while (offset < len)
    {
        if (type == data[offset + 1])
        {
            *element = &(data[offset + 2]);
            return data[offset]-1;  //element length
        }
        offset += (data[offset]+1);
    }

    return -1;
}

static int app_bt_acl_device_parse_adv(uint8_t adv_type, struct net_buf_simple *buf, uint8_t device)
{
    int err = -1;

    /* We're only interested in connectable events */
    if ((adv_type != BT_GAP_ADV_TYPE_ADV_IND) &&
        (adv_type != BT_GAP_ADV_TYPE_ADV_DIRECT_IND) &&
        (adv_type != BT_GAP_ADV_TYPE_EXT_ADV))
    {
        return err;
    }

    err = app_bt_acl_device_check_adv_element(BT_GAP_LE_AD_TYPE_APPEARANCE, buf, &device, sizeof(device));
    if(err){
        return err;
    }

    err = 0;
    /* If want filter device name, uncomment the following code */
#if 0
    uint8_t name[] = "M20";
    err = app_bt_acl_device_check_adv_element(BT_GAP_LE_AD_TYPE_NAME, buf, name, strlen(name));
    if(err){
        err = app_bt_acl_device_check_adv_element(BT_GAP_LE_AD_SHORT_NAME, buf, name, strlen(name));
    }
    LOG_INF("[app_hid_dongle] ret = %d, size = %d", err, strlen(name));
#endif
    if (err == 0){
        LOG_INF("[app_hid_dongle] Find Device!!!");
    }

    return err;
}

static void app_bt_acl_device_found_cb(const bt_addr_le_t *addr, int8_t rssi, uint8_t adv_type, struct net_buf_simple *buf)
{
    app_bt_conn_device_found_t *dev_found;
    int name_len;
    uint8_t *name = NULL;

#if defined(AIR_PURE_GAMING_DONGLE_KB_ENABLE)
    if (app_bt_acl_device_parse_adv(adv_type, buf, APPEARANCE_SERVICE_HID_KEYBOARD) == 0)
    {
        LOG_INF("[app_hid_dongle] ACL Connection Found KB Device, address = 0x%x:0x%x:0x%x:0x%x:0x%x:0x%x, rssi = %d, adv_type = %u",
                addr->a.val[5],
                addr->a.val[4],
                addr->a.val[3],
                addr->a.val[2],
                addr->a.val[1],
                addr->a.val[0],
                rssi,
                adv_type);

        /* push device info into FIFO for process in later  */
        dev_found = (app_bt_conn_device_found_t *)app_bt_conn_manager_malloc(sizeof(app_bt_conn_device_found_t));
        assert(dev_found != NULL);
        dev_found->role = APP_BT_CONN_ROLE_KEYBOARD;
        dev_found->rssi = rssi;
        dev_found->adv_type = adv_type;
        memcpy(&(dev_found->addr), addr, sizeof(bt_addr_le_t));
        name_len = app_bt_acl_device_get_adv_element(BT_GAP_LE_AD_TYPE_NAME, buf, &name);
        if(name_len < 0){
            name_len = app_bt_acl_device_get_adv_element(BT_GAP_LE_AD_SHORT_NAME, buf, &name);
        }
        // assert(name_len >= 0);
        if (name_len <= 0)
        {
            LOG_ERR("[app_hid_dongle] ACL Connection KB Device name length is not right, address = 0x%x:0x%x:0x%x:0x%x:0x%x:0x%x, rssi = %d, adv_type = %u",
                    addr->a.val[5],
                    addr->a.val[4],
                    addr->a.val[3],
                    addr->a.val[2],
                    addr->a.val[1],
                    addr->a.val[0],
                    rssi,
                    adv_type);
            app_bt_conn_manager_free(dev_found);
            return;
        }
        name_len = (name_len > APP_BT_CONN_MANAGER_DEVICE_NAME_MAX) ? APP_BT_CONN_MANAGER_DEVICE_NAME_MAX : name_len;
        dev_found->name_len = name_len;
        memcpy(&(dev_found->name[0]), name, name_len);
        k_fifo_put(&app_bt_acl_dev_fifo, dev_found);

        /* send event to do next step */
        app_events_send(EVT_CMD_ACL_DEVICE_FOUND, NULL);
    }
#endif /* AIR_PURE_GAMING_DONGLE_KB_ENABLE */

#if defined(AIR_PURE_GAMING_DONGLE_GAMEPAD_ENABLE)
    if (app_bt_acl_device_parse_adv(adv_type, buf, APPEARANCE_SERVICE_HID_GAMEPAD) == 0)
    {
        LOG_INF("[app_hid_dongle] ACL Connection Found MS Device, address = 0x%x:0x%x:0x%x:0x%x:0x%x:0x%x, rssi = %d, adv_type = %u",
                addr->a.val[5],
                addr->a.val[4],
                addr->a.val[3],
                addr->a.val[2],
                addr->a.val[1],
                addr->a.val[0],
                rssi,
                adv_type);

        /* push device info into FIFO for process in later  */
        dev_found = (app_bt_conn_device_found_t *)app_bt_conn_manager_malloc(sizeof(app_bt_conn_device_found_t));
        assert(dev_found != NULL);
        dev_found->role = APP_BT_CONN_ROLE_GAMEPAD;
        dev_found->rssi = rssi;
        dev_found->adv_type = adv_type;
        memcpy(&(dev_found->addr), addr, sizeof(bt_addr_le_t));
        name_len = app_bt_acl_device_get_adv_element(BT_GAP_LE_AD_TYPE_NAME, buf, &name);
        if(name_len < 0){
            name_len = app_bt_acl_device_get_adv_element(BT_GAP_LE_AD_SHORT_NAME, buf, &name);
        }
        // assert(name_len >= 0);
        if (name_len <= 0)
        {
            LOG_ERR("[app_hid_dongle] ACL Connection MS Device name length is not right, address = 0x%x:0x%x:0x%x:0x%x:0x%x:0x%x, rssi = %d, adv_type = %u",
                    addr->a.val[5],
                    addr->a.val[4],
                    addr->a.val[3],
                    addr->a.val[2],
                    addr->a.val[1],
                    addr->a.val[0],
                    rssi,
                    adv_type);
            app_bt_conn_manager_free(dev_found);
            return;
        }
        name_len = (name_len > APP_BT_CONN_MANAGER_DEVICE_NAME_MAX) ? APP_BT_CONN_MANAGER_DEVICE_NAME_MAX : name_len;
        dev_found->name_len = name_len;
        memcpy(&(dev_found->name[0]), name, name_len);
        k_fifo_put(&app_bt_acl_dev_fifo, dev_found);

        /* send event to do next step */
        app_events_send(EVT_CMD_ACL_DEVICE_FOUND, NULL);
    }
#endif /* AIR_PURE_GAMING_DONGLE_GAMEPAD_ENABLE */

#if defined(AIR_PURE_GAMING_DONGLE_MS_ENABLE)
    if (app_bt_acl_device_parse_adv(adv_type, buf, APPEARANCE_SERVICE_HID_MOUSE) == 0)
    {
        LOG_INF("[app_hid_dongle] ACL Connection Found MS Device, address = 0x%x:0x%x:0x%x:0x%x:0x%x:0x%x, rssi = %d, adv_type = %u",
                addr->a.val[5],
                addr->a.val[4],
                addr->a.val[3],
                addr->a.val[2],
                addr->a.val[1],
                addr->a.val[0],
                rssi,
                adv_type);

        /* push device info into FIFO for process in later  */
        dev_found = (app_bt_conn_device_found_t *)app_bt_conn_manager_malloc(sizeof(app_bt_conn_device_found_t));
        assert(dev_found != NULL);
        dev_found->role = APP_BT_CONN_ROLE_MOUSE;
        dev_found->rssi = rssi;
        dev_found->adv_type = adv_type;
        memcpy(&(dev_found->addr), addr, sizeof(bt_addr_le_t));
        name_len = app_bt_acl_device_get_adv_element(BT_GAP_LE_AD_TYPE_NAME, buf, &name);
        if(name_len < 0){
            name_len = app_bt_acl_device_get_adv_element(BT_GAP_LE_AD_SHORT_NAME, buf, &name);
        }
        // assert(name_len >= 0);
        if (name_len <= 0)
        {
            LOG_ERR("[app_hid_dongle] ACL Connection MS Device name length is not right, address = 0x%x:0x%x:0x%x:0x%x:0x%x:0x%x, rssi = %d, adv_type = %u",
                    addr->a.val[5],
                    addr->a.val[4],
                    addr->a.val[3],
                    addr->a.val[2],
                    addr->a.val[1],
                    addr->a.val[0],
                    rssi,
                    adv_type);
            app_bt_conn_manager_free(dev_found);
            return;
        }
        name_len = (name_len > APP_BT_CONN_MANAGER_DEVICE_NAME_MAX) ? APP_BT_CONN_MANAGER_DEVICE_NAME_MAX : name_len;
        dev_found->name_len = name_len;
        memcpy(&(dev_found->name[0]), name, name_len);
        k_fifo_put(&app_bt_acl_dev_fifo, dev_found);

        /* send event to do next step */
        app_events_send(EVT_CMD_ACL_DEVICE_FOUND, NULL);
    }
#endif /* AIR_PURE_GAMING_DONGLE_MS_ENABLE */
}

static void app_bt_acl_connection_scan_timer_cb(void *user_data)
{
    /* send event to stop scan */
    app_events_send(EVT_CMD_ACL_SCAN_STOP_REQ, NULL);
}

/* Public functions ----------------------------------------------------------*/
int app_bt_acl_connection_start_scan(uint32_t timeout_ms)
{
    int err;

    err = bt_le_scan_start(&app_acl_scan_param, app_bt_acl_device_found_cb);
    if (err)
    {
        LOG_INF("[app_hid_dongle] ACL Scanning failed to start (err %d)", err);
        return err;
    }

    if (timeout_ms != 0)
    {
        hal_gpt_sw_get_timer(&app_acl_scan_timer);
        if(HAL_GPT_STATUS_OK != hal_gpt_sw_start_timer_ms(app_acl_scan_timer, timeout_ms, app_bt_acl_connection_scan_timer_cb, NULL))
        {
            assert(0);
        }
        app_acl_scan_timer_is_enable = true;
    }

    app_acl_scan_running = true;

    LOG_INF("[app_hid_dongle] ACL Scanning successfully started, timer handle %u, timeout ms %u", app_acl_scan_timer, timeout_ms);

    return err;
}

int app_bt_acl_connection_stop_scan(void)
{
    int err;

    if (app_acl_scan_timer_is_enable)
    {
        hal_gpt_sw_stop_timer_ms(app_acl_scan_timer);
        hal_gpt_sw_free_timer(app_acl_scan_timer);
        app_acl_scan_timer_is_enable = false;
    }

    err = bt_le_scan_stop();
    if (err)
    {
        LOG_INF("[app_hid_dongle] ACL Scanning stop failed (err %d)", err);
    }
    else
    {
        LOG_INF("[app_hid_dongle] ACL Scanning successfully stopped.");
    }

    app_acl_scan_running = false;

    return err;
}

bool app_bt_acl_connection_scan_is_running(void)
{
    return app_acl_scan_running;
}

app_bt_conn_device_found_t *app_bt_acl_connection_get_found_device(app_bt_conn_role_t role, k_timeout_t timeout)
{

    app_bt_conn_device_found_t *dev_found;

    dev_found = k_fifo_get(&app_bt_acl_dev_fifo, timeout);

    return dev_found;
}

int app_bt_acl_connection_connect(app_bt_conn_handle_t *link_handle)
{
    int err;

    // LOG_INF("[app_hid_dongle] ACL Connection connect start.");
    err = bt_conn_le_create(&(link_handle->acl_addr), &app_acl_create_param, &app_acl_conn_param, &(link_handle->acl_conn));
    if (err)
    {
        LOG_INF("[app_hid_dongle] ACL Connection handle 0x%x create start failed, err = %d.link_handle->acl_conn =%x", link_handle, err,link_handle->acl_conn);
    }
    else
    {
        LOG_INF("[app_hid_dongle] ACL Connection handle 0x%x create start.link_handle->acl_conn = %x", link_handle,link_handle->acl_conn);
    }

    return err;
}

int app_bt_acl_security_change(app_bt_conn_handle_t *link_handle)
{
    int err = 0;

#if defined(CONFIG_BT_SMP)
    // LOG_INF("[app_hid_dongle] ACL Connection security change start.");
    err = bt_conn_set_security(link_handle->acl_conn, BT_SECURITY_L2);
    if (err)
    {
        LOG_INF("[app_hid_dongle] ACL Connection handle 0x%x set security start failed, err = %d.", link_handle, err);
    }
    else
    {
        LOG_INF("[app_hid_dongle] ACL Connection handle 0x%x set security start.", link_handle);
    }
#endif

    return err;
}

int app_bt_acl_connection_disconnect(app_bt_conn_handle_t *link_handle)
{
    int err;

    // LOG_INF("[app_hid_dongle] ACL Connection disconnect start.");
    err = bt_conn_disconnect(link_handle->acl_conn, BT_HCI_ERR_REMOTE_USER_TERM_CONN);
    if (err)
    {
        LOG_INF("[app_hid_dongle] ACL Connection handle 0x%x disconnect start fail, err = %d.", link_handle, err);
    }
    else
    {
        LOG_INF("[app_hid_dongle] ACL Connection handle 0x%x disconnect start.", link_handle);
    }

    return err;
}

int app_bt_acl_connection_init(void)
{
    int err;

    LOG_INF("[app_hid_dongle] ACL Connection init start.");

    k_fifo_init(&app_bt_acl_dev_fifo);

#if 0
    #define HID_SCENARIO_NVKEY_ID           0x6100

    bt_addr_le_t addr;
    nvkey_status_t nvkey_ret;
    uint32_t nvkey_size = sizeof(bt_addr_le_t);
    nvkey_ret = nvkey_read_data(HID_SCENARIO_NVKEY_ID, (uint8_t *)&addr, &nvkey_size);
    if ((nvkey_ret == NVKEY_STATUS_OK) && (nvkey_size == sizeof(bt_addr_le_t)))
    {
        LOG_INF("BT address get successfully, address = 0x%x:0x%x:0x%x:0x%x:0x%x:0x%x",
                addr.a.val[5],
                addr.a.val[4],
                addr.a.val[3],
                addr.a.val[2],
                addr.a.val[1],
                addr.a.val[0]);
    }
    else
    {
        addr.type = BT_ADDR_LE_RANDOM;
        hal_trng_get_generated_random_number((uint32_t *)&addr.a.val[0]);
        addr.a.val[4] = 0;
        addr.a.val[5] = 0xc0;
        nvkey_status_t status = NVKEY_STATUS_ERROR;
        status = nvkey_write_data(HID_SCENARIO_NVKEY_ID, (uint8_t *)&addr, sizeof(bt_addr_le_t));
        LOG_INF("BT address save successfully, address = 0x%x:0x%x:0x%x:0x%x:0x%x:0x%x, status = %d, %d, %u",
                addr.a.val[5],
                addr.a.val[4],
                addr.a.val[3],
                addr.a.val[2],
                addr.a.val[1],
                addr.a.val[0],
                status,
                nvkey_ret,
                nvkey_size);
    }

    err = bt_id_create(&addr, NULL);
    if (err < 0) {
        LOG_INF("Failed to set BT address (err %d)", err);
        assert(0);
    } else {
        LOG_INF("BT address set successfully, address = 0x%x:0x%x:0x%x:0x%x:0x%x:0x%x",
                addr.a.val[5],
                addr.a.val[4],
                addr.a.val[3],
                addr.a.val[2],
                addr.a.val[1],
                addr.a.val[0]);
    }
#endif

    err = bt_enable(NULL);
    if (err) {
        LOG_INF("[app_hid_dongle] BT init failed (err %d)", err);
        return err;
    }

    bt_conn_cb_register((struct bt_conn_cb *)(&app_acl_conn_callbacks));

    LOG_INF("[app_hid_dongle] ACL Connection init done.");

    return err;
}

#endif /* AIR_PURE_GAMING_DONGLE_ENABLE */
