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

#if defined(AIR_PURE_GAMING_DONGLE_ENABLE)

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <errno.h>
#include <string.h>
#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/hci.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/flash.h>
#include <zephyr/logging/log.h>
#include <zephyr/kernel.h>
#include <zephyr/devicetree.h>
#include <zephyr/device.h>
#include "app_debug.h"
#include "af_framework.h"
#include "af_events_declaration.h"
#include "app_state.h"
#include "hid_scenario_dongle.h"
#include "app_bt_conn_manager.h"
#include "app_acl_conn.h"
#include "app_bt_ull_conn.h"
#include "assert.h"
#include "app_events_deinit_stage.h"
#include "app_events_init_stage.h"
#include "app_events_disconnected_stage.h"
#include "app_events_scan_stage.h"
#include "app_events_pairing_stage.h"
#include "app_events_reconnect_stage.h"
#include "app_events_connected_stage.h"
#include "app_events_running_stage.h"
#include "app_events_suspend_stage.h"

/* Private define ------------------------------------------------------------*/
#define thisMODULE app_events
#define thisMOD    "app_events"
LOG_MODULE_REGISTER(thisMODULE);

/* Private typedef -----------------------------------------------------------*/
typedef int (*stage_events_hdl_callback)(struct evt_cmd *event);

typedef struct {
    void *fifo_reserved;
    struct evt_cmd event;
} app_events_pending_cmd_t;

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static const stage_events_hdl_callback stage_events_hdl_table[] =
{
    app_events_deinit_stage_hdl,// APP_STATE_DEINIT,
    app_events_init_stage_hdl,// APP_STATE_INIT,
    app_events_disconnected_stage_hdl,// APP_STATE_DISCONNECTED,
    app_events_scan_stage_hdl,// APP_STATE_SCAN,
    app_events_pairing_stage_hdl,// APP_STATE_PAIRING,
    app_events_reconnect_stage_hdl,// APP_STATE_RECONNECT,
    app_events_connected_stage_hdl,// APP_STATE_CONNECTED,
    app_events_running_stage_hdl,// APP_STATE_RUNNING,
    app_events_suspend_stage_hdl,// APP_STATE_SUSPEND,
    NULL,// APP_STATE_END
};

static volatile bool app_events_is_suspend = false;
static uint32_t app_events_prohibited_flag[256/32];
struct k_fifo app_events_pending_fifo;

/* Public variables ----------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
static int app_events_process(struct evt_cmd* event)
{
    int ret = 0;
    APP_STATES current_state = app_state_get_current();

    LOG_INF("app_events_process, state = %u, cmd = %u \n ", current_state, event->cmd);

    if (current_state >= APP_STATE_END)
    {
        assert(0);
    }

    if (stage_events_hdl_table[current_state] != NULL)
    {
        ret = stage_events_hdl_table[current_state](event);
        if (ret != 0)
        {
            assert(0);
        }
    }
    else
    {
        LOG_INF("app_events_process(%u) callback is NULL \n ", current_state);
    }

    return ret;
}

static bool app_events_hdl(const struct af_evt_header *evt_header)
{
    struct evt_cmd* event;
    int ret;
    app_events_pending_cmd_t *pending_cmd = NULL;
    uint32_t bit_offset;
    uint32_t word_offset;

    if (!app_events_is_suspend)
    {
        /* process pending events first */
        pending_cmd = k_fifo_get(&app_events_pending_fifo, K_NO_WAIT);
        while (pending_cmd != NULL)
        {
            event = &pending_cmd->event;
            LOG_INF("app_events_hdl process pending 1 cmd %u 0x%x", event->cmd, pending_cmd);
            ret = app_events_process(event);
            k_free(pending_cmd);
            if (app_events_is_suspend)
            {
                break;
            }
            pending_cmd = k_fifo_get(&app_events_pending_fifo, K_NO_WAIT);
        }
    }

    event = (struct evt_cmd*)evt_header;
    if (app_events_is_suspend)
    {
        bit_offset = event->cmd % 32;
        word_offset = event->cmd / 32;
        if ((app_events_prohibited_flag[word_offset] & (1 << bit_offset)) != 0)
        {
            /* this event is not allowed to process at now */
            pending_cmd = k_malloc(sizeof(app_events_pending_cmd_t));
            assert(pending_cmd != NULL);
            memcpy(&pending_cmd->event, event, sizeof(struct evt_cmd));
            k_fifo_put(&app_events_pending_fifo, pending_cmd);
            LOG_INF("app_events_hdl add pending cmd %u 0x%x", event->cmd, pending_cmd);
        }
        else
        {
            /* specical case: alougth in suspend case, this event is allowed to process at now */
            LOG_INF("app_events_hdl process special cmd %u 0x%x", event->cmd, pending_cmd);
            ret = app_events_process(event);
        }
    }
    else
    {
        /* normal case: this event is allowed to process at now */
        LOG_INF("app_events_hdl process normal cmd %u 0x%x", event->cmd, pending_cmd);
        ret = app_events_process(event);
    }

    if (!app_events_is_suspend)
    {
        /* process pending events again */
        pending_cmd = k_fifo_get(&app_events_pending_fifo, K_NO_WAIT);
        while (pending_cmd != NULL)
        {
            event = &pending_cmd->event;
            LOG_INF("app_events_hdl process pending 2 cmd %u 0x%x", event->cmd, pending_cmd);
            ret = app_events_process(event);
            k_free(pending_cmd);
            if (app_events_is_suspend)
            {
                break;
            }
            pending_cmd = k_fifo_get(&app_events_pending_fifo, K_NO_WAIT);
        }
    }

    return AF_TRAVERSE_NEXT;
}

/* Public functions ----------------------------------------------------------*/
int app_events_suspend_all_events(void)
{
    int ret = 0;

    memset(app_events_prohibited_flag, 0xff, sizeof(app_events_prohibited_flag));
    app_events_is_suspend = true;

    LOG_INF("app_events_suspend_all_events");

    return ret;
}

int app_events_resume_all_events(void)
{
    int ret = 0;

    memset(app_events_prohibited_flag, 0x0, sizeof(app_events_prohibited_flag));
    app_events_is_suspend = false;

    LOG_INF("app_events_resume_all_events");

    return ret;
}

int app_events_allow_special_event(uint8_t evt)
{
    int ret = 0;
    uint32_t bit_offset = evt % 32;
    uint32_t word_offset = evt / 32;

    app_events_prohibited_flag[word_offset] &= ~(0x1<<bit_offset);

    LOG_INF("app_events_allow_special_event %u", evt);

    return ret;
}

int app_events_allow_special_event_range(uint8_t start_evt, uint8_t end_evt)
{
    int ret = 0;
    uint32_t bit_offset;
    uint32_t word_offset;
    uint8_t i;

    for(i=start_evt; i<=end_evt; i++)
    {
        bit_offset = i % 32;
        word_offset = i / 32;
        app_events_prohibited_flag[word_offset] &= ~(0x1<<bit_offset);
    }

    LOG_INF("app_events_allow_special_event_range %u-%u", start_evt, end_evt);

    return ret;
}

void app_events_send(uint8_t evt, void *param)
{
    struct evt_cmd* event = create_evt_cmd();
    if (event){
        event->cmd = evt;
        event->param = param;
        AF_EVT_SUBMIT(event);
    }
}

void app_events_init(void)
{
    k_fifo_init(&app_events_pending_fifo);
}

AF_EVT_SUBSCRIBE_FUN(thisMODULE, evt_cmd, app_events_hdl);

#endif /* AIR_PURE_GAMING_DONGLE_ENABLE */
