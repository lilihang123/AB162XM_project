/* Copyright Statement:
 *
 * (C) 2017  Airoha Technology Corp. All rights reserved.
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

#include <stddef.h>
#include "air_logging.h"
#include <zephyr/logging/log.h>


/* Airoha hci log type requirement define */
#define HCI_COMMAND             (1)
#define HCI_EVENT               (2)
#define HCI_ACL_IN              (4)
#define HCI_ACL_OUT             (8)
#define HCI_ISO_IN              (5)
#define HCI_ISO_OUT             (10)

/* Copy from zephyr subsys bluetooth host monitor.h */
#define BT_MONITOR_COMMAND_PKT  (2)
#define BT_MONITOR_EVENT_PKT    (3)
#define BT_MONITOR_ACL_TX_PKT   (4)
#define BT_MONITOR_ACL_RX_PKT   (5)
#define BT_MONITOR_ISO_TX_PKT   (18)
#define BT_MONITOR_ISO_RX_PKT   (19)

typedef struct {
	uint16_t  data_len;
	uint16_t  opcode;
	uint8_t   flags;
	uint8_t   hdr_len;

	uint8_t   ext[15];
} __packed bt_monitor_hdr;

typedef struct {
	uint8_t   type;
	uint32_t  ts32;
} __packed bt_monitor_ts32;
/* Copy end */

log_create_module(hci_log, PRINT_LEVEL_INFO);

static void *hci_log_buf_arr[3] = {NULL};
static uint32_t hci_buf_len_arr[2] = {0};
static const uint8_t s_monitor_to_hci_log_map[6][2] = {
    {BT_MONITOR_COMMAND_PKT, HCI_COMMAND},
    {BT_MONITOR_EVENT_PKT, HCI_EVENT},
    {BT_MONITOR_ACL_TX_PKT, HCI_ACL_OUT},
    {BT_MONITOR_ACL_RX_PKT, HCI_ACL_IN},
    {BT_MONITOR_ISO_TX_PKT, HCI_ISO_OUT},
    {BT_MONITOR_ISO_RX_PKT, HCI_ISO_IN}
};

static uint8_t s_hci_log_data = 0;
static uint8_t s_hci_header[7] = {0};

static uint8_t bt_monitor_get_hci_log_type(uint16_t opcode)
{
    for (int i = 0; i < sizeof(s_monitor_to_hci_log_map)/sizeof(s_monitor_to_hci_log_map[0]); i++) {
        if (s_monitor_to_hci_log_map[i][0] == opcode) {
            return s_monitor_to_hci_log_map[i][1];
        }
    }
    LOG_INF("unkown hci log type %d", opcode);
    return 0xFF;
}

void monitor_send(const void *data, size_t len)
{
    uint32_t ret_len = 0;
    //LOG_INF("hci log len %u", len);
    if (s_hci_log_data == 0) {
        /* Hci log header fill. */
        bt_monitor_hdr *hdr = (void *)data;
        bt_monitor_ts32 *ts = (bt_monitor_ts32 *)(hdr->ext);
        uint8_t hci_type = bt_monitor_get_hci_log_type(hdr->opcode);
        s_hci_header[2] = ts->ts32 & 0xFF;
        s_hci_header[3] = (ts->ts32 >> 8) & 0xFF;
        s_hci_header[4] = (ts->ts32 >> 16) & 0xFF;
        s_hci_header[5] = (ts->ts32 >> 24) & 0xFF;
        s_hci_header[6] = hci_type;
        s_hci_log_data = 1;
        return;
    } else {
        /* Hci log data fill. */
        s_hci_header[0] = (len + 5) & 0xFF;
        s_hci_header[1] = ((len + 5) >> 8) & 0xFF;
        s_hci_log_data = 0;
    }
    hci_log_buf_arr[0] = &s_hci_header;
    hci_log_buf_arr[1] = (void *)data;
    hci_buf_len_arr[0] = sizeof(s_hci_header);
    hci_buf_len_arr[1] = len;

    if (0xFF != s_hci_header[6]) {
        LOG_TLVDUMP_I(hci_log, LOG_TYPE_HCI_DATA, hci_log_buf_arr, hci_buf_len_arr, ret_len);
        (void)(ret_len);
        //LOG_INF("hci log ret len %u", ret_len);
    }
}

void poll_out(char c)
{
	monitor_send(&c, sizeof(c));
}