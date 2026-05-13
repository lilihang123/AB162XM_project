/* Copyright Statement:
*
* (C) 2022  Airoha Technology Corp. All rights reserved.
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
/* Airoha restricted information */



#include "race_core.h"
#include "hal.h"
#include <zephyr/init.h>
#include "race_port_uart.h"
#ifdef AIR_BTD_IC_PREMIUM_G1
#define RACE_STACK_SIZE 2048
#else
#define RACE_STACK_SIZE 1536
#endif
static K_THREAD_STACK_DEFINE(race_thread_stack, RACE_STACK_SIZE);

static struct k_thread race_thread_data = {0};
/**************************************************************************************************
* Define
**************************************************************************************************/
#define RACE_MSG_QUEUE_MAX_SIZE     (30)

#define RACE_MAX_DELAY              (portMAX_DELAY)
#define RACE_PAYLOAD_MAX_LENGTH     (2000)
#define RACE_PAYLOAD_MIN_LENGTH     (2) /* race id length is 2 */

#define RACE_PKT_USER_MAX           (5)

#define RACE_RELAY_CHECK_HDL_MAX    (2)

#define RACE_IDLE_TIMER_PERIOD      (120000) // uinit: ms

#define RACE_TX_MAX_RETRY_TIME      (100000)  // unit: ms

#define RACE_IS_VALID_ID(id)        (RACE_CHANNEL_RACE == (id) || RACE_CHANNEL_FOTA == (id))
#define RACE_IS_VALID_TYPE(type)    (RACE_TYPE_COMMAND == (type) || RACE_TYPE_RESPONSE == (type) \
    || RACE_TYPE_COMMAND_WITHOUT_RSP == (type) || RACE_TYPE_NOTIFICATION == (type))
#define RACE_IS_VALID_LEN(len)      (RACE_PAYLOAD_MAX_LENGTH >= (len) && RACE_PAYLOAD_MIN_LENGTH <= (len))

#define PROTOCOL_INVALID            (0x00)
#define PROTOCOL_HCI_CMD            (0x01)
#define PROTOCOL_HCI_ACL            (0x02)
#define PROTOCOL_HCI_EVT            (0x04)
#define PROTOCOL_RACE               (0x05)
#define PROTOCOL_RACE_FOTA          (0x15)

#define HCI_CMD_HEADER_LEN          (4)
#define HCI_ACL_HEADER_LEN          (5)
#define HCI_EVT_HEADER_LEN          (3)

/**************************************************************************************************
* Structure
**************************************************************************************************/

typedef uint8_t race_protocol_type_t;


typedef struct {
    const char *user_name;
    race_check_pkt_user_t check_function;
} race_pkt_user_t;

typedef struct {
    race_pkt_user_t user[RACE_PKT_USER_MAX];  /* user[0] SHOULD be the default user "RACE_CMD" */
    uint16_t user_num;
} race_pkt_user_manager_t;
#ifdef HAL_SLEEP_MANAGER_ENABLED
typedef struct {
    uint8_t sleep_handle;
    struct k_timer sleep_lock_timer;
} race_sleep_ctrl_t;
#endif
typedef struct race_port_node_struct{
    struct race_port_node_struct *next;
    race_port_info_t port_info;
} race_port_list_t;

typedef struct {
    race_port_t port;
    race_port_type_t port_type;
    RACE_COMMON_HDR_STRU pkt_hdr;
    race_pkt_relay_info_t relay_info;
} race_pkt_relay_check_t;

typedef struct {
    mux_handle_t handle;
    uint32_t data_len;
} race_msg_mux_data_ready_t;

/**************************************************************************************************
* Static Variable
**************************************************************************************************/

static const char *g_race_default_user_name = "RACE_CMD";
//static const char *g_race_atci_user_name = "ATCI";

static race_port_list_t *g_race_port_list = NULL;

static race_general_msg_hdl_t g_race_msg_hdl_tbl[MSG_ID_RACE_END];
#ifdef HAL_SLEEP_MANAGER_ENABLED
static race_sleep_ctrl_t g_race_sleep_ctrl = {0xff};
#endif
static race_check_relay_t g_race_relay_check_hdl_tbl[RACE_RELAY_CHECK_HDL_MAX] = {NULL};
#if RACE_DEBUG_INFO_ENABLE
static TimerHandle_t g_race_idle_timer = NULL;
#endif
extern struct k_msgq race_queue;

/**************************************************************************************************
* Prototype
**************************************************************************************************/

static race_port_info_t *race_create_port_info(race_port_t port, race_port_type_t port_type);
static bool race_delete_port_info(race_port_info_t *port_info);
static race_port_user_t *race_create_user_for_port(race_port_info_t *port_info);
static bool race_delete_user(race_port_info_t *port_info, race_port_user_t *port_user);

static race_port_user_t *race_search_user_by_handle(race_port_handle_t handle);
static race_port_user_t *race_find_pkt_user(race_port_info_t *port_info, RACE_COMMON_HDR_STRU *pkt_hdr, race_mux_buffer_t *pkt_buf);

static void race_handle_input_data(race_general_msg_t *p_msg);
static void race_cmd_local_handler(race_port_t port, uint8_t *race_pkt);
static void race_handle_ext_cmd(race_general_msg_t *p_msg);

static uint32_t race_tx_default(uint32_t mux_handle, uint8_t *p_data, uint32_t len);
static bool race_rx_default(mux_handle_t handle, mux_buffer_t *buffer, uint32_t *receive_done_data_len);

static bool race_check_default_user(race_port_t port, RACE_COMMON_HDR_STRU *pkt_hdr, race_mux_buffer_t *pkt_buf);
static void race_relay_check(race_pkt_relay_check_t *check_info);

static void race_sleep_timer_init(void);
#ifdef HAL_SLEEP_MANAGER_ENABLED
static void race_sleep_lock_timer_callback(struct k_timer *timer);
#endif

static void race_mux_rx_protocol_callback(mux_handle_t *handle, mux_buffer_t buffers[], uint32_t buffers_counter,
    uint32_t *consume_len, uint32_t *package_len, void *user_data);
static void race_mux_tx_protocol_callback(mux_handle_t handle, const mux_buffer_t payload[], uint32_t buffers_counter,
    mux_buffer_t *head, mux_buffer_t *tail, void *user_data);
static void race_mux_callback(mux_handle_t handle, mux_event_t event, uint32_t data_len, void *user_data);
#if RACE_DEBUG_INFO_ENABLE
static void race_idle_timer_handler(TimerHandle_t xtimer);
static void race_idle_init(void);
static void race_idle_event_handler(race_general_msg_t *msg);
#endif

/**************************************************************************************************
* Static Functions
**************************************************************************************************/

static race_port_info_t *race_create_port_info(race_port_t port, race_port_type_t port_type)
{
    race_port_list_t *port_node = (race_port_list_t *)race_mem_alloc(sizeof(race_port_list_t));
    if (NULL != port_node) {
        memset(port_node, 0, sizeof(race_port_list_t));
        port_node->next = g_race_port_list;
        g_race_port_list = port_node;
        port_node->port_info.port = port;
        port_node->port_info.port_type = port_type;
        LOG_INF("[race_core] race_create_port_info, port:%d, type:%d, malloc_node:0x%x", port, port_type, (uint32_t)port_node);
        return &port_node->port_info;
    }
    return NULL;
}

static bool race_delete_port_info(race_port_info_t *port_info)
{
    race_port_list_t *pre = g_race_port_list;
    race_port_list_t *node = NULL;
    if (NULL == port_info || NULL == pre) {
        return false;
    }
    if (&pre->port_info == port_info) {
        node = pre;
        g_race_port_list = g_race_port_list->next;
        node->next = NULL;
    } else {
        while (pre->next) {
            if (&pre->next->port_info == port_info) {
                node = pre->next;
                pre->next = node->next;
                node->next = NULL;
                break;
            } else {
                pre = pre->next;
            }
        }
    }
    if (NULL == node) {
        // this port info is not in g_race_port_list
        assert(0 && "ERROR: race_delete_port_info, this port info is not in g_race_port_list!");
        return false;
    }
    LOG_INF("[race_core] race_delete_port_info, port:%d, type:%d", port_info->port, port_info->port_type);
    race_mem_free(node);
    return true;
}

static race_port_user_t *race_create_user_for_port(race_port_info_t *port_info)
{
    race_port_user_t *user_info = NULL;

    if (NULL == port_info) {
        return NULL;
    }
    user_info = (race_port_user_t *)race_mem_alloc(sizeof(race_port_user_t));
    if (NULL != user_info) {
        memset(user_info, 0, sizeof(race_port_user_t));
        user_info->next = port_info->user_list;
        port_info->user_list = user_info;
    }
    LOG_INF("[race_core] malloc_user_info:0x%x", (uint32_t)user_info);
    return user_info;
}

static race_port_user_t *race_search_user_by_handle(race_port_handle_t handle)
{
    race_port_info_t *port_info = race_search_port(RACE_GET_PORT_BY_MUX_HANDLE(handle));
    race_port_user_t *user = NULL;

    if (NULL == port_info || NULL == port_info->user_list) {
        return NULL;
    }

    user = port_info->user_list;
    while (NULL != user) {
        if (handle == user->handle) {
            return user;
        } else {
            user = user->next;
        }
    }
    return NULL;
}

static bool race_delete_user(race_port_info_t *port_info, race_port_user_t *port_user)
{
    // [input validation] Check input pointers for NULL
    if ((NULL == port_info) || (NULL == port_user)) {
        return false;
    }

    race_port_user_t *user = port_info->user_list; // [init] Initialize variable at declaration

    // [boundary check] Ensure user_list is not NULL before dereferencing
    if (NULL == user) {
        return false;
    }

    if (user == port_user) {
        port_info->user_list = user->next;
        race_mem_free(port_user);
        return true;
    }
    while (NULL != user->next) {
        if (user->next == port_user) {
            user->next = port_user->next;
            race_mem_free(port_user);
            return true;
        } else {
            user = user->next;
        }
    }
    return false;
}

static race_port_user_t *race_find_pkt_user(race_port_info_t *port_info, RACE_COMMON_HDR_STRU *pkt_hdr, race_mux_buffer_t *pkt_buf)
{
    race_port_user_t *user = NULL;
    race_port_user_t *temp_user = NULL;

    if (NULL == port_info || NULL == port_info->user_list) {
        return NULL;
    }
    temp_user = port_info->user_list;
    while (temp_user) {
        if (temp_user->check_function(port_info->port, pkt_hdr, pkt_buf) == true) {
            if (NULL == user) {
                user = temp_user;
            } else {
                user = user->priority > temp_user->priority ? user : temp_user;
            }
        }
        temp_user = temp_user->next;
    }
    return user;
}

/* deal mux ready to read event */
static void race_handle_input_data(race_general_msg_t *p_msg)
{
    race_port_info_t *port_info = NULL;
    uint8_t *race_pkt = NULL;
    uint32_t rev_len = 0;
    mux_buffer_t mux_buf;
    race_msg_mux_data_ready_t *p_data;
    race_pkt_relay_check_t relay;

    if (NULL == p_msg || NULL == p_msg->msg_data) {
        return;
    }
    p_data = (race_msg_mux_data_ready_t *)p_msg->msg_data;
    port_info = race_search_port(p_msg->dev_t);
    if (NULL == port_info) {
        race_mem_free(p_msg->msg_data);
        return;
    }
    race_pkt = (uint8_t *)race_mem_alloc(p_data->data_len);
    if (NULL == race_pkt) {
        assert(0 && "ERROR: race_handle_input_data, alloc data fail!");
    }
    mux_buf.p_buf = race_pkt;
    mux_buf.buf_size = p_data->data_len;
    if (race_receive_data(&rev_len, p_data->handle, &mux_buf) != true) {
        race_mem_free(race_pkt);
        race_mem_free(p_msg->msg_data);
        return;
    }
    if (p_data->data_len != rev_len) {
        race_mem_free(race_pkt);
        race_mem_free(p_msg->msg_data);
        assert(0 && "ERROR: race_handle_input_data, pkt_len != rev_len");
        return;
    }

    relay.port = port_info->port;
    relay.port_type = port_info->port_type;
    memcpy(&relay.pkt_hdr, race_pkt, sizeof(RACE_COMMON_HDR_STRU));
    race_relay_check(&relay);

    if (relay.relay_info.is_relay_pkt) { // need relay
        LOG_INF("[race_core] race_handle_input_data, relay pkt: port(%d) --> port(%d)", relay.relay_info.from_port, relay.relay_info.to_port);
#if defined RACE_USB_RELAY_ENABLE
        race_usb_relay_set_flag_by_src_port(relay.relay_info.from_port, relay.relay_info.to_port, race_pkt);
#endif
        if (RACE_INVALID_PORT != relay.relay_info.to_port) {
            race_send_data_to_port(relay.relay_info.to_port, race_pkt, p_data->data_len);
        }
#if RACE_DEBUG_INFO_ENABLE
        port_info->debug.total_relay_pkt++;
#endif
    } else {
        race_cmd_local_handler(port_info->port, race_pkt);
    }
    race_mem_free(race_pkt);
    race_mem_free(p_msg->msg_data);
}

static void race_cmd_local_handler(race_port_t port, uint8_t *race_pkt)
{
    race_send_pkt_t *pEvt = NULL;
    race_pkt_t *pCmd = (race_pkt_t *)race_pkt;
    pEvt = RACE_CmdHandler(pCmd, (uint8_t)port);
    if (pEvt) {
        race_send_data_to_port(port, (uint8_t *)&pEvt->race_data, pEvt->length);
        race_mem_free(pEvt);
    }
}

static void race_handle_ext_cmd(race_general_msg_t *p_msg)
{
    if (NULL == p_msg || MSG_ID_RACE_LOCAL_RSP_NOTIFY_IND != p_msg->msg_id || NULL == p_msg->msg_data) {
        return ;
    }
    race_cmd_local_handler(p_msg->dev_t, p_msg->msg_data);
    race_mem_free(p_msg->msg_data);
}
#ifdef AIR_BTD_IC_MANDATORY_G1
static uint32_t race_tx_default(uint32_t mux_handle, uint8_t *p_data, uint32_t len)
{
    uint32_t sent_len;
    mux_buffer_t mux_buffer = {p_data, len};
    mux_status_t res;
    mux_ctrl_para_t mux_para;
    uint32_t ts_start = 0;
    uint32_t ts_curr = 0;
    uint32_t total_sent_len = 0;
    if ((p_data == NULL) || (len == 0)) {
        return 0;
    }
    uint8_t port = RACE_GET_PORT_BY_MUX_HANDLE(mux_handle);
    if (RACE_PORT_IS_UART(port)) {
        res = mux_control(RACE_GET_PORT_BY_MUX_HANDLE(mux_handle), MUX_CMD_GET_TX_AVAIL, &mux_para);
        if ((MUX_STATUS_OK != res) && (mux_para.mux_get_tx_avail.ret_size < len)) {
            return 0;
        }

        mux_buffer.buf_size = len;
        mux_buffer.p_buf = p_data;
        res = mux_tx(mux_handle, &mux_buffer, 1, &sent_len);
        // LOG_INF("race_tx_default, mux_tx buf_size:%d,res:%d", mux_buffer.buf_size,res);

        if ((MUX_STATUS_OK == res) || (MUX_STATUS_ERROR_BUSY == res))  {
            total_sent_len = sent_len;
        } else {
            return 0;
        }
    } else {
        hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_1M, &ts_start);
        while(len > total_sent_len) {
            hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_1M, &ts_curr);
            if (ts_curr - ts_start > RACE_TX_MAX_RETRY_TIME) {
                break;
            }
            res = mux_control(RACE_GET_PORT_BY_MUX_HANDLE(mux_handle), MUX_CMD_GET_TX_AVAIL, &mux_para);
            if (MUX_STATUS_OK != res) {
                break;
            }
            mux_buffer.buf_size = mux_para.mux_get_tx_avail.ret_size > (len - total_sent_len) ? (len - total_sent_len) : mux_para.mux_get_tx_avail.ret_size;
            mux_buffer.p_buf = p_data + total_sent_len;
            if (mux_buffer.buf_size <= 0) {
                continue;
            }
            res = mux_tx(mux_handle, &mux_buffer, 1, &sent_len);
            if (MUX_STATUS_OK == res) {
                total_sent_len += sent_len;
            } else if (MUX_STATUS_USER_TX_BUF_SIZE_NOT_ENOUGH == res) {
                continue;
            } else {
                break;
            }
        }
    }
#if (RACE_DEBUG_PRINT_ENABLE)
    race_dump_data(p_data, len, "race_tx_default");
#endif
    LOG_INF("race_tx_default, data_len:%d, tx_len:%d", len, total_sent_len);
    return total_sent_len;
}
#else
static uint32_t race_tx_default(uint32_t mux_handle, uint8_t *p_data, uint32_t len)
{
    uint32_t sent_len;
    mux_buffer_t mux_buffer = {p_data, len};
    mux_status_t res;
    mux_ctrl_para_t mux_para;
    uint32_t ts_start = 0;
    uint32_t ts_curr = 0;
    uint32_t total_sent_len = 0;

    hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_1M, &ts_start);
    while(len > total_sent_len) {
        hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_1M, &ts_curr);
        if (ts_curr - ts_start > RACE_TX_MAX_RETRY_TIME) {
            break;
        }
        res = mux_control(RACE_GET_PORT_BY_MUX_HANDLE(mux_handle), MUX_CMD_GET_TX_AVAIL, &mux_para);
        if (MUX_STATUS_OK != res) {
            break;
        }
        mux_buffer.buf_size = mux_para.mux_get_tx_avail.ret_size > (len - total_sent_len) ? (len - total_sent_len) : mux_para.mux_get_tx_avail.ret_size;
        mux_buffer.p_buf = p_data + total_sent_len;
        if (mux_buffer.buf_size <= 0) {
            continue;
        }
        res = mux_tx(mux_handle, &mux_buffer, 1, &sent_len);
        if (MUX_STATUS_OK == res) {
            total_sent_len += sent_len;
        } else if (MUX_STATUS_USER_TX_BUF_SIZE_NOT_ENOUGH == res) {
            continue;
        } else {
            break;
        }
    }
#if (RACE_DEBUG_PRINT_ENABLE)
    race_dump_data(p_data, len, "race_tx_default");
#endif
    LOG_INF("race_tx_default, data_len:%d, tx_len:%d", len, total_sent_len);
    return total_sent_len;
}
#endif
static bool race_rx_default(mux_handle_t handle, mux_buffer_t *buffer, uint32_t *receive_done_data_len)
{
    mux_status_t res = mux_rx(handle, buffer, receive_done_data_len);
    if (MUX_STATUS_OK == res) {
        return true;
    } else {
        LOG_INF("race_rx_default, mux_error:%d", res);
        return false;
    }
}

/* check user for "RACE_CMD" */
static bool race_check_default_user(race_port_t port, RACE_COMMON_HDR_STRU *pkt_hdr, race_mux_buffer_t *pkt_buf)
{
    if (NULL == pkt_hdr || NULL == pkt_buf) {
        return false;
    }
    if (RACE_IS_VALID_ID(pkt_hdr->pktId.value) && RACE_IS_VALID_TYPE(pkt_hdr->type) && RACE_IS_VALID_LEN(pkt_hdr->length)) {
        return true;
    }
    return false;
}

static void race_sleep_timer_init(void)
{
#ifdef HAL_SLEEP_MANAGER_ENABLED
#ifdef AIR_BTD_IC_PREMIUM_G1
    if (g_race_sleep_ctrl.sleep_handle == 0xFF) {
        g_race_sleep_ctrl.sleep_handle = hal_sleep_manager_set_sleep_handle("race");
        LOG_INF("[race_core] race_sleep_timer_init, handle[%d]", g_race_sleep_ctrl.sleep_handle);
    }
#endif
    k_timer_init(&g_race_sleep_ctrl.sleep_lock_timer, race_sleep_lock_timer_callback, NULL);
    k_timer_start(&g_race_sleep_ctrl.sleep_lock_timer, K_SECONDS(10), K_NO_WAIT);
#endif
}

#ifdef HAL_SLEEP_MANAGER_ENABLED
static void race_sleep_lock_timer_callback(struct k_timer *timer)
{
    if (NULL == timer) {
        LOG_INF("[race_core]race lock sleep timer is null");
        return;
    }
#ifdef AIR_BTD_IC_MANDATORY_G1
    hal_sleep_manager_unlock_sleep(SLEEP_LOCK_RACE_CMD);
#else
    if (hal_sleep_manager_is_sleep_handle_alive(g_race_sleep_ctrl.sleep_handle) == true) {
        hal_sleep_manager_unlock_sleep(g_race_sleep_ctrl.sleep_handle);
        LOG_INF("[race_core] race_sleep_lock_timer_callback, unlock");
    }
#endif
}
#endif

static void race_relay_check(race_pkt_relay_check_t *check_info)
{
    race_pkt_relay_info_t *relay_info = NULL;
    uint16_t i;
    if (NULL == check_info) {
        return ;
    }
    relay_info = &check_info->relay_info;
    relay_info->is_relay_pkt = false;
    relay_info->from_port = check_info->port;
    for (i = 0; i < RACE_RELAY_CHECK_HDL_MAX; i++) {
        if (g_race_relay_check_hdl_tbl[i]) {
            if (g_race_relay_check_hdl_tbl[i](relay_info, check_info->port, check_info->port_type, &check_info->pkt_hdr) == true) {
                return ;
            }
        }
    }
}

static race_protocol_type_t race_get_protocol_type(mux_buffer_t buffers[], uint32_t buffers_counter)
{
    race_mux_buffer_t pkt_buf;
    race_protocol_type_t protocol = PROTOCOL_INVALID;
    race_multi_buffer_init(&pkt_buf, buffers, buffers_counter);
    race_protocol_fetch(&protocol, 1, &pkt_buf);
    return protocol;
}

/*
* parse hci cmd for controller debug, tool -> host -> controller
* "HCI_CMD" handle will be open in atci_bt_relay_mux_init
*/
static void race_parse_hci(mux_handle_t *handle, uint32_t *consume_len, uint32_t *package_len,
    race_mux_buffer_t *pkt_buf, void *user_data)
{
    uint32_t log = 0;
    uint8_t hci_header = 0;
    uint16_t hci_len = 0;
    uint8_t u8_data = 0;
    uint16_t u16_data = 0;
    bool res;
    mux_handle_t hci_handle;
    race_port_info_t *p_info = (race_port_info_t *)user_data;

    *consume_len = pkt_buf->total_length;
    *package_len = 0;
    if (mux_query_user_handle(p_info->port, "HCI_CMD", &hci_handle) != MUX_STATUS_OK) {
        log |= 1;
        goto HCI_PARSE_END;
    }

    /* step1. parse header */
    if (race_protocol_fetch(&hci_header, 1, pkt_buf) == false) {
        log |= 2;
        goto HCI_PARSE_END;
    }

    /* step2. parse reserved data */
    res = false;
    if (PROTOCOL_HCI_CMD == hci_header || PROTOCOL_HCI_ACL == hci_header) {
        res = race_protocol_fetch((uint8_t *)&u16_data, 2, pkt_buf);
    } else if (PROTOCOL_HCI_EVT == hci_header) {
        res = race_protocol_fetch(&u8_data, 1, pkt_buf);
    }
    if (false == res) {
        log |= 4;
        goto HCI_PARSE_END;
    }

    /* step3. parse length */
    res = false;
    if (PROTOCOL_HCI_CMD == hci_header || PROTOCOL_HCI_EVT == hci_header) {
        res = race_protocol_fetch(&u8_data, 1, pkt_buf);
        hci_len = u8_data;
    } else if (PROTOCOL_HCI_ACL == hci_header) {
        res = race_protocol_fetch((uint8_t *)&u16_data, 2, pkt_buf);
        hci_len = u16_data;
    }
    if (false == res) {
        log |= 8;
        goto HCI_PARSE_END;
    }

    /* step4. calculate total length */
    if (PROTOCOL_HCI_CMD == hci_header) {
        hci_len += HCI_CMD_HEADER_LEN;
    } else if (PROTOCOL_HCI_ACL == hci_header) {
        hci_len += HCI_ACL_HEADER_LEN;
    } else if (PROTOCOL_HCI_EVT == hci_header) {
        hci_len += HCI_EVT_HEADER_LEN;
    }

    *handle = hci_handle;
    *consume_len = 0;
    *package_len = hci_len;

HCI_PARSE_END:
    LOG_INF("[race_core] race_parse_hci: handle[0x%x], pack_len:%d, log:%x", hci_handle, hci_len, log);
}

static void race_parse(mux_handle_t *handle, uint32_t *consume_len, uint32_t *package_len,
    race_mux_buffer_t *pkt_buf, void *user_data)
{
    race_port_info_t *p_info = (race_port_info_t *)user_data;
    RACE_COMMON_HDR_STRU pkt_hdr;
    race_port_user_t *user = NULL;
    uint32_t header_drop_size = 0;
    uint32_t pkt_len = 0;

    if (pkt_buf->total_length < RACE_PROTOCOL_MIN_BYTE) {
        *consume_len = 0;
        *package_len = 0;

#if RACE_DEBUG_INFO_ENABLE
        p_info->debug.current_pkt_irq_cnt++;
        if (p_info->debug.current_pkt_irq_cnt > 30) {
            LOG_ERR("[race_core] ERROR: Port[%d] RX connect to GND", p_info->port);
        }
#endif
        return;
    }
    if (false == race_protocol_fetch_header(&pkt_hdr, pkt_buf)) {
        assert(0 && "ERROR: race_mux_rx_protocol_callback, fetch header fail !");
        return;
    }

#if RACE_DEBUG_INFO_ENABLE
    p_info->debug.current_pkt_irq_cnt = 0;
#endif
    user = race_find_pkt_user(p_info, &pkt_hdr, pkt_buf);
    if (NULL != user && user->status == RACE_USER_ACTIVE) {
        pkt_len = pkt_hdr.length + RACE_PROTOCOL_HEADER_LEN;
        if (user->get_drop_size) {
            header_drop_size = user->get_drop_size(p_info->port, &pkt_hdr, pkt_buf);
        }

        *handle = user->handle;
        *consume_len = header_drop_size > pkt_buf->total_length ? pkt_buf->total_length : header_drop_size;
        *package_len = pkt_len >= header_drop_size ? pkt_len - header_drop_size : 0;

#if RACE_DEBUG_INFO_ENABLE
        p_info->debug.total_valid_pkt_len += *package_len;
#endif
        LOG_INF("[race_core][debug] race_mux_rx_protocol_callback, user handle:0x%x, header_drop:%d, pkt_len:%d",
            user->handle, header_drop_size, *package_len);
    } else {
        *consume_len = pkt_buf->total_length;
        *package_len = 0;
#if (RACE_DEBUG_PRINT_ENABLE)
        uint32_t log_size = pkt_buf->mux_buffer->buf_size;
        race_dump_data(pkt_buf->mux_buffer->p_buf, log_size > 10 ? 10 : log_size, "Drop unknown user:");
#endif
    }

}


/*
* BTA-38607, avoid re-entry
*/
#define RACE_LOCK_RX_PROTOCOL(flag)         ((flag) |= RACE_PORT_FLAG_RX_PROTOCOL_LOCK)
#define RACE_UNLOCK_RX_PROTOCOL(flag)       ((flag) &= ~RACE_PORT_FLAG_RX_PROTOCOL_LOCK)
#define RACE_IS_RX_PROTOCOL_LOCKED(flag)    (((flag) & RACE_PORT_FLAG_RX_PROTOCOL_LOCK) != 0)

static void race_mux_rx_protocol_callback(mux_handle_t *handle, mux_buffer_t buffers[], uint32_t buffers_counter,
    uint32_t *consume_len, uint32_t *package_len, void *user_data)
{
    race_mux_buffer_t pkt_buf = {0}; // [init] Initialize struct to zero
    race_protocol_type_t protocol_type = 0; // [init] Initialize variable
    race_port_info_t *p_info = (race_port_info_t *)user_data;

    if (NULL == p_info) { // [security] Check for NULL pointer instead of assert
        LOG_INF("[race_core][debug] race rx irq p_info is NULL");
        return;
    }

    if (RACE_IS_RX_PROTOCOL_LOCKED(p_info->port_flag)) {
        return;
    }
    RACE_LOCK_RX_PROTOCOL(p_info->port_flag);

    protocol_type = race_get_protocol_type(buffers, buffers_counter);
    race_multi_buffer_init(&pkt_buf, buffers, buffers_counter);
    LOG_INF("[race_core][debug] race rx irq... port[%d], len[%d]", p_info->port, pkt_buf.total_length);

#if RACE_DEBUG_INFO_ENABLE
    p_info->debug.total_irq_cnt++;
#endif

    if (NULL != p_info->rx_protocol_handler) {
        if (RACE_RX_PROTOCOL_RESULT_SUCCESS == p_info->rx_protocol_handler(handle, buffers, buffers_counter, consume_len, package_len, user_data)) {
            RACE_UNLOCK_RX_PROTOCOL(p_info->port_flag);
            return;
        }
    }

    if (PROTOCOL_RACE == protocol_type || PROTOCOL_RACE_FOTA == protocol_type) {
        race_parse(handle, consume_len, package_len, &pkt_buf, user_data);
    } else if (PROTOCOL_HCI_CMD == protocol_type || PROTOCOL_HCI_EVT == protocol_type || PROTOCOL_HCI_ACL == protocol_type) {
        race_parse_hci(handle, consume_len, package_len, &pkt_buf, user_data);
    } else {
        *consume_len = pkt_buf.total_length;
        *package_len = 0;
#if (RACE_DEBUG_PRINT_ENABLE)
        race_dump_data(buffers[0].p_buf, buffers[0].buf_size > 10 ? 10 : buffers[0].buf_size, "unknown protocol:");
#endif
    }

    RACE_UNLOCK_RX_PROTOCOL(p_info->port_flag);
}

#define RACE_LOCK_TX_PROTOCOL(flag)         (flag |= RACE_PORT_FLAG_TX_PROTOCOL_LOCK)
#define RACE_UNLOCK_TX_PROTOCOL(flag)       (flag &= ~RACE_PORT_FLAG_TX_PROTOCOL_LOCK)
#define RACE_IS_TX_PROTOCOL_LOCKED(flag)    ((flag & RACE_PORT_FLAG_TX_PROTOCOL_LOCK) != 0)

static void race_mux_tx_protocol_callback(mux_handle_t handle, const mux_buffer_t payload[], uint32_t buffers_counter,
    mux_buffer_t *head, mux_buffer_t *tail, void *user_data)
{
#if 1
    race_port_info_t *p_info = (race_port_info_t *)user_data;
    race_port_user_t *user = NULL;

    // [input validation] Check input pointers for NULL
    if ((NULL == p_info) || (NULL == head) || (NULL == tail) || (NULL == payload)) {
        LOG_INF("[race_core][debug] race tx protocol p_info is NULL");
        // [boundary check] Return if any input pointer is NULL
        return;
    }

    if (RACE_IS_TX_PROTOCOL_LOCKED(p_info->port_flag)) {
        return;
    }
    RACE_LOCK_TX_PROTOCOL(p_info->port_flag);

    if (p_info->tx_protocol_handler) {
        if (p_info->tx_protocol_handler(handle, payload, buffers_counter, head, tail, user_data) == RACE_TX_PROTOCOL_RESULT_SUCCESS) {
            RACE_UNLOCK_TX_PROTOCOL(p_info->port_flag);
            return;
        }
    }

    user = race_search_user_by_handle(handle);
    if ((NULL != user) && (NULL != user->tx_protocol_handler)) {
        user->tx_protocol_handler(handle, payload, buffers_counter, head, tail, user_data);
    } else {
        head->p_buf = NULL;
        head->buf_size = 0;
        tail->p_buf = NULL;
        tail->buf_size = 0;
    }

    RACE_UNLOCK_TX_PROTOCOL(p_info->port_flag);
#endif
}

static void race_mux_callback(mux_handle_t handle, mux_event_t event, uint32_t data_len, void *user_data)
{
    race_general_msg_t race_msg = {0};
    race_port_user_t *user = NULL;
    user = race_search_user_by_handle(handle);
    if (NULL == user) { // [secure] Remove assert for external modules, return early
        LOG_INF("[race_core][error] race_mux_callback, user is NULL! handle:0x%x", handle);
        return;
    }
    LOG_INF("[race_core][debug] race_mux_callback, handle:0x%x, event:%d, data_len:%d", handle, event, data_len);
    switch (event) {
        case MUX_EVENT_READY_TO_READ: {
            race_msg_mux_data_ready_t *pmsg = NULL;
            race_start_sleep_lock_timer();
            pmsg = (race_msg_mux_data_ready_t *)race_mem_alloc(sizeof(race_msg_mux_data_ready_t));
            if (NULL == pmsg) {
                assert(pmsg && "ERROR: race_mux_callback, memory not enough !");
                break;
            }
            pmsg->handle = handle;
            pmsg->data_len = data_len;
            race_msg.msg_id = MSG_ID_MUX_DATA_READY_TO_READ;
            race_msg.dev_t = RACE_GET_PORT_BY_MUX_HANDLE(handle);
            race_msg.msg_data = (uint8_t *)pmsg;
            if (race_send_msg(&race_msg) != RACE_ERRCODE_SUCCESS) {
                race_mem_free(pmsg);
                race_msg.msg_data = NULL;
            }
            break;
        }
        case MUX_EVENT_WAKEUP_FROM_SLEEP:
            race_start_sleep_lock_timer();
            break;
#if 0
        case MUX_EVENT_TRANSMISSION_DONE:
            break;
#endif
        default:
            break;
    }
    if (user->mux_event_post_handler) {
        user->mux_event_post_handler(handle, event, data_len, user_data);
    }
}
#if RACE_DEBUG_INFO_ENABLE
static void race_idle_timer_handler(TimerHandle_t xtimer)
{
    race_general_msg_t msg;
    msg.msg_id = MSG_ID_RACE_IDLE_EVENT;
    race_send_msg(&msg);
}

static void race_idle_init(void)
{
    g_race_idle_timer = xTimerCreate("race_idle_timer", (RACE_IDLE_TIMER_PERIOD / portTICK_PERIOD_MS), pdTRUE, NULL, race_idle_timer_handler);
    xTimerStart(g_race_idle_timer, 0);
    race_register_general_msg_hdl(MSG_ID_RACE_IDLE_EVENT, race_idle_event_handler);
}

static void race_idle_event_handler(race_general_msg_t *msg)
{

    race_port_list_t *node = g_race_port_list;
    while(node) {
        LOG_INF("[race_core] race port info: port:%d, type:%d, status:%d, flag:0x%x",
            node->port_info.port,
            node->port_info.port_type,
            node->port_info.port_status,
            node->port_info.port_flag);
        LOG_INF("[race_core] race port debug info: irq cnt:%d, drop len:%d, rx len:%d, tx cnt:%d, tx fail cnt:%d, tx_byte:%d, relay_pkt:%d",
            node->port_info.debug.total_irq_cnt,
            node->port_info.debug.total_drop_data_len,
            node->port_info.debug.total_valid_pkt_len,
            node->port_info.debug.total_tx_cnt,
            node->port_info.debug.total_tx_fail_cnt,
            node->port_info.debug.tx_suc_byte,
            node->port_info.debug.total_relay_pkt
            );
        node = node->next;
    }
}
#endif

/**************************************************************************************************
* Public Functions for register callback
**************************************************************************************************/

void race_register_general_msg_hdl(uint32_t msg_id, race_general_msg_hdl_t hdl)
{
    if (msg_id < MSG_ID_RACE_END) {
        g_race_msg_hdl_tbl[msg_id] = hdl;
    } else {
        assert(0 && "ERROR: race_register_general_msg_hdl, msg_id out of range");
    }
}

bool race_register_relay_check_handler(race_check_relay_t hdl)
{
    uint16_t i;
    if (NULL == hdl) {
        return false;
    }
    for (i = 0; i < RACE_RELAY_CHECK_HDL_MAX; i++) {
        if (g_race_relay_check_hdl_tbl[i] == hdl) {
            return true;
        } else if (NULL == g_race_relay_check_hdl_tbl[i]) {
            g_race_relay_check_hdl_tbl[i] = hdl;
            return true;
        }
    }
    assert(0 && "ERROR: race_register_relay_check_handler, out of memory !");
    return false;
}

void race_unregister_relay_check_handler(race_check_relay_t hdl)
{
    uint16_t i;
    if (NULL == hdl) {
        return;
    }
    for (i = 0; i < RACE_RELAY_CHECK_HDL_MAX; i++) {
        if (g_race_relay_check_hdl_tbl[i] == hdl) {
            g_race_relay_check_hdl_tbl[i] = NULL;
            return;
        }
    }
}

/**************************************************************************************************
* Public Functions
**************************************************************************************************/

/* receive data from MUX */
bool race_receive_data(uint32_t *receive_done_data_len, uint32_t mux_handle, mux_buffer_t *buffer)
{
    // [init] Initialize variables
    race_port_info_t *p_info = NULL;
    bool res = false; // [init] Status variable initialized as 'fail'

    // [input validation] Validate input pointers
    if ((NULL == receive_done_data_len) || (NULL == buffer)) {
        LOG_INF("[race_core] race_receive_data buffer || receive_done_data_len is null");
        // [logging] Do not log sensitive information
        return false;
    }

    p_info = race_search_port(RACE_GET_PORT_BY_MUX_HANDLE(mux_handle));
    if (NULL == p_info) {  // [boundary check] Added check to prevent NULL dereference
        LOG_INF("[race_core] race_receive_data p_info is null");
        // [logging] Do not log sensitive information
        return false;
    }
    if (NULL == p_info->rx) {  // [boundary check] Added check to prevent NULL dereference
        LOG_INF("[race_core] race_receive_data p_info->rx is null");
        return false;
    }

    // [range check] Ensure buffer->buf_size does not cause OOB access
    if (0 == buffer->buf_size) {
        LOG_INF("[race_core] race_receive_data buffer->buf_size is 0");
        return false;
    }

    res = p_info->rx(mux_handle, buffer, receive_done_data_len);
    LOG_INF("[race_core] race_receive_data, rx_hdl:0x%x, mux_handle:0x%x, buf_size:%d, rev_size:%d, res:%d",
        (uint32_t)p_info->rx, mux_handle, buffer->buf_size, *receive_done_data_len, res);
    return res;
}

/* msg will be copied into message queue and should be freed after this API returns if it's allocated dynamically. */
RACE_ERRCODE race_send_msg(race_general_msg_t *p_msg)
{
    uint32_t cur_num = 0;
    bool res = false;
    if (NULL == p_msg) {
        return RACE_ERRCODE_PARAMETER_ERROR;
    }
#if 0
    if (0 == g_race_queue) {
        assert(0 && "ERROR: race_send_msg, race queue not init !");
        return RACE_ERRCODE_FAIL;
    }
#endif
    cur_num = race_queue_get_msg_num(&race_queue);

    if (cur_num > (RACE_MSG_QUEUE_MAX_SIZE >> 1)) {
        LOG_WRN("[race_core] WARNING: race_send_msg, queue size[%d]", cur_num);
        assert((cur_num < RACE_MSG_QUEUE_MAX_SIZE) && "ERROR: race_send_msg, queue size overflow !");
    }
    res = race_queue_send(&race_queue, (void *)p_msg, K_NO_WAIT);
    //assert(res);
    return res ? RACE_ERRCODE_SUCCESS : RACE_ERRCODE_FAIL;
}

race_port_info_t *race_search_port(race_port_t port)
{
    race_port_list_t *node = g_race_port_list;
    while (node) {
        if (node->port_info.port == port) {
            return &node->port_info;
        } else {
            node = node->next;
        }
    }
    return NULL;
}

uint16_t race_search_port_type(race_port_info_t **res_buf, uint16_t res_cnt, race_port_type_t port_type)
{
    uint16_t ret_cnt = 0;
    race_port_list_t *node = g_race_port_list;
    if (NULL == res_buf || res_cnt <= 0) {
        return 0;
    }
    while (node) {
        if (node->port_info.port_type == port_type) {
            if (RACE_PORT_INIT_SUC == node->port_info.port_status && ret_cnt < res_cnt) {
                res_buf[ret_cnt] = &node->port_info;
                ret_cnt++;
                if (ret_cnt >= res_cnt) {
                    break;
                }
            }
        }
        node = node->next;
    }
    return ret_cnt;
}

race_port_user_t *race_search_user_by_name(race_port_info_t *port_info, const char *user_name)
{
    race_port_user_t *user = NULL;
    if (NULL == port_info || NULL == port_info->user_list || NULL == user_name) {
        return NULL;
    }

    user = port_info->user_list;
    while (NULL != user) {
        if (strcmp(user_name, user->user_name) == 0) {
            return user;
        } else {
            user = user->next;
        }
    }
    return NULL;
}

mux_handle_t race_get_tx_handle_by_port(race_port_t port)
{
    mux_handle_t handle;
    if (mux_query_user_handle(port, g_race_default_user_name, &handle) == MUX_STATUS_OK) {
        return handle;
    }
    return RACE_MUX_HANDLE_INVALID;
}

uint32_t race_send_data(uint32_t mux_handle, uint8_t *p_data, uint32_t len)
{
    uint32_t res;
    race_port_info_t *p_info = race_search_port(RACE_GET_PORT_BY_MUX_HANDLE(mux_handle));
    if (p_info == NULL || p_info->tx == NULL) {
        res = race_tx_default(mux_handle, p_data, len);
    } else {
        res = p_info->tx(mux_handle, p_data, len);
    }

#if RACE_DEBUG_INFO_ENABLE
    if (p_info) {
        p_info->debug.total_tx_cnt++;
        p_info->debug.tx_suc_byte += res;
        if (res < len) {
            p_info->debug.total_tx_fail_cnt++;
        }
    }
#endif

    return res;
}

uint32_t race_port_send_data_imp(uint32_t mux_handle, uint8_t *p_data, uint32_t len)
{
    uint32_t res;
#if 1
#ifdef RACE_FOTA_ADAPTIVE_MODE_ENABLE
    race_cmd_post_process((race_pkt_t *)p_data);
#endif

#if defined RACE_USB_RELAY_ENABLE
    race_usb_relay_add_flag_for_pkt(mux_handle, p_data);
#endif
#endif

    res = race_send_data(mux_handle, p_data, len);
    LOG_INF("[race_core] race_port_send_data_imp, handle:0x%x, data_len:%d, sent_len:%d", mux_handle, len, res);
    return res;
}

uint32_t race_send_data_to_port(race_port_t port, uint8_t *data, uint32_t len)
{
    mux_handle_t handle = race_get_tx_handle_by_port(port);
    if (handle != RACE_MUX_HANDLE_INVALID) {
        return race_port_send_data_imp(handle, data, len);
    }
    return 0;
}

RACE_ERRCODE race_init_port(race_port_init_t *config)
{
    race_port_t port = RACE_INVALID_PORT;
    race_port_type_t port_type = RACE_PORT_TYPE_INVALID;
    mux_port_setting_t *setting = NULL;
    race_port_info_t *p_info = NULL;
    uint32_t num = 0;
    RACE_ERRCODE res = RACE_ERRCODE_FAIL;
    uint8_t log_step = 0;

    if (NULL == config) {
        res = RACE_ERRCODE_PARAMETER_ERROR;
        goto INIT_EXIT;
    }
    port = config->port;
    port_type = config->port_type;
    setting = config->port_settings;

    p_info = race_search_port(port);
    if (p_info) {
        if (p_info->port_status == RACE_PORT_INIT_SUC) {
            if (p_info->port_type != port_type) {
                // another type of this port has been initialized
                res = RACE_ERRCODE_CONFLICT;
            } else {
                res = RACE_ERRCODE_SUCCESS;
            }
            goto INIT_EXIT;
        } else {
            if (NULL != p_info->user_list) {
                assert(0 && "ERROR: race_init_port, detect memory leak !");  // memory leak
            }
            memset(p_info, 0, sizeof(race_port_info_t));
            p_info->port = port;
            p_info->port_type = port_type;
        }
    } else {
        p_info = race_create_port_info(port, port_type);
        if (NULL == p_info) {
            LOG_INF("[race_core] race_init_port, race_create_port_info fail");
            res = RACE_ERRCODE_NOT_ENOUGH_MEMORY;
            goto INIT_EXIT;
        }
        //assert(p_info && "ERROR: race_init_port, out of memory !");
    }
    log_step = 1;
    p_info->tx = config->tx_function ? config->tx_function : race_tx_default;
    p_info->rx = config->rx_function ? config->rx_function : race_rx_default;
    p_info->tx_protocol_handler = config->tx_protocol_handler;
    p_info->rx_protocol_handler = config->rx_protocol_handler;

    if (MUX_STATUS_OK == mux_query_port_user_number(port, &num)) { // check this port is already inited or not
        p_info->port_flag |= RACE_PORT_FLAG_INITED_BY_OTHERS;
        p_info->port_status = RACE_PORT_INIT_SUC;
        res = RACE_ERRCODE_SUCCESS;
        goto INIT_EXIT;
    }
    log_step = 2;

    if (NULL == setting) {
        race_delete_port_info(p_info);
        res = RACE_ERRCODE_PARAMETER_ERROR;
        goto INIT_EXIT;
    }
    log_step = 3;
    mux_protocol_t protocol = {race_mux_tx_protocol_callback, race_mux_rx_protocol_callback, (void *)p_info};
    mux_status_t mux_res = mux_init(port, setting, &protocol);
    if (MUX_STATUS_OK == mux_res) {
        p_info->port_status = RACE_PORT_INIT_SUC;
        res = RACE_ERRCODE_SUCCESS;
    } else if (MUX_STATUS_ERROR_INITIATED == mux_res) {
        p_info->port_flag |= RACE_PORT_FLAG_INITED_BY_OTHERS;
        p_info->port_status = RACE_PORT_INIT_SUC;
        res = RACE_ERRCODE_SUCCESS;
    } else {
        race_delete_port_info(p_info);
        res = RACE_ERRCODE_FAIL;
    }

INIT_EXIT:
    LOG_INF("[race_core] race_init_port, log_step:%d, port:%d, type:%d, res:%d", log_step, port, port_type, res);
    return res;
}

RACE_ERRCODE race_open_port(race_user_config_t *config)
{
    race_port_t port = RACE_INVALID_PORT;
    race_port_info_t *p_info = NULL;
    mux_status_t mux_res = MUX_STATUS_ERROR;
    race_port_user_t *p_user = NULL;
    const char *user_name = NULL;
    race_mux_event_callback_t mux_event_callback;
    RACE_ERRCODE res = RACE_ERRCODE_FAIL;

    if (NULL == config) {
        res = RACE_ERRCODE_PARAMETER_ERROR;
        goto OPEN_EXIT;
    }
    port = config->port;
    user_name = config->user_name ? config->user_name : g_race_default_user_name;
    mux_event_callback = config->mux_event_handler ? config->mux_event_handler : race_mux_callback;

    p_info = race_search_port(config->port);
    if (NULL == p_info || RACE_PORT_INIT_SUC != p_info->port_status) {
        // port has not been initialized
        res = RACE_ERRCODE_NOT_INITIALIZED;
        goto OPEN_EXIT;
    }

    p_user = race_search_user_by_name(p_info, user_name);
    if (p_user) {
        if (RACE_USER_ACTIVE == p_user->status) {
            res = RACE_ERRCODE_SUCCESS;
            goto OPEN_EXIT;
        } else {
            race_delete_user(p_info, p_user);
        }
    }

    p_user = race_create_user_for_port(p_info);
    if (NULL == p_user) {
        res = RACE_ERRCODE_NOT_ENOUGH_MEMORY;
        goto OPEN_EXIT;
    }
    mux_res = mux_open(port, user_name, &p_user->handle, mux_event_callback, p_info);
    if (MUX_STATUS_OK != mux_res) {
        race_delete_user(p_info, p_user);
        res = RACE_ERRCODE_NOT_SUPPORT;
        goto OPEN_EXIT;
    }
    p_user->status = RACE_USER_ACTIVE;
    p_user->user_name = user_name;
    p_user->mux_event_post_handler = config->mux_event_post_handler;
    p_user->check_function = config->check_function ? config->check_function : race_check_default_user;
    p_user->priority = config->priority;
    p_user->get_drop_size = config->get_drop_size;
    p_user->tx_protocol_handler = config->tx_protocol_handler;
    res = RACE_ERRCODE_SUCCESS;

OPEN_EXIT:
    LOG_INF("[race_core] race_open_port, port:%d, res:%d", port, res);
    return res;
}

RACE_ERRCODE race_close_port(race_port_t port, const char *user_name)
{
    const char *user = NULL;
    race_port_info_t *port_info = NULL;
    race_port_user_t *p_user = NULL;
    mux_status_t mux_res = MUX_STATUS_ERROR;

    port_info = race_search_port(port);
    if (NULL == port_info || RACE_PORT_INIT_SUC != port_info->port_status) {
        return RACE_ERRCODE_SUCCESS;
    }
    user = user_name ? user_name : g_race_default_user_name;
    LOG_INF("[race_core] race_close_port, port:%d", port);

    p_user = race_search_user_by_name(port_info, user);
    if (NULL == p_user) {
        return RACE_ERRCODE_SUCCESS;
    } else {
        mux_res = mux_close(p_user->handle);
        race_delete_user(port_info, p_user);
    }
    if (NULL == port_info->user_list) {
        mux_res = mux_deinit(port);
        if (MUX_STATUS_OK == mux_res ||
            (MUX_STATUS_ERROR_SOME_USER_STILL_OPEN == mux_res && (RACE_PORT_FLAG_INITED_BY_OTHERS & port_info->port_flag))) {
            race_delete_port_info(port_info);
        }
    }
    return RACE_ERRCODE_SUCCESS;
}

RACE_ERRCODE race_close_port_for_all_user(race_port_t port)
{
    bool res;
    race_port_info_t *port_info = NULL;
    race_port_user_t *p_user = NULL;
    mux_status_t mux_res = MUX_STATUS_ERROR;

    LOG_INF("[race_core] race_close_port_for_all_user, port:%d", port);
    port_info = race_search_port(port);
    if (NULL == port_info) {
        return RACE_ERRCODE_SUCCESS;
    }
    if (RACE_PORT_INIT_SUC != port_info->port_status) {
        race_delete_port_info(port_info);
        return RACE_ERRCODE_SUCCESS;
    }

    p_user = port_info->user_list;
    while(p_user) {
        if (p_user->status == RACE_USER_ACTIVE) {
            mux_close(p_user->handle);
            res = race_delete_user(port_info, p_user);
            if (false == res) {
                return RACE_ERRCODE_FAIL;
            }
        }
        p_user = port_info->user_list;
    }
    if (NULL == port_info->user_list) {
        mux_res = mux_deinit(port);
        if (MUX_STATUS_OK == mux_res ||
            (MUX_STATUS_ERROR_SOME_USER_STILL_OPEN == mux_res && (RACE_PORT_FLAG_INITED_BY_OTHERS & port_info->port_flag))) {
            race_delete_port_info(port_info);
        }
    }
    return RACE_ERRCODE_SUCCESS;
}

void race_multi_buffer_init(race_mux_buffer_t *p_race_buf, mux_buffer_t buffers[], uint32_t buffers_counter)
{
    uint32_t i;

    if (NULL == p_race_buf) {
        return;
    }
    memset(p_race_buf, 0, sizeof(race_mux_buffer_t));
    p_race_buf->mux_buffer = buffers;
    p_race_buf->counter = buffers_counter;
    for (i = 0; i < buffers_counter; i++) {
        p_race_buf->left_data_len += buffers[i].buf_size;
    }
    p_race_buf->total_length = p_race_buf->left_data_len;
}

bool race_protocol_fetch(uint8_t *out_buf, uint32_t out_len, race_mux_buffer_t *p_race_buf)
{
    uint32_t i;

    if (NULL == p_race_buf || NULL == out_buf || 0 >= out_len) {
        return false;
    }

    if (p_race_buf->idx >= p_race_buf->counter) {
        return false;
    }

    if (p_race_buf->left_data_len < out_len) {
        return false;
    }

    for (i = 0; i < out_len; i++, p_race_buf->left_data_len--, p_race_buf->offset++) {
        if (p_race_buf->offset >= p_race_buf->mux_buffer[p_race_buf->idx].buf_size) {
            p_race_buf->idx++;
            p_race_buf->offset = 0;
            if (p_race_buf->idx >= p_race_buf->counter) {
                return false;
            }
        }
        *(out_buf + i) = *(p_race_buf->mux_buffer[p_race_buf->idx].p_buf + p_race_buf->offset);
    }
    return true;
}

bool race_protocol_fetch_header(RACE_COMMON_HDR_STRU *p_race_header, race_mux_buffer_t *p_race_buf)
{
    bool res = false;
    if (NULL == p_race_buf || NULL == p_race_header || NULL == p_race_buf->mux_buffer || 0 >= p_race_buf->counter) {
        return false;
    }

    if (p_race_buf->left_data_len < sizeof(RACE_COMMON_HDR_STRU)) {
        return false;
    }

    memset(p_race_header, 0, sizeof(RACE_COMMON_HDR_STRU));
    res = race_protocol_fetch(&p_race_header->pktId.value, 1, p_race_buf);
    if (false == res) {
        return false;
    }
    res = race_protocol_fetch(&p_race_header->type, 1, p_race_buf);
    if (false == res) {
        return false;
    }
    res = race_protocol_fetch((uint8_t *)&p_race_header->length, 2, p_race_buf);
    if (false == res) {
        return false;
    }
    res = race_protocol_fetch((uint8_t *)&p_race_header->id, 2, p_race_buf);
    return res;
}

void race_start_sleep_lock_timer(void)
{
#ifdef HAL_SLEEP_MANAGER_ENABLED
    k_timer_stop(&g_race_sleep_ctrl.sleep_lock_timer);
    k_timer_start(&g_race_sleep_ctrl.sleep_lock_timer, K_SECONDS(10), K_NO_WAIT);
#ifdef AIR_BTD_IC_MANDATORY_G1
    hal_sleep_manager_lock_sleep(SLEEP_LOCK_RACE_CMD);
#else
    if (hal_sleep_manager_is_sleep_handle_alive(g_race_sleep_ctrl.sleep_handle) == true) {
        hal_sleep_manager_unlock_sleep(g_race_sleep_ctrl.sleep_handle);
    }
    hal_sleep_manager_lock_sleep(g_race_sleep_ctrl.sleep_handle);
    LOG_INF("[race_core] race_start_sleep_lock_timer,handle:%x", g_race_sleep_ctrl.sleep_handle);
#endif
#endif
}

void race_core_init(void)
{
    int result = 0;
    result = race_queue_create(RACE_MSG_QUEUE_MAX_SIZE, sizeof(race_general_msg_t));
    //assert((0 != result) && "ERROR: [race_core] race_core_init fail !");
    // init msg handler table
    memset(&g_race_msg_hdl_tbl[0], 0, sizeof(g_race_msg_hdl_tbl));

    race_register_general_msg_hdl(MSG_ID_MUX_DATA_READY_TO_READ, race_handle_input_data);
    race_register_general_msg_hdl(MSG_ID_RACE_LOCAL_RSP_NOTIFY_IND, race_handle_ext_cmd);

    race_sleep_timer_init();
#if RACE_DEBUG_INFO_ENABLE
    race_idle_init();
#endif
}

void race_task(void *arg)
{
    race_general_msg_t race_msg = {0}; // [init] Always initialize variables before use

    LOG_INF("[race_core] race task start...");
    while (1) {
        int ret = race_queue_receive_wait(&race_queue, &race_msg, K_FOREVER);
        // [api check] Check API return value
        if (0 != ret) {
            LOG_ERR("[race_core] race_queue_receive_wait failed: %d", ret);
            continue;
        }
        LOG_INF("[race_core] race task, deal msg:%d", race_msg.msg_id);
        // [boundary check] Added check to prevent out-of-bounds access
        if ((race_msg.msg_id < MSG_ID_RACE_END) && (NULL != g_race_msg_hdl_tbl[race_msg.msg_id])) {
            g_race_msg_hdl_tbl[race_msg.msg_id](&race_msg);
        }
    }
}

#if KERNELVERSION == 0x3030000
static int race_task_create(const struct device *dev)
#elif KERNELVERSION >= 0x3070000
static int race_task_create(void)
#else
#error "Unkown supported kernel version"
#endif
{
    uint32_t mask;
    hal_nvic_save_and_set_interrupt_mask(&mask); // Save the current IRQ settings.
    race_init();
    k_thread_create(&race_thread_data, race_thread_stack,
            RACE_STACK_SIZE,
            (k_thread_entry_t)race_task, NULL, NULL, NULL,
            K_PRIO_PREEMPT(8), 0, K_NO_WAIT);

    k_thread_name_set(&race_thread_data, "race_cmd");
    hal_nvic_restore_interrupt_mask(mask);       // Restore the IRQ settings.
    return 0;
}

SYS_INIT(race_task_create, CONFIG_RACE_CMD_INIT_LEVEL, CONFIG_RACE_CMD_INIT_PRIORITY);

