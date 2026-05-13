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


#if defined(AIR_MUX_ENABLE) && defined(AIR_USB_ENABLE)

#include "mux.h"
#include "mux_port_device.h"
#include "mux_port.h"

#include "air_usb.h"
#include "air_usb_hid.h"

/* Logging Config */
#if defined(CONFIG_LOG)
#include <zephyr/logging/log.h>
// #define LOG_LEVEL LOG_LEVEL_ERR
#define LOG_LEVEL CONFIG_USB_DRIVER_LOG_LEVEL
LOG_MODULE_REGISTER(mux_usb);
#else
/* Temp logging method, backup for no log module environment. */
#include <zephyr/logging/log.h>
#include <zephyr/sys/printk.h>
#define file_tag  "mux_usb"
// #define LOG_LEVEL LOG_LEVEL_NONE
// #define LOG_LEVEL LOG_LEVEL_ERR
// #define LOG_LEVEL LOG_LEVEL_WRN
// #define LOG_LEVEL LOG_LEVEL_INF
#define LOG_LEVEL LOG_LEVEL_DBG
#undef LOG_ERR
#undef LOG_WRN
#undef LOG_INF
#undef LOG_DBG
#define LOG_ERR(...)                                                                               \
    do {                                                                                           \
        if (LOG_LEVEL >= LOG_LEVEL_ERR) {                                                          \
            printk("<err> " file_tag ": %s: ", __func__);                                          \
            printk(__VA_ARGS__);                                                                   \
            printk("\r\n");                                                                        \
        }                                                                                          \
    } while (0)
#define LOG_WRN(...)                                                                               \
    do {                                                                                           \
        if (LOG_LEVEL >= LOG_LEVEL_WRN) {                                                          \
            printk("<wrn> " file_tag ": %s: ", __func__);                                          \
            printk(__VA_ARGS__);                                                                   \
            printk("\r\n");                                                                        \
        }                                                                                          \
    } while (0)
#define LOG_INF(...)                                                                               \
    do {                                                                                           \
        if (LOG_LEVEL >= LOG_LEVEL_INF) {                                                          \
            printk("<inf> " file_tag ": %s: ", __func__);                                          \
            printk(__VA_ARGS__);                                                                   \
            printk("\r\n");                                                                        \
        }                                                                                          \
    } while (0)
#define LOG_DBG(...)                                                                               \
    do {                                                                                           \
        if (LOG_LEVEL >= LOG_LEVEL_DBG) {                                                          \
            printk("<dbg> " file_tag ": %s: ", __func__);                                          \
            printk(__VA_ARGS__);                                                                   \
            printk("\r\n");                                                                        \
        }                                                                                          \
    } while (0)
#endif

/******************************************************************************
 * MUX port macro redirect
 *****************************************************************************/
#define MUX_USB_PORT_HID_1 0
#define MUX_USB_PORT_HID_2 1
#define MUX_USB_PORT_HID_3 2
#define MUX_USB_PORT_CDC_1 3
#define MUX_USB_PORT_CDC_2 4

#define MUX_USB_PORT_HID_NUM 3
// #define MUX_USB_PORT_HID_NUM (MUX_USB_END - MUX_USB_BEGIN + 1)
#define MUX_USB_PORT_CDC_NUM 2

#define USB_PORT_INDEX_TO_MUX_PORT(port_index) (port_index + MUX_USB_COM_1)

static inline uint32_t to_mux_port(uint8_t port_index)
{
    if (port_index == MUX_USB_PORT_HID_1) {
        return MUX_USB_COM_1;
    }
    if (port_index == MUX_USB_PORT_HID_2) {
        return MUX_USB_COM_2;
    }
    if (port_index == MUX_USB_PORT_HID_3) {
        return MUX_PORT_END;
    }
    if (port_index == MUX_USB_PORT_CDC_1) {
        return MUX_PORT_END;
    }
    if (port_index == MUX_USB_PORT_CDC_2) {
        return MUX_PORT_END;
    }
    return MUX_PORT_END;
}

/******************************************************************************
 * Static Variables
 *****************************************************************************/
static mux_irq_handler_t mux_usb_irq_handler = NULL;
static uint32_t mux_usb_user_id = 0;

#ifdef AIR_USB_HID_ENABLE
static virtual_read_write_point_t mux_usb_hid_vrwp[MUX_USB_PORT_HID_NUM] __unused;
static uint8_t mux_usb_hid_data_flag = 0;
#endif

/******************************************************************************
 * Virtual Read Write Point APIs
 *****************************************************************************/
static bool vrwp_is_full(virtual_read_write_point_t *vrwp, bool is_rx)
{
    if (vrwp == NULL) {
        return true;
    }
    return mux_common_device_buf_is_full(vrwp, is_rx);
}

static uint32_t vrwp_get_rx_available_size(virtual_read_write_point_t *vrwp)
{
    if (vrwp == NULL) {
        return 0;
    }
    return vrwp->rx_buff_end - vrwp->rx_buff_start - vrwp->rx_buff_available_len;
}

static uint32_t vrwp_get_tx_available_size(virtual_read_write_point_t *vrwp)
{
    if (vrwp == NULL) {
        return 0;
    }
    return vrwp->tx_buff_available_len;
}

static void vrwp_get_rx_clear_buf(virtual_read_write_point_t *vrwp)
{
    vrwp->rx_buff_available_len = 0;
    vrwp->rx_buff_read_point = vrwp->rx_buff_start;
    vrwp->rx_buff_write_point = vrwp->rx_buff_start;
}

static void vrwp_get_tx_clear_buf(virtual_read_write_point_t *vrwp)
{
    vrwp->tx_buff_available_len = 0;
    vrwp->tx_buff_read_point = vrwp->tx_buff_start;
    vrwp->tx_buff_write_point = vrwp->rx_buff_start;
}

/* Copy data to rx buffer in virtual read write point */
static uint32_t vrwp_rx_cpy(virtual_read_write_point_t *vrwp, const uint8_t *data, uint32_t len)
{
    uint32_t mask_irq = 0;

    if (vrwp == NULL) {
        return 0;
    }
    if (len > vrwp_get_rx_available_size(vrwp)) {
        /* If rx buff is not enough, do nothing*/
        LOG_ERR("[MUX_USB] rx buff is full");
        return 0;
    }
    if (len == 0) {
        /* If data length is zero, do nothing*/
        return 0;
    }

    /* NOTE: RX buf use mux_common_device_get_buf_next_free_block_len */
    hal_nvic_save_and_set_interrupt_mask(&mask_irq);
    uint32_t next_block_len = mux_common_device_get_buf_next_free_block_len(
        vrwp->rx_buff_start, vrwp->rx_buff_read_point, vrwp->rx_buff_write_point, vrwp->rx_buff_end,
        vrwp->rx_buff_available_len);
    hal_nvic_restore_interrupt_mask(mask_irq);

    if (len > next_block_len) {
        memcpy((void *)(vrwp->rx_buff_write_point), data, next_block_len);
        memcpy((void *)(vrwp->rx_buff_start), data + next_block_len, len - next_block_len);
    } else {
        memcpy((void *)(vrwp->rx_buff_write_point), data, len);
    }

    hal_nvic_save_and_set_interrupt_mask(&mask_irq);
    mux_common_device_set_rx_hw_wptr_internal_use(vrwp, len);
    hal_nvic_restore_interrupt_mask(mask_irq);

    return len;
}

/* Copy data from tx buffer in virtual read write point */
static uint32_t vrwp_tx_cpy(virtual_read_write_point_t *vrwp, uint8_t *data, uint32_t len)
{
    uint32_t mask_irq = 0;

    if (vrwp == NULL) {
        return 0;
    }
    if (len > vrwp_get_tx_available_size(vrwp)) {
        /* If tx buff is not enough, do nothing*/
        return 0;
    }
    if (len == 0) {
        /* If data length is zero, do nothing*/
        return 0;
    }

    /* NOTE: TX buf use mux_common_device_get_buf_next_available_block_len */
    hal_nvic_save_and_set_interrupt_mask(&mask_irq);
    uint32_t next_block_len = mux_common_device_get_buf_next_available_block_len(
        vrwp->tx_buff_start, vrwp->tx_buff_read_point, vrwp->tx_buff_write_point, vrwp->tx_buff_end,
        vrwp->tx_buff_available_len);
    hal_nvic_restore_interrupt_mask(mask_irq);

    if (len > next_block_len) {
        memcpy(data, (void *)(vrwp->tx_buff_read_point), next_block_len);
        memcpy(data + next_block_len, (void *)(vrwp->tx_buff_start), len - next_block_len);
    } else {
        memcpy(data, (void *)(vrwp->tx_buff_read_point), len);
    }

    hal_nvic_save_and_set_interrupt_mask(&mask_irq);
    mux_common_device_set_tx_hw_rptr_internal_use(vrwp, len);
    hal_nvic_restore_interrupt_mask(mask_irq);

    return len;
}

static uint32_t vrwp_get_hw_rptr(virtual_read_write_point_t *vrwp, bool is_rx)
{
    if (vrwp == NULL) {
        return 0;
    }
    return mux_common_device_get_hw_rptr(vrwp, is_rx);
}

static uint32_t vrwp_get_hw_wptr(virtual_read_write_point_t *vrwp, bool is_rx)
{
    if (vrwp == NULL) {
        return 0;
    }
    return mux_common_device_get_hw_wptr(vrwp, is_rx);
}

static void vrwp_set_rx_hw_rptr(virtual_read_write_point_t *vrwp, uint32_t move_bytes)
{
    // uint32_t empty_size;

    if (vrwp == NULL) {
        return;
    }

    if (move_bytes == 0) {
        return;
    }

    // empty_size = vrwp->rx_buff_len - vrwp->rx_buff_available_len;
    // if (empty_size < move_bytes) {
    //     return;
    // }

    mux_common_device_set_rx_hw_rptr(vrwp, move_bytes);
}

static void vrwp_set_tx_hw_wptr(virtual_read_write_point_t *vrwp, uint32_t move_bytes)
{
    uint32_t empty_size;

    if (vrwp == NULL) {
        return;
    }

    if (move_bytes == 0) {
        return;
    }

    empty_size = vrwp->tx_buff_len - vrwp->tx_buff_available_len;
    if (empty_size < move_bytes) {
        return;
    }

    mux_common_device_set_tx_hw_wptr(vrwp, move_bytes);
}

/******************************************************************************
 * Common APIs
 *****************************************************************************/
static virtual_read_write_point_t *mux_usb_get_vrwp_ctx(uint8_t port_index)
{
    virtual_read_write_point_t *vrwp = NULL;
    if (port_index >= MUX_USB_PORT_HID_1 && port_index <= MUX_USB_PORT_HID_3) {
#ifdef AIR_USB_HID_ENABLE
        vrwp = &mux_usb_hid_vrwp[port_index - MUX_USB_PORT_HID_1];
#else
        vrwp = NULL;
#endif
    } else if (port_index >= MUX_USB_PORT_CDC_1 && port_index <= MUX_USB_PORT_CDC_2) {
#ifdef AIR_USB_CDC_ENABLE
        vrwp = &mux_usb_cdc_vrwp[port_index - MUX_USB_PORT_CDC_1];
#else
        vrwp = NULL;
#endif
    }

    return vrwp;
}

typedef enum {
    MUX_USB_TYPE_HID,
    MUX_USB_TYPE_CDC,
    MUX_USB_TYPE_UNKNOWN,
} mux_usb_type_t;

static mux_usb_type_t mux_usb_get_port_type(uint8_t port_index)
{
    if (port_index >= MUX_USB_PORT_HID_1 && port_index <= MUX_USB_PORT_HID_3) {
        return MUX_USB_TYPE_HID;
    } else if (port_index >= MUX_USB_PORT_CDC_1 && port_index <= MUX_USB_PORT_CDC_2) {
        return MUX_USB_TYPE_CDC;
    }
    return MUX_USB_TYPE_UNKNOWN;
}

static void mux_usb_send_event(uint8_t port_index, mux_event_t event, void *user_data)
{
    if (mux_usb_irq_handler) {
        mux_usb_irq_handler(to_mux_port(port_index), event, user_data);
    }
}

/******************************************************************************
 * HID APIs
 *****************************************************************************/
#ifdef AIR_USB_HID_ENABLE

#define AIR_USB_HID_AIR_REPORT_DATA_LEN 0x3B
// static uint8_t hid_2_tx_buf[AIR_USB_HID_REPORT_MUX_LEN];
// static uint8_t hid_2_rx_buf[AIR_USB_HID_REPORT_MUX_LEN];

#define TARGET_LOCAL_DEVICE        0x00
#define TARGET_REMOTE_DEVICE       0x80
#define TARGET_REMOTE_MULTIDEVICE1 0x81
#define TARGET_REMOTE_MULTIDEVICE2 0x82
#define TARGET_REMOTE_MULTIDEVICE3 0x83
#define TARGET_REMOTE_MULTIDEVICE4 0x84
#define TARGET_EXTERNAL_DEVICE     0x90
#define TARGET_INVALID_DEVICE      0xFF

uint8_t usb_mux_get_data_flag(void)
{
    return mux_usb_hid_data_flag;
}

uint8_t usb_mux_set_data_flag(uint8_t flag)
{
    if (flag == TARGET_LOCAL_DEVICE || flag == TARGET_REMOTE_DEVICE ||
        flag == TARGET_REMOTE_MULTIDEVICE1 || flag == TARGET_REMOTE_MULTIDEVICE2 ||
        flag == TARGET_REMOTE_MULTIDEVICE3 || flag == TARGET_REMOTE_MULTIDEVICE4 ||
        flag == TARGET_EXTERNAL_DEVICE) {
        mux_usb_hid_data_flag = flag;
        return flag;
    }

    return TARGET_INVALID_DEVICE;
}

static int mux_usb_hid_get_report_cb(const struct device *dev, uint8_t type, uint8_t id,
                                     uint16_t len, uint8_t *buf)
{
    virtual_read_write_point_t *vrwp;
    uint32_t tx_ava_size;
    uint32_t tx_size = 0;
    uint32_t tx_target = 0;
    uint32_t zero_len = 0;
    uint32_t port_index;

    if ((id == AIR_USB_HID_AIR_IN_REPORT_ID && len == AIR_USB_HID_AIR_IN_REPORT_LEN) || (id == AIR_USB_HID_FEATURE_REPORT_ID && len == AIR_USB_HID_FEATURE_REPORT_LEN)) {
        port_index = MUX_USB_PORT_HID_2;
        vrwp = mux_usb_get_vrwp_ctx(MUX_USB_PORT_HID_2);
        tx_ava_size = vrwp_get_tx_available_size(vrwp);
        // tx_ava_size = vrwp->tx_buff_len - vrwp->tx_buff_available_len;

        if (tx_ava_size > AIR_USB_HID_AIR_REPORT_DATA_LEN) {
            tx_size = AIR_USB_HID_AIR_REPORT_DATA_LEN;
            zero_len = 0;
        } else if (tx_ava_size > 0) {
            tx_size = tx_ava_size;
            zero_len = AIR_USB_HID_AIR_REPORT_DATA_LEN - tx_ava_size;
        } else {
            tx_size = 0;
	    zero_len = AIR_USB_HID_AIR_REPORT_DATA_LEN;
	}

        tx_target = usb_mux_get_data_flag();
        buf[0] = id;
        buf[1] = tx_size;
        buf[2] = tx_target; /*Target */

#if 0
        if (tx_size > 0) {
            printk("[MUX_USB] tx_size:%d, zero_len:%d, tx_target:%d, tx_ava_size:%d", tx_size, zero_len,
                    tx_target, tx_ava_size);
            printk("[MUX_USB] tx_s:%p, tx_e:%p, tx_ava_size:%d, twp:%p", (void *)vrwp->tx_buff_start,
                    (void *)vrwp->tx_buff_end, vrwp->tx_buff_available_len,
                    (void *)vrwp->tx_buff_read_point);
            printk("[MUX_USB] tx_size: %d, data: ", tx_size);
            for (int i = 0; i < tx_size + 3; i++) {
                printk("%02X ", buf[3 + i]);
            }
            printk("\r\n");
        }
#endif

        vrwp_tx_cpy(vrwp, &buf[3], tx_size);
        /* Append zero to the end of report */
        memset(&buf[3] + tx_size, 0, zero_len);

        mux_usb_send_event(port_index, MUX_EVENT_READY_TO_WRITE, NULL);
    }

    return 0;
}

static int mux_usb_hid_set_report_cb(const struct device *dev, uint8_t type, uint8_t id,
                                     uint16_t len, const uint8_t *buf)
{
    virtual_read_write_point_t *vrwp;
    uint32_t rx_ava_size;
    uint32_t rx_size = 0;
    uint32_t rx_target;
    uint32_t port_index;

    if ((id == AIR_USB_HID_AIR_OUT_REPORT_ID && len == AIR_USB_HID_AIR_OUT_REPORT_LEN) || (id == AIR_USB_HID_FEATURE_REPORT_ID && len == AIR_USB_HID_FEATURE_REPORT_LEN)) {
        port_index = MUX_USB_PORT_HID_2;

        if ((buf[0] != AIR_USB_HID_AIR_OUT_REPORT_ID) && (buf[0] != AIR_USB_HID_FEATURE_REPORT_ID)) {
            /* Report ID not match, drop this packet */
            return 0;
        }

        vrwp = mux_usb_get_vrwp_ctx(MUX_USB_PORT_HID_2);

        rx_size = buf[1];
        rx_target = buf[2];
        usb_mux_set_data_flag(rx_target);

        rx_ava_size = vrwp_get_rx_available_size(vrwp);

#if 0
        if (rx_size > 0) {
            printk("[MUX_USB] rx_size:%d, rx_target:%d, rx_ava_size:%d", rx_size, rx_target, rx_ava_size);
            printk("[MUX_USB] rx_s:0x%08X, rx_e:0x%08X, rx_ava_size:%d, rwp:0x%08X", (uint32_t)vrwp->rx_buff_start,
                    (uint32_t)vrwp->rx_buff_end, vrwp->rx_buff_available_len,
                    (uint32_t)vrwp->rx_buff_write_point);
            printk("[MUX_USB] rx_size: %d, data: ", rx_size);
            for (int i = 0; i < rx_size + 3; i++) {
                printk("%02X ", buf[3 + i]);
            }
            printk("\r\n");
        }
#endif

        if (rx_size > rx_ava_size) {
            /* Buffer size is not enough, drop this packet */
        } else if (rx_size > 0) {
            vrwp_rx_cpy(vrwp, &buf[3], rx_size);
            mux_usb_send_event(port_index, MUX_EVENT_READY_TO_READ, NULL);
        }
    }

    return 0;
}

#endif

/******************************************************************************
 * CDC APIs
 *****************************************************************************/
#ifdef AIR_USB_CDC_ENABLE
static virtual_read_write_point_t mux_usb_cdc_vrwp[MUX_USB_PORT_CDC_NUM];
#endif

/******************************************************************************
 * HID MUX operation APIs
 *****************************************************************************/
static void mux_usb_evt_cb(air_usb_evt_t evt, const uint8_t *param)
{
    struct device *hiddev = NULL;
    switch (evt) {
    case AIR_USB_EVT_CONNECTED:
        hiddev = air_usb_hid_find_first_device_by_report(AIR_USB_REPORT_DESC_MUX);
        air_usb_hid_register_set_report_cb(
            mux_usb_user_id, hiddev, USB_HID_REPORT_TYPE_OUTPUT, AIR_USB_HID_AIR_OUT_REPORT_ID,
            AIR_USB_HID_AIR_OUT_REPORT_LEN, mux_usb_hid_set_report_cb);
        air_usb_hid_register_get_report_cb(
            mux_usb_user_id, hiddev, USB_HID_REPORT_TYPE_INPUT, AIR_USB_HID_AIR_IN_REPORT_ID,
            AIR_USB_HID_AIR_IN_REPORT_LEN, mux_usb_hid_get_report_cb);
        air_usb_hid_register_set_report_cb(
            mux_usb_user_id, hiddev, USB_HID_REPORT_TYPE_FEATURE, AIR_USB_HID_FEATURE_REPORT_ID,
            AIR_USB_HID_FEATURE_REPORT_LEN, mux_usb_hid_set_report_cb);
        air_usb_hid_register_get_report_cb(
            mux_usb_user_id, hiddev, USB_HID_REPORT_TYPE_FEATURE, AIR_USB_HID_FEATURE_REPORT_ID,
            AIR_USB_HID_FEATURE_REPORT_LEN, mux_usb_hid_get_report_cb);
        break;
    case AIR_USB_EVT_DISCONNECTED:
        hiddev = air_usb_hid_find_first_device_by_report(AIR_USB_REPORT_DESC_MUX);
        air_usb_hid_register_set_report_cb(mux_usb_user_id, hiddev, USB_HID_REPORT_TYPE_OUTPUT,
                                           AIR_USB_HID_AIR_OUT_REPORT_ID,
                                           AIR_USB_HID_AIR_OUT_REPORT_LEN, NULL);
        air_usb_hid_register_get_report_cb(mux_usb_user_id, hiddev, USB_HID_REPORT_TYPE_INPUT,
                                           AIR_USB_HID_AIR_IN_REPORT_ID,
                                           AIR_USB_HID_AIR_IN_REPORT_LEN, NULL);
        air_usb_hid_register_set_report_cb(
            mux_usb_user_id, hiddev, USB_HID_REPORT_TYPE_FEATURE, AIR_USB_HID_FEATURE_REPORT_ID,
            AIR_USB_HID_FEATURE_REPORT_LEN, NULL);
        air_usb_hid_register_get_report_cb(
            mux_usb_user_id, hiddev, USB_HID_REPORT_TYPE_FEATURE, AIR_USB_HID_FEATURE_REPORT_ID,
            AIR_USB_HID_FEATURE_REPORT_LEN, NULL);
        break;
    default:
        LOG_DBG("status %u unhandled", evt);
        break;
    }
}

static mux_status_t mux_usb_hid_init(uint8_t port_index, mux_port_config_t *p_setting,
                                     mux_irq_handler_t irq_handler)
{
    virtual_read_write_point_t *vrwp = NULL;
    vrwp = mux_usb_get_vrwp_ctx(port_index);

    LOG_INF("mux_usb_hid_init port:%d", port_index);

    if (vrwp && p_setting) {
        mux_common_device_r_w_point_init(vrwp, p_setting);
        mux_driver_debug_for_check(vrwp);
    } else {
        return MUX_STATUS_ERROR;
    }

    if (port_index == MUX_USB_PORT_HID_1) {
        return MUX_STATUS_OK;
    }
    if (port_index == MUX_USB_PORT_HID_2) {
#if 0
        /* TODO: remove it, now it's done in connect cb */
        struct device *hiddev = NULL;
        hiddev = air_usb_hid_find_first_device_by_report(AIR_USB_REPORT_DESC_MUX);
        /* TODO: LOG no mux report is list in usb device */
        air_usb_hid_register_set_report_cb(
            mux_usb_user_id, hiddev, USB_HID_REPORT_TYPE_OUTPUT, AIR_USB_HID_AIR_OUT_REPORT_ID,
            AIR_USB_HID_AIR_OUT_REPORT_LEN, mux_usb_hid_set_report_cb);
        air_usb_hid_register_get_report_cb(
            mux_usb_user_id, hiddev, USB_HID_REPORT_TYPE_INPUT, AIR_USB_HID_AIR_IN_REPORT_ID,
            AIR_USB_HID_AIR_IN_REPORT_LEN, mux_usb_hid_get_report_cb);
#endif
        return MUX_STATUS_OK;
    }
    if (port_index == MUX_USB_PORT_HID_3) {
        return MUX_STATUS_OK;
    }

    return MUX_STATUS_ERROR;
}

static mux_status_t mux_usb_hid_control(uint8_t port_index, mux_ctrl_cmd_t command,
                                        mux_ctrl_para_t *para)
{
    virtual_read_write_point_t *vrwp = NULL;
    vrwp = mux_usb_get_vrwp_ctx(port_index);

    if (vrwp == NULL) {
        LOG_INF("vrwp[NULL], port[%d], command[%d]", port_index, command);
        return MUX_STATUS_ERROR;
    }

    switch (command) {
    case MUX_CMD_CLEAN: {
        vrwp_get_rx_clear_buf(vrwp);
        vrwp_get_tx_clear_buf(vrwp);
        return MUX_STATUS_OK;
    }
    case MUX_CMD_CLEAN_RX_VIRUTUAL: {
        vrwp_get_rx_clear_buf(vrwp);
        return MUX_STATUS_OK;
    }
    case MUX_CMD_CLEAN_TX_VIRUTUAL: {
        vrwp_get_tx_clear_buf(vrwp);
        return MUX_STATUS_OK;
    }
    default: {
        break;
    }
    }
    return MUX_STATUS_ERROR;
}

/******************************************************************************
 * MUX operation interface
 *****************************************************************************/

mux_status_t port_mux_usb_normal_init(uint8_t port_index, mux_port_config_t *p_setting,
                                      mux_irq_handler_t irq_handler)
{
    mux_usb_irq_handler = irq_handler;
    if (mux_usb_user_id == 0) {
        air_usb_create_user("MUX_USB", &mux_usb_user_id);
        air_usb_register_evt_cb(mux_usb_user_id, mux_usb_evt_cb);
    }

    if (mux_usb_get_port_type(port_index) == MUX_USB_TYPE_HID) {
        return mux_usb_hid_init(port_index, p_setting, irq_handler);
    } else if (mux_usb_get_port_type(port_index) == MUX_USB_TYPE_CDC) {
        /* Not avaiable */
        return MUX_STATUS_ERROR;
    }

    return MUX_STATUS_OK;
}

mux_status_t port_mux_usb_deinit(uint8_t port_index)
{
    /* 1. Close serial port */
    /* 2. De-register cb to usb airoha subsys */
    if (mux_usb_get_port_type(port_index) == MUX_USB_TYPE_HID) {
        return MUX_STATUS_OK;
    } else if (mux_usb_get_port_type(port_index) == MUX_USB_TYPE_CDC) {
        /* Not avaiable */
        return MUX_STATUS_ERROR;
    }
    return MUX_STATUS_OK;
}

void port_mux_usb_exception_init(uint8_t port_index)
{
    //     PORT_MUX_UNUSED(port_index);
}

void port_mux_usb_exception_send(uint8_t port_index, uint8_t *buffer, uint32_t size)
{
    //     usb_mux_dump_data(port_index, buffer, size);
}

bool port_mux_usb_buf_is_full(uint8_t port_index, bool is_rx)
{
    virtual_read_write_point_t *vrwp = mux_usb_get_vrwp_ctx(port_index);
    return vrwp_is_full(vrwp, is_rx);
}

uint32_t port_mux_usb_get_hw_rptr(uint8_t port_index, bool is_rx)
{
    virtual_read_write_point_t *vrwp = mux_usb_get_vrwp_ctx(port_index);
    return vrwp_get_hw_rptr(vrwp, is_rx);
}

uint32_t port_mux_usb_get_hw_wptr(uint8_t port_index, bool is_rx)
{
    virtual_read_write_point_t *vrwp = mux_usb_get_vrwp_ctx(port_index);
    return vrwp_get_hw_wptr(vrwp, is_rx);
}

void port_mux_usb_set_rx_hw_rptr(uint8_t port_index, uint32_t move_bytes)
{
    virtual_read_write_point_t *vrwp = mux_usb_get_vrwp_ctx(port_index);
    return vrwp_set_rx_hw_rptr(vrwp, move_bytes);
}

void port_mux_usb_set_tx_hw_wptr(uint8_t port_index, uint32_t move_bytes)
{
    virtual_read_write_point_t *vrwp = mux_usb_get_vrwp_ctx(port_index);
    return vrwp_set_tx_hw_wptr(vrwp, move_bytes);
    // TODO: if length is not enough, clear it?
}

mux_status_t port_mux_usb_phase1_send(uint8_t port_index)
{
    if (mux_usb_get_port_type(port_index) == MUX_USB_TYPE_HID) {
        return MUX_STATUS_OK;
    } else if (mux_usb_get_port_type(port_index) == MUX_USB_TYPE_CDC) { /* Not avaiable */
        return MUX_STATUS_ERROR;
    }
    return MUX_STATUS_OK;
}

mux_status_t port_mux_usb_phase2_send(uint8_t port_index)
{
    if (mux_usb_get_port_type(port_index) == MUX_USB_TYPE_HID) {
        return MUX_STATUS_OK;
    } else if (mux_usb_get_port_type(port_index) == MUX_USB_TYPE_CDC) {
        /* Not avaiable */
        return MUX_STATUS_ERROR;
    }
    return MUX_STATUS_OK;
}

mux_status_t port_mux_usb_control(uint8_t port_index, mux_ctrl_cmd_t command, mux_ctrl_para_t *para)
{
    if (mux_usb_get_port_type(port_index) == MUX_USB_TYPE_HID) {
        return mux_usb_hid_control(port_index, command, para);
    } else if (mux_usb_get_port_type(port_index) == MUX_USB_TYPE_CDC) {
    }
    return MUX_STATUS_ERROR;
}

port_mux_device_ops_t g_port_mux_usb_ops = {
#ifdef CORE_MCU
    port_mux_usb_normal_init,
    port_mux_usb_deinit,
    port_mux_usb_exception_init,
    port_mux_usb_exception_send,
    port_mux_usb_buf_is_full,
#endif
    port_mux_usb_get_hw_rptr,
    port_mux_usb_set_rx_hw_rptr,
    port_mux_usb_get_hw_wptr,
    port_mux_usb_set_tx_hw_wptr,
    port_mux_usb_phase1_send,
    port_mux_usb_phase2_send,
    port_mux_usb_control,
    NULL,
    NULL,
};

#endif /* defined(AIR_MUX_ENABLE) && defined(AIR_USB_ENABLE) */
