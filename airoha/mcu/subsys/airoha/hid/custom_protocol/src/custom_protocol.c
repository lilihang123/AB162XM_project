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

#include "zephyr/irq.h"
#include <stdbool.h>
#if defined(AIR_PURE_GAMING_CUSTOM_PROTOCOL_ENABLE)

/* Includes ------------------------------------------------------------------*/
#include <zephyr/kernel.h>
#include <zephyr/devicetree.h>
#include <zephyr/device.h>
#include <zephyr/logging/log.h>
#include <zephyr/bluetooth/bluetooth.h>
#include "air_usb.h"
#include "air_usb_hid.h"
#include "air_daemon_work_q.h"
#include "custom_protocol.h"
#include "assert.h"
#include "bt_ull_le_hid_service.h"
#include <errno.h>
#include "hid_common.h"

/* Private define ------------------------------------------------------------*/
#define thisMODULE  epio_custom_protocol
#define thisMOD    "epio_custom_protocol"
LOG_MODULE_REGISTER(thisMODULE);

#define EPIO_CUSTOM_PROTOCOL_SUPPORT_DROP 0

/* Private typedef -----------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/
static const struct device *epio_usb_interrupt_hiddev;
static const struct device *epio_usb_control_hiddev;
static uint32_t epio_user_interrupt_id;
static uint32_t epio_user_control_id;
struct k_fifo epio_usb_rx_fifo;
#ifdef AIR_PURE_GAMING_CUSTOM_PROTOCOL_USB_REPORT_MODE
struct k_fifo epio_usb_tx_fifo;
#endif /* AIR_PURE_GAMING_CUSTOM_PROTOCOL_USB_REPORT_MODE */
struct k_fifo epio_bt_rx_fifo;
static void epio_custom_protocol_usb_rx_work_handler(struct k_work *work);
K_WORK_DEFINE(epio_custom_protocol_usb_rx_work, epio_custom_protocol_usb_rx_work_handler);
static void epio_custom_protocol_bt_rx_work_handler(struct k_work *work);
K_WORK_DEFINE(epio_custom_protocol_bt_rx_work, epio_custom_protocol_bt_rx_work_handler);
epio_process_callback_t epio_process_callback;

/* Private functions ---------------------------------------------------------*/
static void epio_custom_protocol_usb_rx_work_handler(struct k_work *work)
{
    uint8_t *data;
    uint16_t len;
    uint8_t *buf;
    const struct device *dev;

    data = k_fifo_get(&epio_usb_rx_fifo, K_NO_WAIT);
    while (data != NULL)
    {
        if (epio_process_callback.usb_recv_data_callback != NULL)
        {
            len = *(uint16_t *)((uint32_t)data+sizeof(void *)+sizeof(const struct device *));
            buf = data+sizeof(void *)+sizeof(const struct device *)+sizeof(uint16_t);
            dev = *(const struct device **)((uint32_t)data+sizeof(void *));
            epio_process_callback.usb_recv_data_callback(dev, len, buf);
        }
        k_free(data);
        data = k_fifo_get(&epio_usb_rx_fifo, K_NO_WAIT);
    }
}

static void epio_custom_protocol_bt_rx_work_handler(struct k_work *work)
{
    uint8_t *data;
    uint16_t len;
    uint8_t *buf;

    data = k_fifo_get(&epio_bt_rx_fifo, K_NO_WAIT);
#if EPIO_CUSTOM_PROTOCOL_SUPPORT_DROP
    uint8_t *data_last = k_fifo_get(&epio_bt_rx_fifo, K_NO_WAIT);
    while(data_last != NULL)
    {
        /* always make sure the data is pointer to the last cmd */
        k_free(data);
        data = data_last;
        data_last = k_fifo_get(&epio_bt_rx_fifo, K_NO_WAIT);
    }
#endif /* EPIO_CUSTOM_PROTOCOL_SUPPORT_DROP */
    while (data != NULL)
    {
        if (epio_process_callback.bt_recv_data_callback != NULL)
        {
            len = *(uint16_t *)((uint32_t)data+sizeof(void *)+sizeof(bt_addr_t));
            buf = data+sizeof(void *)+sizeof(bt_addr_t)+sizeof(uint16_t);
            epio_process_callback.bt_recv_data_callback((bt_addr_t *)((uint32_t)data+sizeof(void *)), len, buf);
        }
        k_free(data);
        data = k_fifo_get(&epio_bt_rx_fifo, K_NO_WAIT);
    }
}

#ifdef AIR_PURE_GAMING_CUSTOM_PROTOCOL_USB_REPORT_MODE
static int epio_usb_hid_get_report_cb(const struct device *dev, uint8_t type, uint8_t id, uint16_t len, uint8_t *buf)
{
    int ret = 0;
    uint16_t data_len;
    uint8_t *data_buf;
    uint8_t *data;
    uint8_t *data_last;

    if (((id != 0) && (id != AIR_USB_HID_CUSTOM_GET_REPORT_ID))
        || (len != AIR_USB_HID_CUSTOM_GET_REPORT_LEN))
    {
        return ret;
    }

    data = k_fifo_get(&epio_usb_tx_fifo, K_NO_WAIT);
    data_last = k_fifo_get(&epio_usb_tx_fifo, K_NO_WAIT);
    while(data_last != NULL)
    {
        /* always make sure the data is pointer to the last cmd */
        k_free(data);
        data = data_last;
        data_last = k_fifo_get(&epio_usb_tx_fifo, K_NO_WAIT);
    }
    if (data != NULL)
    {
        data_len = *(uint16_t *)((uint32_t)data+sizeof(void *)+sizeof(const struct device *));
        data_buf = data+sizeof(void *)+sizeof(const struct device *)+sizeof(uint16_t);
        assert(data_len == AIR_USB_HID_CUSTOM_GET_REPORT_LEN);
        if (id != 0)
        {
            assert(data_buf[0] == AIR_USB_HID_CUSTOM_GET_REPORT_ID);
        }
        memcpy(buf, data_buf, data_len);
        k_free(data);
        LOG_INF("[epio_custom_protocol] epio_usb_hid_get_report_cb dev = 0x%x, id = %d, len = %d.", dev, id, data_len);
    }
    else
    {
        memset(buf, 0, len);
    }

    return ret;
}

static int epio_usb_hid_set_report_cb(const struct device *dev, uint8_t type, uint8_t id, uint16_t len, const uint8_t *buf)
{
    int ret = 0;

    if ((id != AIR_USB_HID_CUSTOM_SET_REPORT_ID) || (len != AIR_USB_HID_CUSTOM_SET_REPORT_LEN))
    {
        return ret;
    }

    if ((id != 0) && (buf[0] == AIR_USB_HID_CUSTOM_SET_REPORT_ID))
    {
        return ret;
    }

    uint8_t *data = k_malloc(sizeof(void *)+sizeof(const struct device *)+sizeof(uint16_t)+len);
    assert(data != NULL);
    *(const struct device **)((uint32_t)data+sizeof(void *)) = dev;
    *(uint16_t *)((uint32_t)data+sizeof(void *)+sizeof(const struct device *)) = len;
    memcpy(data+sizeof(void *)+sizeof(const struct device *)+sizeof(uint16_t), buf, len);
#if EPIO_CUSTOM_PROTOCOL_SUPPORT_DROP
    uint8_t *data_last = k_fifo_get(&epio_usb_rx_fifo, K_NO_WAIT);
    while(data_last != NULL)
    {
        /* always make sure the data is pointer to the last cmd */
        k_free(data_last);
        data_last = k_fifo_get(&epio_usb_rx_fifo, K_NO_WAIT);
    }
#endif /* EPIO_CUSTOM_PROTOCOL_SUPPORT_DROP */
    k_fifo_put(&epio_usb_rx_fifo, data);
    air_daemon_wq_work_submit(&epio_custom_protocol_usb_rx_work);

    LOG_INF("[epio_custom_protocol] epio_usb_hid_set_report_cb dev = 0x%x, id = %d, len = %d.", dev, id, len);

    return ret;
}
#endif /* AIR_PURE_GAMING_CUSTOM_PROTOCOL_USB_REPORT_MODE */

#ifdef AIR_PURE_GAMING_CUSTOM_PROTOCOL_USB_INTERRUPT_MODE
int epio_usb_hid_rx_cb(const struct device *dev, uint8_t type, uint8_t id, uint16_t len, const uint8_t *buf)
{
    int ret = 0;

    if ((id == AIR_USB_HID_EPIO_RX_REPORT_ID)
        && (len == AIR_USB_HID_EPIO_RX_REPORT_LEN)
        && (buf[0] == AIR_USB_HID_EPIO_RX_REPORT_ID))
    {
        uint8_t *data = k_malloc(sizeof(void *)+sizeof(const struct device *)+sizeof(uint16_t)+len);
        assert(data != NULL);
        *(const struct device **)((uint32_t)data+sizeof(void *)) = dev;
        *(uint16_t *)((uint32_t)data+sizeof(void *)+sizeof(const struct device *)) = len;
        memcpy(data+sizeof(void *)+sizeof(const struct device *)+sizeof(uint16_t), buf, len);
#if EPIO_CUSTOM_PROTOCOL_SUPPORT_DROP
        uint8_t *data_last = k_fifo_get(&epio_usb_rx_fifo, K_NO_WAIT);
        while(data_last != NULL)
        {
            /* always make sure the data is pointer to the last cmd */
            k_free(data_last);
            data_last = k_fifo_get(&epio_usb_rx_fifo, K_NO_WAIT);
        }
#endif /* EPIO_CUSTOM_PROTOCOL_SUPPORT_DROP */
        k_fifo_put(&epio_usb_rx_fifo, data);
        air_daemon_wq_work_submit(&epio_custom_protocol_usb_rx_work);

        LOG_INF("[epio_custom_protocol] epio_usb_hid_rx_cb dev = 0x%x, id = %d, len = %d.", dev, id, len);
    }

    return ret;
}
#endif /* AIR_PURE_GAMING_CUSTOM_PROTOCOL_USB_REPORT_MODE */

/* Public functions ----------------------------------------------------------*/
int epio_usb_hid_send_data(const struct device *dev, uint16_t len, uint8_t *buf)
{
    int err = 0;

    if (len == 0 || buf == NULL || dev == NULL)
    {
        err = -1;
        return err;
    }

#ifdef AIR_PURE_GAMING_CUSTOM_PROTOCOL_USB_REPORT_MODE
    if (dev == epio_usb_control_hiddev)
    {
        uint8_t *data = k_malloc(sizeof(void *)+sizeof(const struct device *)+sizeof(uint16_t)+len);
        assert(data != NULL);
        *(const struct device **)((uint32_t)data+sizeof(void *)) = dev;
        *(uint16_t *)((uint32_t)data+sizeof(void *)+sizeof(const struct device *)) = len;
        memcpy(data+sizeof(void *)+sizeof(const struct device *)+sizeof(uint16_t), buf, len);
        k_fifo_put(&epio_usb_tx_fifo, data);
        err = 0;
        LOG_INF("[epio_custom_protocol] epio_usb_hid_send_data dev = 0x%x, len = %d, err = %d.", dev, len, err);
    }
#endif /* AIR_PURE_GAMING_CUSTOM_PROTOCOL_USB_REPORT_MODE */

#ifdef AIR_PURE_GAMING_CUSTOM_PROTOCOL_USB_INTERRUPT_MODE
    if (dev == epio_usb_interrupt_hiddev)
    {
        if (len != AIR_USB_HID_EPIO_TX_REPORT_LEN || buf[0] != AIR_USB_HID_EPIO_TX_REPORT_ID)
        {
            err = -1;
        }
        else
        {
            err = air_usb_hid_tx(epio_user_interrupt_id, dev, len, buf);

        }
        LOG_INF("[epio_custom_protocol] epio_usb_hid_send_data dev = 0x%x, len = %d, id = 0x%x, err = %d.", dev, len, buf[0], err);
    }
#endif /* AIR_PURE_GAMING_CUSTOM_PROTOCOL_USB_INTERRUPT_MODE */

    return err;
}

int epio_bt_hid_send_data(bt_addr_t *remote_address, uint16_t len, uint8_t *buf)
{
    int err;

    bt_ull_user_data_t tx_data;
    tx_data.user_data = buf;
    tx_data.user_data_length = len;
    memcpy(&tx_data.remote_address, remote_address, sizeof(bt_addr_t));
    err = bt_ull_le_hid_srv_action(BT_ULL_ACTION_TX_USER_DATA, &tx_data, sizeof(bt_ull_user_data_t));

    if (err)
    {
        LOG_INF("[epio_custom_protocol] epio_bt_hid_send_data tx to device fail.", err);
    }
    else
    {
        LOG_INF("[epio_custom_protocol] epio_bt_hid_send_data len = %d tx to device done.", len);
    }

    return err;
}

int epio_bt_hid_recv_data(bt_addr_t *remote_address, uint16_t len, uint8_t *buf)
{
    int ret = 0;
    #if EPIO_CUSTOM_PROTOCOL_SUPPORT_DROP
    uint8_t *data_last = k_fifo_get(&epio_bt_rx_fifo, K_NO_WAIT);
    while(data_last != NULL)
    {
        /* always make sure the data is pointer to the last cmd */
        k_free(data_last);
        data_last = k_fifo_get(&epio_bt_rx_fifo, K_NO_WAIT);
    }
    #endif /* EPIO_CUSTOM_PROTOCOL_SUPPORT_DROP */
    uint8_t *data = k_malloc(sizeof(void *)+sizeof(bt_addr_t)+sizeof(uint16_t)+len);
    assert(data != NULL);
    memcpy(data+sizeof(void *), remote_address, sizeof(bt_addr_t));
    *(uint16_t *)((uint32_t)data+sizeof(void *)+sizeof(bt_addr_t)) = len;
    memcpy(data+sizeof(void *)+sizeof(bt_addr_t)+sizeof(uint16_t), buf, len);
    k_fifo_put(&epio_bt_rx_fifo, data);
    air_daemon_wq_work_submit(&epio_custom_protocol_bt_rx_work);

    LOG_INF("[epio_custom_protocol] epio_bt_hid_recv_data len = %d.", len);

    return ret;
}

#if defined(AIR_PURE_GAMING_CUSTOM_PROTOCOL_HID_MIXING_ENABLE)
int epio_bt_hid_send_data_mix_with_hid_packet(bt_addr_t *remote_address, uint16_t len, uint8_t *buf)
{
    int err;

    if ((len != EPIO_CUSTOM_PROTOCOL_MIX_WITH_HID_PACKET_SIZE) || (buf == NULL))
    {
        err = -EINVAL;
    }
    else
    {
        /* push data into data queue for HID data path processing */
        T_ACL_PKT_BUFFER_S acl_pkt_payload ;
        acl_pkt_payload.data =  *((uint32_t *)buf);
        hid_common_set_hid_para(RAPA_TYPE_ACL_RESPONSE_VIA_HID_REPORT, (uint8_t*)&acl_pkt_payload, sizeof(acl_pkt_payload));
        err = 0;
    }

    if (err)
    {
        LOG_INF("[epio_custom_protocol] epio_bt_hid_send_data_mix_with_hid_packet tx to device fail.", err);
    }
    else
    {
        LOG_INF("[epio_custom_protocol] epio_bt_hid_send_data_mix_with_hid_packet len = %d tx to device done.", len);
    }

    return err;
}

int epio_bt_hid_recv_data_mix_with_hid_packet(bt_addr_t *remote_address, uint16_t len, uint8_t *buf)
{
    int ret = 0;

    assert(len == EPIO_CUSTOM_PROTOCOL_MIX_WITH_HID_PACKET_SIZE);
    uint8_t *data = k_malloc(sizeof(void *)+sizeof(bt_addr_t)+sizeof(uint16_t)+len);
    assert(data != NULL);
    memcpy(data+sizeof(void *), remote_address, sizeof(bt_addr_t));
    *(uint16_t *)((uint32_t)data+sizeof(void *)+sizeof(bt_addr_t)) = len;
    memcpy(data+sizeof(void *)+sizeof(bt_addr_t)+sizeof(uint16_t), buf, len);
    k_fifo_put(&epio_bt_rx_fifo, data);
    air_daemon_wq_work_submit(&epio_custom_protocol_bt_rx_work);

    LOG_INF("[epio_custom_protocol] epio_bt_hid_recv_data_mix_with_hid_packet len = %d.", len);

    return ret;
}
#endif /* AIR_PURE_GAMING_CUSTOM_PROTOCOL_HID_MIXING_ENABLE */

const struct device *epio_custom_protocol_get_interrupt_transfer_usb_device(void)
{
    return epio_usb_interrupt_hiddev;
}

const struct device *epio_custom_protocol_get_control_transfer_usb_device(void)
{
    return epio_usb_control_hiddev;
}

void epio_custom_protocol_register_callback(epio_process_callback_t *callback)
{
    epio_process_callback.usb_recv_data_callback    = callback->usb_recv_data_callback;
    epio_process_callback.bt_recv_data_callback     = callback->bt_recv_data_callback;

    LOG_INF("[epio_custom_protocol] epio_custom_protocol_register_callbacks done, usb_recv_data_callback = 0x%x, bt_recv_data_callback =0x%x.",
            epio_process_callback.usb_recv_data_callback,
            epio_process_callback.bt_recv_data_callback);
}

void epio_custom_protocol_enable(epio_custom_protocol_path path)
{
    switch (path)
    {
        case EPIO_CUSTOM_PROTOCOL_USB:
#ifdef AIR_PURE_GAMING_CUSTOM_PROTOCOL_USB_REPORT_MODE
            epio_usb_control_hiddev = air_usb_hid_find_first_device_by_report(AIR_USB_REPORT_DESC_CUSTOM);
            air_usb_hid_register_set_report_cb(
                epio_user_control_id, epio_usb_control_hiddev, USB_HID_REPORT_TYPE_OUTPUT, AIR_USB_HID_CUSTOM_SET_REPORT_ID,
                AIR_USB_HID_CUSTOM_SET_REPORT_LEN, epio_usb_hid_set_report_cb);
            air_usb_hid_register_get_report_cb(
                epio_user_control_id, epio_usb_control_hiddev, USB_HID_REPORT_TYPE_INPUT, AIR_USB_HID_CUSTOM_GET_REPORT_ID,
                AIR_USB_HID_CUSTOM_GET_REPORT_LEN, epio_usb_hid_get_report_cb);
            LOG_INF("[epio_custom_protocol] epio_custom_protocol_enable set/get report dev = 0x%x.", epio_usb_control_hiddev);
#endif /* AIR_PURE_GAMING_CUSTOM_PROTOCOL_USB_REPORT_MODE */

#ifdef AIR_PURE_GAMING_CUSTOM_PROTOCOL_USB_INTERRUPT_MODE
            epio_usb_interrupt_hiddev = air_usb_hid_find_first_device_by_report(AIR_USB_REPORT_DESC_EPIO);
            air_usb_hid_register_output_cb(epio_user_interrupt_id, epio_usb_interrupt_hiddev,
                                            USB_HID_REPORT_TYPE_OUTPUT, AIR_USB_HID_EPIO_RX_REPORT_ID, AIR_USB_HID_EPIO_RX_REPORT_LEN, epio_usb_hid_rx_cb);
            LOG_INF("[epio_custom_protocol] epio_custom_protocol_enable in/out report dev = 0x%x.", epio_usb_interrupt_hiddev);
#endif /* AIR_PURE_GAMING_CUSTOM_PROTOCOL_USB_INTERRUPT_MODE */
            break;

        case EPIO_CUSTOM_PROTOCOL_BT:
            LOG_INF("[epio_custom_protocol] epio_custom_protocol_enable bt.");
            break;

        default:
            break;
    }
}

void epio_custom_protocol_disable(epio_custom_protocol_path path)
{
    switch (path)
    {
        case EPIO_CUSTOM_PROTOCOL_USB:
#ifdef AIR_PURE_GAMING_CUSTOM_PROTOCOL_USB_REPORT_MODE
            epio_usb_control_hiddev = air_usb_hid_find_first_device_by_report(AIR_USB_REPORT_DESC_CUSTOM);
            air_usb_hid_register_set_report_cb(
                epio_user_control_id, epio_usb_control_hiddev, USB_HID_REPORT_TYPE_OUTPUT, AIR_USB_HID_CUSTOM_SET_REPORT_ID,
                AIR_USB_HID_CUSTOM_SET_REPORT_LEN, NULL);
            air_usb_hid_register_get_report_cb(
                epio_user_control_id, epio_usb_control_hiddev, USB_HID_REPORT_TYPE_INPUT, AIR_USB_HID_CUSTOM_GET_REPORT_ID,
                AIR_USB_HID_CUSTOM_GET_REPORT_LEN, NULL);
            LOG_INF("[epio_custom_protocol] epio_custom_protocol_disable set/get report dev = 0x%x.", epio_usb_control_hiddev);
#endif /* AIR_PURE_GAMING_CUSTOM_PROTOCOL_USB_REPORT_MODE */

#ifdef AIR_PURE_GAMING_CUSTOM_PROTOCOL_USB_INTERRUPT_MODE
            epio_usb_interrupt_hiddev = air_usb_hid_find_first_device_by_report(AIR_USB_REPORT_DESC_EPIO);
            air_usb_hid_register_output_cb(epio_user_interrupt_id, epio_usb_interrupt_hiddev,
                                            USB_HID_REPORT_TYPE_OUTPUT, AIR_USB_HID_EPIO_RX_REPORT_ID, AIR_USB_HID_EPIO_RX_REPORT_LEN, NULL);
            LOG_INF("[epio_custom_protocol] epio_custom_protocol_disable in/out report dev = 0x%x.", epio_usb_interrupt_hiddev);
#endif /* AIR_PURE_GAMING_CUSTOM_PROTOCOL_USB_INTERRUPT_MODE */
            break;

        case EPIO_CUSTOM_PROTOCOL_BT:
            LOG_INF("[epio_custom_protocol] epio_custom_protocol_disable bt.");
            break;

        default:
            break;
    }
}

void epio_custom_protocol_init(void)
{
    k_fifo_init(&epio_usb_rx_fifo);
    k_fifo_init(&epio_bt_rx_fifo);
#ifdef AIR_PURE_GAMING_CUSTOM_PROTOCOL_USB_REPORT_MODE
    k_fifo_init(&epio_usb_tx_fifo);
#endif /* AIR_PURE_GAMING_CUSTOM_PROTOCOL_USB_REPORT_MODE */

#ifdef AIR_PURE_GAMING_CUSTOM_PROTOCOL_USB_REPORT_MODE
    air_usb_create_user("HID_EPIO_CONTROL", &epio_user_control_id);
#endif /* AIR_PURE_GAMING_CUSTOM_PROTOCOL_USB_REPORT_MODE */

#ifdef AIR_PURE_GAMING_CUSTOM_PROTOCOL_USB_INTERRUPT_MODE
    air_usb_create_user("HID_EPIO_INTERRUPT", &epio_user_interrupt_id);
#endif /* AIR_PURE_GAMING_CUSTOM_PROTOCOL_USB_INTERRUPT_MODE */

    epio_process_callback.usb_recv_data_callback    = NULL;
    epio_process_callback.bt_recv_data_callback     = NULL;

    LOG_INF("[epio_custom_protocol] epio_custom_protocol_init done, id = 0x%x 0x%x.", epio_user_control_id, epio_user_interrupt_id);
}

void epio_custom_protocol_deinit(void)
{

    epio_process_callback.usb_recv_data_callback    = NULL;
    epio_process_callback.bt_recv_data_callback     = NULL;

    LOG_INF("[epio_custom_protocol] epio_custom_protocol_deinit done.");
}

#endif /* AIR_PURE_GAMING_CUSTOM_PROTOCOL_ENABLE */
