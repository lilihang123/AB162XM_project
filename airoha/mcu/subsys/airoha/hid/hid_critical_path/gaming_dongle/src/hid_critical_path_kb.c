/* Copyright Statement:
*
* (C) 2025 Airoha Technology Corp. All rights reserved.
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

#include "hid_critical_path_kb.h"
#include "hid_critical_path_ms.h"


/*
 * Custom Queue Implementation for Keyboard (kb_queue)
 */

// Error code definitions
#define KB_QUEUE_OK            0
#define KB_QUEUE_ERROR_PARAM   -1
#define KB_QUEUE_ERROR_FULL    -2
#define KB_QUEUE_ERROR_EMPTY   -3
#define KB_QUEUE_ERROR_NO_INIT -4
#define KB_QUEUE_ERROR_LOCKED  -5

// -----------------------------------------------------------------------------
// 1. Data structure design
// -----------------------------------------------------------------------------
typedef struct {
    char *buffer;           // Pointer to external ring buffer
    uint16_t item_size;     // Size of each element
    uint16_t capacity;      // Queue capacity (maximum number of elements)
    uint16_t head;          // Head index (read position)
    uint16_t tail;          // Tail index (write position)
    uint16_t count;         // Current number of elements
    bool is_init;           // Queue initialization status
    volatile bool locked;   // Lock for queue processing
} kb_queue_t;

// -----------------------------------------------------------------------------
// 3. Interface implementation
// -----------------------------------------------------------------------------

/**
 * @brief Initialize the queue
 * @param q Pointer to the queue structure
 * @param buffer Pointer to the external storage buffer
 * @param item_size Size of a single element
 * @param capacity Queue capacity
 * @return 0 on success, negative value on failure
 */
ATTR_TEXT_IN_TCM int32_t kb_queue_init(kb_queue_t *q, char *buffer, uint32_t item_size, uint32_t capacity) {
    if (q == NULL || buffer == NULL || item_size == 0 || capacity == 0) {
        return KB_QUEUE_ERROR_PARAM;
    }
    q->buffer = buffer;
    q->item_size = item_size;
    q->capacity = capacity;
    q->head = 0;
    q->tail = 0;
    q->count = 0;
    q->is_init = true;
    q->locked = false;
    return KB_QUEUE_OK;
}

/**
 * @brief Deinitialize the queue (mark as uninitialized)
 * @param q Pointer to the queue structure
 * @return 0 on success, negative value on failure
 */
ATTR_TEXT_IN_TCM int32_t kb_queue_deinit(kb_queue_t *q) {
    if (q == NULL) {
        return KB_QUEUE_ERROR_PARAM;
    }
    if (q->is_init) {
        q->is_init = false;
        // For safety, pointers can be cleared, but the main logic depends on is_init
        q->buffer = NULL;
        q->count = 0;
        q->head = 0;
        q->tail = 0;
    }
    return KB_QUEUE_OK;
}

/**
 * @brief Reset the queue
 * Only resets indices and count, does not clear buffer content
 * @param q Pointer to the queue structure
 * @return 0 on success, negative value on failure
 */
ATTR_TEXT_IN_TCM int32_t kb_queue_reset(kb_queue_t *q) {
    if (q == NULL) {
        return KB_QUEUE_ERROR_PARAM;
    }

    uint32_t mask;
    hal_nvic_save_and_set_interrupt_mask(&mask);

    if (!q->is_init) {
        hal_nvic_restore_interrupt_mask(mask);
        return KB_QUEUE_ERROR_NO_INIT;
    }

    q->head = 0;
    q->tail = 0;
    q->count = 0;
    q->locked = false;
    // As required: do not clear buffer content (add memset here if needed)

    hal_nvic_restore_interrupt_mask(mask);
    return KB_QUEUE_OK;
}

/**
 * @brief Enqueue operation
 * @param q Pointer to the queue structure
 * @param data Pointer to the data to be written
 * @return 0 on success, negative value on failure
 */
ATTR_TEXT_IN_TCM int32_t kb_queue_put(kb_queue_t *q, const void *data) {
    if (q == NULL || data == NULL) {
        return KB_QUEUE_ERROR_PARAM;
    }

    uint32_t mask;
    hal_nvic_save_and_set_interrupt_mask(&mask);

    if (!q->is_init) {
        hal_nvic_restore_interrupt_mask(mask);
        return KB_QUEUE_ERROR_NO_INIT;
    }

    if (q->count >= q->capacity) {
        hal_nvic_restore_interrupt_mask(mask);
        LOG_ERR(BT_HID_CP_TAG"kb_queue_put: Queue is full");
        return KB_QUEUE_ERROR_FULL;
    }

    // Calculate write position: buffer + (tail * item_size)
    char *target = q->buffer + (q->tail * q->item_size);
    memcpy(target, data, q->item_size);

    q->tail = (q->tail + 1) % q->capacity;
    q->count++;

    hal_nvic_restore_interrupt_mask(mask);
    return KB_QUEUE_OK;
}

/**
 * @brief Dequeue operation
 * @param q Pointer to the queue structure
 * @param data Buffer pointer to store the read data
 * @return 0 on success, negative value on failure
 */
ATTR_TEXT_IN_TCM int32_t kb_queue_get(kb_queue_t *q, void *data) {
    if (q == NULL) {
        return KB_QUEUE_ERROR_PARAM;
    }

    uint32_t mask;
    hal_nvic_save_and_set_interrupt_mask(&mask);

    if (!q->is_init) {
        hal_nvic_restore_interrupt_mask(mask);
        return KB_QUEUE_ERROR_NO_INIT;
    }

    if (q->count == 0) {
        hal_nvic_restore_interrupt_mask(mask);
        LOG_ERR(BT_HID_CP_TAG"kb_queue_get: Queue is empty");
        return KB_QUEUE_ERROR_EMPTY;
    }

    // Calculate read position: buffer + (head * item_size)
    if (data != NULL) {
    char *source = q->buffer + (q->head * q->item_size);
    memcpy(data, source, q->item_size);
    }

    q->head = (q->head + 1) % q->capacity;
    q->count--;
    q->locked = false;

    hal_nvic_restore_interrupt_mask(mask);
    return KB_QUEUE_OK;
}

/**
 * @brief Return the current number of elements in the queue
 * @param q Pointer to the queue structure
 * @return >=0 Current count, <0 Error code
 */
ATTR_TEXT_IN_TCM int32_t kb_queue_item_num(kb_queue_t *q) {
    if (q == NULL) {
        return KB_QUEUE_ERROR_PARAM;
    }

    uint32_t mask;
    hal_nvic_save_and_set_interrupt_mask(&mask);

    if (!q->is_init) {
        hal_nvic_restore_interrupt_mask(mask);
        return KB_QUEUE_ERROR_NO_INIT;
    }

    int32_t count = (int32_t)q->count;

    hal_nvic_restore_interrupt_mask(mask);
    return count;
}

/**
 * @brief Copy head data to external buffer without dequeuing
 * @param q Pointer to the queue structure
 * @param data Buffer pointer to store the data
 * @return 0 on success, negative value on failure
 */
ATTR_TEXT_IN_TCM int32_t kb_queue_peek_head(kb_queue_t *q, void **data) {
    if (q == NULL || data == NULL) {
        return KB_QUEUE_ERROR_PARAM;
    }

    uint32_t mask;
    hal_nvic_save_and_set_interrupt_mask(&mask);

    if (!q->is_init) {
        hal_nvic_restore_interrupt_mask(mask);
        return KB_QUEUE_ERROR_NO_INIT;
    }

    if (q->count == 0) {
        hal_nvic_restore_interrupt_mask(mask);
        return KB_QUEUE_ERROR_EMPTY;
    }

    if (q->locked) {
        hal_nvic_restore_interrupt_mask(mask);
        return KB_QUEUE_ERROR_LOCKED;
    }

    // Calculate read position, but do not move head
    *data = q->buffer + (q->head * q->item_size);

    q->locked = true;

    hal_nvic_restore_interrupt_mask(mask);
    return KB_QUEUE_OK;
}

/**
 * @brief Unlock the queue manually (if peeked but not retrieved)
 * @param q Pointer to the queue structure
 * @return 0 on success
 */
ATTR_TEXT_IN_TCM int32_t kb_queue_unlock(kb_queue_t *q) {
    if (q == NULL) {
        return KB_QUEUE_ERROR_PARAM;
    }

    uint32_t mask;
    hal_nvic_save_and_set_interrupt_mask(&mask);

    if (!q->is_init) {
        hal_nvic_restore_interrupt_mask(mask);
        return KB_QUEUE_ERROR_NO_INIT;
    }

    q->locked = false;

    hal_nvic_restore_interrupt_mask(mask);
    return KB_QUEUE_OK;
}

#if CONFIG_AIR_HID_CP_PROCESS_KBD_DATA_ENABLE
/* kbd fifo definition */
typedef struct {
    void *fifo_reserved;
    uint8_t data[HID_NORMAL_DATA_LEN + 1];
} hid_cp_kbd_fifo_t;

/* kbd queue struct */
typedef struct {
    struct k_fifo fifo;
    /* field for know number of queued data */
    uint32_t num;
} hid_cp_kbd_q_t;
hid_cp_kbd_q_t kbd_q;
#endif

#if CONFIG_AIR_HID_CP_PROCESS_KBD_DATA_ENABLE
/* include hid common header file for keyboard/mouse report SOURCE structure definition */

_Static_assert(sizeof(T_HID_REPORT_KB_STD5_S) == 8, "struct changed");
_Static_assert(sizeof(T_HID_REPORT_KB_CONSUMER2_S) == 8, "struct changed");

/* include this header file for keyboard/mouse report DESTINATION structure definition */
#include "air_usb_hid_desc.h"
_Static_assert(0x1 == AIR_USB_HID_GAMING_KB_REPORT_ID, "report id changed");
_Static_assert(0xC == AIR_USB_HID_CONSUMER_REPORT_ID, "report id changed");
_Static_assert(0x7 == sizeof(air_usb_hid_gaming_kb_report_t), "struct changed");
_Static_assert(0x6 == sizeof(air_usb_hid_consumer_report_t), "struct changed");
#endif

#if CONFIG_AIR_HID_CP_PROCESS_KBD_DATA_ENABLE
static void hid_cp_kbd_prepare_boot_protocol(uint8_t *in, uint8_t *out);
static int hid_cp_kbd_data_send_to_usb(uint8_t* data, uint16_t len, bool is_must);
#endif
#if CONFIG_AIR_HID_CP_PROCESS_NKEY_ENABLE
static void hid_cp_nkey_prepare_boot_protocol(uint8_t *in, uint8_t *out);
static int hid_cp_nkey_data_send_to_usb(uint8_t* data, uint16_t len, bool is_must);
#endif

#if CONFIG_AIR_HID_CP_PROCESS_NKEY_ENABLE
#define NKEY_QUEUE_CAPACITY 20
#define NKEY_QUEUE_ITEM_SIZE sizeof(air_usb_hid_gaming_kb_nkey_report_t)
static uint8_t nkey_queue_buffer[NKEY_QUEUE_CAPACITY * NKEY_QUEUE_ITEM_SIZE];
static kb_queue_t nkey_queue;
static air_usb_hid_gaming_kb_nkey_report_t hid_nkey_report_data_last = {0};
static air_usb_hid_gaming_kb_nkey_report_t hid_nkey_report_data = {0};
#endif


#if CONFIG_AIR_HID_CP_PROCESS_KBD_DATA_ENABLE
ATTR_TEXT_IN_TCM static void hid_cp_kbd_prepare_boot_protocol(uint8_t *in, uint8_t *out)
{
    ARG_UNUSED(in);
    ARG_UNUSED(out);
}

static void hid_cp_kbd_data_reset_fifo(void)
{
    void *data = NULL;

    while (kbd_q.num > 0){
        data = k_fifo_get(&(kbd_q.fifo), K_NO_WAIT);
        if (data != NULL)
        {
            k_free(data);
        }
        kbd_q.num--;
    }
}

ATTR_TEXT_IN_TCM static int hid_cp_kbd_data_send_to_usb(uint8_t* data, uint16_t len, bool is_must)
{
    int ret = 0;
    hid_critical_path_t *hid_cp_key_remap_ctx = hid_critical_path_common_get_ctx(HID_CRITICAL_PATH_DEVICE_TYPE_KEY_REMAP);
    if(kbd_q.num){
        if (is_must)
        {
            /* queue has data, send data by sequence */
            if(len != sizeof(hid_cp_kbd_fifo_t)) {
                LOG_ERR(BT_HID_CP_TAG"Invalid len in hid_cp_kbd_data_send_to_usb");
                return -1;
            }
            hid_cp_kbd_fifo_t *p_fifo = k_malloc(sizeof(hid_cp_kbd_fifo_t));
            memcpy(&(p_fifo->data[0]), data, len);
            k_fifo_put(&kbd_q.fifo, p_fifo);
            kbd_q.num++;
        }
        // LOG_ERR(BT_HID_CP_TAG"hid_cp_kbd_data_send_to_usb kbd_q number: %d", kbd_q.num);
    } else {
        /* queue is empty, send data directly */
        if (hid_cp_key_remap_ctx->hid_protocol == USB_PROTOCOL_REPORT_MODE) {
            ret = air_usb_hid_tx(hid_cp_key_remap_ctx->usb_user_id, \
                            hid_cp_key_remap_ctx->hid_dev, len, data);
        } else if (hid_cp_key_remap_ctx->hid_protocol == USB_PROTOCOL_BOOT_MODE) {
        /* Prepare for boot protocol  */
        uint8_t hid_boot_data[HID_BIOS_DATA_LEN] = {0};
        hid_cp_kbd_prepare_boot_protocol(data, &hid_boot_data[0]);
        ret = air_usb_hid_tx(hid_cp_key_remap_ctx->usb_user_id, \
                        hid_cp_key_remap_ctx->hid_dev, HID_BIOS_DATA_LEN, &hid_boot_data[0]);
        } else {
            LOG_ERR(BT_HID_CP_TAG"Unknown usb hid protocol: %d", hid_cp_key_remap_ctx->hid_protocol);
            return -1;
        }
        /* if send directly fail, queue the data */
        if ((ret != 0) && (is_must)) {
            hid_cp_kbd_fifo_t *p_fifo = k_malloc(sizeof(hid_cp_kbd_fifo_t));
            memcpy(&(p_fifo->data[0]), data, len);
            k_fifo_put(&(kbd_q.fifo), p_fifo);
            kbd_q.num++;

            // if(len == sizeof(air_usb_hid_gaming_kb_report_t)){
            //     LOG_ERR(BT_HID_CP_TAG"hid_cp_kbd_data_send_to_usb data[%02X-%02X-%02X-%02X-%02X-%02X-%02X] send std fail, return %d, queue number: %d",
            //         data[0], data[1], data[2], data[3], data[4], data[5], data[6], ret, kbd_q.num);
            // } else if (len == sizeof(air_usb_hid_consumer_report_t)) {
            //     LOG_ERR(BT_HID_CP_TAG"hid_cp_kbd_data_send_to_usb data[%02X-%02X-%02X-%02X-%02X-%02X] send csm fail, return %d, queue number: %d",
            //         data[0], data[1], data[2], data[3], data[4], data[5], ret, kbd_q.num);
            // } else {
            //     __ASSERT_NO_MSG(0);
            // }
            // } else {
            //     if(len == sizeof(air_usb_hid_gaming_kb_report_t)){
            //         LOG_INF(BT_HID_CP_TAG"hid_cp_kbd_data_send_to_usb data[%02X-%02X-%02X-%02X-%02X-%02X-%02X] send std ok, return %d, queue number: %d",
            //             data[0], data[1], data[2], data[3], data[4], data[5], data[6], ret, kbd_q.num);
            //     } else if (len == sizeof(air_usb_hid_consumer_report_t)) {
            //         LOG_INF(BT_HID_CP_TAG"hid_cp_kbd_data_send_to_usb data[%02X-%02X-%02X-%02X-%02X-%02X] send csm ok, return %d, queue number: %d",
            //             data[0], data[1], data[2], data[3], data[4], data[5], ret, kbd_q.num);
            //     } else {
            //         __ASSERT_NO_MSG(0);
            //     }
        }
    }
    return ret;
}

ATTR_TEXT_IN_TCM static int hid_cp_kbd_general_tx_done_cb(const struct device *dev, uint8_t type, uint8_t id,
                    uint16_t len, const uint8_t *buf)
{
    int ret = 0;
    hid_critical_path_t *hid_cp_key_remap_ctx = hid_critical_path_common_get_ctx(HID_CRITICAL_PATH_DEVICE_TYPE_KEY_REMAP);
    uint32_t mask;
    hid_cp_kbd_fifo_t *p_kbd_fifo;
    #if defined(CONFIG_AIR_HID_CP_DEBUG_GPIO)
    hal_gpio_set_output(HID_CP_DEBUG_GPIO_5, HAL_GPIO_DATA_HIGH);
    #endif
    hal_nvic_save_and_set_interrupt_mask(&mask);
    if (kbd_q.num) {
        /* peek the data from the header of queue first */
        p_kbd_fifo = k_fifo_peek_head(&(kbd_q.fifo));
        hal_nvic_restore_interrupt_mask(mask);
        // LOG_INF(BT_HID_CP_TAG"hid_cp_kbd_general_tx_done_cb retry...");
        if (hid_cp_key_remap_ctx->hid_protocol == USB_PROTOCOL_REPORT_MODE) {
            /* Determine the type(length) of data being sent bases on the report ID. */
            uint16_t out_len = (p_kbd_fifo->data[0] == AIR_USB_HID_GAMING_KB_REPORT_ID) ? \
                    (sizeof(air_usb_hid_gaming_kb_report_t)) : \
                    (sizeof(air_usb_hid_consumer_report_t));
            ret = air_usb_hid_tx(hid_cp_key_remap_ctx->usb_user_id, \
                        hid_cp_key_remap_ctx->hid_dev, \
                        out_len, p_kbd_fifo->data);
        } else if (hid_cp_key_remap_ctx->hid_protocol == USB_PROTOCOL_BOOT_MODE) {
            /* Prepare for boot protocol  */
            uint8_t hid_boot_data[HID_BIOS_DATA_LEN] = {0};
            hid_cp_kbd_prepare_boot_protocol(p_kbd_fifo->data, &hid_boot_data[0]);
            ret = air_usb_hid_tx(hid_cp_key_remap_ctx->usb_user_id, \
                            hid_cp_key_remap_ctx->hid_dev, HID_BIOS_DATA_LEN, &hid_boot_data[0]);
        } else {
            LOG_ERR(BT_HID_CP_TAG"Unknown usb hid protocol: %d", hid_cp_key_remap_ctx->hid_protocol);
            #if defined(CONFIG_AIR_HID_CP_DEBUG_GPIO)
            hal_gpio_set_output(HID_CP_DEBUG_GPIO_5, HAL_GPIO_DATA_LOW);
            #endif
            return -1;
        }
        /* Assume that data from kbd_q can always bt sent successfully in the USB TX done callback function. */
        __ASSERT_NO_MSG(ret == 0);

        // LOG_INF(BT_HID_CP_TAG"hid_cp_kbd_general_tx_done_cb retry success, queue number %d...", kbd_q.num);
        hal_nvic_save_and_set_interrupt_mask(&mask);
        /* get(unlink) the data from the header of queue list, and then free its memory */
        k_free(k_fifo_get(&(kbd_q.fifo), K_NO_WAIT));
        kbd_q.num--;
    }
    /* if queue is empty, do nothing */
    hal_nvic_restore_interrupt_mask(mask);
    #if defined(CONFIG_AIR_HID_CP_DEBUG_GPIO)
    hal_gpio_set_output(HID_CP_DEBUG_GPIO_5, HAL_GPIO_DATA_LOW);
    #endif
    return 0;
}

ATTR_TEXT_IN_TCM hid_critical_path_status_t hid_cp_kbd(uint8_t* data, uint16_t len, usb_plc_cb_param *plc_param)
{
    hid_critical_path_status_t status = HID_CP_STATUS_SUCCESS;
    hid_critical_path_t *hid_cp_ms_ctx = hid_critical_path_common_get_ctx(HID_CRITICAL_PATH_DEVICE_TYPE_MOUSE);
    if ((data == NULL) || (len == 0)) {
        LOG_ERR(BT_HID_CP_TAG"Invalid data for hid_cp_kbd");
        status = HID_CP_STATUS_FAIL;
        return status;
    }

    ARG_UNUSED(plc_param);
    #if defined(AIR_PURE_GAMING_CUSTOM_PROTOCOL_HIX_MIXING_ENABLE)
    uint8_t report_id = data[0] & 0x3F;
    #else
    uint8_t report_id = data[0] & 0x7F;
    #endif /* AIR_PURE_GAMING_CUSTOM_PROTOCOL_HIX_MIXING_ENABLE */
    int send_result = 0;
    air_usb_hid_gaming_kb_report_t std_report;
    air_usb_hid_consumer_report_t csm_report;

    if((report_id == REPORT_ID_KB_STD_XY) || \
       (report_id == REPORT_ID_KB_CONSUMER_XY))
    {
        /* process x_y data in report from key remap keyboard report */
        __ASSERT(len >= offsetof(hid_24g_report_kb_std2_xy_s, dummy), "Input data size may error");
        int32_t x_axis = hid_cp_convert_data_extended((int16_t)(data[4] | ((data[5] & 0x0F) << 8)));
        int32_t y_axis = hid_cp_convert_data_extended((int16_t)((data[6] << 4) | ((data[5] & 0xF0) >> 4)));
        int32_t x_axis_out = 0;
        int32_t y_axis_out = 0;

        usb_plc_cb_param fixed_plc_param = {
            .need_plc = false,
            .correct = false,
            .reason = HID_PLC_REASON_RX_SUCCEESS
        };
        /* process x,y axis  but no algorithm process*/
        hid_cp_ms_xy_process(report_id, x_axis, y_axis, &fixed_plc_param, &x_axis_out, &y_axis_out);
        /* packet mouse report and send */
        bt_ms_packet_t ms_usb_data;
        memset(&ms_usb_data, 0, sizeof(bt_ms_packet_t));
        ms_usb_data.report_id = REPORT_ID_MOUSE;
        ms_usb_data.key = hid_cp_ms_ctx->ms_ctx.last_key;
        ms_usb_data.x = (int16_t)x_axis_out;
        ms_usb_data.y = (int16_t)y_axis_out;
        hid_cp_ms_data_send_to_usb((uint8_t*)(&ms_usb_data), sizeof(ms_usb_data));
    }

    /* handle keyboard report first */
    switch(report_id){
        case REPORT_ID_KB_STD_XY:
            hid_24g_report_kb_std2_xy_s *p_std_in = (hid_24g_report_kb_std2_xy_s *)data;
            memset((void*)(&std_report), 0, sizeof(std_report));
            memcpy((void*)(&std_report), (void*)p_std_in, offsetof(hid_24g_report_kb_std2_xy_s, x_y));
            std_report.report_id = AIR_USB_HID_OFFICE_KB_REPORT_ID;
            if(len < offsetof(hid_24g_report_kb_std2_xy_s, dummy)){
                LOG_ERR(BT_HID_CP_TAG"input len is too small for processing hid_24g_report_kb_std2_xy_s, len = %d", (int)len);
                __ASSERT(0, "input data error, not hid_24g_report_kb_std2_xy_s");
            }
            send_result = hid_cp_kbd_data_send_to_usb((uint8_t*)(&std_report), sizeof(std_report), true);
            break;
        case REPORT_ID_KB_CONSUMER_XY:
            hid_24g_report_kb_consumer1_xy_s *p_csm_in = (hid_24g_report_kb_consumer1_xy_s *)data;
            memset((void*)(&csm_report), 0, sizeof(csm_report));
            csm_report.report_id = AIR_USB_HID_CONSUMER_REPORT_ID;
            csm_report.consumer_usage[0] = p_csm_in->consumer;
            csm_report.numkey = p_csm_in->numeric_key_pad;
            if(len < offsetof(hid_24g_report_kb_consumer1_xy_s, dummy)){
                LOG_ERR(BT_HID_CP_TAG"input len is too small for processing hid_24g_report_kb_consumer1_xy_s, len = %d", (int)len);
                __ASSERT(0, "input data error, not hid_24g_report_kb_consumer1_xy_s");
            }
            // LOG_INF(BT_HID_CP_TAG"input data len: %d", (int)len);
            // LOG_INF(BT_HID_CP_TAG"%02X %02X %02X %02X %02X %02X %02X",
            //     data[0], data[1], data[2], data[3],
            //     data[4], data[5], data[6]
            // );
            // LOG_INF(BT_HID_CP_TAG"output data len: %d", (int)sizeof(csm_report));
            // uint8_t* p_out_csm_report = (uint8_t*)(&csm_report);
            // LOG_INF(BT_HID_CP_TAG"%02X %02X %02X %02X %02X %02X",
            //     p_out_csm_report[0], p_out_csm_report[1], p_out_csm_report[2], p_out_csm_report[3],
            //     p_out_csm_report[4], p_out_csm_report[5]
            // );
            send_result = hid_cp_kbd_data_send_to_usb((uint8_t*)(&csm_report), sizeof(csm_report), true);
            break;
        case REPORT_ID_KB_STD:
            __ASSERT_NO_MSG(len >= sizeof(std_report));
            memcpy(&std_report, data, sizeof(std_report));
            std_report.report_id = AIR_USB_HID_GAMING_KB_REPORT_ID;
            send_result = hid_cp_kbd_data_send_to_usb((uint8_t*)(&std_report), sizeof(std_report), true);
            break;
        case REPORT_ID_KB_CONSUMER:
            __ASSERT_NO_MSG(len >= sizeof(csm_report));
            memcpy(&csm_report, data, sizeof(csm_report));
            csm_report.report_id = AIR_USB_HID_CONSUMER_REPORT_ID;
            send_result = hid_cp_kbd_data_send_to_usb((uint8_t*)(&csm_report), sizeof(csm_report), true);
            break;
        default:
            send_result = -1;
            status = HID_CP_STATUS_FAIL;
            __ASSERT_NO_MSG(0);
            break;
    }

    if (send_result != 0){
        status = HID_CP_STATUS_SEND_FAIL;
    }

    return status;
}
#endif

#if CONFIG_AIR_HID_CP_PROCESS_NKEY_ENABLE
ATTR_TEXT_IN_TCM static void hid_cp_nkey_prepare_boot_protocol(uint8_t *in, uint8_t *out)
{
    ARG_UNUSED(in);
    ARG_UNUSED(out);
}

ATTR_TEXT_IN_TCM static int hid_cp_nkey_data_send_to_usb(uint8_t* data, uint16_t len, bool is_must)
{
    int ret = 0;
    hid_critical_path_t *hid_cp_nkey_ctx = hid_critical_path_common_get_ctx(HID_CRITICAL_PATH_DEVICE_TYPE_NKEY);
    uint8_t *peek_data = NULL;

    if ((kb_queue_item_num(&nkey_queue) > 0) && is_must) {
            /* queue has data, send data by sequence */
            kb_queue_put(&nkey_queue, data);

        /* Try to send if queue is not empty but USB might be idle (e.g. missed tx_done) */
        if (kb_queue_peek_head(&nkey_queue, (void **)&peek_data) == KB_QUEUE_OK) {
            /* Locked and got data */
            if (hid_cp_nkey_ctx->hid_protocol == USB_PROTOCOL_REPORT_MODE) {
                ret = air_usb_hid_tx(hid_cp_nkey_ctx->usb_user_id, \
                                hid_cp_nkey_ctx->hid_dev, nkey_queue.item_size, peek_data);
            } else if (hid_cp_nkey_ctx->hid_protocol == USB_PROTOCOL_BOOT_MODE) {
                /* Prepare for boot protocol  */
                uint8_t hid_boot_data[HID_BIOS_DATA_LEN] = {0};
                hid_cp_nkey_prepare_boot_protocol(peek_data, &hid_boot_data[0]);
                ret = air_usb_hid_tx(hid_cp_nkey_ctx->usb_user_id, \
                                hid_cp_nkey_ctx->hid_dev, HID_BIOS_DATA_LEN, &hid_boot_data[0]);
            } else {
                LOG_ERR(BT_HID_CP_TAG"Unknown usb hid protocol: %d", hid_cp_nkey_ctx->hid_protocol);
                ret = -1;
            }

            if (ret == 0) {
                /* Send success, remove from queue (this will unlock) */
                kb_queue_get(&nkey_queue, NULL);
            } else {
                /* Send failed (busy), unlock manually */
                kb_queue_unlock(&nkey_queue);
            }
        }
    } else {
        /* queue is empty, send data directly */
        if (hid_cp_nkey_ctx->hid_protocol == USB_PROTOCOL_REPORT_MODE) {
            ret = air_usb_hid_tx(hid_cp_nkey_ctx->usb_user_id, \
                            hid_cp_nkey_ctx->hid_dev, len, data);
        } else if (hid_cp_nkey_ctx->hid_protocol == USB_PROTOCOL_BOOT_MODE) {
            /* Prepare for boot protocol  */
            uint8_t hid_boot_data[HID_BIOS_DATA_LEN] = {0};
            hid_cp_nkey_prepare_boot_protocol(data, &hid_boot_data[0]);
            ret = air_usb_hid_tx(hid_cp_nkey_ctx->usb_user_id, \
                            hid_cp_nkey_ctx->hid_dev, HID_BIOS_DATA_LEN, &hid_boot_data[0]);
        } else {
            LOG_ERR(BT_HID_CP_TAG"Unknown usb hid protocol: %d", hid_cp_nkey_ctx->hid_protocol);
            return -1;
        }
        /* if send directly fail, queue the data */
        if ((ret != 0) && (is_must)) {
            kb_queue_put(&nkey_queue, data);
            ret = 0;
        }
    }
    return ret;
}

ATTR_TEXT_IN_TCM static int hid_cp_nkey_general_tx_done_cb(const struct device *dev, uint8_t type, uint8_t id,
                    uint16_t len, const uint8_t *buf)
{
    int ret = 0;
    hid_critical_path_t *hid_cp_nkey_ctx = hid_critical_path_common_get_ctx(HID_CRITICAL_PATH_DEVICE_TYPE_NKEY);
    uint8_t *data = NULL;
    
    /* tx_done drop test code */
    // static int tx_done_remove_test = 60;
    // if (tx_done_remove_test == 0 ) {
    //     tx_done_remove_test--;
    //     air_usb_hid_gaming_kb_nkey_report_t fake_data = {0};
    //     memset(&fake_data, 0, sizeof(air_usb_hid_gaming_kb_nkey_report_t));
    //     fake_data.report_id = AIR_USB_HID_GAMING_KB_NKEY_REPORT_ID;
    //     kb_queue_put(&nkey_queue, (void *)&fake_data);
    //     LOG_INF("[debugz] skip tx_done");
    //     return 0;
    // } else if(tx_done_remove_test > 0){
    //     tx_done_remove_test--;
    // }

    #if defined(CONFIG_AIR_HID_CP_DEBUG_GPIO)
    hal_gpio_set_output(HID_CP_DEBUG_GPIO_5, HAL_GPIO_DATA_HIGH);
    #endif

    if (kb_queue_peek_head(&nkey_queue, (void **)&data) == KB_QUEUE_OK) {
        if (hid_cp_nkey_ctx->hid_protocol == USB_PROTOCOL_REPORT_MODE) {
            ret = air_usb_hid_tx(hid_cp_nkey_ctx->usb_user_id, \
                        hid_cp_nkey_ctx->hid_dev, \
                        nkey_queue.item_size, data);
        } else if (hid_cp_nkey_ctx->hid_protocol == USB_PROTOCOL_BOOT_MODE) {
            /* Prepare for boot protocol  */
            uint8_t hid_boot_data[HID_BIOS_DATA_LEN] = {0};
            hid_cp_nkey_prepare_boot_protocol(data, &hid_boot_data[0]);
            ret = air_usb_hid_tx(hid_cp_nkey_ctx->usb_user_id, \
                            hid_cp_nkey_ctx->hid_dev, HID_BIOS_DATA_LEN, &hid_boot_data[0]);
        } else {
            LOG_ERR(BT_HID_CP_TAG"Unknown usb hid protocol: %d", hid_cp_nkey_ctx->hid_protocol);
            kb_queue_unlock(&nkey_queue);
            #if defined(CONFIG_AIR_HID_CP_DEBUG_GPIO)
            hal_gpio_set_output(HID_CP_DEBUG_GPIO_5, HAL_GPIO_DATA_LOW);
            #endif
            return -1;
        }
        /* Assume that data from nkey_q can always bt sent successfully in the USB TX done callback function. */
        __ASSERT_NO_MSG(ret == 0);
        /* get(unlink) the data from the header of queue list (this will unlock) */
        kb_queue_get(&nkey_queue, NULL);
    }
    #if defined(CONFIG_AIR_HID_CP_DEBUG_GPIO)
    hal_gpio_set_output(HID_CP_DEBUG_GPIO_5, HAL_GPIO_DATA_LOW);
    #endif
    return 0;
}

ATTR_TEXT_IN_TCM hid_critical_path_status_t hid_cp_nkey(uint8_t* data, uint16_t len, usb_plc_cb_param *plc_param)
{
    hid_critical_path_status_t status = HID_CP_STATUS_SUCCESS;
    #if defined(AIR_PURE_GAMING_CUSTOM_PROTOCOL_HIX_MIXING_ENABLE)
    uint8_t report_id = data[0] & 0x3F;
    #else
    uint8_t report_id = data[0] & 0x7F;
    #endif /* AIR_PURE_GAMING_CUSTOM_PROTOCOL_HIX_MIXING_ENABLE */

    if ((data == NULL) || (len != 9 && len != 17)) {
        LOG_ERR(BT_HID_CP_TAG"Invalid data for hid_cp_nkey");
        status = HID_CP_STATUS_FAIL;
        return status;
    }
    ARG_UNUSED(plc_param);

    hid_nkey_report_data.report_id = AIR_USB_HID_GAMING_KB_NKEY_REPORT_ID;
    hid_nkey_report_data.modifier = data[1];
/*  merge group data into keymap */
    switch (report_id) {
        case REPORT_ID_KEYBOARD:
            hid_nkey_report_data.modifier = data[1];
            memcpy(&hid_nkey_report_data.keymap[0], &data[2], 15);
            break;
        case REPORT_ID_KEYBOARD_GROUP0:
            hid_nkey_report_data.modifier = data[1];
            memcpy(&hid_nkey_report_data.keymap[0], &data[2], 7);
            break;
        case REPORT_ID_KEYBOARD_GROUP1:
            memcpy(&hid_nkey_report_data.keymap[7], &data[1], 8);
            break;
        default:
            LOG_ERR(BT_HID_CP_TAG"hid_cp_nkey: unexpected report_id: %d", report_id);
            status = HID_CP_STATUS_FAIL;
            return status;
            break;
    }

    /* filter duplicate packets */
    if (memcmp(&hid_nkey_report_data, &hid_nkey_report_data_last, sizeof(air_usb_hid_gaming_kb_nkey_report_t)) == 0) {
        return HID_CP_STATUS_SUCCESS;
    }

    if ((hid_cp_nkey_data_send_to_usb((uint8_t *)&hid_nkey_report_data, sizeof(air_usb_hid_gaming_kb_nkey_report_t), true)) == 0) {
            /* Send to USB Successfully  */
            memcpy(&hid_nkey_report_data_last, &hid_nkey_report_data, sizeof(air_usb_hid_gaming_kb_nkey_report_t));
#ifdef CONFIG_AIR_HID_CP_DEBUG_LOG
        uint32_t mask;
        hid_critical_path_t *hid_cp_ms_ctx = hid_critical_path_common_get_ctx(HID_CRITICAL_PATH_DEVICE_TYPE_MOUSE);
        hal_nvic_save_and_set_interrupt_mask(&mask);
        hid_cp_debug_paramter.usb_data[hid_cp_debug_paramter.usb_print_count].timestamp = GPT(HAL_GPT_US_PORT)->GPT_COUNT;
        memcpy(&hid_cp_debug_paramter.usb_data[hid_cp_debug_paramter.usb_print_count].data[0],
                data,
                len);
        hid_cp_debug_paramter.usb_data[hid_cp_debug_paramter.usb_print_count].data[6] = hid_cp_ms_ctx->ms_ctx.bt_hid_data.data[6];
        hal_nvic_restore_interrupt_mask(mask);
#endif
    } else {
        /* Send to USB Failed */
        status = HID_CP_STATUS_SEND_FAIL;
    }
    return status;
}
#endif

int hid_critical_path_kb_init(void)
{
    int ret = 0;
#if defined(CONFIG_AIR_HID_CP_PROCESS_NKEY_ENABLE)
    hid_critical_path_t *hid_cp_nkey_ctx = hid_critical_path_common_get_ctx(HID_CRITICAL_PATH_DEVICE_TYPE_NKEY);
#endif
#if defined(CONFIG_AIR_HID_CP_PROCESS_KBD_DATA_ENABLE)
    hid_critical_path_t *hid_cp_key_remap_ctx = hid_critical_path_common_get_ctx(HID_CRITICAL_PATH_DEVICE_TYPE_KEY_REMAP);
#endif
    LOG_INF(BT_HID_CP_TAG"HID Critical Path KB Init");
    if (hid_critical_path_get_state(HID_CRITICAL_PATH_DEVICE_TYPE_NKEY) == HID_CP_STATE_IDLE) {
        LOG_ERR(BT_HID_CP_TAG"HID Critical Path Already Init!");
        return -EBUSY;
    }
    if (hid_critical_path_get_state(HID_CRITICAL_PATH_DEVICE_TYPE_KEY_REMAP) == HID_CP_STATE_IDLE) {
        LOG_ERR(BT_HID_CP_TAG"HID Critical Path Already Init!");
        return -EBUSY;
    }
#if defined(CONFIG_AIR_HID_CP_PROCESS_NKEY_ENABLE)
    memset(hid_cp_nkey_ctx, 0, sizeof(hid_critical_path_t));
    hid_critical_path_set_state(HID_CRITICAL_PATH_DEVICE_TYPE_NKEY, HID_CP_STATE_IDLE);
#endif
#if defined(CONFIG_AIR_HID_CP_PROCESS_KBD_DATA_ENABLE)
    memset(hid_cp_key_remap_ctx, 0, sizeof(hid_critical_path_t));
    hid_critical_path_set_state(HID_CRITICAL_PATH_DEVICE_TYPE_KEY_REMAP, HID_CP_STATE_IDLE);
#endif
    /* gaming keyboard device */
#if CONFIG_AIR_HID_CP_PROCESS_KBD_DATA_ENABLE
    hid_cp_key_remap_ctx->hid_dev = \
        air_usb_hid_find_first_device_by_report(AIR_USB_REPORT_DESC_GAMING_KB);
#endif
#if CONFIG_AIR_HID_CP_PROCESS_NKEY_ENABLE
    hid_cp_nkey_ctx->hid_dev = \
        air_usb_hid_find_first_device_by_report(AIR_USB_REPORT_DESC_GAMING_KB_NKEY);
#endif
#if CONFIG_AIR_HID_CP_PROCESS_KBD_DATA_ENABLE
    ret = air_usb_create_user("HID_CP_KBD", &hid_cp_key_remap_ctx->usb_user_id);
    if(ret != 0)
    {
        LOG_ERR(BT_HID_CP_TAG"air_usb_create_user for KBD fail");
        return ret;
    }
    else{
        LOG_INF(BT_HID_CP_TAG"air_usb_create_user for KBD ok");
    }
#endif
#if CONFIG_AIR_HID_CP_PROCESS_NKEY_ENABLE
    ret = air_usb_create_user("HID_CP_NKEY", &hid_cp_nkey_ctx->usb_user_id);
    if(ret != 0)
    {
        LOG_ERR(BT_HID_CP_TAG"air_usb_create_user for NKEY fail");
        return ret;
    }
    else{
        LOG_INF(BT_HID_CP_TAG"air_usb_create_user for NKEY ok");
    }
#endif

#if CONFIG_AIR_HID_CP_PROCESS_KBD_DATA_ENABLE
    k_fifo_init(&(kbd_q.fifo));
    kbd_q.num = 0;
    air_usb_hid_register_protocol_change_cb(hid_cp_key_remap_ctx->usb_user_id, \
                            hid_cp_key_remap_ctx->hid_dev, hid_cp_protocol_change_cb);
#endif
#if CONFIG_AIR_HID_CP_PROCESS_NKEY_ENABLE
    kb_queue_init(&nkey_queue, (char *)nkey_queue_buffer, NKEY_QUEUE_ITEM_SIZE, NKEY_QUEUE_CAPACITY);
    air_usb_hid_register_protocol_change_cb(hid_cp_nkey_ctx->usb_user_id, \
                            hid_cp_nkey_ctx->hid_dev, hid_cp_protocol_change_cb);
#endif

#if CONFIG_AIR_HID_CP_PROCESS_KBD_DATA_ENABLE
    int kbd_tx_done_cb_result = air_usb_hid_register_tx_done_cb(hid_cp_key_remap_ctx->usb_user_id,
                                    hid_cp_key_remap_ctx->hid_dev,
                                    USB_HID_REPORT_TYPE_INPUT,
                                    AIR_USB_HID_GAMING_KB_REPORT_ID,
                                    sizeof(air_usb_hid_gaming_kb_report_t),
                                    hid_cp_kbd_general_tx_done_cb);
    LOG_INF(BT_HID_CP_TAG"kbd(standard kbd report)_tx_done_cb_result: %d", kbd_tx_done_cb_result);
    kbd_tx_done_cb_result = air_usb_hid_register_tx_done_cb(hid_cp_key_remap_ctx->usb_user_id,
                                    hid_cp_key_remap_ctx->hid_dev,
                                    USB_HID_REPORT_TYPE_INPUT,
                                    AIR_USB_HID_CONSUMER_REPORT_ID,
                                    sizeof(air_usb_hid_consumer_report_t),
                                    hid_cp_kbd_general_tx_done_cb);
    LOG_INF(BT_HID_CP_TAG"kbd(consumer kbd report)_tx_done_cb_result: %d", kbd_tx_done_cb_result);
#endif

#if CONFIG_AIR_HID_CP_PROCESS_NKEY_ENABLE
    int nkey_tx_done_cb_result = air_usb_hid_register_tx_done_cb(hid_cp_nkey_ctx->usb_user_id,
                                    hid_cp_nkey_ctx->hid_dev,
                                    USB_HID_REPORT_TYPE_INPUT,
                                    AIR_USB_HID_GAMING_KB_NKEY_REPORT_ID,
                                    sizeof(air_usb_hid_gaming_kb_nkey_report_t),
                                    hid_cp_nkey_general_tx_done_cb);
    LOG_INF(BT_HID_CP_TAG"nkey_tx_done_cb_result: %d", nkey_tx_done_cb_result);
#endif

    return ret;
}

void hid_critical_path_kb_start(void)
{    
#if CONFIG_AIR_HID_CP_PROCESS_NKEY_ENABLE 
    memset((void*)(&hid_nkey_report_data_last), 0, sizeof(air_usb_hid_gaming_kb_nkey_report_t));
    memset((void*)(&hid_nkey_report_data), 0, sizeof(air_usb_hid_gaming_kb_nkey_report_t));
#endif
}

void hid_critical_path_kb_stop(void)
{
#if CONFIG_AIR_HID_CP_PROCESS_KBD_DATA_ENABLE
    air_usb_hid_gaming_kb_report_t std_report;
    air_usb_hid_consumer_report_t csm_report;
    hid_cp_kbd_data_reset_fifo();
    memset((void*)(&std_report), 0, sizeof(std_report));
    std_report.report_id = AIR_USB_HID_GAMING_KB_REPORT_ID;
    hid_cp_kbd_data_send_to_usb((uint8_t*)&std_report, sizeof(std_report), false);
    memset((void*)(&csm_report), 0, sizeof(csm_report));
    csm_report.report_id = AIR_USB_HID_CONSUMER_REPORT_ID;
    hal_gpt_delay_us(500); /* make sure the the STD packet is sent */
    hid_cp_kbd_data_send_to_usb((uint8_t*)&csm_report, sizeof(csm_report), false);
#endif
#if CONFIG_AIR_HID_CP_PROCESS_NKEY_ENABLE
    air_usb_hid_gaming_kb_nkey_report_t nkey_report_data;
    kb_queue_reset(&nkey_queue);
    memset((void*)(&nkey_report_data), 0, sizeof(air_usb_hid_gaming_kb_nkey_report_t));
    nkey_report_data.report_id = AIR_USB_HID_GAMING_KB_NKEY_REPORT_ID;
    hid_cp_nkey_data_send_to_usb((uint8_t *)&nkey_report_data, sizeof(air_usb_hid_gaming_kb_nkey_report_t), false);
#endif
}

void hid_critical_path_kb_deinit(void)
{
    LOG_INF(BT_HID_CP_TAG"HID Critical Path KB DeInit");
#if defined(CONFIG_AIR_HID_CP_PROCESS_NKEY_ENABLE)
    hid_critical_path_t *hid_cp_nkey_ctx = hid_critical_path_common_get_ctx(HID_CRITICAL_PATH_DEVICE_TYPE_NKEY);
    memset(hid_cp_nkey_ctx, 0, sizeof(hid_critical_path_t));
    hid_cp_nkey_ctx->bit_mask &= ~HID_CP_BIT_MASK_LAST_KEY_VAILD;
    kb_queue_deinit(&nkey_queue);
#endif
}

/* End of file */
