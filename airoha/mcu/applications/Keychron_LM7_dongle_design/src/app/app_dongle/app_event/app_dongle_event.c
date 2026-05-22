
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

#include "app_dongle_event.h"

#include <errno.h>
#include <zephyr/logging/log.h>
#include <zephyr/kernel.h>
#include "app_debug.h"
#include "af_framework.h"
#include "af_events_declaration.h"

#include "app_porting.h"



/**================================================================================*/
/**                              Definition & Structure                            */
/**================================================================================*/
#define LOG_TAG             "[APP_DONGLE][EVENT]"

#define thisMODULE          dongle

#define APP_DONGLE_EVENT_MAX_DELAY_EVENTS       20

typedef struct {
    uint16_t                                    event_group;
    uint16_t                                    event_id;
    void                                       *msg_id;
    void                                       *event;
} app_dongle_event_delay_timer_list_t;

static volatile app_dongle_event_delay_timer_list_t app_dongle_event_delay_timer_list[APP_DONGLE_EVENT_MAX_DELAY_EVENTS] = {0};


extern bool app_dongle_cm_le_scanner_event_handler(uint8_t event_group, uint16_t event_id, void *data, uint32_t data_len);
extern bool app_dongle_cm_event_handler(uint8_t event_group, uint16_t event_id, void *data, uint32_t data_len);
extern bool app_hogp_client_event_handler(uint8_t event_group, uint16_t event_id, void *data, uint32_t data_len);
extern bool app_usb_mgr_event_handler(uint8_t event_group, uint16_t event_id, void *data, uint32_t data_len);

const app_dongle_event_handle_func_t app_dongle_event_handler_list[] = {
    app_dongle_cm_event_handler,
    app_dongle_cm_le_scanner_event_handler,
    app_hogp_client_event_handler,
    app_usb_mgr_event_handler,
};




/**================================================================================*/
/**                                  Internal API                                  */
/**================================================================================*/
static bool app_dongle_event_handler(const struct af_evt_header *evt_header)
{
    struct app_dongle_event_t *event = (struct app_dongle_event_t *)evt_header;
    bool ret = FALSE;

    if (event->event_group == APP_DONGLE_EVENT_GROUP_SYSTEM && event->event_id == APP_DONGLE_EVENT_SYSTEM_INIT) {
        extern void app_dongle_init(void);
        app_dongle_init();
    }

    APPS_LOG_MSGID_I(LOG_TAG" event_handler start, group=%d id=%d data=0x%08X data_len=%d",
                     4, event->event_group, event->event_id, event->data, event->data_len);
    for (int i = 0; i < sizeof(app_dongle_event_handler_list) / sizeof(app_dongle_event_handle_func_t); i++) {
        ret = app_dongle_event_handler_list[i](event->event_group, event->event_id, event->data, event->data_len);
        if (ret && !(event->event_group == APP_DONGLE_EVENT_GROUP_SYSTEM && event->event_id == APP_DONGLE_EVENT_SYSTEM_INIT)) {
            break;
        }
    }
    APPS_LOG_MSGID_I(LOG_TAG" event_handler end, group=%d id=%d data=0x%08X data_len=%d",
                     4, event->event_group, event->event_id, event->data, event->data_len);

    if (event->data != NULL && event->data_len > 0) {
        app_porting_free(event->data);
    }
    for (int i = 0; i < APP_DONGLE_EVENT_MAX_DELAY_EVENTS; i++) {
        if (app_dongle_event_delay_timer_list[i].event == event) {
            app_dongle_event_delay_timer_list[i].event_group = 0;
            app_dongle_event_delay_timer_list[i].event_id = 0;
            app_dongle_event_delay_timer_list[i].event = NULL;
            app_dongle_event_delay_timer_list[i].msg_id = NULL;
            break;
        }
    }

    return AF_TRAVERSE_TERMINATED;
}

static bool app_dongle_event_send_event_func(uint16_t event_group, uint16_t event_id, void *data, uint32_t data_len, uint32_t delay_ms)
{
    struct app_dongle_event_t *event = (struct app_dongle_event_t *)create_app_dongle_event_t();
    event->event_group = event_group;
    event->event_id = event_id;
    event->data = data;
    event->data_len = data_len;

    APPS_LOG_MSGID_I(LOG_TAG" send_event, group=%d id=%d data=0x%08X data_len=%d delay_ms=%d",
                     5, event_group, event_id, data, data_len, delay_ms);
    if (delay_ms == 0) {
        AF_EVT_SUBMIT(event);
    } else {
        int i = 0;
        for (i = 0; i < APP_DONGLE_EVENT_MAX_DELAY_EVENTS; i++) {
            if (app_dongle_event_delay_timer_list[i].msg_id == NULL) {
                app_dongle_event_delay_timer_list[i].event = event;
                app_dongle_event_delay_timer_list[i].event_group = event_group;
                app_dongle_event_delay_timer_list[i].event_id = event_id;
                app_dongle_event_delay_timer_list[i].msg_id = AF_DELAYABLE_EVT_SUBMIT(event, K_MSEC(delay_ms));
                break;
            }
        }
        if (i == APP_DONGLE_EVENT_MAX_DELAY_EVENTS) {
            app_porting_free(event);
            APPS_LOG_MSGID_E(LOG_TAG" send_event, not empty delay_msg", 0);
        }
    }
    return TRUE;
}



/**================================================================================*/
/**                                     Public API                                 */
/**================================================================================*/
void app_dongle_event_init(void)
{
    app_dongle_event_send_event(APP_DONGLE_EVENT_GROUP_SYSTEM, APP_DONGLE_EVENT_SYSTEM_INIT);
}

bool app_dongle_event_send_event(uint16_t event_group, uint16_t event_id)
{
    return app_dongle_event_send_event_func(event_group, event_id, NULL, 0, 0);
}

bool app_dongle_event_send_event_data(uint16_t event_group, uint16_t event_id, void *data, uint32_t data_len)
{
    return app_dongle_event_send_event_func(event_group, event_id, data, data_len, 0);
}

bool app_dongle_event_send_delay_event(uint16_t event_group, uint16_t event_id, void *data, uint32_t data_len, uint32_t delay_ms)
{
    return app_dongle_event_send_event_func(event_group, event_id, data, data_len, delay_ms);
}

bool app_dongle_event_remove_event(uint16_t event_group, uint16_t event_id)
{
    APPS_LOG_MSGID_I(LOG_TAG" remove_event, group=%d, id=%d", 2, event_group, event_id);
    for (int i = 0; i < APP_DONGLE_EVENT_MAX_DELAY_EVENTS; i++) {
        if (app_dongle_event_delay_timer_list[i].msg_id != NULL
            && app_dongle_event_delay_timer_list[i].event_group == event_group && app_dongle_event_delay_timer_list[i].event_id == event_id) {
            if (app_dongle_event_delay_timer_list[i].event != NULL) {
                struct app_dongle_event_t *event = (struct app_dongle_event_t *)app_dongle_event_delay_timer_list[i].event;
                if (event->data != NULL && event->data_len > 0) {
                    app_porting_free(event->data);
                }
                app_dongle_event_delay_timer_list[i].event = NULL;
            }
            AF_DELAYABLE_EVT_CANCEL(app_dongle_event_delay_timer_list[i].msg_id);
            app_dongle_event_delay_timer_list[i].msg_id = NULL;
            app_dongle_event_delay_timer_list[i].event_group = 0;
            app_dongle_event_delay_timer_list[i].event_id = 0;
        }
    }
    return 0;
}


/*============================Application Framework============================*/
AF_EVT_SUBSCRIBE_FUN(thisMODULE, app_dongle_event_t, app_dongle_event_handler);
AF_EVT_DECLARE(app_dongle_event_t);
/*=============================================================================*/